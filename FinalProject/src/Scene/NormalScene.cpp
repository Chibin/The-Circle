#include "NormalScene.h"

NormalScene::NormalScene(){
	type = SceneManager::NORMAL;
	std::cout << "Entering Normal Screen..." << std::endl;
	std::cout << "Loading Resources..." << std::endl;
	/*******************************************************************************/
	/* *******************************LEVEL*****************************************/
	/*******************************************************************************/

	std::cout << "\tLoading Level..." ;
	level->loadMap("testLevel2");
	std::cout << "Done!" << std::endl;

	/*******************************************************************************/
	/*****************************SET SETTINGS**************************************/
	/*******************************************************************************/
	std::cout << "\tPlacing Character on map.\n\t\tResult: " ;
	if(player->getPositionX() == 0 && player->getPositionY()  == 0){
		std::cout << "don't know position... setting position to center of map" << std::endl;
		//player->setPosition(level->getWidth()/2 - 12,level->getHeight()/2 +100);
		player->setPosition(scene->getWindowWidth()/2 - 12,scene->getWindowHeight()/2 - 16);
		scene->setCamera();
	}
	else{
		std::cout << "Setting player position to x: " << player->getPositionX() << ", y: " << player->getPositionY() << std::endl;
		player->setPosition( player->getPositionX(),player->getPositionY());
	}
	lastTick = 0;
	currentTick = 0;
	currentState = ROAM;
	player->setAnimState(Player::DOWN);
	std::cout << "Finished Loading!" << std::endl << std::endl;
}
void NormalScene::eventHandler(SDL_Event& event){
	Uint8* keystate =SDL_GetKeyState(NULL);
	if( keystate[SDLK_UP]){
		player->setAnimState(Player::UP);
		level->checkEvent(0,-player->getVelocity());
		level->checkWalk(0,-player->getVelocity());
	}
	else if( keystate[SDLK_DOWN]){
		player->setAnimState(Player::DOWN);
		level->checkEvent(0,player->getVelocity());
		level->checkWalk(0,player->getVelocity());
	}
	else if( keystate[SDLK_LEFT]){
		player->setAnimState(Player::LEFT);
		level->checkEvent(-player->getVelocity(),0);
		level->checkWalk(-player->getVelocity(),0);
	}
	else if( keystate[SDLK_RIGHT]){
		player->setAnimState(Player::RIGHT);
		level->checkEvent(player->getVelocity(),0);
		level->checkWalk(player->getVelocity(),0);
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
					scene->setGameScene(SceneManager::CHARINFO);
					//scene->setGameScene(SceneManager::OPENINGMENU);
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
		case EVENT:
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
	
	level->renderMapLayer(0);
	level->renderMapLayer(1);
	//level->renderMapLayer(2);
	//level->renderMapLayer(3);
	//level->renderMapLayer(4);
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
		level->renderMapLayer(2);
	//draws where collision should be at
	//level->renderMapLayer(3);
	//draws where events should happen
	//level->renderMapLayer(4);
	SDL_Flip(scene->getScreen());
}
void NormalScene::disposeResources(){

}