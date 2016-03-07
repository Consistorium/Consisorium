#pragma once

#include "../Interfaces/IPositionable.h"
#include "../Interfaces/IVisible.h"

class UIElement : public IPositionable,
	public IVisible
{
public:
	UIElement::UIElement(float x, float y, const char* modelName);
	~UIElement();
};