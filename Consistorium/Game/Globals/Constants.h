#include <Box2D/Common/b2Math.h>

namespace Globals
{
	const int PIXELS_PER_METER = 50;
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 768;
	/*
	 * ENTITY CONSTANTS
	 */

	const float DEFAULT_ENTITY_WIDTH = 40;
	const float DEFAULT_ENTITY_HEIGHT = 80;
	const float BLOCK_WIDTH = 31;
	const float BLOCK_HEIGHT = 31;
	const int TREE_WIDTH = 120;
	const int TREE_HEIGHT = 200;
	const float ENTITY_JUMP_POWER = 0.2;

	/*
	 * World Generation
	 */

	// Y-axis - inclusive values

	const b2Vec2 AIR_LAYER_HEIGHT_RANGE(50 * BLOCK_HEIGHT, 2 * BLOCK_HEIGHT);
	const b2Vec2 GROUND_LAYER_HEIGHT_RANGE(1 * BLOCK_HEIGHT, 1 * BLOCK_HEIGHT);
	const b2Vec2 UNDERGROUND_LAYER_HEIGHT_RANGE(0, -25 * BLOCK_HEIGHT);

	// X-axis - inclusive values

	const int LAYER_WIDTH_IN_BLOCKS = 100 * BLOCK_WIDTH;
}