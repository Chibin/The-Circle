#include "NormalScene.h"

NormalScene::NormalScene(){
	type = SceneManager::NORMAL;
	std::cout << "Entering Normal Screen..." << std::endl;
	std::cout << "Loading Resources..." << std::endl;
	/*******************************************************************************/
	/* *******************************LEVEL*****************************************/
	/*******************************************************************************/

	std::cout << "\tLoading Level..." ;
	//if(game->isLoaded()){
	//	std::cout << "from a save." << std::endl;;
	//}
	//else{
	level->loadMap("testLevel2");
	//tempMap = SDL_LoadBMP("../levels/map.bmp");
//	mapRect.x = scene->getWindowWidth()/2 - tempMap->w/2;
//	mapRect.y = scene->getWindowHeight()/2 - tempMap->h/2;
	//}
	std::cout << "Done!" << std::endl;

	/*******************************************************************************/
	/*****************************SET SETTINGS**************************************/
	/*******************************************************************************/
	std::cout << "\tPlacing Character on map.\n\t\tResult: " ;
	if(player->getPositionX() == 0 && player->getPositionY()  == 0){
		std::cout << "don't know position... setting position to center of map" << std::endl;
		player->setPosition(scene->getWindowWidth()/2 - 12,scene->getWindowHeight()/2 - 16);
	}
	else{
		std::cout << "Setting player position to x: " << player->getPositionX() << ", y: " << player->getPositionY() << std::endl;
		player->setPosition( player->getPositionX(),player->getPositionY());
	}
	lastTick = 0;
	currentTick = 0;
	currentState = ROAM;
	std::cout << "Finished Loading!" << std::endl << std::endl;
}
void NormalScene::eventHandler(SDL_Event& event){
	Uint8* keystate =SDL_GetKeyState(NULL);
	if( keystate[SDLK_UP]){
		player->setAnimState(Player::UP);
		level->checkEvent(0,-player->getVelocity());
		level->checkWalk(0,-player->getVelocity());
		//player->move(0,-velocity);
	}
	else if( keystate[SDLK_DOWN]){
		player->setAnimState(Player::DOWN);
		level->checkEvent(0,player->getVelocity());
		level->checkWalk(0,player->getVelocity());
		//player->move(0,velocity);
	}
	else if( keystate[SDLK_LEFT]){
		player->setAnimState(Player::LEFT);
		level->checkEvent(-player->getVelocity(),0);
		level->checkWalk(-player->getVelocity(),0);
		//player->move(-velocity,0);
	}
	else if( keystate[SDLK_RIGHT]){
		player->setAnimState(Player::RIGHT);
		level->checkEvent(player->getVelocity(),0);
		level->checkWalk(player->getVelocity(),0);
		//player->move(velocity,0);
	}
	//Runs through all the queued events
	//Note: we can create our own events
	while(SDL_PollEvent(&event)){
		switch(currentState){
		case ROAM:
			switch(event.type){
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
				case SDLK_UP:
					break;
				case SDLK_DOWN:
					break;
				case SDLK_LEFT:
					break;
				case SDLK_RIGHT:
					break;
				case SDLK_k:
					scene->setGameScene(SceneManager::EVENT);
					break;
				case SDLK_c:
					std::cout << "Starting a battle for no reason at all!" << std::endl;
					scene->setGameScene(SceneManager::BATTLE);
				case SDLK_RETURN:

					break;
				case SDLK_ESCAPE:
					scene->setGameScene(SceneManager::OPENINGMENU);
					//game->setGameOver(true);
					break;
				default:
					break;
				}
				break;
			case SDL_KEYUP:
				lastTick = 0;
				break;
			default:
				break;
			}
			break;
		case DIALOGUE:
			switch(event.type){
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
				}
			}
			break;
		case MERCHANT:
			switch(event.type){
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
				}
			}
			break;
		}
	}

}
void NormalScene::display(){
	level->renderMap();
	currentTick = SDL_GetTicks();
	if(currentTick - lastTick > 150)
	{
		lastTick = currentTick;
		//update animation and draw new frame
		player->renderPlayer();
	}
	else{
		//continue drawing last frame
		player->renderLastPlayerFrame();
	}
	if(currentState == DIALOGUE){
		std::cout << "Hey..someones talking to you" << std::endl;
	}
	level->renderMapCollision();
	SDL_Flip(scene->getScreen());
}
void NormalScene::disposeResources(){

}