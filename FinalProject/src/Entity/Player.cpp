#include "Player.h"

Player::Player(){
	//HP, MP, ATK, DEF, SPD, MATK
	setStats(10,10,10,10,7,10);
	Name = "Player";
	SDL_Color fgColor = {255,255,255};
	SDL_Color fgColor1 = {255,255,0};
	font = TTF_OpenFont("../Fonts/Manga Temple.ttf",25);
	playerText[0] = TTF_RenderText_Blended(font,getName().c_str(),fgColor);
	playerText[1] = TTF_RenderText_Blended(font,getName().c_str(),fgColor1);

}
SDL_Surface** Player::getPlayerText(){
	return playerText;
}
