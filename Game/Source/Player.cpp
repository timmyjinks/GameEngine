#include "Player.h"
#include "Engine.h"
#include "Missle.h"
#include "Bullet.h"
#include "Scene.h"
#include "FNAFGame.h"
#include "GameData.h"

void Player::Update(float deltaTime)
{
	//movement
	Vector2 direction{ 0, 0 };
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_W)) direction.x = 1;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_S)) direction.x = -1;

	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_A)) m_transform.rotation -= Math::DegToRad(180) * deltaTime;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_D)) m_transform.rotation += Math::DegToRad(180) * deltaTime;

	Vector2 acceleration = direction.Rotate(m_transform.rotation) * m_speed;
	m_velocity += acceleration * deltaTime;

	m_transform.position.x = Math::Wrap(m_transform.position.x, (float)g_engine.GetRenderer().GetWidth());
	m_transform.position.y = Math::Wrap(m_transform.position.y, (float)g_engine.GetRenderer().GetHeight());

	// switch weapon
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_Q) && g_engine.GetInput().GetPreviousKeyDown(SDL_SCANCODE_Q)) {
		m_weapon = WeaponClass::BULLET;
	}
	else if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_E) && g_engine.GetInput().GetPreviousKeyDown(SDL_SCANCODE_E)) {
		if (hasMissleClass) {
			m_weapon = WeaponClass::MISSLE;
		}
	}

	//fire	
	m_fireTimer -= deltaTime;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_SPACE) && m_fireTimer <= 0 && g_engine.GetInput().GetPreviousKeyDown(SDL_SCANCODE_SPACE)) {
		// audio
		g_engine.GetAudio().PlaySound("shoot.mp3");

		// actor
		Model* model = new Model{ GameData::bulletPoints, Color{ 1, 1, 0 } };
		Transform transform{ m_transform.position, m_transform.rotation, 1.0f };

		std::unique_ptr<Weapon> weapon;
		switch (m_weapon)
		{
		case Player::WeaponClass::BULLET:
			m_fireTimer = 0.2f * m_fireModifier;
			weapon = std::make_unique<Bullet>(400.0f, transform, model);
			break;
		case Player::WeaponClass::MISSLE:
			m_fireTimer = 5;
			weapon = std::make_unique<Missle>(200.0f, transform, model);
			break;
		}
		weapon->SetLifespan(3);
		weapon->SetTag("PlayerBullet");
		m_scene->AddActor(std::move(weapon));
	}

	m_modifierTimer -= deltaTime;
	if (m_modifierTimer <= 0) {
		m_fireModifier = 1;
	}

	Actor::Update(deltaTime);
}

void Player::OnCollision(Actor* actor)
{
	if (actor->GetTag() == "MisslePickup") {
		hasMissleClass = true;
	}
	if (actor->GetTag() == "FireModifierPickup") {
		m_fireTimer = 0;
		m_fireModifier = 0.5;
		m_modifierTimer = 5;
	}
	if (actor->GetTag() == "Enemy") {
		g_engine.GetAudio().PlaySound("explosion.mp3");
		if (!m_destroyed) {
			FNAFGame* game = dynamic_cast<FNAFGame*>(m_scene->GetGame());
			for (int i = 0; i < 10000; i++) {
				Particle::Data data{
					m_transform.position,
					Vector2{ randomOnUnitCircle() * randomf(0, 500)},
					3,
					255, randomf(80, 200), 0, 255
				};

				g_engine.GetParticleSystem().AddParticle(data);
			}
			game->OnPlayerDeath();
			m_destroyed = true;
		}
	}
}