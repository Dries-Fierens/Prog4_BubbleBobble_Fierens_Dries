#pragma once
#include "Singleton.h"
#include <queue>
#include <string>

struct Event
{
	std::string name{};
};

class EventListener
{
public:
	EventListener();
	virtual ~EventListener() = default;
	EventListener(const EventListener&) = delete;
	EventListener(EventListener&&) = delete;
	EventListener& operator= (const EventListener&) = delete;
	EventListener& operator= (const EventListener&&) = delete;

	virtual void OnEvent(const Event& event) = 0;

	int GetId() const { return m_Id; }

private:
	int m_Id{};
	static int m_IdCounter;
};

namespace dae
{
	class EventQueue final : public Singleton<EventQueue>
	{
	public:
		void SendEvent(const Event& event);
		void NotifyListeners();
		void AddListener(EventListener* listener);
		void RemoveListener(int listenerId);

	private:
		std::queue<Event> m_eventQueue{};
		std::vector<EventListener*> m_listeners;

		bool PollEvent(Event& e);
	};
}

