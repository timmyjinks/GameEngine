#include "FNAFGame.h"
#include "Scene.h"
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Pickup.h"
#include "GameData.h"
#include "Font.h"
#include "Text.h"

bool FNAFGame::Initialize()
{
	m_scene = new Scene(this);

	g_engine.GetAudio().AddSound("bass.wav");

	m_font = new Font();
	m_font->Load("arcadeclassic.ttf", 20);

	m_fontLarge = new Font();
	m_fontLarge->Load("arcadeclassic.ttf", 72);

	m_textScore = new Text(m_font);
	m_textLives = new Text(m_font);
	m_textTitle = new Text(m_fontLarge);

	return true;
}

void FNAFGame::Shutdown()
{

}

void FNAFGame::Update(float deltaTime)
{
	switch (m_state)
	{
	case eState::Title:
		g_engine.GetAudio().PlaySound("bass.wav");
		if (m_engine->GetInput().GetKeyDown(SDL_SCANCODE_SPACE))
		{
			m_state = eState::StartGame;
		}
		break;
	case eState::StartGame:
		m_score = 0;
		m_lives = 3;
		m_state = eState::StartLevel;
		break;
	case eState::StartLevel:
	{
		Transform transform{ { 400, 300 }, 0, 5 };
		auto model = new Model{ GameData::shipPoints, Color{ 1, 1, 1 } };
		auto player = std::make_unique<Player>(600, transform, model);
		player->SetLifespan(-5);
		player->SetDamping(1.5f);
		player->SetTag("Player");
		m_scene->AddActor(std::move(player));
	}

	m_spawnTime = 3;
	m_spawnTimer = m_spawnTime;
	m_state = eState::Game;
	break;
	case eState::Game:
		m_spawnTimer -= deltaTime;
		if (m_spawnTimer <= 0) {
			m_spawnTimer = m_spawnTime;
			auto enemyModel = new Model{ GameData::enemyPoints, Color{ 1, 0, 0 } };
			auto enemy = std::make_unique<Enemy>(60, Transform{ {random(g_engine.GetRenderer().GetWidth()), random(g_engine.GetRenderer().GetHeight())}, 0, 2 }, enemyModel);
			enemy->SetLifespan(-5);
			enemy->SetDamping(1.5f);
			enemy->SetTag("Enemy");
			m_scene->AddActor(std::move(enemy));


			auto pickupModel = new Model{ GameData::pickupPoints, Color{ 1, 1, 0 } };
			auto pickup = std::make_unique<Pickup>(Transform{ { random(g_engine.GetRenderer().GetWidth()), random(g_engine.GetRenderer().GetHeight())}, 0, 2 }, pickupModel);
			pickup->SetLifespan(-5);
			pickup->SetTag("Pickup");
			m_scene->AddActor(std::move(pickup));
		}
		break;
	case eState::PlayerDead:
		m_stateTimer -= deltaTime;
		if (m_stateTimer <= 0)
		{
			if (m_lives == 0) {
				m_state = eState::GameOver;
			}
			else {
				m_state = eState::StartLevel;
			}
		}
		break;
	case eState::GameOver:
		m_scene->RemoveAll();
		m_stateTimer -= deltaTime;
		if (m_stateTimer <= 0)
		{
			m_state = eState::Title;
		}
		break;
	default:
		break;
	}

	m_scene->Update(deltaTime);
}

void FNAFGame::Draw(Renderer& renderer)
{
	switch (m_state)
	{
	case eState::Title:
		m_textTitle->Create(renderer, "1", Color{ 1,0,1,1 });
		m_textTitle->Draw(renderer, 250, 250);
		break;
	case eState::GameOver:
		m_textTitle->Create(renderer, "sad", Color{ 1,1,0,1 });
		m_textTitle->Draw(renderer, 250, 250);
		break;
	default:
		break;
	}

	std::string text = "Score " + std::to_string(m_score);
	m_textScore->Create(renderer, text, { 1, 1, 1, 1 });
	m_textScore->Draw(renderer, 20, 20);

	text = "Lives " + std::to_string(m_lives);
	m_textLives->Create(renderer, text, { 1, 1, 1, 1 });
	m_textLives->Draw(renderer, renderer.GetWidth() - 100, 20);

	m_scene->Draw(renderer);
}

void FNAFGame::OnPlayerDeath()
{
	m_lives--;
	m_state = (m_lives == 0) ? eState::GameOver : eState::PlayerDead;
	m_stateTimer = 3;
}