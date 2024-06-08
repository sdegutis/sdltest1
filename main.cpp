#include <SDL.h>
#undef main

int main() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) return 1;
	SDL_Window* win = SDL_CreateWindow("hello_sdl2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 900, 400, SDL_WINDOW_SHOWN);
	if (win == NULL) return 1;
	SDL_Surface* surf = SDL_GetWindowSurface(win);
	SDL_FillRect(surf, NULL, SDL_MapRGB(surf->format, 0x00, 0x00, 0xff));
	SDL_UpdateWindowSurface(win);
	SDL_Delay(2000);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}
