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
	level->loadMap("../levels/testLevel.tmx");
	tempMap = SDL_LoadBMP("../levels/map.bmp");
	mapRect.x = scene->getWindowWidth()/2 - tempMap->w/2;
	mapRect.y = scene->getWindowHeight()/2 - tempMap->h/2;
	//}
	std::cout << "Done!" << std::endl;
	/*******************************************************************************/
	/* ***************************CHARACTER*****************************************/
	/*******************************************************************************/

	std::cout << "\tLoading Character..." ;
	if(player->getType()==0){
		playerModel = load_imageWhite("../Images/normal/maleModel.bmp");	

	}
	else{
		playerModel = load_imageWhite("../Images/normal/femaleModel.bmp");

	}
	std::cout << "Done!" << std::endl;

	/*******************************************************************************/
	/* ***************************ANIMATION*****************************************/
	/*******************************************************************************/

	//there will be three frames these animation are 24w x 32h
	std::cout << "\tLoading Animation..." ;
	playerAnimUp = new Animation;
	playerAnimDown = new Animation;
	playerAnimLeft = new Animation;
	playerAnimRight = new Animation;

	playerAnimUp->Init(3);
	playerAnimDown->Init(3);
	playerAnimLeft->Init(3);
	playerAnimRight->Init(3);
	//up
	//(frameNumber, x,y,w,h)
	playerAnimUp->SetFrame(0, 0, 0, 24, 32);
	playerAnimUp->SetFrame(1, 24, 0, 24, 32);
	playerAnimUp->SetFrame(2, 48, 0, 24, 32);
	//right
	playerAnimRight->SetFrame(0, 0, 32, 24, 32);
	playerAnimRight->SetFrame(1, 24, 32, 24, 32);
	playerAnimRight->SetFrame(2, 48, 32, 24, 32);
	//down
	playerAnimDown->SetFrame(0, 0, 64, 24, 32);
	playerAnimDown->SetFrame(1, 24, 64, 24, 32);
	playerAnimDown->SetFrame(2, 48, 64, 24, 32);
	//left
	playerAnimLeft->SetFrame(0, 0, 96, 24, 32);
	playerAnimLeft->SetFrame(1, 24, 96, 24, 32);
	playerAnimLeft->SetFrame(2, 48, 96, 24, 32);
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
	//playerModelRect.x = player->getPositionX();
	//playerModelRect.y = player->getPositionY();
	currentAnim = playerAnimDown;
	velocity = 4;
	lastTick = 0;
	currentTick = 0;
	tempAnim = playerAnimDown->GetFrame();
	currentState = ROAM;
	std::cout << "Finished Loading!" << std::endl << std::endl;
}
void NormalScene::eventHandler(SDL_Event& event){
	Uint8* keystate =SDL_GetKeyState(NULL);
	if( keystate[SDLK_UP]){
		currentAnim = playerAnimUp;
		currentAnim->NextFrame();
		player->move(0,-velocity);
	}
	else if( keystate[SDLK_DOWN]){
		currentAnim = playerAnimDown;
		currentAnim->NextFrame();
		player->move(0,velocity);
	}
	else if( keystate[SDLK_LEFT]){
		currentAnim = playerAnimLeft;
		currentAnim->NextFrame();
		player->move(-velocity,0);
	}
	else if( keystate[SDLK_RIGHT]){
		currentAnim = playerAnimRight;
		currentAnim->NextFrame();
		player->move(velocity,0);
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
	//SDL_Delay(125);
	SDL_FillRect(scene->getScreen(),NULL,0x221122);
	SDL_BlitSurface(tempMap,NULL,scene->getScreen(),&mapRect);	
	currentTick = SDL_GetTicks();
	if(currentTick - lastTick > 150)
	{
		lastTick = currentTick;
		//update animation and draw new frame
		SDL_BlitSurface(playerModel, currentAnim->GetFrame(), scene->getScreen(), player->getPlayerPosition());
		tempAnim = currentAnim->GetFrame();
	}
	else{
		//continue drawing last frame
		SDL_BlitSurface(playerModel, tempAnim, scene->getScreen(), player->getPlayerPosition());
	}
	if(currentState == DIALOGUE){
		std::cout << "Hey..someones talking to you" << std::endl;
	}
	SDL_Flip(scene->getScreen());
}
void NormalScene::disposeResources(){

	SDL_FreeSurface(playerModel);
	SDL_FreeSurface(tempMap);
	delete playerAnimUp;
	delete playerAnimDown;
	delete playerAnimLeft;
	delete playerAnimRight;

}