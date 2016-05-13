#pragma once

#include <functional>

class Event
{
	int id_;
	std::function<void*(void*)> callback_;
	std::function<void()> param_;
public:
	Event(int id, std::function<void*(void*)> callback, std::function<void()> param = nullptr);

	~Event();

	int getId();

	void* executeCallback(void* param = nullptr);
};