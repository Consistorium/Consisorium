#pragma once

#include <string>
#include <Box2D/Common/b2Math.h>
#include "Color.h"
namespace Globals
{
	const int DAY_DURATION = 15 * 1000;

	const int PIXELS_PER_METER = 50;
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 768;
	const std::string MODELS_LOCATION = "Models/Game/";
	/*
	 * ENTITY CONSTANTS
		-- haste = attacks per second
	 */

	const float ENTITY_HEALTH = 100;
	const float DEFAULT_ENTITY_WIDTH = 28;
	const float DEFAULT_ENTITY_HEIGHT = 55;
	const float BLOCK_WIDTH = 31; // plEase do not make this int because THE FUCKIGN WORLD WONT GENERATE!!11
	const float BLOCK_HEIGHT = 31;
	const int TREE_WIDTH = 120;
	const int TREE_HEIGHT = 200;
	const int BUSH_WIDTH = 70;
	const int BUSH_HEIGHT = 100;
	const float ENTITY_JUMP_POWER = 0.2;
	const float SKELETON_SCAN_RANGE = 5.0;
	const float SKELETON_DAMAGE = 5;
	const float SKELETON_RANGE = 1.5;
	const float SKELETON_HASTE = 0.3;
	const float INITIAL_PLAYER_HEALTH = 100;
	const int UI_Z_INDEX = 100;
	/*
	 * World Generation
	 */

	// Y-axis - inclusive values

	const b2Vec2 AIR_LAYER_HEIGHT_RANGE(50 * BLOCK_HEIGHT, 2 * BLOCK_HEIGHT);
	const b2Vec2 GROUND_LAYER_HEIGHT_RANGE(1 * BLOCK_HEIGHT, 1 * BLOCK_HEIGHT);
	const b2Vec2 UNDERGROUND_LAYER_HEIGHT_RANGE(0, -50 * BLOCK_HEIGHT);
	const b2Vec2 RUIN_LAYER_HEIGHT_RANGE(-51 * BLOCK_HEIGHT, -90 * BLOCK_HEIGHT);
	const b2Vec2 HELL_LAYER_HEIGHT_RANGE(-91 * BLOCK_HEIGHT, -120 * BLOCK_HEIGHT);
	const b2Vec2 PURGATORY_LAYER_HEIGHT_RANGE(-121 * BLOCK_HEIGHT, -150 * BLOCK_HEIGHT);

	const float TOTAL_LAYER_HEIGHT = AIR_LAYER_HEIGHT_RANGE.x - PURGATORY_LAYER_HEIGHT_RANGE.x + 2 * BLOCK_HEIGHT;

	// X-axis - inclusive values

	const int LAYER_WIDTH_IN_BLOCKS = 200 * BLOCK_WIDTH;
}