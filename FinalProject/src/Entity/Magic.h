#ifndef MAGIC_H_
#define MAGIC_H_
#include <iostream>
#include <string>
#include "Item.h"
class Magic{
	private:
	public: //enums needs ot be public, will rearange later
		enum magicType{DAMAGE,HEAL,BUFF,DEBUFF};
		enum targetType{SINGLE,AOE}; //area of effect: no credit to john
	protected:
		SDL_Surface* magicTextImage[2];
		SDL_Rect magicLoc;
		enum magicType mType;
		enum targetType tType;
		int magicDamage, MPCost;
		std::string MagicName;
	public:
		Magic(){}
		void setMagicType(enum magicType _mType){mType = _mType;}
		magicType getMagicType(){return mType;}	
		void setTargetType(enum targetType _tType){	tType = _tType;}
		targetType getMagicTargetType(){return tType;}
		void setMPCost(int _MPCost){ MPCost = _MPCost;}
		void setMagicDamage(int mDamage){magicDamage = mDamage;}
		void setMagicName(std::string Name){MagicName = Name;}
		void setTextLocation(Sint16 x, Sint16 y){magicLoc.x = x;	magicLoc.y = y;}
		void setMagicTextImage(){
			TTF_Font* font;
			font = TTF_OpenFont("../Fonts/coolvetica.ttf",35); //used to be 30 for manga temple
			SDL_Color fgColor = {255,255,0};
			magicTextImage[0] =TTF_RenderText_Blended(font,MagicName.c_str(),fgColor);
			fgColor.b = 255;
			magicTextImage[1] =TTF_RenderText_Blended(font,MagicName.c_str(),fgColor); 
			TTF_CloseFont(font);
		}
		int getMagicDamage(){return magicDamage;}
		int getMPCost(){return MPCost;}
		std::string getMagicName(){return MagicName;	}
		SDL_Surface** getMagicTextImage(){return magicTextImage;	}
};

class DemonFang : public Magic{
public:
		DemonFang(){
			setMagicType(DAMAGE);
			setTargetType(SINGLE);
			setMagicDamage(10);
			setMPCost(5);
			setMagicName("Demon Fang");
			setMagicTextImage();
		}
};
class FireBall: public Magic{
	public:
		FireBall(){
			setMagicType(DAMAGE);
			setTargetType(SINGLE);
			setMagicDamage(10);
			setMPCost(5);
			setMagicName("FireBall");
			setMagicTextImage();
		}
};
class AngelFeathers : public Magic{
	public:
	AngelFeathers(){
		setMagicType(DAMAGE);
		setTargetType(AOE);
		setMagicDamage(10);
		setMPCost(15);
		setMagicName("Angel Feathers");
		setMagicTextImage();
	}
};
class PowHammer : public Magic{
	public:
 	PowHammer(){
		setMagicType(DAMAGE);
		setTargetType(SINGLE);
		setMagicDamage(8);
		setMPCost(3);
		setMagicName("Pow Hammer");
		setMagicTextImage();
	}
};
class ParaBall : public Magic{
public:
	ParaBall(){
		setMagicType(DAMAGE);
		setTargetType(SINGLE);
		setMagicDamage(20);
		setMPCost(8);
		setMagicName("Para Ball");
		setMagicTextImage();
	}
};
class DumDog : public Magic{ //non-sense skill for john lusby
public:
	DumDog(){
		setMagicType(HEAL);
		setTargetType(SINGLE);
		setMagicDamage(-20);  //inflicts damage to one's self
		setMPCost(0);
		setMagicName("Dum Dog");
		setMagicTextImage();
	};
};

class FirstAid: public Magic{
	public:
		FirstAid(){
		setMagicType(HEAL);
		setTargetType(SINGLE);
		setMagicDamage(8);
		setMPCost(3);
		setMagicName("First Aid");
		setMagicTextImage();
		}
};
#endif
