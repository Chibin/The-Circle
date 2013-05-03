#ifndef ENTITY_H_
#define ENTITY_H_
#include <string>
class Entity{
	protected:
		struct status{
			int HP, MP, ATK, DEF, SPD, MATK, MAXHP, MAXMP;
		};
		status stats;
		string Name;
		TTF_Font* font;
	public:
		// need x and y coor vars for location of the image
		Entity(){}
		void setHP(int _HP){ stats.HP = _HP;}
		void setMP(int _MP){stats.MP = _MP;}
		void setATK(int _ATK){ stats.ATK = _ATK;}
		void setDEF(int _DEF){ stats.DEF = _DEF;}
		void setSPD(int _SPD){ stats.SPD = _SPD;}
		void setMATK(int _MATK){ stats.MATK = _MATK;}
		void setStats(int _HP, int _MP, int _ATK, int _DEF, int _SPD, int _MATK){
			stats.HP = _HP;
			stats.MP = _MP;
			stats.ATK = _ATK;
			stats.DEF = _DEF;
			stats.SPD = _SPD;
			stats.MATK = _MATK;
		}
		virtual void setName(string _Name){Name = _Name;}
		string getName(){return Name;}
		int getHP(){return stats.HP;}
		int getATK(){return stats.ATK;}
		int getSPD(){return stats.SPD;}
		int getMP(){return stats.MP;}
		status getStats(){return stats;}
};

class Mob : public Entity{
	private:
		SDL_Rect enemyLoc;
		SDL_Surface* enemyText[2], enemyImage;
	public:
		Mob(){
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
		void setName(string _Name){
			Name = _Name;
			SDL_Color fgColor = {255,255,0};
			SDL_Color fgColor1 = {255,255,255};
			font = TTF_OpenFont("../Fonts/Manga Temple.ttf",25);
			SDL_FreeSurface(enemyText[0]);
			SDL_FreeSurface(enemyText[1]);
			enemyText[0] = TTF_RenderText_Blended(font,getName().c_str(),fgColor);
			enemyText[1] = TTF_RenderText_Blended(font,getName().c_str(),fgColor1);
		}
		SDL_Surface** getEnemyText(){
			return enemyText;
		}
		~Mob(){
			SDL_FreeSurface(enemyText[0]);
			SDL_FreeSurface(enemyText[1]);
		}
};

class Player: public Entity{
	private:
		//Collision Box
		SDL_Rect box;
		//The velocity of the character
		int xVel, yVel;

		SDL_Surface* playerText[2];
	public:
		Player(){
				//HP, MP, ATK, DEF, SPD, MATK
			setStats(10,10,10,10,7,10);
			Name = "Player";
			SDL_Color fgColor = {255,255,255};
			SDL_Color fgColor1 = {255,255,0};
			font = TTF_OpenFont("../Fonts/Manga Temple.ttf",25);
			playerText[0] = TTF_RenderText_Blended(font,getName().c_str(),fgColor);
			playerText[1] = TTF_RenderText_Blended(font,getName().c_str(),fgColor1);
		}
		SDL_Surface** getPlayerText(){
			return playerText;
		}
};

class NPC : public Entity
{
private:
public:
	NPC()
	{
		setStats(1,1,1,1,1,1); // need to be set because it is still a Entity instance, but these will never be used.

	}
};

#endif