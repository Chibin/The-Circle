#ifndef MAGIC_H_
#define MAGIC_H_
#include <iostream>
#include <string>
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
		int magicDamage, MagicCost;
		std::string MagicName;
	public:
		Magic(){}
		void setMagicType(enum magicType _mType){
			mType = _mType;
		}
		magicType getMagicType(){
			return mType;
		}	
		void setTargetType(enum targetType _tType){
			tType = _tType;
		}
		targetType getMagicTargetType(){
			return tType;
		}
		void setMagicDamage(int mDamage){
			magicDamage = mDamage;
		}
		void setMagicName(std::string Name){
			MagicName = Name;
		}
		void setTextLocation(Sint16 x, Sint16 y){
			magicLoc.x = x;
			magicLoc.y = y;
		}
		void setMagicTextImage(){
			TTF_Font* font;
			font = TTF_OpenFont("../Fonts/coolvetica.ttf",35); //used to be 30 for manga temple
			SDL_Color fgColor = {255,255,0};
			magicTextImage[0] =TTF_RenderText_Blended(font,MagicName.c_str(),fgColor);
			fgColor.b = 255;
			magicTextImage[1] =TTF_RenderText_Blended(font,MagicName.c_str(),fgColor); 
		}
		int getMagicDamage(){
			return magicDamage;
		}
		std::string getMagicName(){
			return MagicName;
		}
		SDL_Surface** getMagicTextImage(){
			return magicTextImage;
		}
};

class DemonFang : public Magic{
public:
		DemonFang(){
			setMagicType(DAMAGE);
			setTargetType(SINGLE);
			setMagicDamage(10);
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
		setMagicName("First Aid");
		setMagicTextImage();
		}
};

class Item{
	private:
	public:
		enum itemActiveOn{BATTLE,NORMAL,BATTLE_NORMAL};
		enum itemType{CONSUMABLE,EQUIPMENT,ETC};
		enum itemEffect{HEAL,DAMAGE,BUFF,DEBUFF};
		Item(){}
protected:
};
class Equipment : public Item{
	public:
		
	private:
};
#endif
