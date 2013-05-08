#include "LevelManager.h"
#include <iostream>

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
	mapImage =SDL_DisplayFormatAlpha(loadedImage);
	SDL_FreeSurface( loadedImage );
	//SDL_SetColorKey( mapImage, SDL_SRCCOLORKEY, SDL_MapRGB( mapImage->format, 0xff, 0xff, 0xff ) );

	printf("\n\t\tStatus:\n\t\t\tParsing file now...");
	currentMap->ParseFile(temp1);
	printf("...Done!\n");
	levelWidth = currentMap->GetLayer(0)->GetWidth();
	levelHeight = currentMap->GetLayer(0)->GetHeight();

}
void LevelManager::renderMapCollision(){
	int colAmount = currentMap->GetTileset(0)->GetImage()->GetWidth()/currentMap->GetTileWidth(); 
	SDL_Rect srcRect;
	SDL_Rect buffRect;
	const Tmx::Layer *layer = currentMap->GetLayer(2);
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
bool LevelManager::checkWalk(const int& _x,const int& _y){
	int colAmount = currentMap->GetTileset(0)->GetImage()->GetWidth()/currentMap->GetTileWidth(); 
	//grab the collision layer
	const Tmx::Layer *layer = currentMap->GetLayer(2);
	for (int x = 0; x < layer->GetWidth(); ++x) 
	{
		for (int y = 0; y < layer->GetHeight(); ++y) 
		{
			if(layer->GetTileId(x,y)==0){
				std::cout << "free to walk on" << std::endl;
				player->move(_x,_y);
				return true;
			}
		}
	}
	return false;
}

void LevelManager::renderMap(){

	//get the number of columns
	int colAmount = currentMap->GetTileset(0)->GetImage()->GetWidth()/currentMap->GetTileWidth(); 
	SDL_Rect srcRect;
	SDL_Rect buffRect;
	for (int i = 0; i < 2; ++i) 
	{
		const Tmx::Layer *layer = currentMap->GetLayer(i);
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
}