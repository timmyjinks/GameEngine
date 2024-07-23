#pragma once
#include <list>
#include <memory>

class Renderer;
class Actor;
class Game;

class Scene {
public:
	Scene() = default;

	void Update(float deltaTime);
	void Draw(Renderer& renderer);

	void AddActor(std::unique_ptr<Actor> actor);

	template<typename T>
	T* GetActor();

	Game* GetGame() { return m_game; }

	friend class Game;

protected:
	std::list<std::unique_ptr<Actor>> m_actors;

	Game* m_game{ nullptr };
};

template<typename T>
T* Scene::GetActor() {
	for (auto& actor : m_actors) {
		T* result = dynamic_cast<T*>(actor);
		if (result) return result;
	}

	return nullptr;
}
