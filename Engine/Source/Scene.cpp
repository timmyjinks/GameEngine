#include "Scene.h"
#include "Actor.h"

void Scene::Update(float deltaTime)
{
	// update
	for (Actor* actor : m_actors) {
		actor->Update(deltaTime);
	}

	// destroy


	// collision

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
