#include "Event.h"

Event::Event(int id, std::function<void*(void*)> callback, std::function<void()> param)
	: id_(id),
	callback_(callback),
	param_(param)
{

}

Event::~Event()
{
}

int Event::getId() { return id_; }

void* Event::executeCallback(void* param) 
{
	if (param_)
	{
		return callback_((void*)&param_);
	}
	else if (param)
	{
		return callback_(param);
	}
	else
	{
		callback_(nullptr);
	}

	return nullptr;
}