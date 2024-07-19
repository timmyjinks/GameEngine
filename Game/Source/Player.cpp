#include "Player.h"
#include "Engine.h"
#include "Bullet.h"
#include "Scene.h"

void Player::Update(float deltaTime)
{
	//movement
	float thrust = 0;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_UP)) thrust = m_speed;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_DOWN)) thrust = -m_speed;

	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_LEFT)) m_transform.rotation -= Math::DegToRad(100) * deltaTime;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_RIGHT)) m_transform.rotation += Math::DegToRad(100) * deltaTime;

	Vector2 acceleration = Vector2{ 1.0f, 0.0f }.Rotate(m_transform.rotation) * thrust;
	m_velocity += acceleration * deltaTime;

	m_transform.position.x = Math::Wrap(m_transform.position.x, (float)g_engine.GetRenderer().GetWidth());
	m_transform.position.y = Math::Wrap(m_transform.position.y, (float)g_engine.GetRenderer().GetHeight());

	//fire 
	m_fireTimer -= deltaTime;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_SPACE) && m_fireTimer <= 0) {
		m_fireTimer = 1;
		std::vector<Vector2> points;
		points.push_back(Vector2{ 5, 0 });
		points.push_back(Vector2{ -5, -5 });
		points.push_back(Vector2{ -5, 5 });
		points.push_back(Vector2{ 5, 0 });

		// actor
		Model* model = new Model{ points, Color{ 1, 1, 0 } };
		Transform transform{ m_transform.position, m_transform.rotation, 1.0f };

		Bullet* bullet = new Bullet(400.0f, transform, model);
		bullet->SetLifespan(2);
		bullet->SetTag("Player");
		m_scene->AddActor(bullet);
	}

	Actor::Update(deltaTime);
}

void Player::OnCollision(Actor* actor)
{
	/*if (actor->GetTag() == "Enemy") {
		m_destroyed = true;
	}*/
}
