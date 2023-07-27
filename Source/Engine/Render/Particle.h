#pragma once
#include "Core/Core.h"
#include "Render/Renderer.h"
namespace Sc {
	struct ParticleData
	{
		V::vec2 position;
		V::vec2 prevPosition;
		V::vec2 velocity;
		float damping = 0;
		Sc::Color color;
		float lifeTimer = 0;
		float lifetime = 0;
	};
	class Particle
	{
	public:
		Particle() = default;
		void Initialize(const ParticleData& data)
		{
			m_data = data;
			m_isActive = true;
		}
		void Update(float dt);
		void Draw(Sc::Render& renderer);
		friend class ParticleSystem;
	private:
		ParticleData m_data;
		bool m_isActive = false;
	};
}
