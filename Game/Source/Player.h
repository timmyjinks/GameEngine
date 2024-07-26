#pragma once
#include "Actor.h"
#include "Weapon.h"

#include <memory>

class Weapon;

class Player : public Actor {
public:
	enum class WeaponClass : char {
		BULLET,
		MISSLE
	};

	Player() = default;
	Player(const Transform& transform) : Actor{ transform } {}
	Player(const Transform& transform, Model* model) : Actor{ transform, model } {}
	Player(float speed, const Transform& transform, Model* model) :
		Actor{ transform, model },
		m_speed{ speed }
	{}

	void Update(float deltaTime);
	virtual void OnCollision(Actor* actor);

	void SetFireModifier(float fireModifier) { m_fireModifier = fireModifier; m_modifierTimer = 5; };

private:
	float m_speed{ 1 };
	float m_fireTimer{ 1 };
	float m_fireModifier{ 1 };
	float m_modifierTimer{ 0 };
	WeaponClass m_weapon{ WeaponClass::BULLET };
	bool hasBulletClass{ true };
	bool hasMissleClass{ false };
};
