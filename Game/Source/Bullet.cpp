#include "Bullet.h"
#include "Engine.h"

void Bullet::Update(float deltaTime)
{
	m_velocity = Vector2{ 1, 0 }.Rotate(m_transform.rotation) * m_speed;

	Actor::Update(deltaTime);
}

void Bullet::OnCollision(Actor* actor)
{
	if (actor->GetTag() == "Enemy") {
		m_destroyed = true;
	}

}
