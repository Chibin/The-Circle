#include "LevelManager.h"
#include <iostream>
#include "../Entity/Player.h"
#include "../Entity/Npc.h"
LevelManager& LevelManager::getInstance(){
	static LevelManager instance;
	return instance;
}
LevelManager::LevelManager(){
	scene = &SceneManager::getInstance();
	game = &GameManager::getInstance();
	player = &Player::getInstance();
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
	std::string buf = "../levels/";
	std::string buff = mapName;
	std::string bmp = ".png";
	std::string tmx = ".tmx";
	std::string imageTmx = buf+buff+tmx;
	std::string imageBmp = buf+buff+bmp;
	char *temp1 = new char[imageTmx.size()+1];
	char *temp2 = new char[imageBmp.size()+1];
	temp1[imageTmx.size()]=0;
	temp2[imageBmp.size()]=0;
	memcpy(temp1,imageTmx.c_str(),imageTmx.size());
	memcpy(temp2,imageBmp.c_str(),imageBmp.size());
	currentMap = new Tmx::Map();

	SDL_Surface* loadedImage = IMG_Load(temp2);
	mapImage = SDL_DisplayFormatAlpha(loadedImage);
	SDL_FreeSurface( loadedImage );
	//SDL_SetColorKey( mapImage, SDL_SRCCOLORKEY, SDL_MapRGB( mapImage->format, 0xff, 0xff, 0xff ) );
	levelName = mapName;
	printf("\n\t\tStatus:\n\t\t\tParsing file now...");
	currentMap->ParseFile(temp1);
	printf("...Done!\n");
	levelWidth = currentMap->GetLayer(0)->GetWidth();
	levelHeight = currentMap->GetLayer(0)->GetHeight();
	loadNPC();// load the NPCs
}

//0 = base tile, 1 = secondary tiles, 2 = collision objects, 3 = collision tiles, 4 = NPC's layer
void LevelManager::renderMapLayer(int layerID){
	int colAmount = currentMap->GetTileset(0)->GetImage()->GetWidth()/currentMap->GetTileWidth(); 
	SDL_Rect srcRect;
	SDL_Rect buffRect;
	const Tmx::Layer *layer = currentMap->GetLayer(layerID);
	for (int x = 0; x < layer->GetWidth(); ++x) 
	{
		for (int y = 0; y < layer->GetHeight(); ++y) 
		{
			if(layer->GetTileId(x,y)==0)
				continue;
			//get the id of the tile and mod it by the colAmount to get the number in that row
			//
			int colNum = (layer->GetTileId(x,y)%colAmount)-1;
			int rowNum = (layer->GetTileId(x,y)/colAmount-1);
			srcRect.x = ((layer->GetTileId(x,y)%colAmount)) * currentMap->GetTileWidth() ;
			srcRect.y = (layer->GetTileId(x,y)/colAmount)* currentMap->GetTileHeight();
			srcRect.h = currentMap->GetTileHeight();
			srcRect.w = currentMap->GetTileWidth();
			buffRect.x = x * currentMap->GetTileWidth();
			buffRect.y = y * currentMap->GetTileHeight();
			buffRect.h = currentMap->GetTileHeight();
			buffRect.w = currentMap->GetTileWidth();
			SDL_BlitSurface(mapImage,&srcRect,scene->getScreen(),&buffRect);	

		}
	}
}

bool LevelManager::checkEvent(const int& _x,const int& _y){
	const Tmx::Layer *layer = currentMap->GetLayer(4);
	int playerX = (player->getPositionX()+_x-4)/currentMap->GetTileWidth();
	int playerY = (player->getPositionY()+ _y)/currentMap->GetTileHeight();
	if(layer->GetTileId(playerX+1,playerY+1)!=0){
		//printf("EVENT!!\n");
		printf("EventID: %d\n", layer->GetTileId(playerX+1,playerY+1));
		int buff2 = layer->GetTileId(playerX+1,playerY+1);
		int buff = layer->GetTileTilesetIndex(playerX,playerY);

		if(levelName == "testLevel2"){
			if(layer->GetTileId(playerX+1,playerY+1) == 26){
				scene->setGameScene(SceneManager::EVENT);
				return true;
			}
			if (layer->GetTileId(playerX+1,playerY+1) == 27){
				//printf("Switch scene here\n");
				clearNPC(); // clear the NPC vector. so old NPC's wont appear on new map.
				loadMap("testLevel2a");
				scene->setGameScene(SceneManager::NORMAL);
				player->setPosition(20,player->getPositionY());
				return true;
			}
		}
		if(levelName == "testLevel2a"){
			if(layer->GetTileId(playerX+1,playerY+1) == 27){
				loadMap("testLevel2-cave");
				scene->setGameScene(SceneManager::NORMAL);
				player->setPosition(player->getPositionX() - 20,550);
				return true;
			}
			if(layer->GetTileId(playerX+1,playerY+1) == 28){
				//printf("Switch scene here\n");
				loadMap("testLevel2");
				scene->setGameScene(SceneManager::NORMAL);
				player->setPosition(770,player->getPositionY()-20);
				return true;
			}

		}
		if(levelName == "testLevel2-cave"){
			if(layer->GetTileId(playerX+1,playerY+1) == 26){
				loadMap("testLevel2a");
				scene->setGameScene(SceneManager::NORMAL);
				player->setPosition(player->getPositionX() + 20,305);
			}
		}
	}
	return false;
}

bool LevelManager::checkWalk(const int& _x,const int& _y){

	SDL_Rect* playerBox = player->getPlayerPosition();
	//get current spot of player on map and check if the attempted motion will walk out of the tile
	int playerX = 0;
	int playerY = 0;
	int playerX2 = 0;
	int playerY2 = 0;
	//check if player is within screen
	if((playerBox->x+ playerBox->w +_x ) > 800 ){
		return false;
	}
	if((playerBox->y+ playerBox->h +_y ) > 600 ){
		return false;
	}
	const Tmx::Layer *layer = currentMap->GetLayer(3);

	//check what id is the tile where the is player on
	//player is moving to the left
	//printf("Player is currently on tile(%d,%d) position(%d,%d)\n", (playerBox->x/currentMap->GetTileWidth()), (playerBox->y/currentMap->GetTileHeight()),playerBox->x, playerBox->y);

	if(_y ==0 && _x < 0){	
		playerX = (playerBox->x + _x + playerBox->w / 4)/ currentMap->GetTileWidth();
		playerX2 = (playerBox->x + _x + playerBox->w / 4)/ currentMap->GetTileWidth();
		playerY = (playerBox->y + (playerBox->h - playerBox->h/4 ) + _y) / currentMap->GetTileHeight();
		playerY2 = (playerBox->y + playerBox->h / 2 + _y) / currentMap->GetTileHeight();
	}
	//player is moving to the right
	if(_y==0 && _x>0){
		playerX = (playerBox->x + (playerBox->w - playerBox->w / 4) + _x) / currentMap->GetTileWidth();
		playerX2 = (playerBox->x + (playerBox->w - playerBox->w / 4) + _x) / currentMap->GetTileWidth();
		playerY = (playerBox->y + playerBox->h - 8) /currentMap->GetTileHeight();
		playerY2 = (playerBox->y + playerBox->h / 2) / currentMap->GetTileHeight();
		//ayerY = (playerBox->y + playerBox->h / 4) /currentMap->GetTileHeight();
	}
	//player moving up
	if(_x==0 && _y < 0){
		playerX = (playerBox->x + _x + playerBox->w / 4)/ currentMap->GetTileWidth();	
		playerX2 = (playerBox->x + (playerBox->w - playerBox->w / 4) + _x) / currentMap->GetTileWidth();
		playerY = (playerBox->y + playerBox->h / 2 + _y) / currentMap->GetTileHeight();
		playerY2 = (playerBox->y + playerBox->h / 2 + _y) / currentMap->GetTileHeight();
	}
	//player moving down
	if(_x==0 && _y > 0){
		playerX = (playerBox->x + _x + playerBox->w / 4)/ currentMap->GetTileWidth();
		playerY = (playerBox->y + playerBox->h)/currentMap->GetTileHeight();
		playerX2 = (playerBox->x + (playerBox->w - playerBox->w / 4) + _x) / currentMap->GetTileWidth();
		playerY2 = (playerBox->y + playerBox->h / 2) / currentMap->GetTileHeight();
	}
	//printf("walking to tile(%d,%d)\n", playerX,playerY);
	//if(layer->GetTileId(playerX,playerY)==0 )
	if(layer->GetTileId(playerX,playerY)==0 && layer->GetTileId(playerX2,playerY2)==0 ){
		player->move(_x,_y);
		//printf("Player is going to tile(%d,%d) position(%d,%d)\n", ((playerBox->x+_x)/currentMap->GetTileWidth()), ((playerBox->y+_y)/currentMap->GetTileHeight()),playerBox->x + _x, playerBox->y + _y);
	}
	//else{
	//printf("Colliding with tile id:%d\n",layer->GetTileId(playerX,playerY));
	//}


	return false;
}
// This function should use the tmx file and get the npc object layer from currentmap
// It should then go through and add every NPC character to the NPCvector.
void LevelManager::loadNPC(void)
{
	const Tmx::ObjectGroup* npcGroup = currentMap->GetObjectGroup(0); // NPC is the first object group so id=0
	for(int i=0; i < npcGroup->GetNumObjects(); ++i) // to iterate through all the objects
	{
		const Tmx::Object* npcObject = npcGroup->GetObject(i); // get single npc object
		int npcIndex = -1; // temp var for easier access
		//std::cout << "NPC: " << npcObject->GetName().c_str() << std::endl;
		if( npcObject->GetName() == "guy1")
		{
			NPCvector.push_back(new NPC_guy1);
			npcIndex = NPCvector.size()-1;
		}	
		else if( npcObject->GetName() == "girl1")
		{
			NPCvector.push_back(new NPC_girl1);
			npcIndex = NPCvector.size()-1;
		}
		else if( npcObject->GetName() == "guyRed")
		{
			NPCvector.push_back(new NPC_guyRed);
			npcIndex = NPCvector.size()-1;
		}
		if(npcIndex == -1)
			std::cout << "Oh No! ... No NPC characters" << std::endl;
		else
		{
			SDL_Rect* tempRect = NPCvector[npcIndex]->getRect(); // set the Rect coordinate for the NPC
			tempRect->x = npcObject->GetX();
			tempRect->y = npcObject->GetY()-30;
			tempRect->w = npcObject->GetWidth();
			tempRect->h = npcObject->GetHeight();
			//SDL_BlitSurface(NPCvector[npcIndex]->getSurface(), NPCvector[npcIndex]->getAnimation()->GetFrame(), scene->getScreen(), NPCvector[npcIndex]->getRect());
		}
	}

}

// Function to clear the NPC vector which should be called when going to a new scene
void LevelManager::clearNPC(void)
{
	for(int i=0; i<(int)NPCvector.size(); i++)
		delete NPCvector[i];
	NPCvector.clear();
}

void LevelManager::renderNPC(void)
{
	for(int i=0; i<(int)NPCvector.size(); i++) // go through and redner very NPC
	{
		SDL_BlitSurface(NPCvector[i]->getSurface(), NPCvector[i]->getAnimation()->GetFrame(), scene->getScreen(), NPCvector[i]->getRect());
	}
}