#include "UIElement.h"

UIElement::UIElement(float x, float y, const char* modelName)
	:IPositionable(x, y),
	IVisible(modelName, x, y)
{
}

void UIElement::setOnClick(void* handler)
{
	if (handler)
	{
		onClick_ = (void*)handler;
	}
}

void* UIElement::click(void* args)
{
	//delegate as function pointer
	if (onClick_)
	{
		return ((void*(*)(void*)) onClick_)(args); //beautifull
	}
}

void* UIElement::getOnClick()
{
	return onClick_;
}

UIElement::~UIElement()
{
}