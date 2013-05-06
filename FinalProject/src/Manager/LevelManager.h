#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H
#include <string>
#include <vector>


class LevelManager{
private:
	char* levelName;
	//Current Level size
	int levelWidth, levelHeight;
	int firstGid;
	//total amount of tiles and unique sprites
	int  totalTiles, totalSprites;
	LevelManager();
	//disable copy constructors
	LevelManager(LevelManager const& copy);
	LevelManager& operator = (LevelManager const& copy);

public:
	static LevelManager& getInstance();
	int getWidth();
	int getHeight();
	int getTotalSprites();
	int getTotalTiles();
	void loadMap(char *);


};

class MapLayer {
public:
	std::string name;
	int width;
	int height;
	int* data;

	~MapLayer() {
		delete [] data;
	}

};

struct tileProperty {
	std::string name;
	std::string value;
};

class MapObject {
public:
	std::string name;
	int gid;
	int x;
	int y;
	int width;
	int height;
	std::vector<tileProperty*> properties;

public:

	~MapObject() {
		//for ( auto property : properties ) {
		//	delete property;
		//}
	}
};

class MapObjectGroup {
public:
	std::string name;
	int width;
	int height;
	bool visible;

	std::vector<MapObject*> objects;

	~MapObjectGroup() {
		//for ( auto o : objects ) {
			//delete o;
		//}
	}
};

class Map {
public:

	int width;
	int height;
	int tileWidth;
	int tileHeight;

	std::vector<LevelManager*> tilesets;
	std::vector<MapObject*> layers;
	std::vector<MapObjectGroup*> groups;

	~Map() {
		/*for ( auto g : groups ) {
			delete g;
		}

		for ( auto l : layers ) {
			delete l;
		}

		for ( auto ts : tilesets ) {
			delete ts;
		}
		*/
	}


};


#endif