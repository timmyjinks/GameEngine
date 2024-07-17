#include "Enemy.h"
#include "Player.h"
#include "Scene.h"

void Enemy::Update(float deltaTime)
{
	Player* player = m_scene->GetActor<Player>();
	if (player) {
		Vector2 direction = player->GetTransform().position - m_transform.position;
		m_velocity += direction.Normalized() * deltaTime;
		m_transform.rotation = direction.Angle();
	}

	Actor::Update(deltaTime);
}
