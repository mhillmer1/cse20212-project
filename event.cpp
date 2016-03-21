// James Ryan, Michael Hillmer, Megan O'Bryan
// Megaman Project
// 20 March 2016

// This code was heavily based on code from lazyfoo's tutorials. 
// The program provides a default sprite, whose positioning can 
// be changed by pressing the up or down arrows on the keypad. 

#include<SDL2/SDL.h>
#include <stdio.h>
#include <string>

//Screen dimension 
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Key press surfaces constants
enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_TOTAL
};

// function prototypes
bool init();
bool loadMedia();
void close();
SDL_Surface* loadSurface( std::string path );
SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gKeyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL ];
SDL_Surface* gCurrentSurface = NULL;

// INITIALIZATION FUNCTION
bool init()
{
	bool success = true;

	// initailizes SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		// creates window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			// gets window surface
			gScreenSurface = SDL_GetWindowSurface( gWindow );
		}
	}

	return success;
}

// .bmp loading function
bool loadMedia()
{
	bool success = true;

	// default (parade rest)
	gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] = loadSurface( "parade.bmp" );
	if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] == NULL )
	{
		printf( "Failed to load image.\n" );
		success = false;
	}

	// salute (up key)
	gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] = loadSurface( "salute.bmp" );
	if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] == NULL )
	{
		printf( "Failed to load image.\n" );
		success = false;
	}

	// parade rest (down key)
	gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] = loadSurface( "parade.bmp" );
	if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] == NULL )
	{
		printf( "Failed to load image.\n" );
		success = false;
	}

	return success;
}

// CLOSING FUNCTION
void close()
{
	// deallocate surfaces
	for( int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i )
	{
		SDL_FreeSurface( gKeyPressSurfaces[ i ] );
		gKeyPressSurfaces[ i ] = NULL;
	}

	// destroys window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	// quit subsystems
	SDL_Quit();
}

// SURFACE LOADING FUNCTION
SDL_Surface* loadSurface( std::string path )
{
	// load images
	SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s. SDL Error: %s\n", path.c_str(), SDL_GetError() );
	}

	return loadedSurface;
}

// MAIN PROGRAM LOOP
int main( int argc, char* args[] )
{
	// open window
	if( !init() )
	{
		printf( "Failed to initialize.\n" );
	}
	else
	{
		// load media
		if( !loadMedia() )
		{
			printf( "Failed to load media.\n" );
		}
		else
		{	
			bool quit = false;

			// event handler
			SDL_Event e;

			// set default image
			gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];

			// game loop
			while( !quit )
			{
				// event handler
				while( SDL_PollEvent( &e ) != 0 )
				{
					// quit option
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					// user input
					else if( e.type == SDL_KEYDOWN )
					{
						// display proper picture
						switch( e.key.keysym.sym )
						{
							case SDLK_UP:
							gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ];
							break;

							case SDLK_DOWN:
							gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ];
							break;

							default:
							gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
							break;
						}
					}
				}

				// applys current image
				SDL_BlitSurface( gCurrentSurface, NULL, gScreenSurface, NULL );
			
				// updates surface
				SDL_UpdateWindowSurface( gWindow );
			}
		}
	}

	// close everything
	close();

	return 0;
}
