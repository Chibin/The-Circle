#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

class LevelManager{
private:
	char* levelName;
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
	void loadMap(char *);


};

#endif