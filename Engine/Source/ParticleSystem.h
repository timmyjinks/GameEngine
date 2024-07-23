#pragma once
#include "Particle.h"
#include <vector>

class Renderer;

class ParticleSystem {
public:
	ParticleSystem(int maxSize) {
		m_particles.resize(maxSize);
	}

	void Update(float deltaTime);
	void Draw(Renderer& renderer);

	void AddParticle(const Particle::Data& data);

private:
	Particle* GetFreeParticle();
	std::vector<Particle> m_particles;
};
