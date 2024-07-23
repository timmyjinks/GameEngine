#include "Enemy.h"
#include "Player.h"
#include "Scene.h"
#include "Game.h"
#include "ParticleSystem.h"
#include "Engine.h"

void Enemy::Update(float deltaTime)
{
	Player* player = m_scene->GetActor<Player>();
	if (player) {
		Vector2 direction = player->GetTransform().position - m_transform.position;
		m_velocity += direction.Normalized() * m_speed * deltaTime;
		m_transform.rotation = direction.Angle();
	}

	Actor::Update(deltaTime);
}

void Enemy::OnCollision(Actor* actor)
{
	if (actor->GetTag() == "Player") {
		m_destroyed = true;

		/*Particle::Data data{
			m_transform.position,
			Vector2{ 1,0}.Rotate(randomf(Math::TwoPi)) * 50,
			5,
		};*/

		for (int i = 0; i < 100; i++) {
			//g_engine.GetParticleSystem().;
		}
	}
}
