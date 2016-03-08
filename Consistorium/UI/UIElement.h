#pragma once

#include "../Interfaces/IPositionable.h"
#include "../Interfaces/IVisible.h"

class UIElement : public IPositionable,
	public IVisible
{
private:
	void* onClick_;
public:
	UIElement::UIElement(float x, float y, const char* modeslName);
	~UIElement();

	virtual void setOnClick(void* handler);
	virtual void* getOnClick();
	virtual void* click(void* args);
};