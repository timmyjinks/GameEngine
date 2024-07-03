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
	for (int i = 0; i < 0; i++) {
		particles.push_back(Particle{ Vector2{ rand() % 800, rand() % 800 }, { randomf(100, 300), 0.0f } });
	}

	Vector2 v1{ 400, 200 };
	Vector2 v2{ 700, 500 };

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
			points.push_back(mousePosition);
		}

		if (input.GetMouseButtonDown(0) && !input.GetPreviousMouseButtonDown(0)) {
			std::cout << "mouse down\n";
			points.push_back(mousePosition);
		}


		/*	if (input.GetMouseButtonDown(0) && input.GetPreviousMouseButtonDown(0)) {
				particles.push_back(Particle{ mousePosition, { randomf(-100, 100), randomf(-100, 100)} });
			}*/

			// DRAW
			// clear screen
		renderer.SetColor(0, 0, 0, 0);
		renderer.BeginFrame();

		// particles
		renderer.SetColor(255, 255, 255, 0);
		for (Particle particle : particles) {
			particle.Draw(renderer);
		}

		// 
		for (int i = 0; points.size() > 1 && i < points.size() - 1; i++) {
			renderer.SetColor(255, 0, 0, 0);
			renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
		}

		// show screen
		renderer.EndFrame();
	}

	return 0;
}