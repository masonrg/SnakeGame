#include <iostream>
#include "Game.h"
#include "Engine/Vector2.h"
#include "Constants.h"

Game* game = nullptr;

int main(int argc, char* argv[])
{
	const int frameDelay = 1000 / SNAKE_FPS;

	Uint32 frameStart;
	int frameTime;

	entt::registry registry;

	game = new Game();
	game->initSDL("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SNAKE_SCREEN_WIDTH, SNAKE_SCREEN_HEIGHT, false);
	game->initEntt(registry);

	while (game->running())
	{
		frameStart = SDL_GetTicks();

		game->handleEvents(registry);
		game->update(registry);
		game->render(registry);

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->cleanEntt(registry);
	game->cleanSDL();

	return 0;
}