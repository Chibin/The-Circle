#include "NormalScene.h"
#include "../Manager/GameManager.h"
NormalScene::NormalScene(){
	type = SceneManager::NORMAL;
	std::cout << "Entering Normal Screen..." << std::endl;
	std::cout << "Loading Resources..." << std::endl;
	std::cout << "\tLoading Level " ;
	if(game->isLoaded()){
		std::cout << "from a save." << std::endl;;
	}
	else{
		tempMap = SDL_LoadBMP("../levels/map.bmp");
		mapRect.x = scene->getWindowWidth()/2 - tempMap->w/2;
		mapRect.y = scene->getWindowHeight()/2 - tempMap->h/2;
	}
	std::cout << "\tLoading Character...\n" ;
	if(player->getType()==0){
		std::cout << "\t\tLoading Llyod..." << std::endl;
		playerModel = load_imageWhite("../Images/normal/maleModel.bmp");	
		if(playerModel == 0)
			std::cout << "Image did not load" << std::endl;
	}
	else{
		std::cout << "Loading Natalia..." << std::endl;
		if(playerModel == 0)
			std::cout << "Image did not load" << std::endl;

	}
	if(player->getPositionX() == 0 && player->getPositionY()  == 0){
		std::cout << "don't know position... setting position to center of map" << std::endl;
		playerModelRectSrc.w = 24;
		playerModelRectSrc.h = 34;
		playerModelRectSrc.y = 68;
		playerModelRectSrc.x = 24;
		playerModelRectDest.x = scene->getWindowWidth()/2;
		playerModelRectDest.y = scene->getWindowHeight()/2;
	}
	else{
		std::cout << "Setting player position to x: " << player->getPositionX() << ", y: " << player->getPositionY() << std::endl;
		playerModelRectDest.x = player->getPositionX();
		playerModelRectDest.y = player->getPositionY();
	}
	//playerModelRect.x = player->getPositionX();
	//playerModelRect.y = player->getPositionY();

	std::cout << "Done!" << std::endl;;
	std::cout << "Finished Loading!" << std::endl << std::endl;
}
void NormalScene::eventHandler(SDL_Event& event){
	Uint8* keystate =SDL_GetKeyState(NULL);
	if( keystate[SDLK_UP]){
		cout << "UP" << endl;
		playerModelRectSrc.x;
		playerModelRectSrc.y;
	}
	if( keystate[SDLK_DOWN]){
		cout << "DOWN" << endl;
	}
	if( keystate[SDLK_LEFT]){
		cout << "LEFT" << endl;
	}
	if( keystate[SDLK_RIGHT]){
		cout << "RIGHT" << endl;
	}
	//Runs through all the queued events
	//Note: we can create our own events
	while(SDL_PollEvent(&event)){
		switch(event.type){
		case SDL_KEYDOWN:
			switch(event.key.keysym.sym){
			case SDLK_RETURN:

				break;
			case SDLK_ESCAPE:
				game->setGameOver(true);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}

}
void NormalScene::display(){
	currentTick = SDL_GetTicks();
	if(currentTick - lastTick > 150)
	{
		lastTick = currentTick;
		//update animation
		
	}
	SDL_FillRect(scene->getScreen(),NULL,0x221122);
	SDL_BlitSurface(tempMap,NULL,scene->getScreen(),&mapRect);
	SDL_BlitSurface(playerModel, &playerModelRectSrc, scene->getScreen(), &playerModelRectDest);

	SDL_Flip(scene->getScreen());
}
void NormalScene::disposeResources(){
}