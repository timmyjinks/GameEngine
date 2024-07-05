#pragma once
#include "Vector2.h"
#include "Renderer.h"

struct Particle {
	Vector2 position;
	Vector2 velocity;
	float lifespan = 5;

	Particle() = default;
	Particle(Vector2 position, Vector2 velocity) :
		position{ position },
		velocity{ velocity }
	{}

	void Update(float deltaTime);
	void Draw(Renderer& renderer);
};