#include "Engine.h"

Engine g_engine;

bool Engine::Initialize()
{
	m_renderer = std::make_unique<Renderer>();
	m_input = std::make_unique<Input>();
	m_audio = std::make_unique<Audio>();

	m_renderer->Initialize();
	m_renderer->CreateWindow("Game Engine", 800, 600);
	m_input->Initialize();
	m_audio->Initialize();

	m_time = std::make_unique<Time>();

	m_particleSystem = std::make_unique<ParticleSystem>(10000);

	return true;
}

void Engine::Shutdown()
{
	m_renderer->Shutdown();
	m_input->Shutdown();
	m_audio->Shutdown();
}

void Engine::Update()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT) {
			m_quit = true;
		}

		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
			m_quit = true;
		}
	}

	m_time->Tick();

	m_input->Update();
	m_audio->Update();
	m_particleSystem->Update(m_time->GetDeltaTime());
}
