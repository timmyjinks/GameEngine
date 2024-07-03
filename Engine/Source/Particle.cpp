#include "Particle.h"

void Particle::Update(float deltaTime)
{
	position = position + (velocity * deltaTime);
}

void Particle::Draw(Renderer& renderer)
{
	renderer.DrawPoint(position.x, position.y);
}
