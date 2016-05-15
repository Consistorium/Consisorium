#include "Player.h"

#include <iostream>
#include <Game\Globals\Constants.h>
#include <Game\Entities\EntityTypes.h>
#include <Game\EventIds.h>
#include <Game\Utils\Directions.h>

namespace Entities
{
	Player::Player(b2Body* body, GameEngine::RenderComponent* rc, GameEngine::AnimationComponent* ac, EventManager& eManager)
		: FluentEntity(body, rc, ac),
		actionbarSelected_(0)
	{
		footContacts_ = 0;
		setHealth(100);
		setRange(3);
		b2Vec2 playerSize = b2Vec2(
			getSize().x / Globals::PIXELS_PER_METER,
			getSize().y / Globals::PIXELS_PER_METER);

		b2PolygonShape polygonShape;
		b2FixtureDef sensorFixtureDef;
		sensorFixtureDef.isSensor = true;

		b2Vec2 sensorDim = b2Vec2(playerSize.x, 0.3);
		b2Vec2 sensorCentre(0, -playerSize.y / 2);
		polygonShape.SetAsBox(sensorDim.x, sensorDim.y, sensorCentre, 0);
		sensorFixtureDef.shape = &polygonShape;

		b2Fixture* footSensorFixture = getBody()->CreateFixture(&sensorFixtureDef);
		footSensorFixture->SetUserData((void*)EntityTypes::FootSensor);

		sensorDim = b2Vec2(0.1, playerSize.y / 2);
		sensorCentre = b2Vec2(playerSize.x / 2, 0);
		polygonShape.SetAsBox(sensorDim.x, sensorDim.y, sensorCentre, 0);
		sensorFixtureDef.shape = &polygonShape;

		footSensorFixture = getBody()->CreateFixture(&sensorFixtureDef);
		footSensorFixture->SetUserData((void*)EntityTypes::RightSensor);

		sensorCentre = b2Vec2(-playerSize.x / 2, 0);
		polygonShape.SetAsBox(sensorDim.x, sensorDim.y, sensorCentre, 0);
		sensorFixtureDef.shape = &polygonShape;

		footSensorFixture = getBody()->CreateFixture(&sensorFixtureDef);
		footSensorFixture->SetUserData((void*)EntityTypes::LeftSensor);

		eManager.addWithParams(
			ON_PLAYER_LAND_OR_JUMP, 
			[&](bool hasContact) {
				footContacts_ += hasContact ? 1 : -1;
				return nullptr;
			});

		eManager.addWithParams(
			ON_PLAYER_HIT_WALL,
			[&](void* arg) 
			{
				int dir = *(int*)(arg);
				if (dir == LEFT)
				{
					leftSensorContacts_++;
				}
				else
				{
					rightSensorContacts_++;
				}

				return nullptr;
			});

		eManager.addWithParams(
			ON_PLAYER_STOP_HITTING_WALL,
			[&](void* arg)
		{
			int dir = *(int*)(arg);
			if (dir == LEFT)
			{
				leftSensorContacts_--;
			}
			else
			{
				rightSensorContacts_--;
			}

			return nullptr;
		});
	}

	bool Player::rightSensorSensing()
	{
		return rightSensorContacts_ > 0;
	}

	bool Player::leftSensorSensing()
	{
		return leftSensorContacts_ > 0;
	}

	bool Player::canJump()
	{
		return footContacts_ > 0;
	}

	void Player::dig()
	{
	}

	int Player::addToActionbar(Entities::GameEntity* entity)
	{
		for (int i = 0; i < actionbar_.size(); i++)
		{
			auto rc = dynamic_cast<GameEngine::RenderComponent*>(entity->getRenderableComponent());
			if (actionbar_[i]->tryAdd(1, entity, rc))
			{
				return i;
			}
		}

		if (actionbar_.size() >= ACTIONBAR_SIZE)
		{
			return -1;
		}

		auto itemSlot = new Utils::ItemSlot(entity->getSize(), entity->getPosition(), 1);
		itemSlot->getItem().first->setType(entity->getType());
		itemSlot->getItem().second->setTextureName(*entity->getRenderableComponent()->getTextureName());

		actionbar_.push_back(std::shared_ptr<Utils::ItemSlot>(itemSlot));
		return actionbar_.size() - 1;
	}

	int Player::addToInventory(Entities::GameEntity* entity)
	{
		auto itemSlot = new Utils::ItemSlot(entity->getSize(), entity->getPosition());
		for (int i = 0; i < inventory_.size(); i++)
		{
			auto rc = dynamic_cast<GameEngine::RenderComponent*>(entity->getRenderableComponent());
			if (inventory_[i]->tryAdd(1, entity, rc))
			{
				return i;
			}
		}

		if (inventory_.size() >= INVENTORY_SIZE)
		{
			std::cout << "Inventory is full!" << std::endl;
			return -1;
		}

		inventory_.push_back(std::shared_ptr<Utils::ItemSlot>(itemSlot));
		return inventory_.size() - 1;
	}

	std::vector<std::shared_ptr<Utils::ItemSlot>> Player::getInventory()
	{
		return inventory_;
	}

	std::vector<std::shared_ptr<Utils::ItemSlot>> Player::getActionbar()
	{
		return actionbar_;
	}

	Player::~Player()
	{
		actionbar_.clear();
	}
}