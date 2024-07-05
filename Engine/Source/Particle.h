#pragma once
#include "Vector2.h"
#include "Renderer.h"

struct Particle {
	Vector2 position;
	Vector2 velocity;
	float lifespan = 0;
	uint8_t color[3];

	Particle() = default;
	Particle(Vector2 position, Vector2 velocity) :
		position{ position },
		velocity{ velocity }
	{}
	Particle(Vector2 position, Vector2 velocity, float lifespan) :
		position{ position },
		velocity{ velocity },
		lifespan{ lifespan }
	{}
	Particle(Vector2 position, Vector2 velocity, float lifespan, uint8_t r, uint8_t g, uint8_t b) :
		position{ position },
		velocity{ velocity },
		lifespan{ lifespan },
		color{ r,g,b }
	{}

	void Update(float deltaTime);
	void Draw(Renderer& renderer);
};