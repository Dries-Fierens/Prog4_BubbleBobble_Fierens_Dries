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
		// Thread safe cleanup
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			m_running = false;
		}
		m_conditionVariable.notify_all();

		m_thread.join();

		for (auto sound : m_pSounds) {
			Mix_FreeChunk(sound);
		}
		Mix_Quit();
	};

	ConsoleAudioImpl(const ConsoleAudioImpl& other) = delete;
	ConsoleAudioImpl operator=(const ConsoleAudioImpl& rhs) = delete;
	ConsoleAudioImpl(ConsoleAudioImpl&& other) = delete;
	ConsoleAudioImpl operator=(ConsoleAudioImpl&& rhs) = delete;

	void Initialize() 
	{
		Mix_Init(MIX_INIT_MP3);
		SDL_Init(SDL_INIT_AUDIO);
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
			std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;

		m_thread = std::thread(&ConsoleAudioImpl::Update, this);
	};

	void Update()
	{
		while (m_running)
		{
			std::unique_lock<std::mutex> lock(m_mutex);
			m_conditionVariable.wait(lock, [this] { return !m_queue.empty() || !m_running; });

			if (!m_running) break;

			SoundEvent e = m_queue.front();
			m_queue.pop();
			lock.unlock();

			if (e.isMusic)
			{
				if (Mix_PlayingMusic() == 0)
				{
					Mix_VolumeMusic((MIX_MAX_VOLUME * e.volume) / 100);
					Mix_PlayMusic(m_pMusic[e.id], e.loops);
				}
			}
			else 
			{
				Mix_VolumeChunk(m_pSounds[e.id], (MIX_MAX_VOLUME * e.volume) / 100);
				Mix_PlayChannel(1, m_pSounds[e.id], e.loops);
			}
		}
	}

	void PlaySound(const std::string& file, int volume, int loops)
	{
		// Thread safe addition
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			m_queue.push(SoundEvent{ LoadSound(file), volume, false, loops});
		}
		m_conditionVariable.notify_all();
	};	
	
	void PlayMusic(const std::string& file, int volume, int loops)
	{
		// Thread safe addition
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			m_queue.push(SoundEvent{ LoadMusic(file), volume, true, loops });
		}
		m_conditionVariable.notify_all();
	};

	void PauseMusic(bool isPaused)
	{
		if (bool(Mix_PausedMusic()) != isPaused)
		{
			if (isPaused)
			{
				Mix_PauseMusic();
			}
			else
			{
				Mix_ResumeMusic();
			}
		}
	}

	void MuteSound(bool isMuted)
	{
		if (isMuted)
		{
			Mix_Volume(-1, 0);
			Mix_VolumeMusic(0);
		}
		else
		{
			Mix_Volume(-1, MIX_MAX_VOLUME);
			Mix_VolumeMusic(MIX_MAX_VOLUME);
		}
	}

private:
	struct SoundEvent
	{
		int id;
		int volume;
		bool isMusic;
		int loops;
	};

	bool m_running;
	std::mutex m_mutex;
	std::condition_variable m_conditionVariable;
	std::queue<SoundEvent> m_queue;
	std::vector<Mix_Chunk*> m_pSounds;
	std::vector<Mix_Music*> m_pMusic;
	std::thread m_thread;

	int LoadSound(const std::string& file)
	{
		auto sound{ Mix_LoadWAV(file.c_str()) };
		if (!sound) return -1;
		m_pSounds.push_back(sound);

		return int(m_pSounds.size()) - 1;
	};

	int LoadMusic(const std::string& file)
	{
		auto sound{ Mix_LoadMUS(file.c_str()) };
		if (!sound) return -1;
		m_pMusic.push_back(sound);
		return int(m_pMusic.size()) - 1;
	};
};

ConsoleAudio::ConsoleAudio() : m_pImpl{ std::make_unique<ConsoleAudioImpl>() } {}

ConsoleAudio::~ConsoleAudio() {}

void ConsoleAudio::PlaySound(const std::string& file, int volume, int loops)
{
	m_pImpl->PlaySound(file, volume, loops);
}

void ConsoleAudio::PlayMusic(const std::string& file, int volume, int loops)
{
	m_pImpl->PlayMusic(file, volume, loops);
}

void ConsoleAudio::PauseMusic(bool isPaused)
{
	m_pImpl->PauseMusic(isPaused);
}

void ConsoleAudio::MuteSound(bool isMuted)
{
	m_pImpl->MuteSound(isMuted);
}
