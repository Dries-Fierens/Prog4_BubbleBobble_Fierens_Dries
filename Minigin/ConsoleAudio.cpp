#include "ConsoleAudio.h"
#include <SDL_mixer.h>
#include <SDL.h>

class ConsoleAudio::ConsoleAudioImpl final
{
public:
	ConsoleAudioImpl() : m_running(true) 
	{
		Initialize();
	}

	~ConsoleAudioImpl() 
	{
		for (auto sound : m_pSounds) {
			Mix_FreeChunk(sound);
		}
	};

	void Initialize() 
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
	};

	void Update()
	{
		while (m_running)
		{
			int id = -1;
			{
				std::unique_lock<std::mutex> lock(m_mutex);
				m_conditionVariable.wait(lock, [this] { return !m_queue.empty() || !m_running; });

				if (!m_running) break;
				if (!m_queue.empty())
				{
					id = m_queue.front();
					m_queue.pop();
				}
			}

			if (id != -1)
			{
				Mix_PlayChannel(-1, m_pSounds.at(id), 0);
			}
		}
	}

	int LoadSound(const char* file) 
	{
		auto sound{ Mix_LoadWAV(file) };
		m_pSounds.push_back(sound);
		return int(m_pSounds.size()) - 1;
	};

	void PlaySound(int soundID) 
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		m_queue.push(soundID);
		m_conditionVariable.notify_all();
	};

	void StopSound(int soundID = -1)
	{
		Mix_HaltChannel(soundID);
	};

	void StopAllSounds() 
	{
		Mix_CloseAudio();

		m_running = false;
		m_conditionVariable.notify_all();
	};

private:
	bool m_running;
	std::mutex m_mutex;
	std::condition_variable m_conditionVariable;
	std::queue<int> m_queue;
	std::vector<Mix_Chunk*> m_pSounds;
};

ConsoleAudio::ConsoleAudio() : m_pImpl{ std::make_unique<ConsoleAudioImpl>() } {}

ConsoleAudio::~ConsoleAudio()
{
}

void ConsoleAudio::Update()
{
	m_pImpl->Update();
}

void ConsoleAudio::PlaySound(int soundID)
{
	m_pImpl->PlaySound(soundID);
}

void ConsoleAudio::StopSound(int soundID = -1)
{
	m_pImpl->StopSound(soundID);
}

void ConsoleAudio::StopAllSounds()
{
	m_pImpl->StopAllSounds();
}

int ConsoleAudio::LoadSound(const char* file)
{
	return m_pImpl->LoadSound(file);
}
