#pragma once

#include <string>
#include <Box2D\Box2D.h>
#include <GameEngine\Entity.h>
#include <GameEngine\RenderComponent.h>

namespace UI
{
	//TODO: should contain logic for when the player accesses items
	class ItemSlot : public Entities::Entity
	{
	private:
		int itemCount_;
		std::pair<
			Entities::Entity*,
			GameEngine::RenderComponent*> item_;
	public:
		ItemSlot(b2Vec2 itemSize, b2Vec2 itemPos);

		std::pair<
			Entities::Entity*,
			GameEngine::RenderComponent*> getItem();

		bool isEmpty();

		void add(int count, Entities::Entity*, GameEngine::RenderComponent* rc);

		void remove(int count);

		void empty();

		void setTexture(std::string);

		~ItemSlot();
	};
}