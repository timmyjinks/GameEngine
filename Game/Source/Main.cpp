#include <SDL.h>
#include <iostream>

int main(int argc, char* argv[])
{
	// initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
		return 1;
	}

	// create window
	// returns pointer to window if successful or nullptr if failed
	SDL_Window* window = SDL_CreateWindow("Game Engine",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		800, 600,
		SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		std::cerr << "Error creating SDL window: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	// create renderer
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	int numberOfLines = 1024;
	while (true)
	{
		//clear screen
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);

		// draw line

		for (int i = 0; i < 500; i++) {
			SDL_SetRenderDrawColor(renderer, rand() % 256, rand() % 256, rand() % 256, 0);
			SDL_RenderDrawLine(renderer, rand() % 999, rand() % 999, rand() % 999, rand() % 999);
		}

		// draw triangle
	/*	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
		SDL_RenderDrawLine(renderer, 400, 200, 200, 400);
		SDL_RenderDrawLine(renderer, 400, 200, 600, 400);
		SDL_RenderDrawLine(renderer, 200, 400, 600, 400);*/

		// show screen
		SDL_RenderPresent(renderer);
	}

	return 0;
}