#pragma once
#include "Actor.h"

class Weapon : public Actor {
public:
	Weapon() = default;
	Weapon(const Transform& transform) : Actor{ transform } {}
	Weapon(const Transform& transform, Model* model) : Actor{ transform, model } {}
	Weapon(float speed, const Transform& transform, Model* model) :
		Actor{ transform, model },
		m_speed{ speed }
	{}

	virtual void Update(float deltaTime) = 0;
	virtual void OnCollision(Actor* actor) = 0;

protected:
	float m_speed{ 0 };
	float m_trailTimer{ 0 };
};
