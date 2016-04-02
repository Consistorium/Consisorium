#pragma once

#include "IRenderable.h"

namespace GameEngine {
	class RenderComponent : public GameEngine::IRenderable
	{
	private:
		std::string *texturePath_;
		b2Vec2 scale_;
		b2Vec2 position_;
	public:
		RenderComponent(std::string texturePath, b2Vec2 scale, b2Vec2 position);

		~RenderComponent();

		void RenderComponent::setTextureName(std::string value);
		
		std::string* getTextureName() override;

		void setScale(b2Vec2 scale);

		b2Vec2 getScale() override;

		void setPosition(b2Vec2 pos);

		b2Vec2 getPosition() override;
	};
}

