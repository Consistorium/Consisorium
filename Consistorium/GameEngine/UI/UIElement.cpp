#include <iostream>
#include <vector>
#include <SDL/SDL_image.h>

#include "UIElement.h"

namespace GameEngineUI
{
	UIElement::UIElement(float x, float y, const char* modelName)
		:x_(x),
		y_(y),
		model_(IMG_Load(modelName))
	{
		if (!model_.get()) {
			printf("IMG_Load: %s\n", IMG_GetError());
		}

		bounds_.x = x;
		bounds_.y = y;
		bounds_.w = model_.get()->w;
		bounds_.h = model_.get()->h;
	}

	double UIElement::getX()
	{
		return x_;
	}

	void UIElement::setX(double value)
	{
		x_ = value;
	}

	void UIElement::setY(double value)
	{
		y_ = value;
	}

	double UIElement::getY()
	{
		return this->y_;
	}

	SDL_Surface* UIElement::getModel()
	{
		return model_.get();
	}

	SDL_Rect UIElement::getBounds()
	{
		return this->bounds_;
	}

	void UIElement::setBounds(SDL_Rect value)
	{
		this->bounds_ = value;
	}

	void UIElement::setOnClick(void* handler)
	{
		if (handler == nullptr)
		{
			std::cerr << "UIElement error: Trying to set null handler." << std::endl;
			return;
		}

		onClick_ = handler;
	}

	void* UIElement::click(void* args)
	{
		//delegate as function pointer
		if (onClick_)
		{
			return ((void*(*)(void*)) onClick_)(args); //beautiful
		};
	}

	void* UIElement::getOnClick()
	{
		return onClick_;
	}

	UIElement::~UIElement()
	{
	}
}