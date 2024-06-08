#include "sdlgame1.hpp"

#include <Box2D.h>

#include <SDL.h>
#undef main

void sdlgame1::run() {


	b2Vec2 gravity(0.0f, -20.0f);
	b2World world(gravity);

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);

	b2Body* groundBody = world.CreateBody(&groundBodyDef);

	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 10.0f);

	groundBody->CreateFixture(&groundBox, 0.0f);

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(3.0, 300.0f);
	b2Body* body = world.CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	body->CreateFixture(&fixtureDef);

	float timeStep = 1.0f / 30.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;


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

			world.Step(timeStep, velocityIterations, positionIterations);
			b2Vec2 position = body->GetPosition();
			float angle = body->GetAngle();
			//printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);

			SDL_FillRect(surf, NULL, SDL_MapRGB(surf->format, 0x33, 0x99, 0xff));
			SDL_Rect rect = { position.x,position.y,30,20 };
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
