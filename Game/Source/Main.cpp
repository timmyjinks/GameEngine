#include "Engine.h"
#include "Player.h"
#include "Scene.h"
#include "Enemy.h"
#include "GameData.h"
#include "FNAFGame.h"

#include <iostream>
#include <stdlib.h>
#include <vector>

int main(int argc, char* argv[])
{
	g_engine.Initialize();

	FNAFGame* game = new FNAFGame(&g_engine);
	game->Initialize();

	std::vector<Particle> particles;

	while (!g_engine.IsQuit())
	{
		g_engine.Update();
		game->Update(g_engine.GetTime().GetDeltaTime());

		g_engine.GetRenderer().SetColor(0, 0, 0, 0);
		g_engine.GetRenderer().BeginFrame();

		game->Draw(g_engine.GetRenderer());
		g_engine.GetParticleSystem().Draw(g_engine.GetRenderer());

		g_engine.GetRenderer().EndFrame();
	}

	g_engine.Shutdown();

	return 0;
}

/*
	g_engine.GetAudio().AddSound("bass.wav");
	g_engine.GetAudio().AddSound("snare.wav");
	g_engine.GetAudio().AddSound("close-hat.wav");
	g_engine.GetAudio().AddSound("open-hat.wav");
	g_engine.GetAudio().AddSound("clap.wav");
	g_engine.GetAudio().AddSound("cowbell.wav");

	std::vector<Particle> particles;
	float offset = 0;




	float spawnTime = 0;

	float i = 5;
	bool quit = false;

		g_engine.Update();
		// input
		// update
		// draw

		// INPUT

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
		scene->Update(g_engine.GetTime().GetDeltaTime());
		g_engine.GetInput().Update();


		for (Particle& particle : particles) {
			particle.Update(g_engine.GetTime().GetDeltaTime());
			if (particle.position.x > 800) particle.position.x = 0;
			if (particle.position.x < 0) particle.position.x = 800;
		}

		for (float angle = 0; angle < 360; angle += 360 / 30) {
			float x = Math::Cos(Math::DegToRad(angle + offset)) * Math::Cos(offset * 0.01f) * radius;
			float y = Math::Sin(Math::DegToRad(angle + offset)) * Math::Cos(offset * 0.01f) * radius;

			g_engine.GetRenderer().DrawRect(400 + x, 300 + y, 4.0f, 4.0f);

			if (g_engine.GetInput().GetMouseButtonDown(0) && !g_engine.GetInput().GetPreviousMouseButtonDown(0)) {
					for (int i = 0; i < 1000; i++) {
						particles.push_back(Particle{ mousePosition, randomOnUnitCircle() * 100 ,randomf(1,5), (uint8_t)random(256), (uint8_t)random(256), (uint8_t)random(256) });
					}
					break;
				}
		}

		// DRAW
		// clear screen
		g_engine.GetRenderer().SetColor(0, 0, 0, 0);
		g_engine.GetRenderer().BeginFrame();

		float radius = 180;
		offset += (90 * g_engine.GetTime().GetDeltaTime());
		g_engine.GetRenderer().SetColor(0, 255, 255, 0);

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
*/