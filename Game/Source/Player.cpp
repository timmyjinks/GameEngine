#include "Player.h"
#include "Engine.h"
#include "Bullet.h"
#include "Scene.h"
#include "FNAFGame.h"
#include "GameData.h"

#include <memory>

void Player::Update(float deltaTime)
{
	//movement
	Vector2 direction{ 0, 0 };
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_W)) direction.x = 1;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_S)) direction.x = -1;

	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_Q)) direction.y = -1;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_E)) direction.y = 1;

	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_A)) m_transform.rotation -= Math::DegToRad(180) * deltaTime;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_D)) m_transform.rotation += Math::DegToRad(180) * deltaTime;

	Vector2 acceleration = direction.Rotate(m_transform.rotation) * m_speed;
	m_velocity += acceleration * deltaTime;

	m_transform.position.x = Math::Wrap(m_transform.position.x, (float)g_engine.GetRenderer().GetWidth());
	m_transform.position.y = Math::Wrap(m_transform.position.y, (float)g_engine.GetRenderer().GetHeight());

	//fire	
	m_fireTimer -= deltaTime;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_SPACE) && m_fireTimer <= 0 && g_engine.GetInput().GetPreviousKeyDown(SDL_SCANCODE_SPACE)) {
		m_fireTimer = 0.1f * m_fireModifier;

		// actor
		Model* model = new Model{ GameData::bulletPoints, Color{ 1, 1, 0 } };
		Transform transform{ m_transform.position, m_transform.rotation, 1.0f };

		auto bullet = std::make_unique<Bullet>(400.0f, transform, model);
		bullet->SetLifespan(1);
		bullet->SetTag("PlayerBullet");
		m_scene->AddActor(std::move(bullet));
	}

	m_modifierTimer -= deltaTime;
	if (m_modifierTimer <= 0) {
		m_fireModifier = 1;
	}

	Actor::Update(deltaTime);
}

void Player::OnCollision(Actor* actor)
{
	if (actor->GetTag() == "Enemy") {
		if (!m_destroyed) {
			FNAFGame* game = dynamic_cast<FNAFGame*>(m_scene->GetGame());
			game->OnPlayerDeath();
			m_destroyed = true;
		}
	}
}
