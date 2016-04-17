#pragma once

#include <SDL/SDL.h>
#include <string>
#include <memory>

namespace GameEngine
{
	class UIElement
	{
	private:
		void* onClick_;
		float x_, y_;
		std::unique_ptr<SDL_Surface> model_;
		SDL_Rect bounds_;
	public:
		UIElement::UIElement(float x, float y, const char* modeslName);

		~UIElement();

		virtual void setOnClick(void* handler);

		virtual void* getOnClick();

		virtual void* click(void* args);

		virtual double getX();

		virtual void setX(double value);

		virtual double getY();

		virtual void setY(double value);

		virtual SDL_Surface* getModel();

		virtual SDL_Rect getBounds();

		virtual void setBounds(SDL_Rect value);
	};
}