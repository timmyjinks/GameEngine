#pragma once
#include "Game.h"

class Font;
class Text;

class FNAFGame : public Game {
public:

	enum class eState : char {
		TITLE,
		STARTGAME,
		STARTLEVEL,
		GAME,
		PLAYERDEAD,
		GAMEOVER
	};

	FNAFGame(Engine* engine) : Game{ engine } {}

	bool Initialize() override;
	void Shutdown() override;
	void Update(float deltaTime) override;
	void Draw(Renderer& renderer) override;

	void OnPlayerDeath();

private:
	eState m_state{ eState::TITLE };
	float m_spawnTimer{ 0 };
	float m_spawnTime{ 0 };
	float m_stateTimer{ 0 };

	Font* m_font{ nullptr };
	Font* m_fontMedium{ nullptr };
	Font* m_fontLarge{ nullptr };
	Text* m_textScore{ nullptr };
	Text* m_textLives{ nullptr };
	Text* m_textTitle{ nullptr };
	Text* m_scoreTitle{ nullptr };
	Text* m_pressSpace{ nullptr };
};
