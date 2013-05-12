#include "EventScene.h"
EventScene::EventScene(){
	type = SceneManager::EVENT;
	std::cout << "Entering Event Scene" << std::endl;
	std::cout << "Loading Event Resources..." << std::endl; 

	//loads the background images
	SDL_Surface *temp;
	temp = IMG_Load("../Images/event/merchantstore.png");
	bg = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
	bgRectSrc.x = 0;
	bgRectSrc.y = 0;
	bgRectSrc.h = bg->h;
	bgRectSrc.w = bg->w;	
	bgRect.x = 0;
	bgRect.y = 0;
	bgRect.w = 600;
	bgRect.h = 450;
	//loads portiat
	temp = IMG_Load("../Images/event/face.bmp");
	portait = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);

	//loads the merchant girl
	SDL_Surface* loadedImage = IMG_Load("../Images/event/girlportraits.png");
	sideRight = SDL_DisplayFormatAlpha(loadedImage);
	SDL_FreeSurface(loadedImage);
	sideLeft = load_imageWhite("../Images/event/actor.png");
	merchantGirl.x = 1024;
	merchantGirl.y = 0;
	merchantGirl.h = 512;
	merchantGirl.w = 512;
	sideRect.x = 400;
	sideRect.y = 0;
	//load the menu background
	temp = IMG_Load("../Images/event/buy.png");
	menu = SDL_DisplayFormatAlpha(temp);
	SDL_FreeSurface(temp);
	menuRect.x = 2;
	menuRect.y = 2;
	//loads the item list background
	temp = IMG_Load("../Images/event/itemlist.png");
	itemListBG = SDL_DisplayFormatAlpha(temp);
	SDL_FreeSurface(temp);
	itemListBGRect.x = 200;
	itemListBGRect.y = 20;
	portaitRectSrc.x = 0;
	portaitRectSrc.y = 0;
	portaitRectSrc.h = portait->h;
	portaitRectSrc.w = portait->w;
	portaitRect.x = 400-75;
	portaitRect.y = 300-150;
	portaitRect.w = 150;
	portaitRect.h = 150;

	//loads the background for the text
	loadedImage = IMG_Load("../Images/event/bgtext.png");
	textbg = SDL_DisplayFormatAlpha(loadedImage);
	SDL_FreeSurface( loadedImage );
	textbgRect.x = 0;
	textbgRect.y = 400;	
	count = 0;
	menuCount = 0;
	font = TTF_OpenFont("../Fonts/coolvetica.ttf",20);	
	//TTF_SetFontStyle(font, TTF_STYLE_BOLD);
	printf("Resources loaded!\n");
	currentType = MERCHANT;


	SDL_Color black = {0,0,0}, yellow = {255,255,0};
	string txt = "Merchant";
	font = TTF_OpenFont("../Fonts/coolvetica.ttf",25);	
	name = TTF_RenderText_Blended( font, txt.c_str(), black );

	font = TTF_OpenFont("../Fonts/coolvetica.ttf",20);	
	txt = "Hi!~ Welcome to the item shop.";
	enter = TTF_RenderText_Blended( font, txt.c_str(), black );
	txt = "Take your time.";
	wait = TTF_RenderText_Blended( font, txt.c_str(), black );
	txt = "What are you looking for?";
	buy = TTF_RenderText_Blended( font, txt.c_str(), black );
	txt = "I'll buy anything! Just for you!";
	sell = TTF_RenderText_Blended( font, txt.c_str(), black );
	txt = "Please come again!~";
	bye = TTF_RenderText_Blended( font, txt.c_str(), black );

	font = TTF_OpenFont("../Fonts/coolvetica.ttf",24);	
	txt = "Buy";
	buys[0] = TTF_RenderText_Blended( font, txt.c_str(), black );
	buys[1] = TTF_RenderText_Blended( font, txt.c_str(), yellow );
	txt = "Sell";

	sells[0] = TTF_RenderText_Blended( font, txt.c_str(), black );
	sells[1] = TTF_RenderText_Blended( font, txt.c_str(), yellow );
	txt = "Exit";

	exit[0] = TTF_RenderText_Blended( font, txt.c_str(), black );
	exit[1] = TTF_RenderText_Blended( font, txt.c_str(), yellow );
}

void EventScene::eventHandler(SDL_Event& event){
	while(SDL_PollEvent(&event)){
		switch(event.type){
		case SDL_KEYDOWN:
			switch(event.key.keysym.sym){
			case SDLK_z:
				switch(currentType)
				{
				case MERCHANT:
					//count++;
					switch(count){
					case 0:
						count++;
						break;
					case 1:
						if(menuCount == 0){
							printf("I want to buy something....\n");
							count = 2;
						}
						if(menuCount == 1){
							printf("I want to sell something...\n");
							count= 3;
						}
						if(menuCount == 2)
							count = 4;

						break;
					case 4:
						scene->setGameScene(SceneManager::NORMAL);
					default:
						break;
					}
					break;
				case SWITCHLEVEL:
					break;
				default:
					break;
				}
				//scene->setGameScene(SceneManager::NORMAL);
				break;
			case SDLK_x:
				switch(currentType)
				{
				case MERCHANT:
					if(count == 2 || count == 3)
						count = 1;
					break;
				default:
					break;
				}
				break;
			case SDLK_RETURN:
				switch(currentType)
				{
				case MERCHANT:
					//count++;
					switch(count){
					case 0:
						count++;
						break;
					case 1:
						if(menuCount == 0){
							printf("I want to buy something....\n");
							count = 2;
						}
						if(menuCount == 1){
							printf("I want to sell something...\n");
							count= 3;
						}
						if(menuCount == 2)
							count = 4;

						break;
					case 4:
						scene->setGameScene(SceneManager::NORMAL);
					default:
						break;
					}
					break;
				case SWITCHLEVEL:
					break;
				default:
					break;
				}
				break;
			case SDLK_UP:
				switch(currentType)
				{
				case MERCHANT:
					if(count == 1){
						menuCount--;
						if(menuCount < 0)
							menuCount = 0;
					}
					break;
				default:
					break;
				}
				break;
			case SDLK_DOWN:
				switch(currentType)
				{
				case MERCHANT:
					if(count == 1){
						menuCount++;
						if(menuCount >2)
							menuCount =2;
					}
					break;
				default:
					break;
				}
				break;
			case SDLK_ESCAPE:
				switch(currentType)
				{
				case MERCHANT:
					if(count == 2 || count == 3)
						count = 1;
					break;
				default:
					break;
				}
				break;
				//game->setGameOver(true);
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

void EventScene::display(){
	SDL_Surface *text;
	SDL_FillRect(scene->getScreen(),NULL,0x221122);

	if(currentType == MERCHANT){
		//set picture for the girl
		if(count == 0)
			merchantGirl.x = 1024;
		if(count == 1)
			merchantGirl.x = 512;
		if(count == 4){
			merchantGirl.x = 512;
			merchantGirl.y = 512;
		}
		//draw the background
		SDL_BlitSurface(bg, &bgRectSrc, scene->getScreen(),&bgRect);
		//draw the girl
		SDL_BlitSurface(sideRight,&merchantGirl,scene->getScreen(),&sideRect );
		//draw the dialouge background
		SDL_BlitSurface(textbg,NULL, scene->getScreen(), &textbgRect);
		text = name;
		SDL_Rect temp;
		temp.x = 10;
		temp.y = 413;
		//draw title for merchant
		SDL_BlitSurface(text, NULL, scene->getScreen(),&temp);
		if(count == 0)
			text = enter;
		if(count == 1) 
			text = wait;
		if(count == 2)
			text = buy;
		if(count == 3)
			text = sell;
		if(count == 4)
			text = bye;
		temp.x = 10;
		temp.y = 450;
		//draw dialouge text
		SDL_BlitSurface(text, NULL, scene->getScreen(),&temp);
		//drawing the menu
		if(count > 0 && count < 4){
			SDL_BlitSurface(menu, NULL, scene->getScreen(),&menuRect);
			if(menuCount != 0)
				text = buys[0];
			else
				text = buys[1];
			temp.x = 15;
			temp.y = 10;
			SDL_BlitSurface(text, NULL, scene->getScreen(),&temp);
			if(menuCount != 1)
				text = sells[0];
			else
				text = sells[1];
			temp.y = 30;
			SDL_BlitSurface(text, NULL, scene->getScreen(),&temp);
			if(menuCount != 2)
				text = exit[0];
			else
				text = exit[1];
			temp.y = 120;
			SDL_BlitSurface(text, NULL, scene->getScreen(),&temp);
		}
		if(count == 2 || count == 3)
			SDL_BlitSurface(itemListBG, NULL, scene->getScreen(),&itemListBGRect);
	}
	SDL_Flip(scene->getScreen());
}

void EventScene::disposeResources(){
	std::cout << "Cleaning Event Scene" << std::endl;
	SDL_FreeSurface(bg);
	SDL_FreeSurface(portait);
	SDL_FreeSurface (textbg);
	SDL_FreeSurface(sideRight);
	SDL_FreeSurface(sideLeft);
	SDL_FreeSurface(menu);
	SDL_FreeSurface(itemListBG);
	SDL_FreeSurface(enter);
	SDL_FreeSurface(wait);
	SDL_FreeSurface(buy);
	SDL_FreeSurface(sell);
	SDL_FreeSurface(bye);
	SDL_FreeSurface(name);
	SDL_FreeSurface(buys[0]);
	SDL_FreeSurface(buys[1]);
	SDL_FreeSurface(sells[0]);
	SDL_FreeSurface(sells[1]);
	SDL_FreeSurface(exit[0]);
	SDL_FreeSurface(exit[1]);
	std::cout << "Cleaning Finished!" << std::endl << std::endl;
}