#pragma once
#include <vector>
#include <string>
#include <Box2D/Common/b2Math.h>
#include <memory>

class SpecialPlace
{
private:
	static int IdGiver;

	int id_;
	std::vector<std::vector<std::string>> elements_;
	std::string parentLayer_;
	std::string name_;
	std::shared_ptr<int> frequency_;
	std::shared_ptr<b2Vec2> center_;
public:
	SpecialPlace(std::string parentLayer, std::string name, std::vector<std::vector<std::string>> elements);

	~SpecialPlace();

	std::string getLayer();

	std::string getName();

	std::vector<std::vector<std::string>> getElements();

	std::shared_ptr<b2Vec2> getCenter();

	std::shared_ptr<int> getFrequency();

	int getId();
};

