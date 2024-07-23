#include "Player.h"
#include "Engine.h"
#include "Bullet.h"
#include "Scene.h"
#include "FNAFGame.h"

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

	Vector2 acceleration = Vector2{ 1.0f, 0.0f }.Rotate(m_transform.rotation) * m_speed;
	m_velocity += acceleration * deltaTime;

	m_transform.position.x = Math::Wrap(m_transform.position.x, (float)g_engine.GetRenderer().GetWidth());
	m_transform.position.y = Math::Wrap(m_transform.position.y, (float)g_engine.GetRenderer().GetHeight());

	//fire 
	m_fireTimer -= deltaTime;
	if (g_engine.GetInput().GetMouseButtonDown(0) && m_fireTimer <= 0) {
		Vector2 direction = g_engine.GetInput().GetMousePosition() - m_transform.position;
		float angle = direction.Angle();

		m_fireTimer = 0.3f * m_fireModifier;
		std::vector<Vector2> points;
		points.push_back(Vector2{ 5, 0 });
		points.push_back(Vector2{ -5, -5 });
		points.push_back(Vector2{ -5, 5 });
		points.push_back(Vector2{ 5, 0 });

		// actor
		Model* model = new Model{ points, Color{ 1, 1, 0 } };
		Transform transform{ m_transform.position, angle, 1.0f };

		auto bullet = std::make_unique<Bullet>(400.0f, transform, model);
		bullet->SetLifespan(2);
		bullet->SetTag("Player");
		m_scene->AddActor(std::move(bullet));
	}

	Actor::Update(deltaTime);
}

void Player::OnCollision(Actor* actor)
{
	/*if (actor->GetTag() == "Enemy") {
		m_destroyed = true;
	}*/
}
