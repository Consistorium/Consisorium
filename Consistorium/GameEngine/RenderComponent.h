#pragma once

#include "IRenderable.h"
#include "Entity.h"

namespace GameEngine {
	class RenderComponent : public IRenderable
	{
	private:
		std::string *texturePath_;
		b2Vec2 scale_;
		b2Vec2 size_;
		Entities::Entity* entity_;
		bool alwaysRender_;
		int zIndex_;
	public:
		RenderComponent(std::string texturePath, b2Vec2 size, Entities::Entity* entity, bool alwaysRender);

		~RenderComponent();

		void setTextureName(std::string value);

		std::string* getTextureName() override;

		b2Vec2 getScale(SDL_Rect textureSize) override;

		void setScale(b2Vec2) override;

		b2Vec2 getSize() override;

		void setPosition(const b2Vec2& pos);
		
		int getId() override;

		b2Vec2 getPosition() override;

		int getOrientation() override;

		void forEntity(Entities::Entity* entity);

		bool alwaysRender();

		void RenderComponent::setAlwaysRender(bool value);

		int getZIndex();
	};
}

