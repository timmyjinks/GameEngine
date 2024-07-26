#pragma once
#include "Weapon.h"

class Missle : public Weapon {
public:
	Missle() = default;
	Missle(const Transform& transform) : Weapon{ transform } {}
	Missle(const Transform& transform, Model* model) : Weapon{ transform, model } {}
	Missle(float speed, const Transform& transform, Model* model) :
		Weapon{ transform, model },
		m_speed{ speed }
	{}

	void Update(float deltaTime);
	virtual void OnCollision(Actor* actor);

private:
	float m_speed{ 0 };
};
