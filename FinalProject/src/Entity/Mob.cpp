#include "Mob.h"

Mob::Mob(){
	setHP(20);
	setATK(1);
	setDEF(1);
	setSPD(9);
	setMATK(1);
	Name = "The Game";
	TTF_Font* font;
	SDL_Color fgColor = {255,255,0};
	SDL_Color fgColor1 = {255,255,255};
	font = TTF_OpenFont("../Fonts/Manga Temple.ttf",25);
	enemyText[0] = TTF_RenderText_Blended(font,getName().c_str(),fgColor);
	enemyText[1] = TTF_RenderText_Blended(font,getName().c_str(),fgColor1);
}
void Mob::setName(std::string _Name){
	Name = _Name;
	SDL_Color fgColor = {255,255,0};
	SDL_Color fgColor1 = {255,255,255};
	font = TTF_OpenFont("../Fonts/Manga Temple.ttf",25);
	SDL_FreeSurface(enemyText[0]);
	SDL_FreeSurface(enemyText[1]);
	enemyText[0] = TTF_RenderText_Blended(font,getName().c_str(),fgColor);
	enemyText[1] = TTF_RenderText_Blended(font,getName().c_str(),fgColor1);
}
SDL_Surface** Mob::getEnemyText(){
	return enemyText;
}

Mob::~Mob(){
	SDL_FreeSurface(enemyText[0]);
	SDL_FreeSurface(enemyText[1]);
}