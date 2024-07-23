#pragma once
#include "Particle.h"
#include <vector>

class Renderer;
class Engine;

class ParticleSystem {
public:
	ParticleSystem() = default;
	ParticleSystem(int maxSize) {
		m_particles.resize(maxSize);
	}

	void Update(float deltaTime);
	void Draw(Renderer& renderer);

	void AddParticle(const Particle::Data& data);

	friend class Engine;

private:
	Particle* GetFreeParticle();
	std::vector<Particle> m_particles;
};
