#include "Weapon.h"

void Weapon::Update(float dt){
	Actor::Update(dt);
	V::vec2 forward = V::vec2{ 0, -1 }.Rotate(m_transform.rotation);
	m_transform.position += forward * m_speed * 1 * kiko::g_time.getDeltaTime();
	m_transform.position.x = MaUt::Wrap(m_transform.position.x, (float)Sc::g_render.GetWidth());
	m_transform.position.y = MaUt::Wrap(m_transform.position.y, (float)Sc::g_render.GetHeight());
}

void Weapon::OnCollision(Actor* other){
	if (other->m_tag != m_tag) {
		m_destroyed = true;
	}
}
