#include "Renderer.h"
#include "Vector2.h"
#include "Input.h"
#include "Particle.h"
#include "Random.h"
#include "ETime.h"
#include "MathUtils.h"
#include "Model.h"
#include "Transform.h"

#include <fmod.hpp>
#include <iostream>
#include <cstdlib>
#include <vector>

int main(int argc, char* argv[])
{
	FMOD::System* audio;
	FMOD::System_Create(&audio);

	void* extradriverdata = nullptr;
	audio->init(32, FMOD_INIT_NORMAL, extradriverdata);

	FMOD::Sound* sound = nullptr;
	std::vector<FMOD::Sound*> sounds;
	audio->createSound("bass.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	audio->createSound("clap.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	audio->createSound("close-hat.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	audio->createSound("cowbell.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	audio->createSound("open-hat.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	audio->createSound("snare.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	// create systems 
	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Game Engine", 800, 600);

	Input input;
	input.Initialize();

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

	Model model{ points, Color{ 1,0,0,0 } };
	Transform transform{ { renderer.GetWidth() >> 1 , renderer.GetHeight() >> 1 }, 0, 10 };

	bool quit = false;
	while (!quit)
	{
		time.Tick();

		// input
		// update
		input.Update();
		// draw

		// INPUT

		if (input.GetKeyDown(SDL_SCANCODE_ESCAPE)) {
			quit = true;
		}

		float thrust = 0;
		if (input.GetKeyDown(SDL_SCANCODE_UP)) thrust = 500;
		if (input.GetKeyDown(SDL_SCANCODE_DOWN)) thrust = -500;

		if (input.GetKeyDown(SDL_SCANCODE_LEFT)) transform.rotation -= Math::DegToRad(100) * time.GetDeltaTime();
		if (input.GetKeyDown(SDL_SCANCODE_RIGHT)) transform.rotation += Math::DegToRad(100) * time.GetDeltaTime();

		Vector2 velocity = Vector2{ thrust, 0.0f }.Rotate(transform.rotation);
		transform.position = transform.position + velocity * time.GetDeltaTime();
		transform.position.x = Math::Wrap(transform.position.x, (float)renderer.GetWidth());
		transform.position.y = Math::Wrap(transform.position.y, (float)renderer.GetHeight());

		// UPDATE


		for (Particle& particle : particles) {
			particle.Update(time.GetDeltaTime());
			if (particle.position.x > 800) particle.position.x = 0;
			if (particle.position.x < 0) particle.position.x = 800;
		}

		Vector2 mousePosition = input.GetMousePosition();

		if (input.GetMouseButtonDown(0) && input.GetPreviousMouseButtonDown(0)) {
			particles.push_back(Particle{ mousePosition, randomOnUnitCircle() * 300 ,randomf(1,5), (uint8_t)random(256), (uint8_t)random(256), (uint8_t)random(256) });
		}

		if (input.GetKeyDown(SDL_SCANCODE_Q) && !input.GetPreviousKeyDown(SDL_SCANCODE_Q)) audio->playSound(sounds[0], 0, false, nullptr);
		if (input.GetKeyDown(SDL_SCANCODE_W) && !input.GetPreviousKeyDown(SDL_SCANCODE_W)) audio->playSound(sounds[1], 0, false, nullptr);
		if (input.GetKeyDown(SDL_SCANCODE_E) && !input.GetPreviousKeyDown(SDL_SCANCODE_E)) audio->playSound(sounds[2], 0, false, nullptr);
		if (input.GetKeyDown(SDL_SCANCODE_R) && !input.GetPreviousKeyDown(SDL_SCANCODE_R)) audio->playSound(sounds[3], 0, false, nullptr);
		if (input.GetKeyDown(SDL_SCANCODE_A) && !input.GetPreviousKeyDown(SDL_SCANCODE_A)) audio->playSound(sounds[4], 0, false, nullptr);
		if (input.GetKeyDown(SDL_SCANCODE_S) && !input.GetPreviousKeyDown(SDL_SCANCODE_S)) audio->playSound(sounds[5], 0, false, nullptr);

		audio->update();
		// DRAW
		// clear screen
		renderer.SetColor(0, 0, 0, 0);
		renderer.BeginFrame();

		float radius = 180;
		offset += (90 * time.GetDeltaTime());
		renderer.SetColor(0, 255, 255, 0);
		for (float angle = 0; angle < 360; angle += 360 / 30) {
			float x = Math::Cos(Math::DegToRad(angle + offset)) * Math::Sin(offset * 0.01f) * radius;
			float y = Math::Sin(Math::DegToRad(angle + offset)) * Math::Sin(offset * 0.01f) * radius;

			renderer.DrawRect(400 + x, 300 + y, 4.0f, 4.0f);

			if (input.GetMouseButtonDown(0) && !input.GetPreviousMouseButtonDown(0)) {
				for (int i = 0; i < 1000; i++) {
					particles.push_back(Particle{ mousePosition, randomOnUnitCircle() * 100 ,randomf(1,5), (uint8_t)random(256), (uint8_t)random(256), (uint8_t)random(256) });
				}
				break;
			}

		}

		// particles
		for (Particle particle : particles) {
			particle.Draw(renderer);
		}

		model.Draw(renderer, transform);

		// show screen

		renderer.EndFrame();
	}

	return 0;
}