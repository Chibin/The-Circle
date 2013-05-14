#include "Player.h"
#include "../Manager/LevelManager.h"

Player::Player(){

	/*******************************************************************************/
	/* ***************************ANIMATION*****************************************/
	/*******************************************************************************/

	//setting animation
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
	velocity = 4;
	current = playerAnimDown;
	tempAnim = playerAnimDown->GetFrame();
}
SDL_Surface** Player::getPlayerText(){
	return playerText;
}

void Player::setPlayer(bool isLoaded){
	std::cout << "\tLoading Character..." ;
	if(isLoaded){
		//STR,DEX,INT
		//level = 5;
		//currentXP = 134;
		//maxXP = 500;
		//setStats(10,7,5,3,2,2);
		Name = "Player";
		SDL_Color fgColor = {255,255,255};
		SDL_Color fgColor1 = {255,255,0};
		font = TTF_OpenFont("../Fonts/Manga Temple.ttf",30);
		playerText[0] = TTF_RenderText_Blended(font,getName().c_str(),fgColor1);
		playerText[1] = TTF_RenderText_Blended(font,getName().c_str(),fgColor);
	}	

	/*******************************************************************************/
	/* ***************************Model*****************************************/
	/*******************************************************************************/

	SDL_Surface * loadedImage;
	if(type == LLYOD)
		loadedImage = SDL_LoadBMP("../Images/normal/maleModel.bmp");	
	else
		loadedImage = SDL_LoadBMP("../Images/normal/femaleModel.bmp");
	model = SDL_DisplayFormat(loadedImage);
	SDL_FreeSurface( loadedImage );
	SDL_SetColorKey( model, SDL_SRCCOLORKEY, SDL_MapRGB( model->format, 0xff, 0xff, 0xff ) );
	std::cout << "Done!" << std::endl;
}
Player& Player::getInstance(){
	static Player instance;
	return instance;
}

Player::PlayerType Player::getType(){
	return type;
}

void Player::setType(Player::PlayerType _type){
	type = _type;
}

int Player::getPositionX(){
	return rect.x;
}

int Player::getPositionY(){
	return rect.y;
}

void Player::setPosition(int x, int y){
	rect.x = x;
	rect.y = y;
	mapOffsetX = x;
	mapOffsetY = y;
}
void Player::move(int x, int y){
	rect.x += x;
	rect.y += y;
}

SDL_Rect* Player::getPlayerPosition(){
	return &rect;
}

void Player::renderPlayer(){
	SDL_BlitSurface(model,current->GetFrame(),SceneManager::getInstance().getScreen(),&rect);	
	tempAnim = current->GetFrame();
}
void Player::renderLastPlayerFrame(){
	SDL_BlitSurface(model,tempAnim,SceneManager::getInstance().getScreen(),&rect);	

}
Animation* Player::getAnimDown(){
	return playerAnimDown;
}
Animation* Player::getAnimUp(){
	return playerAnimUp;
}
Animation* Player::getAnimLeft(){
	return playerAnimLeft;
}
Animation* Player::getAnimRight(){
	return playerAnimRight;
}
int Player::getVelocity(){
	return velocity;
}
void Player::setAnimState(Player::MoveState state){
	switch(state){
	case UP:
		current = playerAnimUp;
		break;
	case DOWN:
		current = playerAnimDown;
		break;
	case LEFT:
		current = playerAnimLeft;
		break;
	case RIGHT:
		current = playerAnimRight;
		break;
	default:
		break;
	}
	current->NextFrame();
}

int Player::getMapOffsetX(){
return mapOffsetX;
}
int Player::getMapOffsetY(){
return mapOffsetY;
}
int Player::getXP(){
	return currentXP;
}
int Player::getMaxXp(){
	return maxXP;
}