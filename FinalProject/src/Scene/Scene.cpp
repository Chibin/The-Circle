#include "Scene.h"

Scene::Scene(){
	game = &GameManager::getInstance();
	player = &Player::getInstance();
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