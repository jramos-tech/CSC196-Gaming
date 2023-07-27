#include "Enemy.h"
#include "Player.h"
#include "Weapon.h"
#include "Input/InputSystem.h"
#include "Render/Renderer.h"
#include "Framework/Scene.h"
#include "Audio/AudioSystem.h"
#include "SpaceWars.h"
#include "Framework/Emiter.h"

void Enemy::Update(float dt) {
	Actor::Update(dt);
	V::vec2 forward = V::vec2{ 0,-1 }.Rotate(m_transform.rotation);
	Player* player = m_Scene->GetActor<Player>();
	if (player) {
		V::Vector2 direction = player->m_transform.position - m_transform.position;
		float turnAngle = V::vec2::SignedAngle(forward, direction.Normalized());
		m_transform.rotation += turnAngle * dt; ;
		if (std::fabs(turnAngle) < MaUt::DegreesToRadians(30.0f)) {

		}
	}
	m_transform.position += forward * m_speed * 1 * kiko::g_time.getDeltaTime();
	m_transform.position.x = MaUt::Wrap(m_transform.position.x, (float)Sc::g_render.GetWidth());
	m_transform.position.y = MaUt::Wrap(m_transform.position.y, (float)Sc::g_render.GetHeight());
	m_fireTimer -= dt;
	if (m_fireTimer <= 0) {
		m_fireTimer = m_fireRate;
		T::Transform transform{ m_transform.position, m_transform.rotation, 1};
		std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(500, transform, m_model);
		weapon->m_tag = "Enemy";
		m_Scene->Add(std::move(weapon));
		Audi::g_audioSystem.PlayOneShot("laser");
	}
}

void Enemy::OnCollision(Actor* other){
	if (other->m_tag == "Player") {
		m_game->AddPoints(100);
		Sc::EmitterData data;
		data.burst = true;
		data.burstCount = 100;
		data.spawnRate = 200;
		data.angle = 0;
		data.angleRange = MaUt::Pi;
		data.lifetimeMin = 0.5f;
		data.lifetimeMax = 1.5f;
		data.speedMin = 50;
		data.speedMax = 250;
		data.damping = 0.5f;
		data.color = Sc::Color{ 1, 1, 1, 1 };
		T::Transform transform{ { m_transform.position }, 0, 1 };
		auto emitter = std::make_unique<Sc::Emitter>(transform, data);
		emitter->m_lifespan = 1.0f;
		m_Scene->Add(std::move(emitter));
		m_destroyed = true;
	}
}
