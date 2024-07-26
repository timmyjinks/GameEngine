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
	if (actor->GetTag() == "Player" || actor->GetTag() == "PlayerBullet") {
		g_engine.GetAudio().PlaySound("explosion.mp3");
		m_destroyed = true;

		/*for (int i = 0; i < 25; i++) {
			Particle::Data data{
				m_transform.position,
				Vector2{ randomOnUnitCircle() * randomf(-50, 50)},
				1.5f,
			};

			g_engine.GetParticleSystem().GetFreeParticle()->Initialize(data);*/
			//}
	}
}
