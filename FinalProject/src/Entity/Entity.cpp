#include "Entity.h"


Entity::Entity(){};
void Entity::setHP(int _HP){ stats.HP = _HP;}
void Entity::setMP(int _MP){stats.MP = _MP;}
void Entity::setATK(int _ATK){ stats.ATK = _ATK;}
void Entity::setDEF(int _DEF){ stats.DEF = _DEF;}
void Entity::setSPD(int _SPD){ stats.SPD = _SPD;}
void Entity::setMATK(int _MATK){ stats.MATK = _MATK;}
void Entity::setStats(int _HP, int _MP, int _ATK, int _DEF, int _SPD, int _MATK){
	stats.HP = _HP;
	stats.MP = _MP;
	stats.ATK = _ATK;
	stats.DEF = _DEF;
	stats.SPD = _SPD;
	stats.MATK = _MATK;
}
void Entity::setName(std::string _Name){Name = _Name;}
std::string Entity::getName(){return Name;}
int Entity::getHP(){return stats.HP;}
int Entity::getATK(){return stats.ATK;}
int Entity::getSPD(){return stats.SPD;}
int Entity::getMP(){return stats.MP;}
Entity::status Entity::getStats(){return stats;}

