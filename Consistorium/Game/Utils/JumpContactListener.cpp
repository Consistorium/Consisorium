#include "../Entities/EntityTypes.h"

#include "JumpContactListener.h"

EntityTypes lastSensor;

JumpContactListener::JumpContactListener()
{
	footContactsCount_ = 0;
}

void JumpContactListener::EndContact(b2Contact* contact) {
	//checks if each fixture is the player foot sensor
	void* fixtureAUserData = contact->GetFixtureA()->GetUserData();
	void* fixtureBUserData = contact->GetFixtureB()->GetUserData();
	if ((int)fixtureAUserData == (int)EntityTypes::FootSensor ||
		(int)fixtureBUserData == (int)EntityTypes::FootSensor)
	{
		footContactsCount_--;
	}
}

void JumpContactListener::BeginContact(b2Contact* contact) {
	//checks if each fixture is the player foot sensor
	void* fixtureAUserData = contact->GetFixtureA()->GetUserData();
	void* fixtureBUserData = contact->GetFixtureB()->GetUserData();
	if ((int)fixtureAUserData == (int)EntityTypes::FootSensor ||
		(int)fixtureBUserData == (int)EntityTypes::FootSensor )
	{
		footContactsCount_++;
	}
}

int JumpContactListener::getContactsCount()
{
	return footContactsCount_;
}

JumpContactListener::~JumpContactListener()
{
}