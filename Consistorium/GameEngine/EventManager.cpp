#include "EventManager.h"


EventManager::EventManager()
{
}

void EventManager::add(int id, std::function<void()> callback)
{
	Event e(id, callback);
	eventQueues_[id].push_back(std::make_unique<Event>(e));
}

void EventManager::signal(int id)
{
	for (std::unique_ptr<Event>& e : eventQueues_[id])
	{
		e->executeCallback();
	}
}

EventManager::~EventManager()
{
}
