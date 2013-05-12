#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H
#include <string>
#include <vector>
#include "../Utility/Tmx.h"
#include "SceneManager.h"
#include "GameManager.h"
#include "../Entity/Player.h"
#include "../Entity/NPC.h"
class Tmx::Map;
class Player;
class LevelManager{
private:
	SceneManager* scene;
	GameManager* game;
	SDL_Surface *mapImage;
	//level name
	std::string levelName;
	//map holder
	Tmx::Map *currentMap;
	Player* player;
	//Current Level size
	int levelWidth, levelHeight;
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
	void loadMap(char*);
	void renderMapLayer(int);
	bool checkWalk(const int& x,const int& y);
	bool checkEvent(const int& x,const int& y);
	vector<NPC*> NPCvector; // vector of NPC pointer to keep track of all NPCs
	void loadNPC(void); // add NPCs to the NPCvector and display them
};


class MapLayer{

};
#endif