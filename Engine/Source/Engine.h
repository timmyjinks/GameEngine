#pragma once
#include "Renderer.h"
#include "Vector2.h"

#include "ETime.h"

#include "Input.h"
#include "Audio.h"

#include "Random.h"
#include "MathUtils.h"

#include "Particle.h"
#include "ParticleSystem.h"
#include "Model.h"
#include "Transform.h"

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
	Time* m_time{ nullptr };

	Renderer* m_renderer{ nullptr };
	Input* m_input{ nullptr };
	Audio* m_audio{ nullptr };

	std::unique_ptr<ParticleSystem> m_particleSystem;
};

extern Engine g_engine;
