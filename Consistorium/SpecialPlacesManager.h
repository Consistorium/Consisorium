#pragma once

#include <map>
#include <vector>
#include <SpecialPlace.h>
#include <memory>

class SpecialPlacesManager
{
private:
	std::map<std::string, std::vector<SpecialPlace*>> places_;

	void populatePlaces();
	
	const std::string PATH = "Generation";
public:
	SpecialPlacesManager();

	~SpecialPlacesManager();

	SpecialPlace* getPlace(std::string layerName, std::string name);

	SpecialPlace* getRandomPlace(std::string layerName);
};