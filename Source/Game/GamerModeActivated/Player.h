#pragma once
#include "Framework/Actor.h"

class Player : public Sc::Actor {
public:

	Player(float speed, float turnRate, float health, const T::Transform& transform, std::shared_ptr<Sc::Model> model):
		Actor{ transform, model },
		m_speed{speed},
		m_turnRate{turnRate},
		m_health{health}
	{
		m_fireRate = 2.0f;
	}
	void Update(float dt) override;
	void OnCollision(Actor* other) override;

private:
	float m_speed = 0;
	float m_turnRate = 0;
	float m_health = 100.0f;
	float m_fireRate = 0;
	float m_fireCooldown = 1.0f;
};
