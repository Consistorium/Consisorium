#pragma once

#include "IRenderable.h"

namespace GameEngine {
	class RenderComponent : public IRenderable
	{
	private:
		std::string *texturePath_;
		b2Vec2 scale_;
		b2Vec2 size_;
		b2Body *body_;
	public:
		RenderComponent(std::string texturePath, b2Vec2 scale, b2Vec2 size, b2Body *body);

		~RenderComponent();

		void setTextureName(std::string value);
		
		std::string* getTextureName() override;

		void setScale(b2Vec2 scale);

		b2Vec2 getScale(SDL_Rect textureSize) override;

		b2Vec2 getSize() override;

		b2Body* getBody();

		void setPosition(const b2Vec2& pos);

		b2Vec2 getPosition() override;
	};
}

