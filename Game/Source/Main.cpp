#include "Engine.h"
#include "Player.h"
#include "Scene.h"
#include "Enemy.h"

#include <iostream>
#include <cstdlib>
#include <vector>

int main(int argc, char* argv[])
{
	g_engine.Initialize();

	g_engine.GetAudio().AddSound("bass.wav");
	g_engine.GetAudio().AddSound("snare.wav");
	g_engine.GetAudio().AddSound("close-hat.wav");
	g_engine.GetAudio().AddSound("open-hat.wav");
	g_engine.GetAudio().AddSound("clap.wav");
	g_engine.GetAudio().AddSound("cowbell.wav");

	Time time;

	std::vector<Particle> particles;
	float offset = 0;

	std::vector<Vector2> points;
	points.push_back(Vector2{ 5, 0 });
	points.push_back(Vector2{ -2, 7 });
	points.push_back(Vector2{ -3, 6 });
	points.push_back(Vector2{ 0, 3 });
	points.push_back(Vector2{ -2, 2 });
	points.push_back(Vector2{ -1, 1 });
	points.push_back(Vector2{ -2, 0 });
	points.push_back(Vector2{ -1, -1 });
	points.push_back(Vector2{ -2, -2 });
	points.push_back(Vector2{ 0, -3 });
	points.push_back(Vector2{ -3, -6 });
	points.push_back(Vector2{ -2, -7 });
	points.push_back(Vector2{ 5, 0 });

	Model* model = new Model{ points, Color{ 1,1,0 } };
	Scene* scene = new Scene();

	Transform transform{ { 400, 300 }, 0, 10 };
	Player* player = new Player(1000, transform, model);
	player->SetDamping(2.0f);
	player->SetTag("Player");
	player->SetLifespan(-5);
	scene->AddActor(player);

	float spawnTime = 0;

	float i = 5;
	bool quit = false;
	while (!quit)
	{
		// input
		// update
		// draw

		time.Tick();

		// INPUT

		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_ESCAPE)) {
			quit = true;
		}

		spawnTime -= time.GetDeltaTime();
		if (spawnTime <= 0) {
			auto* enemyModel = new Model{ points, Color{ 1,0,0 } };
			auto* enemy = new Enemy(20, Transform{ { 100, 100 }, 0, i }, enemyModel);
			enemy->SetDamping(1.0f);
			enemy->SetLifespan(-5);
			enemy->SetTag("Enemy");
			scene->AddActor(enemy);

			spawnTime = 8888888;
			i++;
		}

		Vector2 mousePosition = g_engine.GetInput().GetMousePosition();

		if (g_engine.GetInput().GetMouseButtonDown(0) && g_engine.GetInput().GetPreviousMouseButtonDown(0)) {
			particles.push_back(Particle{ mousePosition, randomOnUnitCircle() * 300 ,randomf(1,5), (uint8_t)random(256), (uint8_t)random(256), (uint8_t)random(256) });
		}

		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_Q) && !g_engine.GetInput().GetPreviousKeyDown(SDL_SCANCODE_Q)) g_engine.GetAudio().PlaySound("bass.wav");
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_W) && !g_engine.GetInput().GetPreviousKeyDown(SDL_SCANCODE_W)) g_engine.GetAudio().PlaySound("snare");
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_E) && !g_engine.GetInput().GetPreviousKeyDown(SDL_SCANCODE_E)) g_engine.GetAudio().PlaySound("close-hat.wav");
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_R) && !g_engine.GetInput().GetPreviousKeyDown(SDL_SCANCODE_R)) g_engine.GetAudio().PlaySound("open-hat.wav");
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_A) && !g_engine.GetInput().GetPreviousKeyDown(SDL_SCANCODE_A)) g_engine.GetAudio().PlaySound("clap.wav");
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_S) && !g_engine.GetInput().GetPreviousKeyDown(SDL_SCANCODE_S)) g_engine.GetAudio().PlaySound("cowbell");

		// UPDATE
		scene->Update(time.GetDeltaTime());
		g_engine.GetInput().Update();


		for (Particle& particle : particles) {
			particle.Update(time.GetDeltaTime());
			if (particle.position.x > 800) particle.position.x = 0;
			if (particle.position.x < 0) particle.position.x = 800;
		}

		// DRAW
		// clear screen
		g_engine.GetRenderer().SetColor(0, 0, 0, 0);
		g_engine.GetRenderer().BeginFrame();

		float radius = 180;
		offset += (90 * time.GetDeltaTime());
		g_engine.GetRenderer().SetColor(0, 255, 255, 0);
		for (float angle = 0; angle < 360; angle += 360 / 30) {
			float x = Math::Cos(Math::DegToRad(angle + offset)) * Math::Cos(offset * 0.01f) * radius;
			float y = Math::Sin(Math::DegToRad(angle + offset)) * Math::Cos(offset * 0.01f) * radius;

			g_engine.GetRenderer().DrawRect(400 + x, 300 + y, 4.0f, 4.0f);

			/*	if (g_engine.GetInput().GetMouseButtonDown(0) && !g_engine.GetInput().GetPreviousMouseButtonDown(0)) {
					for (int i = 0; i < 1000; i++) {
						particles.push_back(Particle{ mousePosition, randomOnUnitCircle() * 100 ,randomf(1,5), (uint8_t)random(256), (uint8_t)random(256), (uint8_t)random(256) });
					}
					break;
				}*/
		}

		// particles
		for (Particle particle : particles) {
			particle.Draw(g_engine.GetRenderer());
		}

		scene->Draw(g_engine.GetRenderer());
		// show screen
		g_engine.Update();
		g_engine.GetRenderer().EndFrame();
	}

	return 0;
}