#include "RenderComponent.h"

namespace GameEngine {
	RenderComponent::RenderComponent(std::string texturePath, b2Vec2 scale, b2Vec2 position)
		: texturePath_(new std::string(texturePath)),
		scale_(scale),
		position_(position)
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
	
	void RenderComponent::setScale(b2Vec2 scale)
	{
		scale_ = scale;
	}

	b2Vec2 RenderComponent::getScale()
	{
		return this->scale_;
	}

	void RenderComponent::setPosition(b2Vec2 pos)
	{
		this->position_ = pos;
	}

	b2Vec2 RenderComponent::getPosition()
	{
		return this->position_;
	}
}