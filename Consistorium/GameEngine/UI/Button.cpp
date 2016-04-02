#include "Button.h"

namespace GameEngineUI
{
	Button::Button(float x, float y, const char * modelName, char * text)
		:UIElement(x, y, modelName),
		text_(text)
	{
	}

	Button::~Button()
	{
	}

	char * Button::get_text()
	{
		return text_;
	}

	void Button::set_text(char* text)
	{
		text_ = text;
	}

}