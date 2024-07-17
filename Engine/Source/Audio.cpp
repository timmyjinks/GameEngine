#include "Audio.h"
#include <string>
#include <iostream>

bool Audio::Initialize()
{
	FMOD::System_Create(&m_audio);

	void* extradriverdata = nullptr;
	m_audio->init(32, FMOD_INIT_NORMAL, extradriverdata);

	return true;
}

void Audio::Shutdown()
{
	m_audio->close();
}

void Audio::Update()
{
	m_audio->update();
}

bool Audio::AddSound(const std::string& name)
{
	m_audio->createSound(name.c_str(), FMOD_DEFAULT, 0, &m_sound);

	if (m_sound == nullptr) {
		std::cerr << "Could not load sound: " << name << std::endl;
		return false;
	}
	m_sounds[name] = m_sound;
}

bool Audio::PlaySound(const std::string& name)
{
	if (m_sounds.find(name) == m_sounds.end()) {
		if (!AddSound(name)) return false;
	}

	m_audio->playSound(m_sounds[name], 0, false, nullptr);

	return true;
}


