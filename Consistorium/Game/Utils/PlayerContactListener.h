#pragma once

#include <Box2D\Box2D.h>
#include <GameEngine\EventManager.h>

class PlayerContactListener : public b2ContactListener
{
private:
	EventManager& eManager_;
public:
	PlayerContactListener(EventManager& eManager);
	~PlayerContactListener();

	void BeginContact(b2Contact* contact);

	void EndContact(b2Contact* contact);
};