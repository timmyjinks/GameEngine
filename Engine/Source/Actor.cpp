#include "Actor.h"
#include "Model.h"

void Actor::Update(float deltaTime)
{
	if (m_lifespan != -5) {
		m_lifespan -= deltaTime;
		if (m_lifespan <= 0) {
			m_destroyed = true;
		}
	}

	m_transform.position += m_velocity * deltaTime;
	m_velocity *= 1.0f / (1.0f + m_damping * deltaTime);
}

void Actor::Draw(Renderer& renderer)
{
	if (m_destroyed) return;

	if (m_model) {
		m_model->Draw(renderer, m_transform);
	}
}
