#include "BattleAnimations.h"
///battleanimation
#include "../Scene/Scene.h"
BattleAnimations::BattleAnimations(){
	animationCounter =0;
	position.x = 400; position.y = 300;
}
SDL_Surface* BattleAnimations::getIdleImage(){ return idle->getImage(); }
void BattleAnimations::setIdleImage(std::string path,int maxNumOfFrames, int r, int g, int b){
	idle = new Animation;
	idle->Init(maxNumOfFrames);
	idle->setImage(path,r,g,b);
}
void BattleAnimations::setFrame(BattleAnimations::animationState state,  int frame_number, int x, int y, int w, int h){
	if(state == IDLE)
		idle->SetFrame(frame_number,x,y,w,h);
}
void BattleAnimations::setAnimationPosition(int x, int y){
	position.x = x; position.y = y;
}
void BattleAnimations::drawAnim(BattleAnimations::animationState state, SDL_Surface* screen, int _timeStep, int speed){
	for(int i = timeStep; i+1000/idle->getNumFrames()/speed < _timeStep; i+= 1000/idle->getNumFrames()/speed){
		idle->NextFrame();
		timeStep = _timeStep;
	}
		SDL_BlitSurface(idle->getImage(),idle->GetFrame(),screen,&position);
}