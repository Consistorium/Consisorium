#pragma once

#include <string>
#include "IEntityModel.h"

class EntityModel : public IEntityModel
{
public: 
	EntityModel(std::string path)
		: IEntityModel(path)
	{ }
};