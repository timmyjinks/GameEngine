#include "Renderer.h"
#include "Vector2.h"
#include "Input.h"
#include "Particle.h"
#include "Random.h"
#include "ETime.h"

#include <iostream>
#include <cstdlib>
#include <vector>

int main(int argc, char* argv[])
{
	// create systems 
	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Game Engine", 800, 600);

	Input input;
	input.Initialize();

	Time time;

	std::vector<Particle> particles;
	std::vector<Vector2> points;

	bool quit = false;
	while (!quit)
	{
		time.Tick();

		// input
		// update
		// draw

		// INPUT
		input.Update();

		if (input.GetKeyDown(SDL_SCANCODE_ESCAPE)) {
			quit = true;
		}

		// UPDATE
		for (Particle& particle : particles) {
			particle.Update(time.GetDeltaTime());
			if (particle.position.x > 800) particle.position.x = 0;
			if (particle.position.x < 0) particle.position.x = 800;
		}

		Vector2 mousePosition = input.GetMousePosition();

		if (input.GetMouseButtonDown(0) && input.GetPreviousMouseButtonDown(0)) {
			particles.push_back(Particle{ mousePosition, { randomf(-100, 100), randomf(-100, 100)} });
		}

		// DRAW
		// clear screen
		renderer.SetColor(0, 0, 0, 0);
		renderer.BeginFrame();

		// particles
		renderer.SetColor(255, 255, 255, 0);
		for (Particle particle : particles) {
			if (particle.lifespan > 0) {
				particle.Draw(renderer);
			}
		}

		// show screen
		renderer.EndFrame();
	}

	return 0;
}