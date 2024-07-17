#pragma once
#include "Transform.h"

class Model;
class Renderer;
class Scene;

class Actor {
public:

	Actor() = default;
	Actor(const Transform& transform) : m_transform{ transform } {}
	Actor(const Transform& transform, Model* model) :
		m_transform{ transform },
		m_model{ model }
	{}

	virtual void Update(float deltaTime);
	virtual void Draw(Renderer& renderer);

	void SetDamping(float damping) { m_damping = damping; }
	void SetLifespan(float lifespan) { m_lifespan = lifespan; }
	Transform GetTransform() { return m_transform; }

	friend class Scene;

protected:
	bool m_destroyed = false;
	float m_lifespan = 0;

	Transform m_transform;
	Vector2 m_velocity{ 0, 0 };
	float m_damping{ 0 };

	Model* m_model{ nullptr };
	Scene* m_scene{ nullptr };
};


