#include "LevelManager.h"

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

}

