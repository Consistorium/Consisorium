#pragma once

#include "IRenderable.h"

namespace GameEngine {
	class RenderComponent : public IRenderable
	{
	private:
		std::string *texturePath_;
		b2Vec2 scale_;
		b2Body *body_;
	public:
		RenderComponent(std::string texturePath, b2Vec2 scale, b2Body *body_);

		~RenderComponent();

		void setTextureName(std::string value);
		
		std::string* getTextureName() override;

		void setScale(b2Vec2 scale);

		b2Vec2 getScale() override;

		b2Body* getBody();

		void setPosition(const b2Vec2& pos);

		b2Vec2 getPosition() override;
	};
}

