#include "Player.h"
#include "../Manager/LevelManager.h"
Player::Player(){
	//STR,DEX,INT
	setStats(10,7,5,3,2,2);
	Name = "Player";
	SDL_Color fgColor = {255,255,255};
	SDL_Color fgColor1 = {255,255,0};
	font = TTF_OpenFont("../Fonts/Manga Temple.ttf",30);
	playerText[0] = TTF_RenderText_Blended(font,getName().c_str(),fgColor1);
	playerText[1] = TTF_RenderText_Blended(font,getName().c_str(),fgColor);

}


SDL_Surface** Player::getPlayerText(){
	return playerText;
}

void Player::move(Tiles *tiles[]){
	//Move the dot left or right
	rect.x += xVel;

	//If the dot went too far to the left or right or touched a wall
	/*if( ( box.x < 0 ) || ( 2*box.x > LevelManager::getInstance().getWidth()) || touches_wall( box, tiles ) )
	{
	//move back
	box.x -= xVel;    
	}
	*/
	//Move the dot up or down
	rect.y += yVel;
	/*
	//If the dot went too far up or down or touched a wall
	if( ( box.y < 0 ) || ( 2*box.y  > LevelManager::getInstance().getHeight() ) || touches_wall( box, tiles ) )
	{
	//move back
	box.y -= yVel;    
	} 
	*/
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
}
void Player::move(int x, int y){
	rect.x += x;
	rect.y += y;
}

SDL_Rect* Player::getPlayerPosition(){
	return &rect;
}