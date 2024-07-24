#pragma once
#include <list>
#include <memory>

class Renderer;
class Actor;
class Game;
class Player;

class Scene
{
public:
	Scene() = default;
	Scene(Game* game) : m_game{ game } {}

	void Update(float delta);
	void Draw(Renderer& renderer);

	void AddActor(std::unique_ptr<Actor> actor);
	void RemoveAll();

	template<typename T>
	T* GetActor();

	Game* GetGame() const { return m_game; }

protected:
	std::list<std::unique_ptr<Actor>> m_actors;

private:
	Game* m_game{ nullptr };
};

template<typename T>
T* Scene::GetActor()
{
	for (auto& actor : m_actors)
	{
		T* result = dynamic_cast<T*>(actor.get());
		if (result) return result;
	}

	return nullptr;
}