#pragma once

#include <list>
#include <map>
#include <memory>
#include "Event.h"

class EventManager
{
	std::map<int, std::list<std::unique_ptr<Event>>> eventQueues_;

	EventManager();

	~EventManager();
public:

	void add(int id, std::function<void()> callback);

	void addWithParams(int id, std::function<void*(void*)> callback);

	void signal(int id);

	void* signal(int id, void* param);

	static EventManager& get()
	{
		static EventManager INSTANCE;
		return INSTANCE;
	}
};

