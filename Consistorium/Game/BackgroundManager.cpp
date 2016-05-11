#include "BackgroundManager.h"

#include <Game\Globals\Constants.h>
#include "GameUtils.h"
#include <Color.h>
#include "EventIds.h"
#include <EventManager.h>

BackgroundManager::BackgroundManager(GameEngine::IGraphicsRenderer *renderer)
	: renderer_(renderer),
	DAY_COLOR({ 52, 152, 219, 255 }),
	NIGHT_COLOR({ 44, 62, 80, 255 }),
	UNDERGROUND_COLOR({ 97, 63, 16, 255 })
{
	renderer_->SetRenderColor(DAY_COLOR);
}

void BackgroundManager::update(float dt, b2Vec2 playerPos)
{
	float yAxis = playerPos.y * Globals::BLOCK_HEIGHT;
	timeElapsed_ += dt;
	if (timeElapsed_ > 15000)
	{
		timeElapsed_ = 0;
		isDay_ = !isDay_;
		EventManager::get().signal(isDay_ ? ON_BECOME_DAY : ON_BECOME_NIGHT);
	}

	Color newColor;
	if (GameUtils::isInInterval(yAxis, Globals::GROUND_LAYER_HEIGHT_RANGE) ||
		GameUtils::isInInterval(yAxis, Globals::AIR_LAYER_HEIGHT_RANGE))
	{
		newColor = isDay_ ? BackgroundManager::DAY_COLOR : BackgroundManager::NIGHT_COLOR;
	}
	else if (GameUtils::isInInterval(yAxis, Globals::UNDERGROUND_LAYER_HEIGHT_RANGE))
	{
		newColor = BackgroundManager::UNDERGROUND_COLOR;
	}
	else
	{
		return;
	}

	renderer_->SetRenderColor(newColor);
}

bool BackgroundManager::isDay() { return isDay_; }

BackgroundManager::~BackgroundManager()
{
}
