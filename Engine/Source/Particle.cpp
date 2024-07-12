#include "Particle.h"

void Particle::Update(float deltaTime)
{
	position = position + (velocity * deltaTime);
	if (lifespan != 0) {
		lifespan -= deltaTime;
	}
}

void Particle::Draw(Renderer& renderer)
{
	if (lifespan >= 0) {
		renderer.SetColor(color[0], color[1], color[2], 0);
		renderer.DrawRect(position.x, position.y, 4.0f, 4.0f);
	}
}
