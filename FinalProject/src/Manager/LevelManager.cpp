#include "LevelManager.h"
#include "../Utility/RapidXML/rapidxml.hpp"
#include <iostream>
using namespace rapidxml;

LevelManager& LevelManager::getInstance(){
	static LevelManager instance;
	return instance;
}
LevelManager::LevelManager(){
	levelName = 0;
	totalTiles = totalSprites = levelWidth =  levelHeight = 0;
}

int LevelManager::getHeight(){
	return levelHeight;
}

int LevelManager::getWidth(){
	return levelWidth;
}

int LevelManager::getTotalSprites(){
	return totalSprites;
}

int LevelManager::getTotalTiles(){
	return totalTiles;
}
void LevelManager::loadMap(char* mapName){
	xml_document<> doc;
	doc.parse<0>(mapName);
	xml_node<> *mapnode = doc.first_node("map");


}

