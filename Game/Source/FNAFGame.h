#pragma once
#include "Game.h"

enum eState : char {
	Title,
	StartGame,
	StartLevel,
	Game,
	PlayerDead,
	GameOver
};

class FNAFGame : public Game {
public:
	FNAFGame(Engine* engine) : Game{ engine } {}

	bool Initialize() override;
	void Shutdown() override;
	void Update(float deltaTime) override;
	void Draw(Renderer& renderer) override;

private:
	eState m_state{ eState::Title };
	float m_spawnTimer{ 0 };
	float m_spawnTime{ 0 };
};
