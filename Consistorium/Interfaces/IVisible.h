#pragma once

#include <string>
#include <memory>
#include <SDL_image.h>

class IVisible
{
private:
	std::unique_ptr<SDL_Surface> model;
	SDL_Rect bounds;
public:

	IVisible(const char *name, float beginX, float beginY)
		: model(IMG_Load(name))
	{ 
		if (!model.get()) {
			printf("IMG_Load: %s\n", IMG_GetError());
		}

		bounds.x = beginX;
		bounds.y = beginY;
		bounds.w = model.get()->w;
		bounds.h = model.get()->h;
		this->bounds = bounds;
	}

	virtual ~IVisible() { }

	virtual SDL_Surface* getModel() { return this->model.get(); }

	virtual SDL_Rect getBounds() { return this->bounds; }

	virtual void setBounds(SDL_Rect value) { this->bounds = value; }
};