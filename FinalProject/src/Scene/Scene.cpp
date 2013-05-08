#include "Scene.h"

Scene::Scene(){
	game = &GameManager::getInstance();
	player = &Player::getInstance();
	scene = &SceneManager::getInstance();
	level = &LevelManager::getInstance();
}

void Scene::apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
	//Holds offsets
	SDL_Rect offset;

	//Get offsets
	offset.x = x;
	offset.y = y;

	//Blit
	SDL_BlitSurface( source, clip, destination, &offset );
}
void Scene::SetSurfaceAlpha (SDL_Surface *surface, Uint8 alpha)
{
	SDL_PixelFormat* fmt = surface->format;

	// If surface has no alpha channel, just set the surface alpha.
	if( fmt->Amask == 0 ) 
		SDL_SetAlpha( surface, SDL_SRCALPHA, alpha );

	// Else change the alpha of each pixel.
	else {
		unsigned bpp = fmt->BytesPerPixel;
		// Scaling factor to clamp alpha to [0, alpha].
		float scale = alpha / 255.0f;
		SDL_LockSurface(surface);
		for (int y = 0; y < surface->h; ++y) 
			for (int x = 0; x < surface->w; ++x) 
			{
				// Get a pointer to the current pixel.
				Uint32* pixel_ptr = (Uint32 *)( (Uint8 *)surface->pixels+ y * surface->pitch+ x * bpp);
				// Get the old pixel components.
				Uint8 r, g, b, a;
				SDL_GetRGBA( *pixel_ptr, fmt, &r, &g, &b, &a );
				// Set the pixel with the new alpha.
				*pixel_ptr = SDL_MapRGBA( fmt, r, g, b, scale * a );
			}
			SDL_UnlockSurface(surface);

	}
}
SDL_Surface* Scene::load_imageWhite( std::string file )
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
			SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0xff, 0xff, 0xff ) );
		}
	}

	//Return the optimized surface
	return optimizedImage;
}
SDL_Surface* Scene::load_imageBlue( std::string file )
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


void Animation::Init( int number_of_frames )
{
	// create a new array of SDL_Rects to tell where on the Sprite surface(s)
	// the individual frames are
	rectangles = new SDL_Rect[ number_of_frames ];

	// record how many frames we have in total
	NumberOfFrames = number_of_frames - 1;  // -1 because arrays start counting from 0 not 1
	
	// set the current frame
	CurrentFrame = 0;
}

SDL_Rect* Animation::GetFrame(void)
{
	// return a pointer to the current frame
	return &rectangles[ CurrentFrame ];
}

void Animation::SetFrame( int frame_number, int x, int y, int w, int h)
{
	// setup the location and dimensions of a frame
	rectangles[ frame_number ].x = x;
	rectangles[ frame_number ].y = y;
	rectangles[ frame_number ].w = w;
	rectangles[ frame_number ].h = h;
}

void Animation::NextFrame(void)
{
	CurrentFrame++; // advance one frame
	if(CurrentFrame > NumberOfFrames) CurrentFrame = 0; // if we go over the top set to zero
}

void Animation::LastFrame(void)
{
	CurrentFrame--; // step back one frame
	if(CurrentFrame < 0) CurrentFrame = NumberOfFrames; // if we underrun the list set to top
}
	