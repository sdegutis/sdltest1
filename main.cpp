#include <SDL.h>
#undef main

extern "C"
{
	#include <lauxlib.h>
	#include <lualib.h>
}

int main() {
	lua_State* lua = luaL_newstate();
	luaL_openlibs(lua);
	lua_close(lua);

	if (SDL_Init(SDL_INIT_VIDEO) < 0) return 1;
	SDL_Window* win = SDL_CreateWindow("hello_sdl2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 900, 400, SDL_WINDOW_SHOWN);
	if (win == NULL) return 1;
	SDL_Surface* surf = SDL_GetWindowSurface(win);
	SDL_FillRect(surf, NULL, SDL_MapRGB(surf->format, 0xff, 0x00, 0x00));
	SDL_UpdateWindowSurface(win);
	SDL_Delay(2000);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}
