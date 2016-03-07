#pragma once

#include <memory>
#include <SDL.h>
#include <SDL_image.h>

class IEntityModel
{
private:
	std::unique_ptr<SDL_Surface> entityModel;

protected:
	IEntityModel(std::string path)
		: entityModel(IMG_Load(path.c_str()))
	{ }

	virtual ~IEntityModel() = 0;

public:
	SDL_Surface* getModel() { return this->entityModel.get(); }
};

IEntityModel::~IEntityModel() { }