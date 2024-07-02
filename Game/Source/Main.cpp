#include "Renderer.h"
#include "Vector2.h"
#include "Input.h"

#include <iostream>
#include <cstdlib>
#include <vector>

int main(int argc, char* argv[])
{
	// create renderer
	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Game Engine", 800, 600);

	Input input;
	input.Initialize();

	Vector2 v1{ 400, 200 };
	Vector2 v2{ 700, 500 };

	std::vector<Vector2> points;

	bool quit = false;
	while (!quit)
	{
		// input
		// update
		// draw

		// INPUT
		input.Update();

		if (input.GetKeyDown(SDL_SCANCODE_ESCAPE)) {
			quit = true;
		}

		// UPDATE
		Vector2 mousePosition = input.GetMousePosition();
		// std::cout << mousePosition.x << " " << mousePosition.y << std::endl;

		if (input.GetMouseButtonDown(0) && !input.GetPreviousMouseButtonDown(0)) {
			std::cout << "mouse down\n";
			points.push_back(mousePosition);
		}

		if (input.GetMouseButtonDown(0) && input.GetPreviousMouseButtonDown(0)) {
			points.push_back(mousePosition);
		}

		// DRAW
		// clear screen
		renderer.SetColor(0, 0, 0, 0);
		renderer.BeginFrame();

		// draw line
		/*for (int i = 0; i < 50; i++) {
			renderer.SetColor(rand() % 256, rand() % 256, rand() % 256, 0);
			renderer.DrawLine(rand() % 999, rand() % 999, rand() % 999, rand() % 999);
		}*/

		for (int i = 0; points.size() > 1 && i < points.size() - 1; i++) {
			renderer.SetColor(255, 255, 255, 0);
			renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
		}

		// draw triangle
		/*renderer.SetColor(255, 255, 255, 0);
		renderer.DrawLine(400, 200, 200, 400);
		renderer.DrawLine(400, 200, 600, 400);
		renderer.DrawLine(200, 400, 600, 400);*/

		// show screen
		renderer.EndFrame();
	}

	return 0;
}