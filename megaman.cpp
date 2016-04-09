#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <iostream>

bool collision(SDL_Rect* rec1, SDL_Rect* rec2){
	if(rec1->y >= rec2->y + rec2->h)
		return 0;
	if(rec1->x >= rec2->x + rec2->w)
		return 0;
	if(rec1->y + rec1 -> h <= rec2->y)
		return 0;
	if(rec1->x + rec1->w <= rec2->x)
		return 0;
	return 1;
}

int main(int argc, char** argv){
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Surface* screen, *background, *image;
	screen = SDL_SetVideoMode(960, 614, 32, SDL_SWSURFACE);
	bool running = true;
	const int FPS = 30;
	const int speed = 5;
	Uint32 start;
	int x, y;
	x = 0;
	y = 0;
	background = SDL_LoadBMP("city_background.bmp");
	SDL_Rect camera;
	camera.x=0;
	camera.y=0;
	camera.w=960;
	camera.h=614;
	bool b[2] = {0,0};
	while(running){
		start = SDL_GetTicks();
		SDL_Event event;
		int x;
		int y;
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
					running = false;
					break;
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym)
					{
						case SDLK_RIGHT:
							b[0] = 1;
							break;
						case SDLK_LEFT:
							b[1] = 1;
							break;
					}
				break;
				case SDL_KEYUP:
					switch(event.key.keysym.sym)
					{
						case SDLK_RIGHT:
							b[0] = 0;
							break;
						case SDLK_LEFT:
							b[1] = 0;
							break;
					}
				break;
			}
		}
		// logic
		// if(b[0]){
			// x += speed;
			camera.x += speed;
			if(camera.x >= 3824 - 960)
				camera.x = 0;
		// }
		// else if(b[1]){
			// x -= speed;
			// camera.x -= speed;
			// if(camera.x<=0){
				// camera.x = 3824-960;
			// }
		// }

	// render
	SDL_BlitSurface(background, &camera, screen, NULL);


	SDL_Flip(screen);
		if(1000/FPS>SDL_GetTicks()-start)
			SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
	}
	SDL_Quit();
	return 0;
}
