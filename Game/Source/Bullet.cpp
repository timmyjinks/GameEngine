#include "Bullet.h"
#include "Engine.h"

void Bullet::Update(float deltaTime)
{
	m_velocity = Vector2{ 1, 0 }.Rotate(m_transform.rotation) * m_speed;

	m_transform.position.x = Math::Wrap(m_transform.position.x, (float)g_engine.GetRenderer().GetWidth());
	m_transform.position.y = Math::Wrap(m_transform.position.y, (float)g_engine.GetRenderer().GetHeight());

	Actor::Update(deltaTime);
}
