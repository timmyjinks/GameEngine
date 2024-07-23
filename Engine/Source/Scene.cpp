#include "Scene.h"
#include "Actor.h"
#include "Model.h"

#include <algorithm>
#include <chrono>

void Scene::Update(float deltaTime)
{
	// update
	for (auto& actor : m_actors) {
		actor->Update(deltaTime);
	}

	// destroy	
	std::erase_if(m_actors, [](auto& actor) { return actor->m_destroyed;});

	// collision
	for (auto& actor1 : m_actors) {
		for (auto& actor2 : m_actors) {
			if (actor1 == actor2) continue;

			Vector2 direction = actor1->GetTransform().position - actor2->GetTransform().position;
			float disitance = direction.Length();
			float radius = actor1->m_model->GetRadius() * actor2->m_model->GetRadius();

			if (disitance <= radius) {
				actor1->OnCollision(actor2.get());
				actor2->OnCollision(actor1.get());
			}
		}
	}
}

void Scene::Draw(Renderer& renderer)
{
	for (auto& actor : m_actors) {
		actor->Draw(renderer);
	}
}

void Scene::AddActor(std::unique_ptr<Actor> actor)
{
	actor->m_scene = this;
	m_actors.push_back(std::move(actor));
}

void Scene::RemoveAll()
{
	m_actors.clear();
}
