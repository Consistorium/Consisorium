#pragma once

#include <functional>

class Event
{
	int id_;
	std::function<void()> callback_;
public:
	Event(int id, std::function<void()> callback);

	~Event();

	int getId();

	void executeCallback();
};