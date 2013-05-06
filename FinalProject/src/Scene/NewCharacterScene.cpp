#include "NewCharacterScene.h"
#include "../Entity/Player.h"
#include <SDL_ttf.h>
#include <sstream>
#include <stdlib.h>
//64 width 64 height for male
NewCharScreen::NewCharScreen(SDL_Surface* screen){
	type = GameManager::CHARACTERCREATION;
	currentTick = SDL_GetTicks();
	lastTick = 0;
	char1Tick = 0;
	char2Tick = 0;
	back = false;
	selected = true;
	goBack = false;
	continued = false;
	points = 10;
	curStats = 0;
	currentStage = PICK;
	std::cout << "Entering Character Creation Screen..." << std::endl;
	std::cout << "Loading Resources..." << std::endl;
	TTF_Init();
	std::cout << "\tgoBack Resources..." ;
	/*******************load goBack resources***********************************/
	/**/backScreen = load_imageWhite("../Images/charCreation/goBack.bmp");
	/**/backScreen1 = load_imageWhite("../Images/charCreation/goBack1.bmp");
	/**/backScreenRect.x = (Sint16)game->getWindowWidth()/2 - (backScreen->w/2); 
	/**/backScreenRect.y = (Sint16)game->getWindowHeight()/2 - (backScreen->h/2); 
	/****************************************************************************/
	std::cout << "Done!" << std::endl;;

	std::cout << "\tStage1 Resources...";
	/*******************load stage1 resources************************************/
	//male portrait
	/**/malebg = load_imageWhite("../Images/charCreation/maleBG.bmp");
	/**/maleBgRect.h = 1024;
	/**/maleBgRect.w = 800;
	/**/maleBgRect.y = 0;
	/**/maleBgRect.x = 0;
	//female portait
	/**/femalebg = load_imageWhite("../Images/charCreation/femaleBG1.bmp");
	/**/femaleBgRect.h = 600;
	/**/femaleBgRect.w = 469;
	/**/femaleBgRect.y = 0;
	/**/femaleBgRect.x = 0;
	/**/
	/**///background image
	/**/bg = load_imageWhite("../Images/charCreation/bgChar2.bmp");
	/**/bgRect.x = 0;
	/**/bgRect.y = 0;
	/**/bgRect.h = (Sint16)game->getWindowHeight();
	/**/bgRect.w = (Sint16)game->getWindowWidth();
	/**/
	/**/bg1 = load_imageWhite("../Images/charCreation/bgChar3.bmp");
	/**/bgRect1.x = 0;
	/**/bgRect1.y = 0;
	/**/bgRect1.h = (Sint16)game->getWindowHeight();
	/**/bgRect1.w = (Sint16)game->getWindowWidth();
	/**/
	//male animation selected
	/**/maleChar = load_imageBlue("../Images/charCreation/maleStanding1.bmp");
	/**/maleChar1 = load_imageBlue("../Images/charCreation/maleStanding2.bmp");
	//clip the male animation
	/**/maleCharRect[0].x = 0;
	/**/maleCharRect[0].y = 0;
	/**/maleCharRect[0].w = 64;
	/**/maleCharRect[0].h = 64;
	/**/
	/**/maleCharRect[1].x = 64;
	/**/maleCharRect[1].y = 0;
	/**/maleCharRect[1].w = 64;
	/**/maleCharRect[1].h = 64;
	/**/
	/**/maleCharRect[2].x = 128;
	/**/maleCharRect[2].y = 0;
	/**/maleCharRect[2].w = 64;
	/**/maleCharRect[2].h = 64;
	/**/
	/**/femaleChar = load_imageBlue("../Images/charCreation/girlStanding1.bmp");
	/**/femaleChar1 = load_imageBlue("../Images/charCreation/girlStanding2.bmp");
	//clip the female animation
	/**/femaleCharRect[0].x = 0;
	/**/femaleCharRect[0].y = 0;
	/**/femaleCharRect[0].w = 64;
	/**/femaleCharRect[0].h = 64;
	/**/
	/**/femaleCharRect[1].x = 64;
	/**/femaleCharRect[1].y = 0;
	/**/femaleCharRect[1].w = 64;
	/**/femaleCharRect[1].h = 64;
	/**/
	/**/femaleCharRect[2].x = 128;
	/**/femaleCharRect[2].y = 0;
	/**/femaleCharRect[2].w = 64;
	/**/femaleCharRect[2].h = 64;
	/**/
	/**/char1.x = 500;
	/**/char1.y = 300;
	/**/
	/**/char2.x = 650;
	/**/char2.y = 300;
	/****************************************************************************/
	std::cout << "Done!" << std::endl;;

	std::cout << "\tStage2 Resources...";
	//male background
	malebgp2 = load_imageWhite("../Images/charCreation/bgLLYODpart2.bmp");
	malebgp2Rect.h = 600;
	malebgp2Rect.w = (Sint16)game->getWindowWidth();;
	malebgp2Rect.y = 0;
	malebgp2Rect.x = 0;

	//female background
	femalebgp2 = load_imageWhite("../Images/charCreation/bgNATALIApart2.bmp");
	femalebgp2Rect.h = 600;
	femalebgp2Rect.w = (Sint16)game->getWindowWidth();;
	femalebgp2Rect.y = 0;
	femalebgp2Rect.x = 0;

	//arrows
	arrows = load_imageWhite("../Images/charCreation/arrows.bmp");
	arrows1 = load_imageWhite("../Images/charCreation/arrows1.bmp");
	arrowsRect[0].x = 0;
	arrowsRect[0].y = 0;
	arrowsRect[0].w = 16;
	arrowsRect[0].h = 16;
	arrowsRect[1].x = 16;
	arrowsRect[1].y = 0;
	arrowsRect[1].w = 16;
	arrowsRect[1].h = 16;
	//font
	font = TTF_OpenFont("../Fonts/Lucida.ttf",18);
	std::cout << "Done!" << std::endl;;

	std::cout << "Finished Loading!" << std::endl << std::endl;
	SDL_Flip(screen);	
}


void NewCharScreen::eventHandler(SDL_Event& event){
	while(SDL_PollEvent(&event)){

		switch (currentStage){
		case GOBACK:
			switch(event.type){
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
				case SDLK_LEFT:
					goBack = true;
					break;
				case SDLK_RIGHT:
					goBack = false;
					break;
				case SDLK_z:	
					if(goBack)
						game->setGameState(GameManager::OPENINGMENU);
					else
						currentStage = PICK;
					break;
				case SDLK_RETURN:	
					if(goBack)
						game->setGameState(GameManager::OPENINGMENU);
					else
						currentStage = PICK;
					break;
				case SDLK_x:
					currentStage = PICK;
					break;

				case SDLK_ESCAPE:
					currentStage = PICK;
					break;
				}
				break;
			}
			break;
		case PICK:
			switch(event.type){
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
				case SDLK_LEFT:
					selected = true;
					break;
				case SDLK_RIGHT:
					selected = false;
					break;

				case SDLK_z:	
					if(selected){
						//set base stats for male
						baseStat[0] = 8; baseStat[1] = 5; baseStat[2] = 6 ;baseStat[3] = 6; baseStat[4] = 4; baseStat[5] = 2;
						std::cout << "Player has choosen Llyod!" << std::endl;
					}
					else{
						baseStat[0] = 5; baseStat[1] = 6; baseStat[2] = 3; baseStat[3] = 2; baseStat[4] = 7; baseStat[5] = 7;
						std::cout << "Player has choosen Natalia" << std::endl;
					}
					std::cout << "Base Stats:\n\t  HP: " << baseStat[0] << std::endl;
					std::cout << "\t  MP: " << baseStat[1] << std::endl;
					std::cout << "\t ATK: " << baseStat[2] << std::endl;
					std::cout << "\t DEF: " << baseStat[3] << std::endl;
					std::cout << "\t SPD: " << baseStat[4] << std::endl;
					std::cout << "\tMATK: " << baseStat[5] << std::endl;
					memcpy(&editStats, &baseStat,sizeof(baseStat));
					currentStage = STATS;
					break;
				case SDLK_RETURN:	
					if(selected){
						//set base stats for male
						baseStat[0] = 8; baseStat[1] = 5; baseStat[2] = 6 ;baseStat[3] = 6; baseStat[4] = 4; baseStat[5] = 2;
						std::cout << "Player has choosen Llyod!" << std::endl;
					}
					else{
						baseStat[0] = 5; baseStat[1] = 6; baseStat[2] = 3; baseStat[3] = 2; baseStat[4] = 7; baseStat[5] = 7;
						std::cout << "Player has choosen Natalia" << std::endl;
					}
					std::cout << "Base Stats:\n\t  HP: " << baseStat[0] << std::endl;
					std::cout << "\t  MP: " << baseStat[1] << std::endl;
					std::cout << "\t ATK: " << baseStat[2] << std::endl;
					std::cout << "\t DEF: " << baseStat[3] << std::endl;
					std::cout << "\t SPD: " << baseStat[4] << std::endl;
					std::cout << "\tMATK: " << baseStat[5] << std::endl;
					memcpy(&editStats, &baseStat,sizeof(baseStat));
					points = 10;
					curStats = 0;
					currentStage = STATS;
					break;
				case SDLK_x:
					currentStage = GOBACK;
					break;
				case SDLK_ESCAPE:
					currentStage = GOBACK;
					break;
				default:
					break;
				}
			}
			break;
		case STATS:
			switch(event.type){
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
				case SDLK_LEFT:
					if(editStats[curStats]-1 >= baseStat[curStats]){
						editStats[curStats]--;
						points++;
					}
					break;
				case SDLK_RIGHT:
					if(points > 0 && editStats[curStats] < 15){
						points--;
						editStats[curStats]++;
					}

					break;

				case SDLK_UP:
					continued = false;
					curStats--;
					if (curStats < 0)
						curStats = 0;
					break;
				case SDLK_DOWN:
					curStats++;
					if(points != 0){

						if (curStats > 5)
							curStats = 5;
					}
					if(points == 0 && curStats == 6 ){
						//	std::cout << "Available to continue!" << std::endl;
						//std::cout << "points: " << points << "curStats: " << curStats << std::endl;
						continued = true;
					}
					break;
				case SDLK_z:
					if(continued){
						std::cout << "\nCharacter Created...";
						Player::getInstance().setStats(editStats[0],editStats[1],editStats[2],editStats[3],editStats[4],editStats[5]);
						if(selected){
							std::cout << "Player created Llyod" << std::endl;
							Player::getInstance().setType(Player::PlayerType::LLYOD);
						}
						else{
							std::cout << "Player created Natilia" << std::endl;
							Player::getInstance().setType(Player::PlayerType::NATILIA);
						}
						std::cout << "Starting Stats:\n\t  HP: " << editStats[0] << std::endl;
						std::cout << "\t  MP: " << editStats[1] << std::endl;
						std::cout << "\t ATK: " << editStats[2] << std::endl;
						std::cout << "\t DEF: " << editStats[3] << std::endl;
						std::cout << "\t SPD: " << editStats[4] << std::endl;
						std::cout << "\tMATK: " << editStats[5] << std::endl;
						game->setGameState(GameManager::NORMAL);
					}
					break;
				case SDLK_RETURN:	
					if(continued){
						std::cout << "\nCharacter Created...";
						Player::getInstance().setStats(editStats[0],editStats[1],editStats[2],editStats[3],editStats[4],editStats[5]);
						if(selected){
							std::cout << "Player created Llyod" << std::endl;
							Player::getInstance().setType(Player::PlayerType::LLYOD);
						}
						else{
							std::cout << "Player created Natilia" << std::endl;
							Player::getInstance().setType(Player::PlayerType::NATILIA);
						}
						std::cout << "Starting Stats:\n\t  HP: " << editStats[0] << std::endl;
						std::cout << "\t  MP: " << editStats[1] << std::endl;
						std::cout << "\t ATK: " << editStats[2] << std::endl;
						std::cout << "\t DEF: " << editStats[3] << std::endl;
						std::cout << "\t SPD: " << editStats[4] << std::endl;
						std::cout << "\tMATK: " << editStats[5] << std::endl;
						game->setGameState(GameManager::NORMAL);
					}

					break;
				case SDLK_x:
					currentStage = PICK;
					break;
				case SDLK_ESCAPE:
					currentStage = PICK;
					break;
				default:
					break;
				}
			}
			break;
		}
	}
}

void NewCharScreen::display(SDL_Surface* screen){

	currentTick = SDL_GetTicks();
	if(currentTick - lastTick > 150)
	{
		lastTick = currentTick;
		//update animation
		if(selected){
			char2Tick = 0;
			if(char1Tick == 0)
				back = false;
			if(!back)
				char1Tick++;
			else
				char1Tick--;
			if(char1Tick == 2){
				back = !back;
			}	
			if(char1Tick == 0)
				back = !back;
		}
		else{
			char1Tick = 0;
			if(char2Tick == 0) 
				back = false;
			if(!back)
				char2Tick++;
			else
				char2Tick--;
			if(char1Tick == 2)
				back = !back;	
			if(char1Tick == 0)
				back = !back;
		}
	}

	if (selected){
		if(currentStage == PICK){
			SDL_BlitSurface(bg,NULL,screen,&bgRect);
			SDL_BlitSurface(malebg,NULL,screen,&maleBgRect);
			SDL_BlitSurface(maleChar1,&maleCharRect[char1Tick],screen,&char1);
			SDL_BlitSurface(femaleChar,&femaleCharRect[char2Tick],screen,&char2);
		}
		if(currentStage == STATS){
			SDL_BlitSurface(malebgp2,NULL,screen,&malebgp2Rect);
			SDL_BlitSurface(malebg,NULL,screen,&maleBgRect);
		}
	}
	else{
		if(currentStage == PICK){
			SDL_BlitSurface(bg1,NULL,screen,&bgRect1);
			SDL_BlitSurface(femalebg,NULL,screen,&femaleBgRect);
			SDL_BlitSurface(maleChar,&maleCharRect[char1Tick],screen,&char1);
			SDL_BlitSurface(femaleChar1,&femaleCharRect[char2Tick],screen,&char2);
		}
		if(currentStage == STATS){
			SDL_BlitSurface(femalebgp2,NULL,screen,&femalebgp2Rect);
			SDL_BlitSurface(femalebg,NULL,screen,&femaleBgRect);
		}

	}

	if(currentStage == STATS){
		for(int i = 0; i < 6; i++){
			arrowsRect[0].x = 0;
			//draws the left side arrows
			arrowsRect[1].x = 570;
			arrowsRect[1].y = 257+ 22*i;
			if(editStats[i] > baseStat[i])
				if(curStats == i)
					SDL_BlitSurface(arrows1, &arrowsRect[0], screen, &arrowsRect[1]);
				else
					SDL_BlitSurface(arrows, &arrowsRect[0], screen, &arrowsRect[1]);
			//draw the numbers
			SDL_Surface * nums;
			SDL_Color black = {0,0,0};
			{std::ostringstream oss;
			oss << editStats[i];
			nums = TTF_RenderText_Blended(font,oss.str().c_str(),black);
			numRect.x = 620;
			numRect.y = 257+ 22*i;
			SDL_BlitSurface(nums, NULL, screen, &numRect);
			SDL_FreeSurface(nums);
			}
			{std::ostringstream test;
			SDL_Surface * pointSurface;
			test << points;
			pointSurface = TTF_RenderText_Blended(font,test.str().c_str(),black);
			pointRect.x = 620;
			pointRect.y = 387;
			SDL_BlitSurface(pointSurface, NULL, screen, &pointRect);
			SDL_FreeSurface(pointSurface);
			}
			//draws the right side arrows
			arrowsRect[0].x = 16;
			arrowsRect[1].x = 670;
			arrowsRect[1].y = 257+ 22*i;
			if(editStats[i] < 15 )
				if(curStats == i)
					SDL_BlitSurface(arrows1, &arrowsRect[0], screen, &arrowsRect[1]);
				else
					SDL_BlitSurface(arrows, &arrowsRect[0], screen, &arrowsRect[1]);
			if(points == 0){
				TTF_Font* temp;
				temp = TTF_OpenFont("../Fonts/Lucida.ttf",18);
				std::ostringstream test;
				SDL_Surface *text_surface;
				test << "Continue...";
				if(continued)
					temp = TTF_OpenFont("../Fonts/Lucida.ttf", 22);
				text_surface	= TTF_RenderText_Blended( temp, test.str().c_str(), black );
				finish.x = 670;
				finish.y = 387;
				finish.w = text_surface->w;
				finish.h = text_surface->h;
				SDL_BlitSurface(text_surface, NULL, screen, &finish);

			}
		}

	}
	if(currentStage == GOBACK)
		if(goBack)
			SDL_BlitSurface(backScreen, NULL, screen, &backScreenRect);
		else
			SDL_BlitSurface(backScreen1, NULL, screen, &backScreenRect);

	SDL_Flip(screen);	
}

void NewCharScreen::disposeResources(){
	std::cout << "Cleaning Character Creation Scene" << std::endl;
	SDL_FreeSurface( backScreen );
	SDL_FreeSurface( backScreen1);
	SDL_FreeSurface( maleChar );
	SDL_FreeSurface( maleChar1 );
	SDL_FreeSurface( femaleChar );
	SDL_FreeSurface( femaleChar1 );
	SDL_FreeSurface( bg );
	SDL_FreeSurface( bg1 );
	SDL_FreeSurface( malebg );
	SDL_FreeSurface( femalebg );
	SDL_FreeSurface( malebgp2 );
	SDL_FreeSurface( femalebgp2 );
	SDL_FreeSurface( arrows );
	SDL_FreeSurface( arrows1 );

	std::cout << "Cleaning Finished!" << std::endl << std::endl;
}