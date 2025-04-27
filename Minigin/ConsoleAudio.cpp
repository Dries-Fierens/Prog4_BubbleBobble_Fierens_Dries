#include "ConsoleAudio.h"
#include <iostream>

ConsoleAudio::ConsoleAudio() : m_running(true)
{
	Initialize();
}

void ConsoleAudio::Initialize()
{
	int flags = MIX_INIT_MP3;
	int result = Mix_Init(flags);

	if ((result & flags) != flags) {
		printf("Mix_Init: %s\n", Mix_GetError());
	}
	if (SDL_Init(SDL_INIT_AUDIO) == -1) {
		printf("SDL_Init: %s\n", SDL_GetError());
		exit(1);
	}
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
		printf("Mix_OpenAudio: %s\n", Mix_GetError());
		exit(2);
	}

	MIX_CHANNELS;
}

void ConsoleAudio::Update()
{
	while (m_running)
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		m_conditionVariable.wait(lock);

		while (!m_queue.empty() && m_running)
		{
			int id = m_queue.front();
			m_queue.pop();
			Mix_PlayChannel(-1, m_pSounds.at(id), 0);
		}
	}

	std::cout << "Audio Update Closed" << std::endl;
}

void ConsoleAudio::PlaySound(int soundID)
{
	std::lock_guard<std::mutex> lock(m_mutex);
	m_queue.push(soundID);
	m_conditionVariable.notify_one();
}

void ConsoleAudio::StopSound(int soundID = -1)
{
	Mix_HaltChannel(soundID);
}

void ConsoleAudio::StopAllSounds()
{
	Mix_CloseAudio();

	m_running = false;
	m_conditionVariable.notify_one();
}

int ConsoleAudio::LoadSound(const char* file)
{
	auto sound{ Mix_LoadWAV(file) };
	m_pSounds.push_back(sound);
	return int(m_pSounds.size()) - 1;
}
