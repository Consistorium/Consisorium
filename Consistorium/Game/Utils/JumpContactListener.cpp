#include "../Entities/EntityIndexesEnum.h"

#include "JumpContactListener.h"

JumpContactListener::JumpContactListener()
{
	footContactsCount_ = 0;
}

void JumpContactListener::EndContact(b2Contact* contact) {
	//checks if each fixture is the player foot sensor
	void* fixtureAUserData = contact->GetFixtureA()->GetUserData();
	void* fixtureBUserData = contact->GetFixtureB()->GetUserData();
	if (((int)fixtureAUserData == (int)EntityIndexes::FootSensor && (int)fixtureBUserData != (int)EntityIndexes::PlayerParts)
		|| ((int)fixtureBUserData == (int)EntityIndexes::FootSensor && (int)fixtureAUserData != (int)EntityIndexes::PlayerParts))
	{
		footContactsCount_--;
	}
}

void JumpContactListener::BeginContact(b2Contact* contact) {
	//checks if each fixture is the player foot sensor
	void* fixtureAUserData = contact->GetFixtureA()->GetUserData();
	void* fixtureBUserData = contact->GetFixtureB()->GetUserData();
	if (((int)fixtureAUserData == (int)EntityIndexes::FootSensor && (int)fixtureBUserData != (int)EntityIndexes::PlayerParts)
		|| ((int)fixtureBUserData == (int)EntityIndexes::FootSensor && (int)fixtureAUserData != (int)EntityIndexes::PlayerParts))
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