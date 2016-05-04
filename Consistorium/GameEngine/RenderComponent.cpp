#include "RenderComponent.h"

namespace GameEngine {
	RenderComponent::RenderComponent(std::string texturePath, b2Vec2 size, Entities::Entity* entity)
		: texturePath_(new std::string(texturePath)),
		size_(size),
		entity_(entity)
	{
	}


	RenderComponent::~RenderComponent()
	{
	}

	void RenderComponent::setTextureName(std::string value)
	{
		*texturePath_ = value;
	}

	std::string* RenderComponent::getTextureName()
	{
		return texturePath_;
	}

	b2Vec2 RenderComponent::getScale(SDL_Rect textureSize)
	{
		return b2Vec2(size_.x / textureSize.w, size_.y / textureSize.h);
	}

	void RenderComponent::setPosition(const b2Vec2& pos)
	{
		//this->position_ = pos;
	}

	b2Vec2 RenderComponent::getSize()
	{
		return size_;
	}

	void RenderComponent::forEntity(Entities::Entity* entity)
	{
		entity_ = entity;
	}

	b2Vec2 RenderComponent::getPosition()
	{
		if (entity_ == nullptr || !entity_ || entity_ == NULL)
		{
			throw std::invalid_argument("Invalid entity pointer. \"getPosition\" should be used on a specific entity. Did you forget to call \"forEntity()\"?");
		}

		return entity_->getPosition();
	}

	void RenderComponent::setAlwaysRender(bool value)
	{
		alwaysRender_ = value;
	}

	bool RenderComponent::alwaysRender()
	{
		return alwaysRender_;
	}

	int RenderComponent::getZIndex() { return zIndex_; }
}