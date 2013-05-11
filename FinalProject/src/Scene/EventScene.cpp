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

	//loads portiat
	temp = IMG_Load("../Images/event/face.bmp");
	portait = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);

	//loads the merchant girl
	SDL_Surface* loadedImage = IMG_Load("../Images/event/merchantgirl.png");
	sideRight = SDL_DisplayFormatAlpha(loadedImage);
	SDL_FreeSurface(loadedImage);
	sideLeft = load_imageWhite("../Images/event/actor.png");

	merchantGirl.x = 512;
	merchantGirl.y = 0;
	merchantGirl.h = 512;
	merchantGirl.w = 512;


	sideRect.x = 450;
	sideRect.y = 0;
	bgRectSrc.x = 0;
	bgRectSrc.y = 0;
	bgRectSrc.h = bg->h;
	bgRectSrc.w = bg->w;
	bgRect.x = 0;
	bgRect.y = 0;
	bgRect.w = 600;
	bgRect.h = 450;

	portaitRectSrc.x = 0;
	portaitRectSrc.y = 0;
	portaitRectSrc.h = portait->h;
	portaitRectSrc.w = portait->w;
	portaitRect.x = 400-75;
	portaitRect.y = 300-150;
	portaitRect.w = 150;
	portaitRect.h = 150;
	loadedImage = IMG_Load("../Images/event/bgtext.png");
	textbg = SDL_DisplayFormatAlpha(loadedImage);
	SDL_FreeSurface( loadedImage );
	textbgRect.x = 0;
	textbgRect.y = 400;	
	count = 0;
	font = TTF_OpenFont("../Fonts/coolvetica.ttf",20);	
	//TTF_SetFontStyle(font, TTF_STYLE_BOLD);
	printf("Resources loaded!\n");
	currentType = MERCHANT;
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
						count++;
					case 2:
						scene->setGameScene(SceneManager::NORMAL);
						break;
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
			case SDLK_ESCAPE:
				scene->setGameScene(SceneManager::NORMAL);
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
	SDL_Color black = {0,0,0};
	SDL_FillRect(scene->getScreen(),NULL,0x221122);


	if(currentType == MERCHANT){
		if(count == 0)
			merchantGirl.x = 512;
		else
			merchantGirl.x = 0;
		SDL_BlitSurface(bg, &bgRectSrc, scene->getScreen(),&bgRect);
		SDL_BlitSurface(sideRight,&merchantGirl,scene->getScreen(),&sideRect );
		SDL_BlitSurface(textbg,NULL, scene->getScreen(), &textbgRect);
		font = TTF_OpenFont("../Fonts/coolvetica.ttf",25);	
		string txt = "Merchant";
		text	= TTF_RenderText_Blended( font, txt.c_str(), black );
		SDL_Rect temp;
		temp.x = 10;
		temp.y = 413;
		SDL_BlitSurface(text, NULL, scene->getScreen(),&temp);
		if(count == 0)
			txt = "Hi! Welcome to the item shop.";
		else 
			txt = "Take your time.";
		font = TTF_OpenFont("../Fonts/coolvetica.ttf",20);	
		text	= TTF_RenderText_Blended( font, txt.c_str(), black );
		temp.x = 10;
		temp.y = 450;
		SDL_BlitSurface(text, NULL, scene->getScreen(),&temp);

	}
	SDL_Flip(scene->getScreen());
}

void EventScene::disposeResources(){
	std::cout << "Cleaning Event Scene" << std::endl;
	SDL_FreeSurface(bg);
	SDL_FreeSurface(portait);
	SDL_FreeSurface (textbg);
	SDL_FreeSurface(sideRight);
	std::cout << "Cleaning Finished!" << std::endl << std::endl;
}