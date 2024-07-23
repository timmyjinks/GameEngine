#include "ParticleSystem.h"

void ParticleSystem::Update(float deltaTime) {
	for (auto& particle : m_particles) {
		if (particle.isActive) particle.Update(deltaTime);
	}
}

void ParticleSystem::Draw(Renderer& renderer) {
	for (auto& particle : m_particles) {
		if (particle.isActive) particle.Draw(renderer);
	}
}

void ParticleSystem::AddParticle(const Particle::Data& data) {
	Particle* particle = GetFreeParticle();
	if (particle) {
		m_particles.data;
	}
}

Particle* ParticleSystem::GetFreeParticle()
{
	for (auto& particle : m_particles) {
		if (!particle.isActive) return &particle;
	}

	return nullptr;
}
