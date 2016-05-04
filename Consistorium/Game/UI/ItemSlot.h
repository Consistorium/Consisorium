#pragma once

#include <string>
#include <Box2D\Box2D.h>
#include <GameEngine\Entity.h>

namespace UI
{
	//TODO: should contain logic for when the player accesses items
	class ItemSlot : public Entities::Entity
	{
	private:
		int itemCount_;
		std::string itemTexture_;
		b2Vec2 position_;
	public:
		ItemSlot(b2Vec2 position);

		bool isEmpty();

		void add(int count, std::string itemTexture);

		void remove(int count);

		void empty();

		std::string getItemTexture();

		void setTexture(std::string texture);

		~ItemSlot();

		b2Vec2 getPosition();
	};
}