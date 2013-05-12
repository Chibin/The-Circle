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
	return levelHeight*16;
}

int LevelManager::getWidth(){
	return levelWidth*16;
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

	printf("\n\t\tStatus:\n\t\t\tParsing file now...");
	currentMap->ParseFile(temp1);
	printf("...Done!\n");
	levelWidth = currentMap->GetLayer(0)->GetWidth();
	levelHeight = currentMap->GetLayer(0)->GetHeight();
	loadNPC();// load the NPCs
	scene->getCamera()->x = 160;
	scene->getCamera()->y = 160;
}

//0 = base tile, 1 = secondary tiles, 2 = collision objects, 3 = collision tiles, 4 = NPC's layer
void LevelManager::renderMapLayer(int layerID){
	int colAmount = currentMap->GetTileset(0)->GetImage()->GetWidth()/currentMap->GetTileWidth(); 
	SDL_Rect srcRect;
	SDL_Rect buffRect;
	int cameraX = scene->getCamera()->x/16;
	int cameraY = scene->getCamera()->y/16;
	int drawX = 0, drawY = 0;
	const Tmx::Layer *layer = currentMap->GetLayer(layerID);
	for (int x = 0; x < scene->getWindowWidth()/16; ++x) 
	{
		for (int y = 0; y < scene->getWindowHeight()/16; ++y) 
		{
			if(layer->GetTileId(x,y)==0)
				continue;
			//get the id of the tile and mod it by the colAmount to get the number in that row
			//
			drawX = cameraX + x;
			drawY = cameraY + y;
			//printf("start loc x: %d, y: %d\n", drawX,drawY );
			int colNum = (layer->GetTileId(drawX,drawY)%colAmount)-1;
			int rowNum = (layer->GetTileId(drawX,drawY)/colAmount-1);
			srcRect.x = ((layer->GetTileId(drawX,drawY)%colAmount)) * currentMap->GetTileWidth() ;
			srcRect.y = (layer->GetTileId(drawX,drawY)/colAmount)* currentMap->GetTileHeight();
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
	//int playerX = (player->getPositionX()+_x-4)/currentMap->GetTileWidth();
	//int playerY = (player->getPositionY()+ _y)/currentMap->GetTileHeight();

	int playerX = (player->getMapOffsetX()+_x-4)/currentMap->GetTileWidth();
	int playerY = (player->getMapOffsetY()+ _y)/currentMap->GetTileHeight();
	if(layer->GetTileId(playerX+1,playerY+1)!=0){
		printf("EVENT!!\n");
		currentMap->GetProperties().GetList();
		int buff2 = layer->GetTileId(playerX+1,playerY+1);
		int buff = layer->GetTileTilesetIndex(playerX,playerY);
		scene->setGameScene(SceneManager::EVENT);
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
	//check if player is within level
	if((player->getMapOffsetX()+ playerBox->w +_x ) > getWidth() && (player->getMapOffsetX()+ playerBox->w +_x ) < 0 ){
		return false;
	}
	if((player->getMapOffsetY()+ playerBox->h +_y ) > getHeight() && (player->getMapOffsetY()+ playerBox->h +_y ) < 0()){
		return false;
	}
	const Tmx::Layer *layer = currentMap->GetLayer(3);

	//check what id is the tile where the is player on
	//player is moving to the left
	//printf("Player is currently on tile(%d,%d) position(%d,%d)\n", (player->getMapOffsetX()/currentMap->GetTileWidth()), (playerBox->y/currentMap->GetTileHeight()),playerBox->x, playerBox->y);

	if(_y ==0 && _x < 0){	
		playerX = (player->getMapOffsetX() + _x + playerBox->w / 4)/ currentMap->GetTileWidth();
		playerX2 = (player->getMapOffsetX() + _x + playerBox->w / 4)/ currentMap->GetTileWidth();
		playerY = (player->getMapOffsetY() + (playerBox->h - playerBox->h/4 ) + _y) / currentMap->GetTileHeight();
		playerY2 = (player->getMapOffsetY() + playerBox->h / 2 + _y) / currentMap->GetTileHeight();
	}
	//player is moving to the right
	if(_y==0 && _x>0){
		playerX = (player->getMapOffsetX() + (playerBox->w - playerBox->w / 4) + _x) / currentMap->GetTileWidth();
		playerX2 = (player->getMapOffsetX() + (playerBox->w - playerBox->w / 4) + _x) / currentMap->GetTileWidth();
		playerY = (player->getMapOffsetY() + playerBox->h - 8) /currentMap->GetTileHeight();
		playerY2 = (player->getMapOffsetY() + playerBox->h / 2) / currentMap->GetTileHeight();
		//ayerY = (playerBox->y + playerBox->h / 4) /currentMap->GetTileHeight();
	}
	//player moving up
	if(_x==0 && _y < 0){
		playerX = (player->getMapOffsetX() + _x + playerBox->w / 4)/ currentMap->GetTileWidth();	
		playerX2 = (player->getMapOffsetX() + (playerBox->w - playerBox->w / 4) + _x) / currentMap->GetTileWidth();
		playerY = (player->getMapOffsetY() + playerBox->h / 2 + _y) / currentMap->GetTileHeight();
		playerY2 = (player->getMapOffsetY() + playerBox->h / 2 + _y) / currentMap->GetTileHeight();
	}
	//player moving down
	if(_x==0 && _y > 0){
		playerX = (player->getMapOffsetX() + _x + playerBox->w / 4)/ currentMap->GetTileWidth();
		playerY = (player->getMapOffsetY() + playerBox->h)/currentMap->GetTileHeight();
		playerX2 = (player->getMapOffsetX() + (playerBox->w - playerBox->w / 4) + _x) / currentMap->GetTileWidth();
		playerY2 = (player->getMapOffsetY() + playerBox->h / 2) / currentMap->GetTileHeight();
	}
	//printf("walking to tile(%d,%d)\n", playerX,playerY);
	//if(layer->GetTileId(playerX,playerY)==0 )
	if(layer->GetTileId(playerX,playerY)==0 && layer->GetTileId(playerX2,playerY2)==0 ){
		player->move(_x,_y);
		
		scene->updateCamera(_x,_y);
		scene->setCamera();
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

void LevelManager::renderNPC(void)
{
	for(int i=0; i<(int)NPCvector.size(); i++) // go through and redner very NPC
	{
		SDL_BlitSurface(NPCvector[i]->getSurface(), NPCvector[i]->getAnimation()->GetFrame(), scene->getScreen(), NPCvector[i]->getRect());
	}
}