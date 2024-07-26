#pragma once
#include "Weapon.h"

class Bullet : public Weapon {
public:
	Bullet() = default;
	Bullet(const Transform& transform) : Weapon{ transform } {}
	Bullet(const Transform& transform, Model* model) : Weapon{ transform, model } {}
	Bullet(float speed, const Transform& transform, Model* model) :
		Weapon{ speed, transform, model }
	{}

	void Update(float deltaTime);
	virtual void OnCollision(Actor* actor);
};
