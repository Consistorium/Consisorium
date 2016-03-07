#pragma once

#include "UIElement.h"

class Button : public UIElement
{
private:
	char* text_;
public:
	Button(float x, float y, const char* modelName, char* text);
	~Button();
	char* get_text();
	void set_text(char* text);
};