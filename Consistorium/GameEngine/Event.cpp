#include "Event.h"

Event::Event(int id, std::function<void()> callback)
	: id_(id),
	callback_(callback)
{
}


Event::~Event()
{
}

int Event::getId() { return id_; }

void Event::executeCallback() { callback_(); }