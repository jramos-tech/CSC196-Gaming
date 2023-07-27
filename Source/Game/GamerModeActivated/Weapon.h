#pragma once
#include "Framework/Actor.h"

class Weapon : public Sc::Actor {
public:

	Weapon(float speed, const T::Transform& transform, std::shared_ptr<Sc::Model> model) :
		Actor{ transform, model },
		m_speed{ speed }
	{
		m_lifespan = 2.0f;
	}
	void Update(float dt) override;
	void OnCollision(Actor* other) override;

private:
	float m_speed = 0;
};
