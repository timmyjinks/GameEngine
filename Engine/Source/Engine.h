#pragma once
#include "Renderer.h"
#include "Vector2.h"

#include "ETime.h"

#include "Input.h"
#include "Audio.h"

#include "Random.h"
#include "MathUtils.h"

#include "Particle.h"
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

	Renderer& GetRenderer() { return *m_renderer; }
	Input& GetInput() { return *m_input; }
	Audio& GetAudio() { return *m_audio; }

private:
	Renderer* m_renderer{ nullptr };
	Input* m_input{ nullptr };
	Audio* m_audio{ nullptr };
};

extern Engine g_engine;
