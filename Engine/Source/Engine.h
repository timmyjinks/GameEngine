#pragma once
#include "Renderer.h"
#include "Input.h"
#include "Audio.h"

#include "ETime.h"

#include "Vector2.h"
#include "Random.h"
#include "MathUtils.h"

#include "Transform.h"
#include "ParticleSystem.h"
#include "Particle.h"
#include "Model.h"

#include <fmod.hpp>
#include <SDL.h>

class Engine {
public:
	Engine() = default;
	~Engine() = default;

	bool Initialize();
	void Shutdown();

	void Update();

	Time& GetTime() { return *m_time; }
	Renderer& GetRenderer() { return *m_renderer; }
	Input& GetInput() { return *m_input; }
	Audio& GetAudio() { return *m_audio; }
	ParticleSystem& GetParticleSystem() { return *m_particleSystem; }

	bool IsQuit() { return m_quit; }

private:
	bool m_quit{ false };
	std::unique_ptr<Time> m_time;
	std::unique_ptr<Renderer> m_renderer;
	std::unique_ptr<Input> m_input;
	std::unique_ptr<Audio> m_audio;
	std::unique_ptr<ParticleSystem> m_particleSystem;
};

extern Engine g_engine;
