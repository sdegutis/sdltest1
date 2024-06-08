#include <SDL.h>
#undef main

#pragma once
class sdlgame1
{

public:

	void run() {


		if (SDL_Init(SDL_INIT_VIDEO) < 0) return;
		SDL_Window* win = SDL_CreateWindow("hello_sdl2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 900, 400, SDL_WINDOW_SHOWN);
		if (win == NULL) return;
		SDL_Surface* surf = SDL_GetWindowSurface(win);
		SDL_FillRect(surf, NULL, SDL_MapRGB(surf->format, 0xff, 0x00, 0x00));
		SDL_UpdateWindowSurface(win);

		auto running = true;
		while (running) {
			SDL_Event event;
			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT) {
					running = false;
				}
			}
		}

		SDL_DestroyWindow(win);
		SDL_Quit();

	}

};
