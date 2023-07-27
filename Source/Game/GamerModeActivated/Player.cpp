#include "Player.h"
#include "Input/InputSystem.h"
#include "Weapon.h"
#include "Render/Renderer.h"
#include "Framework/Scene.h"
#include "Audio/AudioSystem.h"
#include "SpaceWars.h"
#include "Framework/Emiter.h"

void Player::Update(float dt) {
	Actor::Update(dt);
	//movement
	float rotate = 0;
	if (I::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
	if (I::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
	m_transform.rotation += rotate * m_turnRate * kiko::g_time.getDeltaTime();
	float thrust = 0;
	if (I::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;
	V::vec2 forward = V::vec2{ 0, -1 }.Rotate(m_transform.rotation);
	AddForce(forward * m_speed * thrust);
	//m_transform.position += forward * m_speed * thrust * kiko::g_time.getDeltaTime();
	m_transform.position.x = MaUt::Wrap(m_transform.position.x, (float)Sc::g_render.GetWidth());
	m_transform.position.y = MaUt::Wrap(m_transform.position.y, (float)Sc::g_render.GetHeight());
	//fire weapon
	if (I::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE) &&
		!I::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_F)) {
		//create weapon
		if(m_fireCooldown <= 0) {
			m_fireCooldown = 1.0f;
			T::Transform transform1{ m_transform.position, m_transform.rotation + MaUt::DegreesToRadians(10.0f), 1};
			std::unique_ptr<Weapon> weapon1 = std::make_unique<Weapon>(500, transform1, m_model);
			weapon1->m_tag = "Player";
			m_Scene->Add(std::move(weapon1));
			Audi::g_audioSystem.PlayOneShot("laser");

			/*T::Transform transform2{ m_transform.position, m_transform.rotation - MaUt::DegreesToRadians(10.0f), 1};
			std::unique_ptr<Weapon> weapon2 = std::make_unique<Weapon>(500, transform2, m_model);
			weapon2->m_tag = "Player";
			m_Scene->Add(std::move(weapon2));
			Audi::g_audioSystem.PlayOneShot("laser");*/
		}
		if (I::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE)) kiko::g_time.SetTimeScale(0.5f);
		else kiko::g_time.SetTimeScale(1.0f);
	}
	m_fireCooldown -= dt;
}


	void Player::OnCollision(Actor* other){
		if (other->m_tag == "Enemy") {
			m_health -= 10.0f;
			Audi::g_audioSystem.PlayOneShot("hit");
			if (m_health <= 0) {
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
				m_game->SetLives(m_game->GetLives() - 1);
				dynamic_cast<SpaceWars*>(m_game)->SetState(SpaceWars::PlayerDeadStart);
				Audi::g_audioSystem.PlayOneShot("ship");
				m_destroyed = true;
			}
		}
	}
