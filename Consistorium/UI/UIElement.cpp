#include "UIElement.h"

UIElement::UIElement(float x, float y, const char* modelName)
	:IPositionable(x, y),
	IVisible(modelName, x, y)
{
}

UIElement::~UIElement()
{
}
