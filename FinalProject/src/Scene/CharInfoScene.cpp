#include "CharInfoScene.h"

CharInfoScene::CharInfoScene(){
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
	//loads all message here
	SDL_Color black = {0,0,0}, yellow = {255,255,0};
	font =  TTF_OpenFont("../Fonts/Viner.ttf",40);	
	TTF_SetFontStyle(font, TTF_STYLE_BOLD);
	string txt = "Status";
	statusTitle =  TTF_RenderText_Blended( font, txt.c_str(), black );
	statusTitleRect.x = 300;
	statusTitleRect.y = 150;
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
	currentChoice = MAIN;
	mainMenuChoice = 0;
	std::cout << "Finished Loading!" << std::endl;
}

void CharInfoScene::eventHandler(SDL_Event& event){

	while(SDL_PollEvent(&event)){
		switch(event.type){
		case SDL_KEYDOWN:
			switch(event.key.keysym.sym){
			case SDLK_ESCAPE:
				scene->setGameScene(SceneManager::NORMAL);
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
	if(currentChoice == SKILLS){}
	if(currentChoice == EQUIPS){}
	if(currentChoice == OPTIONS){
	
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
	std::cout << "Cleaning Finished!" << std::endl << std::endl;
}