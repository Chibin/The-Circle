#include "NormalScene.h"

NormalScene::NormalScene(){
	type = SceneManager::NORMAL;
	std::cout << "Entering Normal Screen..." << std::endl;
	std::cout << "Loading Resources..." << std::endl;
	/*******************************************************************************/
	/* *******************************LEVEL*****************************************/
	/*******************************************************************************/

	
	/*******************************************************************************/
	/* ***************************CHARACTER*****************************************/
	/*******************************************************************************/
	textBox = IMG_Load("../Images/npc/bgtext.png");
	textBox = SDL_DisplayFormatAlpha(textBox);
	textBoxRect.x = 0;
	textBoxRect.y = 400;
	textBoxRect.h = 100;
	textBoxRect.w = 200;
	/*******************************************************************************/
	/*****************************SET SETTINGS**************************************/
	/*******************************************************************************/
	std::cout << "\tPlacing Character on map.\n\t\tResult: " ;
	if(player->getPositionX() == 0 && player->getPositionY()  == 0){
		std::cout << "don't know position... setting position to center of map" << std::endl;
		//player->setPosition(level->getWidth()/2 - 12,level->getHeight()/2 +100);
		//player->setPosition((int)scene->getWindowWidth()/2 - 12, (int)scene->getWindowHeight()/2 - 16);
		//scene->setCamera();
	}
	else{
		std::cout << "Setting player position to x: " << player->getPositionX() << ", y: " << player->getPositionY() << std::endl;
	//	player->setPosition( player->getPositionX(),player->getPositionY());
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
					//std::cout << "Pressed Enter!!" << std::endl;
					for(int i=0; i<(int)level->NPCvector.size(); i++) // check if trying to talk to an NPC
					{
						int xdiff = abs(player->getPositionX() - level->NPCvector[i]->getRect()->x);
						int ydiff = abs(player->getPositionY() - level->NPCvector[i]->getRect()->y);
						if(xdiff < 20 && ydiff < 20) // some random range
						{
							std::cout << level->NPCvector[i]->getName() << ":\n";
							level->speakingNPC = i;
							//->NPCvector[level->speakingNPC]->sentence = 0;
							npcText = level->NPCvector[level->speakingNPC]->speak();
							currentState = DIALOGUE;
						}
					}
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
				default:
					break;
				}
			case SDLK_RETURN:
				npcText = level->NPCvector[level->speakingNPC]->speak();
			default:
				break;
			}
			break;
		case EVENT:
			switch(event.type){
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
				default:
					break;
				}
			default:
				break;
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

	level->renderNPC(); // render NPCs layer
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
	level->renderMapLayer(2);
	if(currentState == DIALOGUE){
		//std::cout << "Hey " << level->NPCvector[level->speakingNPC]->getName() << " is speaking to you." << std::endl;
		if (npcText != "-1")
		{
			//std::cout << npcText << std::endl;
			//temp = level->NPCvector[level->speakingNPC]->speak();
			SDL_BlitSurface(textBox,NULL,scene->getScreen(), &textBoxRect);
			level->NPCvector[level->speakingNPC]->displayText(scene->getScreen());
		}
		else
		{
			std::cout << "---------------------------------------------------------------------\n";//std::endl;
			currentState = ROAM;
		}
	}
	//draws where collision should be at
	//level->renderMapLayer(3);
	//draws where events should happen
	//level->renderMapLayer(4);
	SDL_Flip(scene->getScreen());
}
void NormalScene::disposeResources(){

}