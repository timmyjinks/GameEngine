#include "FNAFGame.h"
#include "Scene.h"
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "GameData.h"

bool FNAFGame::Initialize()
{
	m_scene = new Scene();
	if (!m_scene) return false;
	return true;
}

void FNAFGame::Shutdown()
{

}

void FNAFGame::Update(float deltaTime)
{
	switch (m_state) {
	case eState::Title:
		if (m_engine->GetInput().GetKeyDown(SDL_SCANCODE_SPACE)) m_state = eState::StartGame;
		break;
	case eState::StartGame:
		m_score = 0;
		m_state = eState::StartLevel;
		break;
	case eState::StartLevel:
	{
		Model* model = new Model{ GameData::shipPoints, Color{ 1,1,0 } };
		Transform transform{ { 400, 300 }, 0, 10 };
		auto player = std::make_unique<Player>(1000, transform, model);
		player->SetDamping(2.0f);
		player->SetTag("Player");
		player->SetLifespan(-5);
		m_scene->AddActor(std::move(player));
	}

	m_spawnTime = 2;
	m_spawnTimer = m_spawnTime;

	m_state = eState::Game;
	break;
	case eState::Game:
		m_spawnTimer -= deltaTime;
		if (m_spawnTimer <= 0) {
			m_spawnTimer = m_spawnTime;

			Model* enemyModel = new Model{ GameData::shipPoints, Color{ 1,0,0 } };
			auto enemy = std::make_unique<Enemy>(20, Transform{ { 100, 100 }, 0, randomf(0, 5) }, enemyModel);
			enemy->SetDamping(1.0f);
			enemy->SetLifespan(-5);
			enemy->SetTag("Enemy");
			m_scene->AddActor(std::move(enemy));
		}

		break;
	case eState::PlayerDead:
		break;
	case eState::GameOver:
		break;
	default:
		break;
	}
	m_scene->Update(deltaTime);
}

void FNAFGame::Draw(Renderer& renderer)
{
	switch (m_state) {
	case eState::Title:
		// draw text "Game Title"
		break;
	case eState::GameOver:
		// draw text "Game Over"
		break;
	default:
		break;
	}

	// draw scores
	// draw lives
	m_scene->Draw(renderer);
}
