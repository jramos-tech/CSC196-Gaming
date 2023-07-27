#pragma once
#include "Renderer.h"
#include "Particle.h"
#include <vector>
namespace Sc {
	class ParticleSystem
	{
	public:
		ParticleSystem() = default;
		ParticleSystem(int maxCount)
		{
			m_particles.resize(maxCount);
		}
		void Update(float dt);
		void Draw(Render& renderer);
		Particle* GetFreeParticle();

	private:
		std::vector<Particle> m_particles;
	};
	extern ParticleSystem g_particleSystem;
}