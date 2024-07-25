#include "Bullet.h"
#include "Engine.h"
#include "Scene.h"
#include "FNAFGame.h"

void Bullet::Update(float deltaTime)
{
	Particle::Data data{
		m_transform.position,
		Vector2{ 1,0 }.Rotate(randomf(Math::TwoPi)) * 90,
		5
	};

	g_engine.GetParticleSystem().AddParticle(data);

	m_velocity = Vector2{ 1, 0 }.Rotate(m_transform.rotation) * m_speed;

	Actor::Update(deltaTime);
}

void Bullet::OnCollision(Actor* actor) {
	if (actor->GetTag() == "Enemy") {
		if (!m_destroyed) {
			m_scene->GetGame()->AddPoints(100);
			m_destroyed = true;
		}
	}
}
