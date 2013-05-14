#include "CharInfoScene.h"

CharInfoScene::CharInfoScene(){
	if(!TTF_WasInit)
		TTF_Init();
	type = SceneManager::CHARINFO;
	std::cout << "Entering CharInfo Screen..." << std::endl;
	std::cout << "Loading Resources..." << std::endl;
	//loads background
	SDL_Surface* loadedImage = IMG_Load("../Images/menu/bg.jpg");
	bg = SDL_DisplayFormatAlpha(loadedImage);
	SDL_FreeSurface(loadedImage);
	bgRect.x = 0;
	bgRect.y = 0;
	//loads the top menu
	loadedImage = IMG_Load("../Images/menu/menuTop.png");
	menuTop = SDL_DisplayFormatAlpha(loadedImage);
	SDL_FreeSurface(loadedImage);
	loadedImage = IMG_Load("../Images/menu/menuTop1.png");
	menuTop1 = SDL_DisplayFormatAlpha(loadedImage);
	SDL_FreeSurface(loadedImage);
	loadedImage = IMG_Load("../Images/menu/menuTop2.png");
	menuTop2 = SDL_DisplayFormatAlpha(loadedImage);
	SDL_FreeSurface(loadedImage);
	loadedImage = IMG_Load("../Images/menu/menuTop3.png");
	menuTop3 = SDL_DisplayFormatAlpha(loadedImage);
	SDL_FreeSurface(loadedImage);
	menuTopRect.x = 100;
	menuTopRect.y = 25;
	loadedImage = IMG_Load("../Images/menu/secondaryBg.png");
	secondBG = SDL_DisplayFormatAlpha(loadedImage);
	SDL_FreeSurface(loadedImage);
	loadedImage = IMG_Load("../Images/menu/hand.png");
	hand = SDL_DisplayFormatAlpha(loadedImage);
	SDL_FreeSurface(loadedImage);
	//loads status
	loadedImage = IMG_Load("../Images/menu/status1.png");
	status1 =  SDL_DisplayFormatAlpha(loadedImage);
	SDL_FreeSurface(loadedImage);
	status1Rect.x = 100;
	status1Rect.y = 210;
	loadedImage = IMG_Load("../Images/menu/face.png");
	portrait = SDL_DisplayFormatAlpha(loadedImage);
	SDL_FreeSurface(loadedImage);
	if(player->getType() == 1){
		loadedImage = IMG_Load("../Images/menu/bgCollete.png");
		bgChar =  SDL_DisplayFormatAlpha(loadedImage);
		SDL_FreeSurface(loadedImage);
		portraitSrcRect.x = 0;
		portraitSrcRect.y = 66;
		portraitSrcRect.w = 66;
		portraitSrcRect.h = 66;
		bgCharRect.x = 400;
		bgCharRect.y = 150;
	}
	else{
		loadedImage = IMG_Load("../Images/menu/bgLloyd.png");
		bgChar =  SDL_DisplayFormatAlpha(loadedImage);
		SDL_FreeSurface(loadedImage);
		portraitSrcRect.x = 0;
		portraitSrcRect.y = 0;
		portraitSrcRect.w = 66;
		portraitSrcRect.h = 66;
		bgCharRect.x = 400;
		bgCharRect.y = 210;
	}
	portraitDestRect.x = 110;
	portraitDestRect.y = 225;


	//options
	loadedImage = IMG_Load("../Images/menu/status1.png");
	status1 =  SDL_DisplayFormatAlpha(loadedImage);
	SDL_FreeSurface(loadedImage);
	loadedImage = IMG_Load("../Images/menu/optionBg.png");
	optionBg =  SDL_DisplayFormatAlpha(loadedImage);
	SDL_FreeSurface(loadedImage);
	optionBgRect.x = 300;
	optionBgRect.y = 210;
	secondBGRect.x = 100;
	secondBGRect.y = 210;
	//loads all message here
	SDL_Color black = {0,0,0}, yellow = {255,255,0};
	font =  TTF_OpenFont("../Fonts/Viner.ttf",40);	
	TTF_SetFontStyle(font, TTF_STYLE_BOLD);
	string txt = "Status";
	statusTitle =  TTF_RenderText_Blended( font, txt.c_str(), black );
	statusTitleRect.x = 320;
	statusTitleRect.y = 150;
	txt = "Options";
	status4 = TTF_RenderText_Blended( font, txt.c_str(), black );
	txt = "Skills";
	status2 = TTF_RenderText_Blended( font, txt.c_str(), black );
	txt = "Items";
	status3 = TTF_RenderText_Blended( font, txt.c_str(), black );
	font =  TTF_OpenFont("../Fonts/coolvetica.ttf",18);	
	txt = "Current XP:";
	currXpTxt = TTF_RenderText_Blended( font, txt.c_str(), black );
	currXpTxtRect.x = 400;
	currXpTxtRect.y = 240;
	txt = "TNL:";
	nextXPTxtRect.x = 450;
	nextXPTxtRect.y = 260;
	nextXPTxt = TTF_RenderText_Blended( font, txt.c_str(), black );
	txt = "HP: ";
	hpTxtRect.x = 180;
	hpTxtRect.y = 240;
	hpTxt = TTF_RenderText_Blended( font, txt.c_str(), black );
	txt = "MP: ";
	mpTxtRect.x = 180;
	mpTxtRect.y = 260;
	mpTxt = TTF_RenderText_Blended( font, txt.c_str(), black );
	if(player->getType() == 0)
		txt = "Lloyd";
	else
		txt = "Collete";
	font =  TTF_OpenFont("../Fonts/coolvetica.ttf",20);	
	TTF_SetFontStyle(font, TTF_STYLE_BOLD);
	nameTxt = TTF_RenderText_Blended( font, txt.c_str(), black );
	nameTxtRect.x = 180;
	nameTxtRect.y = 220;
	font =  TTF_OpenFont("../Fonts/coolvetica.ttf",32);	
	txt = "Save";
	saveTxt = TTF_RenderText_Blended( font, txt.c_str(), black );
	saveTxtRect.x = 365 ;
	saveTxtRect.y = 245;
	txt = "Load";
	loadTxt = TTF_RenderText_Blended( font, txt.c_str(), black );
	loadTxtRect.x = 365;
	loadTxtRect.y = 280;
	txt = "Quit To Menu";
	quitToMenu = TTF_RenderText_Blended( font, txt.c_str(), black );
	quitToMenuRect.x = 312;
	quitToMenuRect.y = 320;
	txt = "Quit Game";
	quitGame = TTF_RenderText_Blended( font, txt.c_str(), black );
	quitGameRect.x = 330;
	quitGameRect.y = 360;

	currentChoice = MAIN;
	mainMenuChoice = 0;
	optionChoice = 0;
	std::cout << "Finished Loading!" << std::endl;
}

void CharInfoScene::eventHandler(SDL_Event& event){

	while(SDL_PollEvent(&event)){
		switch(event.type){
		case SDL_KEYDOWN:
			switch(event.key.keysym.sym){
			case SDLK_ESCAPE:
				switch (currentChoice){
				case MAIN:
					scene->setGameScene(SceneManager::NORMAL);
					break;
				case STATUS:
					currentChoice = MAIN;
					break;
				case SKILLS:
					currentChoice = MAIN;
					break;
				case EQUIPS:
					currentChoice = MAIN;
					break;
				case OPTIONS:
					currentChoice = MAIN;
					break;
				}
				break;
			case SDLK_z:
				switch (currentChoice){
				case MAIN:
					if(mainMenuChoice == 0)
						currentChoice = STATUS;
					if(mainMenuChoice == 1)
						currentChoice = SKILLS;
					if(mainMenuChoice == 2)
						currentChoice = EQUIPS;
					if(mainMenuChoice == 3)
						currentChoice = OPTIONS;
					break;
				case STATUS:

					break;
				case EQUIPS:
					break;
				case OPTIONS:
					switch(optionChoice){
					case 0:
						game->saveGame();
						break;
					case 1:
						game->loadGame();
						break;
					case 2:
						scene->setGameScene(SceneManager::OPENINGMENU);
						break;
					case 3:
						game->setGameOver(true);
					}

					break;

				}
				break;

			case SDLK_RETURN:
				switch (currentChoice){
				case MAIN:
					if(mainMenuChoice == 0)
						currentChoice = STATUS;
					if(mainMenuChoice == 1)
						currentChoice = SKILLS;
					if(mainMenuChoice == 2)
						currentChoice = EQUIPS;
					if(mainMenuChoice == 3)
						currentChoice = OPTIONS;
					break;
				case STATUS:

					break;
				case EQUIPS:
					break;
				case OPTIONS:
					break;
				}
				break;
			case SDLK_x:
				switch (currentChoice){
				case MAIN:
					scene->setGameScene(SceneManager::NORMAL);
					break;
				case STATUS:
					currentChoice = MAIN;
					break;
				case SKILLS:
					currentChoice = MAIN;
					break;
				case EQUIPS:
					currentChoice = MAIN;
					break;
				case OPTIONS:
					currentChoice = MAIN;
					break;
				}
				break;
			case SDLK_LEFT:
				switch (currentChoice){
				case MAIN:
					mainMenuChoice--;
					if(mainMenuChoice <0)
						mainMenuChoice = 0;
					break;
				case STATUS:
					break;
				case EQUIPS:
					break;
				case OPTIONS:
					break;
				}
				break;

			case SDLK_RIGHT:
				switch (currentChoice){
				case MAIN:
					mainMenuChoice++;
					if(mainMenuChoice > 3)
						mainMenuChoice = 3;
					break;
				case STATUS:
					break;

				}
				break;
			case SDLK_DOWN:
				switch (currentChoice){
				case MAIN:
					break;
				case STATUS:
					break;
				case EQUIPS:
					break;
				case OPTIONS:
					optionChoice++;
					if(optionChoice >3)
						optionChoice = 3;
					break;
				}
				break;
			case SDLK_UP:
				switch (currentChoice){
				case MAIN:
					break;
				case STATUS:
					break;
				case EQUIPS:
					break;
				case OPTIONS:
					optionChoice--;
					if(optionChoice < 0)
						optionChoice = 0;
					break;
				}
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


void CharInfoScene::display(){
	//	SDL_FillRect(scene->getScreen(),NULL,0x221122);
	SDL_BlitSurface( bg, NULL, scene->getScreen(), &bgRect);

	switch(mainMenuChoice){
	case 0:
		SDL_BlitSurface( menuTop, NULL, scene->getScreen(), &menuTopRect);
		handRect.x = 55;
		handRect.y = 50;
		break;
	case 1:
		SDL_BlitSurface( menuTop1, NULL, scene->getScreen(), &menuTopRect);
		handRect.x = 170;
		handRect.y = 50;
		break;
	case 2:
		SDL_BlitSurface( menuTop2, NULL, scene->getScreen(), &menuTopRect);
		handRect.x = 280;
		handRect.y = 50;
		break;
	case 3:
		SDL_BlitSurface( menuTop3, NULL, scene->getScreen(), &menuTopRect);
		handRect.x = 480;
		handRect.y = 50;
		break;
	default:
		break;
	}

	//	SDL_BlitSurface( hand, NULL, scene->getScreen(), &handRect);
	if(currentChoice == STATUS || mainMenuChoice == 0){
		SDL_BlitSurface( statusTitle, NULL, scene->getScreen(), &statusTitleRect);
		SDL_BlitSurface( bgChar, NULL, scene->getScreen(), &bgCharRect);
		SDL_BlitSurface( status1, NULL, scene->getScreen(), &status1Rect);
		SDL_BlitSurface( portrait, &portraitSrcRect, scene->getScreen(), &portraitDestRect);
		//text
		SDL_BlitSurface( currXpTxt, NULL, scene->getScreen(), &currXpTxtRect);
		SDL_BlitSurface( nextXPTxt, NULL, scene->getScreen(), &nextXPTxtRect);
		SDL_BlitSurface( hpTxt, NULL, scene->getScreen(), &hpTxtRect);
		SDL_BlitSurface( mpTxt, NULL, scene->getScreen(), &mpTxtRect);
		SDL_BlitSurface( nameTxt, NULL, scene->getScreen(), &nameTxtRect);
		//stats
		SDL_Color fgColor = {0,0,0};
		font =  TTF_OpenFont("../Fonts/coolvetica.ttf",18);	
		std::ostringstream oss;
		oss << player->getXP();
		currXp = TTF_RenderText_Blended(font,oss.str().c_str(),fgColor);
		currXpRect.x = 500;
		currXpRect.y = 240;
		SDL_BlitSurface( currXp, NULL, scene->getScreen(), &currXpRect);
		oss.str("");
		oss << player->getMaxXp()-player->getXP();
		nextXP = TTF_RenderText_Blended(font,oss.str().c_str(),fgColor);
		nextXpRect.x = 500;
		nextXpRect.y = 260;
		SDL_BlitSurface( nextXP, NULL, scene->getScreen(), &nextXpRect);
		oss.str("");
		oss	<< player->getHP() << "/" << player->getMaxHP();
		hp = TTF_RenderText_Blended(font,oss.str().c_str(),fgColor);
		hpRect.x = 220;
		hpRect.y = 240;
		SDL_BlitSurface( hp, NULL, scene->getScreen(), &hpRect);
		oss.str("");
		oss << player->getMP() << "/" << player->getMaxMP();
		mp = TTF_RenderText_Blended(font,oss.str().c_str(),fgColor);
		mpRect.x = 220;
		mpRect.y = 260;
		SDL_BlitSurface( mp, NULL, scene->getScreen(), &mpRect);
		oss.str("");
		font =  TTF_OpenFont("../Fonts/coolvetica.ttf",20);	
		TTF_SetFontStyle(font, TTF_STYLE_BOLD);
		oss << "Level: " << player->getLevel();
		level = TTF_RenderText_Blended(font,oss.str().c_str(),fgColor);
		levelRect.x = 600;
		levelRect.y = 220;
		SDL_BlitSurface( level, NULL, scene->getScreen(), &levelRect);

		if(currentChoice == STATUS){
			handRect.x = 40;
			handRect.y = 240;
		}
	}
	if(currentChoice == SKILLS || mainMenuChoice == 1){
		SDL_BlitSurface( secondBG, NULL, scene->getScreen(), &secondBGRect);
		SDL_BlitSurface( status3, NULL, scene->getScreen(), &statusTitleRect);
	}
	if(currentChoice == EQUIPS || mainMenuChoice == 2){
		SDL_BlitSurface( secondBG, NULL, scene->getScreen(), &secondBGRect);
		SDL_BlitSurface( status3, NULL, scene->getScreen(), &statusTitleRect);
	}
	if(currentChoice == OPTIONS || mainMenuChoice == 3){
		SDL_BlitSurface( status4, NULL, scene->getScreen(), &statusTitleRect);
		SDL_BlitSurface( optionBg, NULL, scene->getScreen(), &optionBgRect);	
		SDL_BlitSurface( saveTxt, NULL, scene->getScreen(), &saveTxtRect);	
		SDL_BlitSurface( loadTxt, NULL, scene->getScreen(), &loadTxtRect);	
		SDL_BlitSurface( quitToMenu, NULL, scene->getScreen(), &quitToMenuRect);	
		SDL_BlitSurface( quitGame, NULL, scene->getScreen(), &quitGameRect);	
		if(currentChoice == OPTIONS){
			switch(optionChoice)
			{
			case 0:
				handRect.x = 305;
				handRect.y = 245;
				break;
			case 1:
				handRect.x = 305;
				handRect.y = 280;
				break;
			case 2:
				handRect.x = 252;
				handRect.y = 320;
				break;
			case 3:
				handRect.x = 270;
				handRect.y = 360;
				break;
			}
		}
	}
	SDL_BlitSurface( hand, NULL, scene->getScreen(), &handRect);
	SDL_Flip(scene->getScreen());
}

void CharInfoScene::disposeResources(){
	std::cout << "Cleaning CharInfo Scene" << std::endl;
	SDL_FreeSurface(bg);
	SDL_FreeSurface(menuTop);
	SDL_FreeSurface(menuTop1);
	SDL_FreeSurface(menuTop2);
	SDL_FreeSurface(menuTop3);
	SDL_FreeSurface(status1);
	SDL_FreeSurface(statusTitle);
	SDL_FreeSurface(bgChar);
	SDL_FreeSurface(portrait);
	SDL_FreeSurface(currXpTxt);
	SDL_FreeSurface(nextXPTxt);
	SDL_FreeSurface(hpTxt);
	SDL_FreeSurface(mpTxt);
	SDL_FreeSurface(nameTxt);
	SDL_FreeSurface(currXp);
	SDL_FreeSurface(nextXP);
	SDL_FreeSurface(hp);
	SDL_FreeSurface(mp);
	SDL_FreeSurface(level);
	SDL_FreeSurface(status4);
	SDL_FreeSurface(saveTxt);
	SDL_FreeSurface(loadTxt);
	SDL_FreeSurface(quitToMenu);
	SDL_FreeSurface(quitGame);
	SDL_FreeSurface(optionBg);

	std::cout << "Cleaning Finished!" << std::endl << std::endl;
}