#pragma once

#include "Player.h"
#include "../../Interfaces/IPositionable.h"
#include "../../Interfaces/IMoveable.h"
#include "../../Interfaces/IVisible.h"
#include "../../GameEngine/IRenderable.h"
#include "Entity.h"
#include "../../GameEngine/TextureManager.h"
#include <memory>

class Player :
	public Entity,
	public IMoveable,
	public IPositionable,
	public GameEngine::IRenderable
{
private:
	char *textureName_;
public:
	Player(GameEngine::Vector2D position, char *modelName);
	~Player();

	void init(SDL_Renderer *renderer);

	char* getTextureName() override;

	GameEngine::Vector2D getScreenPosition() override;
};

