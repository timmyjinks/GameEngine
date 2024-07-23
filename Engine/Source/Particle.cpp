#include "Particle.h"

void Particle::Initialize()
{
	isActive = true;
	position = data.position;
	velocity = data.velocity;
	lifespan = data.lifespan;
	position = data.position;
	position = data.position;
}

void Particle::Update(float deltaTime)
{
	if (lifespan != 0.0f) lifespan -= deltaTime;
	position = position + (velocity * deltaTime);
	isActive = (lifespan <= 0);
}

void Particle::Draw(Renderer& renderer)
{
	if (lifespan >= 0) {
		renderer.SetColor(r, g, b, a);
		renderer.DrawRect(position.x, position.y, 4.0f, 4.0f);
	}
}
