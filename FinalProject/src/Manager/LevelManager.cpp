#include "LevelManager.h"
#include <iostream>

LevelManager& LevelManager::getInstance(){
	static LevelManager instance;
	return instance;
}
LevelManager::LevelManager(){
	scene = &SceneManager::getInstance();
	game = &GameManager::getInstance();
	levelName = "";
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
	//make sure to delete old map before continuing
	if(currentMap !=0)
		delete currentMap;

	std::string buf = mapName;
	currentMap = new Tmx::Map();

	printf("\n\t\tStatus:\n\t\t\tParsing file now...");
	currentMap->ParseFile("../levels/"+buf);
	printf("...Done!\n");
	/*
	// Iterate through the layers.
	for (int i = 0; i < currentMap->GetNumLayers(); ++i) {
	printf("                                    \n");
	printf("====================================\n");
	printf("Layer : %02d/%s \n", i, map->GetLayer(i)->GetName().c_str());
	printf("====================================\n");

	// Get a layer.
	const Tmx::Layer *layer = map->GetLayer(i);

	for (int y = 0; y < layer->GetHeight(); ++y) {
	for (int x = 0; x < layer->GetWidth(); ++x) {
	// Get the tile's id.
	printf("%03d", layer->GetTileId(x, y));

	// Find a tileset for that id.
	const Tmx::Tileset *tileset = map->FindTileset(layer->GetTileId(x, y));
	if (layer->IsTileFlippedHorizontally(x, y)){
	printf("h");
	}else{
	printf(" ");
	}
	if (layer->IsTileFlippedVertically(x, y)){
	printf("v");
	}else{
	printf(" ");
	}
	if (layer->IsTileFlippedDiagonally(x, y)){
	printf("d ");
	} else {
	printf("  ");
	}
	}

	printf("\n");
	}
	}

	printf("\n\n");

	// Iterate through all of the object groups.
	for (int i = 0; i < map->GetNumObjectGroups(); ++i) {
	printf("                                    \n");
	printf("====================================\n");
	printf("Object group : %02d\n", i);
	printf("====================================\n");

	// Get an object group.
	const Tmx::ObjectGroup *objectGroup = map->GetObjectGroup(i);

	// Iterate through all objects in the object group.
	for (int j = 0; j < objectGroup->GetNumObjects(); ++j) {
	// Get an object.
	const Tmx::Object *object = objectGroup->GetObject(j);

	// Print information about the object.
	printf("Object Name: %s\n", object->GetName().c_str());
	printf("Object Position: (%03d, %03d)\n", object->GetX(), object->GetY());
	printf("Object Size: (%03d, %03d)\n", object->GetWidth(), object->GetHeight());

	// Print Polygon points.
	const Tmx::Polygon *polygon = object->GetPolygon();
	if (polygon != 0) {
	for (int i = 0; i < polygon->GetNumPoints(); i++) {
	const Tmx::Point &point = polygon->GetPoint(i);
	printf("Object Polygon: Point %d: (%d, %d)\n", i, point.x, point.y);
	}
	}

	// Print Polyline points.
	const Tmx::Polyline *polyline = object->GetPolyline();
	if (polyline != 0) {
	for (int i = 0; i < polyline->GetNumPoints(); i++) {
	const Tmx::Point &point = polyline->GetPoint(i);
	printf("Object Polyline: Point %d: (%d, %d)\n", i, point.x, point.y);
	}
	}
	}
	}

	*/


}

void LevelManager::renderMap(){
	for (int i = 0; i < currentMap->GetNumLayers(); ++i) 
	{
		const Tmx::Layer *layer = currentMap->GetLayer(i);
		for (int x = 0; x < layer->GetWidth(); ++x) 
		{
			for (int y = 0; y < layer->GetHeight(); ++y) 
			{

			}
		}


	}
}