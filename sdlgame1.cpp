#include "sdlgame1.hpp"

#include <SDL.h>
#undef main

void sdlgame1::run() {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) return;
	SDL_Window* win = SDL_CreateWindow("Game1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 900, 400, SDL_WINDOW_SHOWN);
	if (win == NULL) return;

	SDL_Surface* surf = SDL_GetWindowSurface(win);
	int x = 0;

	auto frameDuration = 33;
	auto lastFrame = SDL_GetTicks64();

	auto running = true;
	while (running) {
		SDL_Event event;

		auto newFrame = SDL_GetTicks64();
		if (newFrame >= lastFrame + frameDuration) {
			lastFrame = newFrame;

			SDL_FillRect(surf, NULL, SDL_MapRGB(surf->format, 0x33, 0x99, 0xff));
			SDL_Rect rect = { x++,20,300,200 };
			SDL_FillRect(surf, &rect, SDL_MapRGBA(surf->format, 0xff, 0xff, 0xff, 0x00));
			SDL_UpdateWindowSurface(win);
		}

		while (SDL_PollEvent(&event)) {

			switch (event.type) {
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_SPACE) {
					running = false;
				}
				break;
			}
		}
	}

	SDL_DestroyWindow(win);
	SDL_Quit();

}
