#pragma once
#include "Actor.h"

class Player : public Actor {
public:
	Player() = default;
	Player(const Transform& transform) : Actor{ transform } {}
	Player(const Transform& transform, Model* model) : Actor{ transform, model } {}
	Player(float speed, const Transform& transform, Model* model) :
		Actor{ transform, model },
		m_speed{ speed }
	{}

	void Update(float deltaTime);
	virtual void OnCollision(Actor* actor);

	void SetFireModifier(float fireModifier) { m_fireModifier = fireModifier; };

private:
	float m_speed{ 0 };
	float m_fireTimer{ 0 };
	float m_fireModifier{ 0 };
};
