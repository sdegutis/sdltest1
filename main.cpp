#include <SDL.h>
#undef main

#include <Box2D.h>

extern "C"
{
	#include <lauxlib.h>
	#include <lualib.h>
}

int main() {
	lua_State* lua = luaL_newstate();
	luaL_openlibs(lua);
	lua_close(lua);

	b2Vec2 gravity(0.0f, -10.0f);
	b2World world(gravity);

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);

	b2Body* groundBody = world.CreateBody(&groundBodyDef);

	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 10.0f);

	groundBody->CreateFixture(&groundBox, 0.0f);

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0, 4.0f);
	b2Body* body = world.CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	body->CreateFixture(&fixtureDef);

	float timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	for (int32 i = 0; i < 60; ++i) {
		world.Step(timeStep, velocityIterations, positionIterations);
		b2Vec2 position = body->GetPosition();
		float angle = body->GetAngle();
		printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
	}

	if (SDL_Init(SDL_INIT_VIDEO) < 0) return 1;
	SDL_Window* win = SDL_CreateWindow("hello_sdl2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 900, 400, SDL_WINDOW_SHOWN);
	if (win == NULL) return 1;
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
	return 0;
}
