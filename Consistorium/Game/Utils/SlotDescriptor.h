#pragma once

#include <string>
#include <GameEngine\Entity.h>
#include <GameEngine\IRenderable.h>

struct SlotDescriptor
{
	int index;
	Entities::Entity* entity;
	GameEngine::IRenderable* rc;
};