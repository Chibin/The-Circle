#ifndef ENTITY_H_
#define ENTITY_H_
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

class Entity{
protected:
	struct status{
		int HP, MP, ATK, DEF, SPD, MATK, MAXHP, MAXMP;
	};
	status stats;
	//current level
	int level;
	std::string Name;
	TTF_Font* font;
public:
	// need x and y coor vars for location of the image
	Entity();
	void setHP(int _HP);
	void setMP(int _MP);
	void setATK(int _ATK);
	void setDEF(int _DEF);
	void setSPD(int _SPD);
	void setMATK(int _MATK);
	void setStats(int _HP, int _MP, int _ATK, int _DEF, int _SPD, int _MATK);
	virtual void setName(std::string _Name);
	std::string getName();
	int getHP();
	int getATK();
	int getSPD();
	int getMP();
	status getStats();
};

#endif