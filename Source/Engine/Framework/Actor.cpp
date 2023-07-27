#include "Actor.h"

namespace Sc {
	void Actor::Update(float dt){
		if (m_lifespan != -1.0f) {
			m_lifespan -= dt;
			if (m_lifespan <= 0) {
				m_destroyed = true;
			}
		}
		m_transform.position += m_velocity * dt;
		m_velocity *= std::pow(1.0f - m_damping, dt);
	}
	void Actor::Draw(Sc::Render& render) {
		m_model->Draw(render, m_transform);
	}
}
