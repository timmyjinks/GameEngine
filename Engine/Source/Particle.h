#pragma once
#include "Renderer.h"
#include "Vector2.h"

struct Particle {
	struct Data {
		Vector2 position{ 0,0 };
		Vector2 velocity{ 0,0 };
		float lifespan = 0;
		uint8_t r, g, b, a = 255;
	};

	Data m_data;
	Vector2 position{ 0,0 };
	Vector2 velocity{ 0,0 };
	float lifespan = 0;
	uint8_t r{ 255 };
	uint8_t g{ 255 };
	uint8_t b{ 255 };
	uint8_t a{ 255 };
	bool isActive{ false };

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
	Particle(Vector2 position, Vector2 velocity, float lifespan, uint8_t r, uint8_t g, uint8_t b, uint8_t a) :
		position{ position },
		velocity{ velocity },
		lifespan{ lifespan },
		r{ r }, g{ g }, b{ b }, a{ a }
	{}

	void Initialize(const Data& data);
	void Update(float deltaTime);
	void Draw(Renderer& renderer);
};