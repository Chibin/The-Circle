#ifndef MOB_H
#define MOB_H
#include "Entity.h"

class Mob: public Entity{
private:
		SDL_Rect enemyLoc;
		SDL_Surface* enemyText[2], enemyImage;
public:
	Mob();
	void setName(std::string);
	SDL_Surface** getEnemyText();
	~Mob();
};


#endif