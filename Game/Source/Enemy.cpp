#include "Enemy.h"
#include "Player.h"
#include "Scene.h"
#include <iostream>

int i = 0;
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
		//	m_destroyed = true;
		std::cout << "collision: " << i << std::endl;
		i++;
	}
}
