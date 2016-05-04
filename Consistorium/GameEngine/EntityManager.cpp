#include "EntityManager.h"
#include "../Game/Globals/Constants.h"

EntityManager::EntityManager(b2World* world, GameEngine::IGraphicsRenderer* renderer, std::vector<Entities::GameEntity*>& entities)
	: world_(world),
	renderer_(renderer),
	entities_(entities)
{

}

EntityManager::~EntityManager()
{

}

bool EntityManager::clickedOnEntity(b2Vec2 clickPoint, b2Vec2 entityPosition, b2Vec2 entitySize)
{
	if ((clickPoint.x > entityPosition.x - entitySize.x / 2)
		&& (clickPoint.x < entityPosition.x + entitySize.x / 2))
	{
		if ((clickPoint.y < entityPosition.y + entitySize.y / 2)
			&& (clickPoint.y > entityPosition.y - entitySize.y / 2))
		{
			return true;
		}
	}

	return false;
}

Entities::GameEntity* EntityManager::getClickedEntity(b2Vec2 worldCoords, int* entityIndex)
{
	for (int i = entities_.size() - 1; i >= 0; i--)
	{
		b2Vec2 entitySize = entities_[i]->getSize();
		entitySize.x /= Globals::PIXELS_PER_METER;
		entitySize.y /= Globals::PIXELS_PER_METER;

		b2Vec2 entityCoords = entities_[i]->getPosition();
		if (clickedOnEntity(worldCoords, entityCoords, entitySize))
		{
			*entityIndex = i;
			return entities_[i];
		}
	}

	return nullptr;
}

b2Vec2 EntityManager::getWorldCoordinates(SDL_Point clickPoint, b2Vec2 camera)
{
	float clickHeight = Globals::SCREEN_HEIGHT - clickPoint.y;
	float renderingHeight = 4;
	b2Vec2 worldCoords;
	worldCoords.x = (camera.x + clickPoint.x) / Globals::PIXELS_PER_METER;
	worldCoords.y = (camera.y + clickHeight) / Globals::PIXELS_PER_METER - renderingHeight;

	return worldCoords;
}

b2World* EntityManager::getWorld()
{
	return world_;
}

void EntityManager::addToWorld(Entities::GameEntity* e)
{
	renderer_->AddRenderable(e->getRenderableComponent());
	entities_.push_back(e);
}

void EntityManager::removeFromWorld(Entities::GameEntity* entity)
{
	renderer_->RemoveRenderable(entity->getRenderableComponent());
	world_->DestroyBody(entity->getBody());
	entities_.erase(std::remove(entities_.begin(), entities_.end(), entity));
}

void EntityManager::removeFromWorld(int index)
{
	renderer_->RemoveRenderable(entities_[index]->getRenderableComponent());
	world_->DestroyBody(entities_[index]->getBody());
	entities_.erase(entities_.begin() + index);
}
