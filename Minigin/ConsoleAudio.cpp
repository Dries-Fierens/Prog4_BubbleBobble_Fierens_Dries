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
			int id = -1;

			std::unique_lock<std::mutex> lock(m_mutex);
			m_conditionVariable.wait(lock, [this] { return !m_queue.empty() || !m_running; });

			if (!m_running) break;

			id = m_queue.front();
			m_queue.pop();
			lock.unlock();

			if (id != -1)
			{
				Mix_VolumeChunk(m_pSounds.at(id), (MIX_MAX_VOLUME * 100) / 100);
				Mix_PlayChannel(1, m_pSounds.at(id), 0);
			}
		}
	}

	void PlaySound(const std::string& file)
	{
		// Thread safe addition
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			m_queue.push(LoadSound(file));
		}
		m_conditionVariable.notify_all();
	};

private:
	bool m_running;
	std::mutex m_mutex;
	std::condition_variable m_conditionVariable;
	std::queue<int> m_queue;
	std::vector<Mix_Chunk*> m_pSounds;
	std::thread m_thread;

	int LoadSound(const std::string& file)
	{
		auto sound{ Mix_LoadWAV(file.c_str()) };
		if (!sound) return -1;
		m_pSounds.push_back(sound);
		return int(m_pSounds.size()) - 1;
	};
};

ConsoleAudio::ConsoleAudio() : m_pImpl{ std::make_unique<ConsoleAudioImpl>() } {}

ConsoleAudio::~ConsoleAudio() {}

void ConsoleAudio::PlaySound(const std::string& file)
{
	m_pImpl->PlaySound(file);
}
