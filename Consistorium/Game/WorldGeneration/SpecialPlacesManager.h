#pragma once

#include <map>
#include <vector>
#include <Game\WorldGeneration\SpecialPlace.h>
#include <memory>

class SpecialPlacesManager
{
private:
	std::map<std::string, std::vector<std::shared_ptr<SpecialPlace>>> places_;

	void populatePlaces();
	
	const std::string PATH = "Generation";
public:
	SpecialPlacesManager();

	~SpecialPlacesManager();

	std::shared_ptr<SpecialPlace> getPlace(std::string layerName, std::string name);

	std::shared_ptr<SpecialPlace> getRandomPlace(std::string layerName);
};