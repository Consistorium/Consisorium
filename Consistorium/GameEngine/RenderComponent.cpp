#include "RenderComponent.h"

namespace GameEngine {
	RenderComponent::RenderComponent(std::string texturePath, b2Vec2 scale, b2Body *body)
		: texturePath_(new std::string(texturePath)),
		scale_(scale),
		body_(body)
	{
	}


	RenderComponent::~RenderComponent()
	{
	}

	void RenderComponent::setTextureName(std::string value)
	{
		*texturePath_ = value;
	}

	b2Body* RenderComponent::getBody()
	{
		return body_;
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

	void RenderComponent::setPosition(const b2Vec2& pos)
	{
		//this->position_ = pos;
	}

	b2Vec2 RenderComponent::getPosition()
	{
		return this->body_->GetPosition();
	}
}