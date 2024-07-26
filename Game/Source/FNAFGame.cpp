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

	g_engine.GetAudio().AddSound("explosion.mp3");
	g_engine.GetAudio().AddSound("click.mp3");
	g_engine.GetAudio().AddSound("shoot.mp3");

	m_font = new Font();
	m_font->Load("arcadeclassic.ttf", 20);

	m_fontMedium = new Font();
	m_fontMedium->Load("arcadeclassic.ttf", 32);

	m_fontLarge = new Font();
	m_fontLarge->Load("arcadeclassic.ttf", 72);

	m_textScore = new Text(m_font);
	m_textLives = new Text(m_font);
	m_pressSpace = new Text(m_font);
	m_scoreTitle = new Text(m_fontMedium);
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
	case eState::TITLE:
		if (m_engine->GetInput().GetKeyDown(SDL_SCANCODE_SPACE) && !g_engine.GetInput().GetPreviousKeyDown(SDL_SCANCODE_SPACE))
		{
			g_engine.GetAudio().PlaySound("click.mp3");
			m_state = eState::STARTGAME;
		}
		break;
	case eState::STARTGAME:
		m_score = 0;
		m_lives = 3;
		m_state = eState::STARTLEVEL;
		break;
	case eState::STARTLEVEL:
	{
		Transform transform{ { 400, 300 }, 0, 5 };
		auto model = new Model{ GameData::shipPoints, Color{ 1, 1, 1 } };
		auto player = std::make_unique<Player>(600, transform, model);
		player->SetLifespan(-5);
		player->SetDamping(1.5f);
		player->SetTag("Player");
		m_scene->AddActor(std::move(player));
	}

	m_spawnTime = 2;
	m_spawnTimer = m_spawnTime;
	m_state = eState::GAME;
	break;
	case eState::GAME:
		m_spawnTimer -= deltaTime;
		if (m_spawnTimer <= 0) {
			m_spawnTimer = m_spawnTime;
			float width;
			float height;

			switch (random(0, 3)) {
			case 0:
				width = randomf(0, g_engine.GetRenderer().GetWidth());
				height = 0;
				break;
			case 1:
				width = 0;
				height = randomf(0, g_engine.GetRenderer().GetWidth());
				break;
			case 2:
				width = g_engine.GetRenderer().GetWidth();
				height = randomf(0, g_engine.GetRenderer().GetWidth());
				break;
			case 3:
				width = 0;
				height = randomf(0, g_engine.GetRenderer().GetWidth());
				break;
			}

			auto enemyModel = new Model{ GameData::enemyPoints, Color{ 1, 0, 0 } };
			auto enemy = std::make_unique<Enemy>(100, Transform{ { width, height }, 0, 2.5 }, enemyModel);
			enemy->SetLifespan(-5);
			enemy->SetDamping(1.5f);
			enemy->SetTag("Enemy");
			m_scene->AddActor(std::move(enemy));

			if (randomf(0, 100) > 85) {
				auto fireModifierModel = new Model{ GameData::pickupPoints, Color{ 1, 1, 0 } };
				auto fireModifierPickup = std::make_unique<Pickup>(Transform{ { random(g_engine.GetRenderer().GetWidth()), random(g_engine.GetRenderer().GetWidth())}, 0, 2 }, fireModifierModel);
				fireModifierPickup->SetLifespan(-5);
				fireModifierPickup->SetTag("FireModifierPickup");
				m_scene->AddActor(std::move(fireModifierPickup));
			}

			if (m_score > 2000 && randomf(0, 100) > 50) {
				auto missleModel = new Model{ GameData::pickupPoints, Color{ 1, 0.5, 0 } };
				auto misslePickup = std::make_unique<Pickup>(Transform{ { random(g_engine.GetRenderer().GetWidth()), random(g_engine.GetRenderer().GetHeight())}, 0, 2 }, missleModel);
				misslePickup->SetLifespan(3);
				misslePickup->SetTag("MisslePickup");
				m_scene->AddActor(std::move(misslePickup));
			}
			switch (m_score)
			{
			case 2000:
				m_spawnTime = 1.5;
				break;
			case 5000:
				m_spawnTime = 1;
				break;
			case 10000:
				m_spawnTime = 0.5;
				break;
			}
		}
		break;
	case eState::PLAYERDEAD:
		m_scene->RemoveAll();
		m_stateTimer -= deltaTime;
		if (m_stateTimer <= 0)
		{
			if (m_lives == 0) {
				m_state = eState::GAMEOVER;
			}
			else {
				m_state = eState::STARTLEVEL;
			}
		}
		break;
	case eState::GAMEOVER:
		m_scene->RemoveAll();
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_SPACE) && !g_engine.GetInput().GetPreviousKeyDown(SDL_SCANCODE_SPACE)) {
			g_engine.GetAudio().PlaySound("click.mp3");
			m_state = eState::TITLE;
		}
		break;
	}
	m_scene->Update(deltaTime);
}

void FNAFGame::Draw(Renderer& renderer)
{
	switch (m_state)
	{
	case eState::TITLE:

		m_textTitle->Create(renderer, "Bread SpaceGAME", Color{ 1,1,1,1 });
		m_pressSpace->Create(renderer, "Press space to start", Color{ 1,1,1,1 });
		m_textTitle->Draw(renderer, 125, 150);
		m_pressSpace->Draw(renderer, 300, 250);
		break;
	case eState::GAMEOVER:
		std::string text = "Score " + std::to_string(m_score);
		m_textTitle->Create(renderer, "GAME OVER", Color{ 1,0,0,1 });
		m_scoreTitle->Create(renderer, text, Color{ 1,1,1,1 });

		m_textTitle->Draw(renderer, 250, 250);
		m_scoreTitle->Draw(renderer, 350, 300);
		break;
	}

	if (m_state != eState::TITLE && m_state != eState::GAMEOVER) {
		std::string text = "Score " + std::to_string(m_score);
		m_textScore->Create(renderer, text, { 1, 1, 1, 1 });
		m_textScore->Draw(renderer, 20, 20);

		text = "Lives " + std::to_string(m_lives);
		m_textLives->Create(renderer, text, { 1, 1, 1, 1 });
		m_textLives->Draw(renderer, renderer.GetWidth() - 100, 20);
	}

	m_scene->Draw(renderer);
}

void FNAFGame::OnPlayerDeath()
{
	m_lives--;
	m_state = (m_lives == 0) ? eState::GAMEOVER : eState::PLAYERDEAD;
	m_stateTimer = 3;
}