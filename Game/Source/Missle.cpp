#include "Missle.h"
#include "Engine.h"
#include "Scene.h"
#include "FNAFGame.h"

void Missle::Update(float deltaTime)
{
	m_trailTimer -= deltaTime;
	if (m_trailTimer <= 0) {
		m_trailTimer = 0.1f;
		Particle::Data data{
			m_transform.position,
			Vector2{ 1,1 },
			0.2f,
			255, 100, 0, 255
		};
		g_engine.GetParticleSystem().AddParticle(data);
	}

	m_velocity = Vector2{ 1, 0 }.Rotate(m_transform.rotation) * m_speed;
	if (m_lifespan - deltaTime <= 0) {
		for (int i = 0; i < 1000; i++) {
			g_engine.GetAudio().PlaySound("explosion.mp3");
			Particle::Data data{
				m_transform.position,
				Vector2{ randomOnUnitCircle() * randomf(0, 80)},
				0.8,
				255, randomf(80, 255), 0
			};
			g_engine.GetParticleSystem().AddParticle(data);
		}
		m_transform.scale *= 10;
	}

	Actor::Update(deltaTime);
}

void Missle::OnCollision(Actor* actor) {
	if (actor->GetTag() == "Enemy") {
		if (!m_destroyed) {
			for (int i = 0; i < 1000; i++) {
				Particle::Data data{
					m_transform.position,
					Vector2{ randomOnUnitCircle() * randomf(0, 80)},
					0.8,
					255, randomf(80, 255), 0, 255
				};

				g_engine.GetParticleSystem().AddParticle(data);
			}
			m_transform.scale *= 10;
			m_scene->GetGame()->AddPoints(500);
			m_destroyed = true;
		}
	}
}
