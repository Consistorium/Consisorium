#pragma once

#include "Player.h"
#include "../../Interfaces/IPositionable.h"
#include "../../Interfaces/IMoveable.h"
#include "../../GameEngine/AnimationManager.h"
#include "../../Interfaces/IVisible.h"
#include "../../GameEngine/IRenderable.h"
#include "../../GameEngine/IAnimateable.h"
#include "Entity.h"
#include "../../GameEngine/TextureManager.h"
#include <memory>

class Player :
	public Entity,
	public IMoveable,
	public IPositionable,
	public GameEngine::IAnimateable,
	public GameEngine::IRenderable
{
private:
	std::string textureName_;
	GameEngine::AnimationManager animationManager_;
public:
	Player(GameEngine::Vector2D position, std::string animationName);

	~Player();

	void init(SDL_Renderer *renderer);

	void setFrameTexture(std::string path) override;

	std::string getTextureName() override;

	GameEngine::Vector2D getScreenPosition() override;

	std::string getAnimationsFolder() override;

	double getAnimationSpeed() override;

	GameEngine::Vector2D getScale() override;

	void die();
};

