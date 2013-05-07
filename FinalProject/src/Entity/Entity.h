#ifndef ENTITY_H_
#define ENTITY_H_
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Magic.h"

class Entity{
protected:
	struct status{
		int HP, MP, STR, DEF, SPD, INT, DEX, MAXHP, MAXMP;
	};
	status stats;
	//current level
	int level;
	int gold; //or whatever our currency is
	int	experience;
	std::string Name;
	TTF_Font* font;
public:
	// need x and y coor vars for location of the image
	Entity();
	void setHP(int _HP);
	void setMP(int _MP);
	void setSTR(int _STR);
	void setDEF(int _DEF);
	void setSPD(int _SPD);
	void setDEX(int _DEX);
	void setINT(int _INT);
	void setStats(int _STR,int _DEX,int _INT);
	virtual void setName(std::string _Name);
	std::string getName();
	int getHP();
	int getMP();
	int getSTR();
	int getDEF();
	int getSPD();
	int getINT();
	status getStats();
};

#endif
