#include "Player.h"

#include <iostream>
#include "../EventIds.h"
#include "EventManager.h"

namespace Entities
{
	Player::Player(b2Body* body, GameEngine::RenderComponent* rc, GameEngine::AnimationComponent* ac)
		: FluentEntity(body, rc, ac)// doesnt work with constants wtf
	{
		setHealth(100);
	}

	void Player::dig()
	{
	}

	bool Player::addToActionbar(Entities::GameEntity* entity)
	{
		if (actionbar_.size() >= ACTIONBAR_SIZE)
		{
			return addToInventory(entity);
		}

		actionbar_.push_back(std::shared_ptr<Entities::GameEntity>(entity));
		return true;
	}

	bool Player::addToInventory(Entities::GameEntity* entity)
	{
		if (inventory_.size() >= INVENTORY_SIZE * 100)
		{
			std::cout << "Inventory is full!" << std::endl;
			return false;
		}

		inventory_.push_back(std::shared_ptr<Entities::GameEntity>(entity));
		return true;
	}

	std::vector<std::shared_ptr<Entities::GameEntity>> Player::getInventory()
	{
		return inventory_;
	}

	std::vector<std::shared_ptr<Entities::GameEntity>> Player::getActionbar()
	{
		return actionbar_;
	}

	Player::~Player()
	{
		actionbar_.clear();
	}
}