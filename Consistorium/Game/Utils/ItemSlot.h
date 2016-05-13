#pragma once

#include <string>
#include <Box2D\Box2D.h>
#include <GameEngine\Entity.h>
#include <GameEngine\RenderComponent.h>

namespace Utils
{
	//TODO: should contain logic for when the player accesses items
	class ItemSlot : public Entities::Entity
	{
	private:
		const int MAX_ITEM_COUNT = 10;
		int itemCount_,
			maxItemCount_;
		std::pair<
			Entities::Entity*,
			GameEngine::RenderComponent*> item_;
	public:
		ItemSlot(b2Vec2 itemSize, b2Vec2 itemPos, int count = 0);

		std::pair<
			Entities::Entity*,
			GameEngine::RenderComponent*> getItem();

		bool isEmpty();

		bool tryAdd(int count, Entities::Entity*, GameEngine::IRenderable* rc);

		void remove(int count);

		void empty();

		void setTexture(std::string);

		~ItemSlot();
	};
}