#include "sdlgame1.hpp"

extern "C"
{
	#include <lauxlib.h>
	#include <lualib.h>
}

int main() {
	lua_State* lua = luaL_newstate();
	luaL_openlibs(lua);
	lua_close(lua);

	sdlgame1 game;
	game.run();

	return 0;
}
