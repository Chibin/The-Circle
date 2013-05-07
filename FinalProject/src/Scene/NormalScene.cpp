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
		playerModel = load_imageWhite("../Images/normal/maleModel.bmp");
		if(playerModel == 0)
			std::cout << "Image did not load" << std::endl;

	}
	//there will be three frames these animation are 24w x 32h
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
	if(player->getPositionX() == 0 && player->getPositionY()  == 0){
		std::cout << "don't know position... setting position to center of map" << std::endl;
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
	currentAnim = playerAnimDown;
	std::cout << "Done!" << std::endl;;
	std::cout << "Finished Loading!" << std::endl << std::endl;
}
void NormalScene::eventHandler(SDL_Event& event){

	//Runs through all the queued events
	//Note: we can create our own events
	while(SDL_PollEvent(&event)){
		switch(event.type){
		case SDL_KEYDOWN:
			switch(event.key.keysym.sym){
			case SDLK_UP:
				currentAnim = playerAnimUp;
				currentAnim->NextFrame();
				break;
			case SDLK_DOWN:
				currentAnim = playerAnimDown;
				currentAnim->NextFrame();
				break;
			case SDLK_LEFT:
				currentAnim = playerAnimLeft;
				currentAnim->NextFrame();
				break;
			case SDLK_RIGHT:
				currentAnim = playerAnimRight;
				currentAnim->NextFrame();
				break;
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
	SDL_Delay(125);
	SDL_FillRect(scene->getScreen(),NULL,0x221122);
	SDL_BlitSurface(tempMap,NULL,scene->getScreen(),&mapRect);
	SDL_BlitSurface(playerModel, currentAnim->GetFrame(), scene->getScreen(), &playerModelRectDest);

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