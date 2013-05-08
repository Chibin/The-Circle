#include "Npc.h"

NPC::NPC(){
	setStats(1,1,1,1,1,1); // need to be set because it is still a Entity instance, but these will never be used.
	npcName = "Default NPC";
	// default image - should not be used. But just in case
	SDL_Surface* tempSurface = IMG_Load("../Images/npc/default.png");
	npcImage = SDL_DisplayFormatAlpha(tempSurface);
	SDL_FreeSurface(tempSurface);
	setFrames(); // set the frames
}

SDL_Rect* NPC::getPosition()
{
	return &npcRect; // dereference to return a point to the npcRect
}

void NPC::setFrames()
{
	// initialize animations
	npcUp->Init(3); // 3 frames per direction
	npcDown->Init(3);
	npcLeft->Init(3);
	npcRight->Init(3);
	// set the frame dimensions
	// (x, y, width, height)
	npcUp->SetFrame(0, 0, 0, 24, 32);
	npcUp->SetFrame(1, 24, 0, 24, 32);
	npcUp->SetFrame(2, 48, 0, 24, 32);
	//right
	npcRight->SetFrame(0, 0, 32, 24, 32);
	npcRight->SetFrame(1, 24, 32, 24, 32);
	npcRight->SetFrame(2, 48, 32, 24, 32);
	//down
	npcDown->SetFrame(0, 0, 64, 24, 32);
	npcDown->SetFrame(1, 24, 64, 24, 32);
	npcDown->SetFrame(2, 48, 64, 24, 32);
	//left
	npcLeft->SetFrame(0, 0, 96, 24, 32);
	npcLeft->SetFrame(1, 24, 96, 24, 32);
	npcLeft->SetFrame(2, 48, 96, 24, 32);
	// current Animation
	currentAnimation = npcDown; // so that it is facing the screen
}

NPC_girl1::NPC_girl1()
{
	npcName = "NPC Girl"; // non original name
	// should load image
	SDL_Surface* tempSurface = IMG_Load("../Images/npc/girl1.png");
	npcImage = SDL_DisplayFormatAlpha(tempSurface);
	SDL_FreeSurface(tempSurface);
	setFrames();
}

NPC_guy1::NPC_guy1()
{
	npcName = "NPC Guy";
	SDL_Surface* tempSurface = IMG_Load("../Images/npc/guy1.png");
	npcImage = SDL_DisplayFormatAlpha(tempSurface);
	SDL_FreeSurface(tempSurface);
	setFrames();
}