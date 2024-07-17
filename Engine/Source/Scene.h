#pragma once
#include <list>

class Renderer;
class Actor;

class Scene {
public:
	Scene() = default;

	void Update(float deltaTime);
	void Draw(Renderer& renderer);

	void AddActor(Actor* actor);

	template<typename T>
	T* GetActor();

protected:
	std::list<Actor*> m_actors;
};

template<typename T>
T* Scene::GetActor() {
	for (Actor* actor : m_actors) {
		T* result = dynamic_cast<T*>(actor);
		if (result) return result;
	}

	return nullptr;
}
