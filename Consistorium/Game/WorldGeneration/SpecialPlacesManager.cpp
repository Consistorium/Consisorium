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
				std::regex expr("[a-zA-Z]+|-|[0-9]+");
				elements.push_back(std::vector<std::string>());
				while (std::regex_search(fileContents[i], m_res, expr)) {
					for (auto x : m_res) 
					{
						elements[i].push_back(x);
					}

					fileContents[i] = m_res.suffix().str();
				}
			}

			places_[dir].emplace_back(new SpecialPlace(dir, place, elements));
		}
	}
}

std::shared_ptr<SpecialPlace> SpecialPlacesManager::getPlace(std::string layerName, std::string name)
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

void SpecialPlacesManager::spawnPlace(b2Vec2 pos, std::shared_ptr<SpecialPlace> place, Entities::EntityFactory& factory)
{
	std::shared_ptr<b2Vec2> center = place->getCenter();
	for (int k = 0; k < place->getElements().size(); k++)
	{
		int innerSize = place->getElements()[k].size();
		for (int l = 0; l < innerSize; l++)
		{
			factory.createFromName(b2Vec2(pos.x + (-center->y + l) * Globals::BLOCK_WIDTH, pos.y + (center->x - k) * Globals::BLOCK_WIDTH), place->getElements()[k][l]);
		}
	}
}

void SpecialPlacesManager::spawnPlace(b2Vec2 pos, std::shared_ptr<SpecialPlace> place, Entities::EntityFactory& factory, std::vector<std::vector<Entities::GameEntity*>>& cache, b2Vec2 indexes)
{
	std::shared_ptr<b2Vec2> center = place->getCenter();
	b2Vec2 dynIndexes(indexes);
	for (int k = 0; k < place->getElements().size(); k++)
	{
		int innerSize = place->getElements()[k].size();
		dynIndexes.y = indexes.y + center->y - k;
		for (int l = 0; l < innerSize; l++)
		{
			dynIndexes.x = indexes.x - center->y + l;
			factory.createFromName(b2Vec2(pos.x + (l - center->y) * Globals::BLOCK_WIDTH, pos.y + (center->x - k) * Globals::BLOCK_WIDTH), place->getElements()[k][l], cache, dynIndexes);
		}
	}
}

std::shared_ptr<SpecialPlace> SpecialPlacesManager::getRandomPlace(std::string layerName)
{
	int index = rand() % places_[layerName].size();
	return places_[layerName][index];
}
