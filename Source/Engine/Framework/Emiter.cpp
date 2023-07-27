#include "Emiter.h"
#include "Render/ParticleSystem.h"
namespace Sc {
	void Emitter::Update(float dt) {
		Actor::Update(dt);
		if (m_data.burst)
		{
			m_data.burst = false;
			for (int i = 0; i < m_data.burstCount; i++)
			{
				Emit();
			}
		}
		if (m_data.spawnRate > 0.0f)
		{
			m_data.spawnRateTimer += dt;
			while (m_data.spawnRateTimer > 0)
			{
				Emit();
				m_data.spawnRateTimer -= (1 / m_data.spawnRate);
			}
		}

	}
	void Emitter::Draw(Sc::Render& renderer) {

	}
	void Emitter::Emit()
	{
		Particle* particle = g_particleSystem.GetFreeParticle();
		if (particle)
		{
			ParticleData data;
			data.lifetime = R::randomf(m_data.lifetimeMin, m_data.lifetimeMax);
			data.lifeTimer = 0.0f;
			data.position = m_transform.position;
			data.prevPosition = data.position;
			data.color = m_data.color;
			float angle = m_transform.rotation + m_data.angle + R::randomf(-m_data.angleRange, m_data.angleRange);
			V::vec2 direction = V::vec2{ 0, -1 }.Rotate(angle);
			data.velocity = direction * R::randomf(m_data.speedMin, m_data.speedMax);
			data.damping = m_data.damping;
			particle->Initialize(data);
		}
	}
}