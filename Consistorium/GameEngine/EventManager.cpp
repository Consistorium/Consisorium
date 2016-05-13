#include "EventManager.h"


EventManager::EventManager()
{
}

void* callParameterless(void* p)
{
	auto func = (std::function<void()>*)(p);
	(*func)();
	return nullptr;
}

void EventManager::add(int id, std::function<void()> callback)
{
	Event e(id, callParameterless, callback);
	eventQueues_[id].push_back(std::make_unique<Event>(e));
}

void EventManager::addWithParams(int id, std::function<void*(void*)> callback)
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

void* EventManager::signal(int id, void* param)
{
	for (std::unique_ptr<Event>& e : eventQueues_[id])
	{
		return e->executeCallback(param);
	}
}

EventManager::~EventManager()
{
}
