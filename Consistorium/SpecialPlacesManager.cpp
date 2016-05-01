#include "SpecialPlacesManager.h"
#include <Utils.h>
#include <regex>
#include <iostream>

SpecialPlacesManager::SpecialPlacesManager()
{
	populatePlaces();
}


SpecialPlacesManager::~SpecialPlacesManager()
{
	for(auto m : places_)
	{
		while (!places_[m.first].empty()) 
		{
			delete places_[m.first].back(), places_[m.first].pop_back();
		}
	}
}

void SpecialPlacesManager::populatePlaces()
{
	std::vector<std::string> layerDirectories = Utils::getDirectoryContents(PATH);
	for (auto dir : layerDirectories)
	{
		if (dir == "." || dir == "..") {
			continue;
		}

		std::vector<std::string> layerPlaces = Utils::getDirectoryContents(PATH + '/' + dir);
		for (auto place : layerPlaces)
		{
			if (place == "." || place == "..") {
				continue;
			}

			std::vector<std::string> fileContents = Utils::getFileContents(PATH + '/' + dir + '/' + place);
			std::vector<std::vector<std::string>> elements;
			std::smatch matched;
			for (int i = 0; i < fileContents.size(); i++)
			{
				std::smatch m_res;
				std::regex expr("[a-zA-Z]+|-");
				elements.push_back(std::vector<std::string>());
				while (std::regex_search(fileContents[i], m_res, expr)) {
					for (auto x : m_res) 
					{
						elements[i].push_back(x);
					}

					fileContents[i] = m_res.suffix().str();
				}
			}

			places_[dir].push_back(new SpecialPlace(dir, place, elements));
		}
	}
}

SpecialPlace* SpecialPlacesManager::getPlace(std::string layerName, std::string name)
{
	std::vector<std::string> result;
	for (int i = 0; i < places_[layerName].size(); i++)
	{
		if (places_[layerName][i]->getName().compare(name) == 0)
		{
			return places_[layerName][i];
		}
	}

	return nullptr;
}

SpecialPlace* SpecialPlacesManager::getRandomPlace(std::string layerName)
{
	int index = rand() % places_[layerName].size();
	return places_[layerName][index];
}
