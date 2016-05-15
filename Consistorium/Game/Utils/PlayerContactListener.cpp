#include "../Entities/EntityTypes.h"

#include "PlayerContactListener.h"
#include <Game\EventIds.h>
#include "Directions.h"

EntityTypes lastSensor;

PlayerContactListener::PlayerContactListener(EventManager& eManager)
	:eManager_(eManager)
{
}

bool hasLandedOrJumped(b2Fixture* fixtureA, b2Fixture* fixtureB)
{
	if (((int)fixtureA->GetUserData() == (int)EntityTypes::FootSensor && !fixtureB->IsSensor()) ||
		((int)fixtureB->GetUserData() == (int)EntityTypes::FootSensor && !fixtureA->IsSensor()))
	{
		return true;
	}

	return false;
}

int hasHitAWall(b2Fixture* fixtureA, b2Fixture* fixtureB)
{
	if (((int)fixtureA->GetUserData() == (int)EntityTypes::LeftSensor && !fixtureB->IsSensor()) ||
		((int)fixtureB->GetUserData() == (int)EntityTypes::LeftSensor && !fixtureA->IsSensor()))
	{
		return -1;
	}
	else if (((int)fixtureA->GetUserData() == (int)EntityTypes::RightSensor && !fixtureB->IsSensor()) ||
		((int)fixtureB->GetUserData() == (int)EntityTypes::RightSensor && !fixtureA->IsSensor()))
	{
		return 1;
	}

	return 0;
}

void PlayerContactListener::EndContact(b2Contact* contact) 
{
	//checks if each fixture is the player foot sensor
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	if (hasLandedOrJumped(fixtureA, fixtureB))
	{
		eManager_.signal(ON_PLAYER_LAND_OR_JUMP, (void*)false);
	}
	else
	{
		/*int wallHitDir = hasHitAWall(fixtureA, fixtureB);
		if (wallHitDir != 0)
		{
			eManager_.signal(ON_PLAYER_HIT_WALL, (void*)(Directions)wallHitDir);
		}*/
	}
}

void PlayerContactListener::BeginContact(b2Contact* contact) 
{
	//checks if each fixture is the player foot sensor
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	if (hasLandedOrJumped(fixtureA, fixtureB))
	{
		eManager_.signal(ON_PLAYER_LAND_OR_JUMP, (void*)true);
	}
	else
	{
		int wallHitDir = hasHitAWall(fixtureA, fixtureB);
		if (wallHitDir != 0)
		{
			eManager_.signal(ON_PLAYER_STOP_HITTING_WALL, &wallHitDir);
		}
	}	
}

PlayerContactListener::~PlayerContactListener()
{
}