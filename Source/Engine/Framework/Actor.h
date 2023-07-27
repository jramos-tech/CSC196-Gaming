#pragma once
#include "Core/Core.h"
#include "Render/Model.h"
#include <memory>
namespace Sc {
	class Actor {
	public:
		Actor() = default;
		Actor(const T::Transform& transform, std::shared_ptr<Model> model) :
			m_transform{ transform },
			m_model{ model }
		{ }
		Actor(const T::Transform& transform) :
			m_transform{ transform }
		{}
		virtual void Update(float dt);
		virtual void Draw(Render& render);
		float GetRadius() { return (m_model) ? m_model->GetRadius() * m_transform.scale : -10000; }
		virtual void OnCollision(Actor* other){}
		void AddForce(const V::vec2& force) { m_velocity += force; }
		void SetDamping(float damping) { m_damping = damping; }
		class Scene* m_Scene = nullptr;
		friend class Scene;
		class Game* m_game = nullptr;
		T::Transform m_transform;
		std::string m_tag;
		float m_lifespan = -1.0f;
	protected:
		bool m_destroyed = false;
		std::shared_ptr<Model> m_model;

		V::vec2 m_velocity;
		float m_damping = 0;
	};
}
