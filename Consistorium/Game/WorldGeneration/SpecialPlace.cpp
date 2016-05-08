#include "SpecialPlace.h"

#include <algorithm>

int SpecialPlace::IdGiver = 0;

SpecialPlace::SpecialPlace(std::string parentLayer, std::string name, std::vector<std::vector<std::string>> elements)
	: id_(IdGiver++),
	parentLayer_(parentLayer),
	center_(nullptr),
	height_(0),
	width_(0),
	frequency_(nullptr),
	name_(name),
	elements_(elements)
{
}

SpecialPlace::~SpecialPlace()
{
}

int SpecialPlace::getHeight()
{
	if (height_ == 0)
	{
		height_ = elements_.size();
	}

	return height_;
}

int SpecialPlace::getWidth()
{
	if (width_ == 0)
	{
		int maxWidth = elements_[0].size();
		for (int i = 1; i < elements_.size(); i++)
		{
			maxWidth = std::max(maxWidth, static_cast<int>(elements_[i].size()));
		}

		width_ = maxWidth;
	}

	return width_;
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

std::shared_ptr<b2Vec2> SpecialPlace::getCenter()
{
	if (center_ == nullptr)
	{
		for (int i = 0; i < elements_.size(); i++)
		{
			for (int j = 0; j < elements_[i].size(); j++)
			{
				if (elements_[i][j].find("center") != std::string::npos)
				{
					int pos = elements_[i][j].find("center");
					elements_[i][j].erase(pos, std::string("center").size());
					center_ = std::make_shared<b2Vec2>(b2Vec2(i, j));
					return center_;
				}
			}
		}
	}

	return center_;
}

std::shared_ptr<int> SpecialPlace::getFrequency()
{
	if (frequency_ == nullptr)
	{
		int last = elements_.size() - 1;
		frequency_ = std::make_shared<int>(std::stoi(elements_[last][elements_[last].size() - 1]));
	}

	return frequency_;
}

int SpecialPlace::getId()
{
	return id_;
}
