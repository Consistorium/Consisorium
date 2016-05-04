#pragma once

#include "IGraphicsRenderer.h"
#include <vector>
#include "GameEntity.h"

class EntityManager
{
private:
	b2World* world_;
	GameEngine::IGraphicsRenderer *renderer_;
	std::vector<Entities::GameEntity*>& entities_;

	bool clickedOnEntity(b2Vec2 clickPoint, b2Vec2 entityPosition, b2Vec2 entitySize);
public:
	EntityManager(b2World* world, GameEngine::IGraphicsRenderer *renderer, std::vector<Entities::GameEntity*>& entities);

	~EntityManager();

	Entities::GameEntity* getClickedEntity(b2Vec2 worldCoords, int *entityIndex);

	b2Vec2 getWorldCoordinates(SDL_Point clickPoint, b2Vec2 camera);

	b2World* getWorld();

	void addToWorld(Entities::GameEntity *e);

	void removeFromWorld(Entities::GameEntity *entity);

	void removeFromWorld(int index);
};

