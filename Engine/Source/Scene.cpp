#include "Scene.h"
#include "Actor.h"
#include "Model.h"

#include <algorithm>
#include <iostream>

void Scene::Update(float deltaTime)
{
	// update
	for (Actor* actor : m_actors) {
		actor->Update(deltaTime);
	}

	// destroy	
	m_actors.erase(std::remove_if(m_actors.begin(), m_actors.end(), [](Actor* actor) { return actor->m_destroyed; }), m_actors.end());

	// collision
	for (Actor* actor1 : m_actors) {
		for (Actor* actor2 : m_actors) {
			if (actor1 == actor2) continue;

			Vector2 direction = actor1->GetTransform().position - actor2->GetTransform().position;
			float disitance = direction.Length();
			float radius = actor1->m_model->GetRadius() * actor2->m_model->GetRadius();

			if (disitance <= radius) {
				actor1->OnCollision(actor2);
				actor2->OnCollision(actor1);
			}
		}
	}
}

void Scene::Draw(Renderer& renderer)
{
	for (Actor* actor : m_actors) {
		actor->Draw(renderer);
	}
}

void Scene::AddActor(Actor* actor)
{
	actor->m_scene = this;
	m_actors.push_back(actor);
}
