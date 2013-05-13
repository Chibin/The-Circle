#include "NPC.h"

NPC::NPC(){
	setStats(1,1,1,1,1,1); // need to be set because it is still a Entity instance, but these will never be used.
	npcName = "Default NPC";
	speach.push_back("I don't know what kinda of NPC I am. :(");
	// default image - should not be used. But just in case
	SDL_Surface* tempSurface = IMG_Load("../Images/npc/default.png");
	npcImage = SDL_DisplayFormatAlpha(tempSurface);
	SDL_FreeSurface(tempSurface);
	setFrames(); // set the frames
}

NPC::~NPC()
{
	// prevent memory memory leak when changing between many scenes with NPCs
	speach.clear();
	delete npcImage;
	delete npcUp;
	delete npcDown;
	delete npcLeft;
	delete npcRight;
	delete currentAnimation;
}

SDL_Rect* NPC::getRect(void)
{
	return &npcRect; // dereference to return a point to the npcRect
}

SDL_Surface* NPC::getSurface(void)
{
	return npcImage;
}

Animation* NPC::getAnimation(void)
{
	return currentAnimation;
}

std::string NPC::getName()
{
	return npcName;
}

std::string NPC::speak()
{
	static int sentence = 0; // keep track what sentence you are on
	if(sentence >= speach.size()) // already said all sentences
	{
		sentence = 0; // reset
		return "ENDofSPEACH"; // special return to know when speach has ended
	}
	return speach[sentence++];
}

void NPC::setFrames(void)
{
	// initialize animations
	npcUp = new Animation;
	npcDown = new Animation;
	npcLeft = new Animation;
	npcRight = new Animation; 

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
	currentAnimation->NextFrame();
}

NPC_girl1::NPC_girl1()
{
	npcName = "NPC Girl"; // non original name
	speach.push_back("Hello, Hero");
	speach.push_back("Please protect me from that scary fire head guy!");
	// should load image
	//SDL_Surface* tempSurface = IMG_Load("../Images/npc/girl1.bmp");
	//npcImage = SDL_DisplayFormatAlpha(tempSurface);
	//SDL_FreeSurface(tempSurface);
	npcImage = load_imageBlue("../Images/npc/girl1.bmp");
	//SDL_SetColorKey( npcImage, SDL_SRCCOLORKEY, SDL_MapRGB( npcImage->format, 0xff, 0xff, 0xff ) );
	setFrames();
}

NPC_guy1::NPC_guy1()
{
	npcName = "NPC Guy";
	speach.push_back("Hey Mr. have you ever seen a guy his head on fire?");
	speach.push_back("Well for only 3 gold coins I'll show you someone just like that");
	speach.push_back("Fine your lose.");
	npcImage =  SDL_LoadBMP("../Images/npc/guy1.bmp");
	SDL_SetColorKey( npcImage, SDL_SRCCOLORKEY, SDL_MapRGB( npcImage->format, 0xff, 0xff, 0xff ) );
	setFrames();
}

NPC_guyRed::NPC_guyRed()
{
	npcName = "Red Guy";
	speach.push_back("No actually my head is not on Fire ... why do people keep asking that?");
	speach.push_back("Careful don't fall into that well mysteriously placed hole and latter.");
	npcImage = load_imageBlue("../Images/npc/guyRed.bmp");
	setFrames();
}

SDL_Surface* NPC::load_imageBlue( std::string file )
{
	//The image that's loaded
	SDL_Surface* loadedImage = NULL;

	//The optimized surface that will be used
	SDL_Surface* optimizedImage = NULL;

	//Load the image
	loadedImage = IMG_Load( file.c_str() );

	//If the image loaded
	if( loadedImage != NULL )
	{
		//Create an optimized surface
		optimizedImage = SDL_DisplayFormat( loadedImage );

		//Free the old surface
		SDL_FreeSurface( loadedImage );

		//If the surface was optimized
		if( optimizedImage != NULL )
		{
			//Color key surface
			SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0, 0xff ) );
		}
	}

	//Return the optimized surface
	return optimizedImage;
}