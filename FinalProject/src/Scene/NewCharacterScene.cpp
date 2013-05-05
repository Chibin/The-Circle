#include "NewCharacterScene.h"

NewCharScreen::NewCharScreen(SDL_Surface* screen){
	malebg = game->load_image("../Images/charCreation/makeBG.bmp");
	bg = game->load_image("../Images/charCreation/bgChar.bmp");
}
void NewCharScreen::eventHandler(SDL_Event& event){

}

void NewCharScreen::display(SDL_Surface* screen){

}