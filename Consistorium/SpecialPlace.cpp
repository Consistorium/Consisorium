#include "SpecialPlace.h"

int SpecialPlace::IdGiver = 0;

SpecialPlace::SpecialPlace(std::string parentLayer, std::string name, std::vector<std::vector<std::string>> elements)
	: id_(IdGiver++),
	parentLayer_(parentLayer),
	center_(nullptr),
	name_(name),
	elements_(elements)
{
}

SpecialPlace::~SpecialPlace()
{
}

std::string SpecialPlace::getLayer()
{
	return parentLayer_;
}

std::string SpecialPlace::getName()
{
	return name_;
}

std::vector<std::vector<std::string>> SpecialPlace::getElements()
{
	return elements_;
}

std::unique_ptr<b2Vec2> SpecialPlace::getCenter()
{
	if (center_ == nullptr)
	{
		for (int i = 0; i < elements_.size(); i++)
		{
			for (int j = 0; j < elements_[i].size(); j++)
			{
				if (elements_[i][j].compare("center") == 0)
				{
					center_ = std::make_unique<b2Vec2>(b2Vec2(i, j));
					return std::move(center_);
				}
			}
		}
	}

	return std::move(center_);
}

int SpecialPlace::getId()
{
	return id_;
}
