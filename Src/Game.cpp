#include "Game.h"
#include "Engine/Logger.h"
#include "Components/Components.h"
#include "Factories.h"
#include "Constants.h"
#include "PlayerSnake.h"
#include "Engine/Color.h"
#include "CollisionHandler.h"
#include "CustomEvents.h"
#include "PlayerPickups.h"
#include "GameText.h"

SDL_Renderer* Game::renderer = nullptr;

void Game::initSDL(const char * title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen) flags += SDL_WINDOW_FULLSCREEN;

	isRunning = SDL_Init(SDL_INIT_EVERYTHING) == 0;
	if (isRunning)
	{
		LOG("SDL Subsystems Initialized");

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			LOG("Window Created");
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			LOG("Renderer Created");
			//SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
		}

		//initialize font
		TTF_Init();

		//initialize our custom event
		initEvent();
	}

}

void Game::initEntt(entt::registry& registry)
{
	//Generate the boundaries - form a boundary around the visible play area
	const int SIZE = SNAKE_CELL_SIZE;
	const int WID = SNAKE_SCREEN_WIDTH;
	const int HGT = SNAKE_SCREEN_HEIGHT;

	makeBoundary(registry, -SIZE, -SIZE, WID + 2*SIZE, SIZE); //top left to top right
	makeBoundary(registry, -SIZE, HGT, WID + 2*SIZE, SIZE); //bottom left to bottom right
	makeBoundary(registry, -SIZE, 0, SIZE, HGT); //top left to bottom left
	makeBoundary(registry, WID, 0, SIZE, HGT); //top right to bottom right

	//Generate the snake
	float centerX = WID / 2 - SIZE / 2;
	float centerY = HGT / 2;
	float scl = 1;

	makeSnakeHead(registry, centerX, centerY, scl, scl);
	makeSnakeTail(registry, centerX, centerY + SIZE, scl, scl);

	//Generate the pickup
	makePickup(registry);
	movePickup(registry);

	//Generate text
	makeGameOverText(registry, 40, { 200, 0, 0, 255 });
	makeScoreText(registry, 25, { 240, 210, 0, 255 });
	updateScoreText(registry);
}

void Game::handleEvents(entt::registry& registry)
{
	while (SDL_PollEvent(NULL))
	{
		SDL_PollEvent(&event);

		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
				isRunning = false;

			if (isAwaitingRestart)
			{
				if (event.key.keysym.sym == SDLK_RETURN)
				{
					isAwaitingRestart = false;
					cleanEntt(registry);
					initEntt(registry);
				}
			}
			else 
			{
				processInput(registry, event);
			}
		default:
			break;
		}

		if (!isAwaitingRestart && event.type == SNAKE_EVENT_TYPE)
		{
			switch (event.user.code)
			{
			case SnakeEvent::EV_endGame:
				setGameOverText(registry);
				destroySnake(registry);
				isAwaitingRestart = true;
				break;
			case SnakeEvent::EV_pickup:
				makeSnakeBody(registry, -SNAKE_CELL_SIZE, -SNAKE_CELL_SIZE, 1., 1.);
				movePickup(registry);
				updateScoreText(registry);
				break;
			default:
				break;
			}
		}
	}
}

void Game::update(entt::registry& registry)
{
	if (isAwaitingRestart)
		return;

	//update and move the snake
	bool movePending = updateSnake(registry);
	if (movePending)
	{
		moveSnake(registry);
	}

	//update colliders
	updateColliders(registry);
	checkPlayerCollision(registry);

	//update sprites
	auto view = registry.view<Sprite, Transform>();
	for (auto entity : view)
	{
		view.get<Sprite>(entity).update(view.get<Transform>(entity));
	}

	frameCounter++;
}

void Game::render(entt::registry& registry)
{
	TextureManager::SetDrawColor(Color::grey());
	SDL_RenderClear(renderer);

	//render border
	TextureManager::SetDrawColor(Color::black());
	int w = SNAKE_SCREEN_WIDTH - 1;
	int h = SNAKE_SCREEN_HEIGHT - 1;
	SDL_RenderDrawLine(renderer, 0, 0, w, 0); //top left to top right
	SDL_RenderDrawLine(renderer, 0, 0, 0, h); //top left to bottom left
	SDL_RenderDrawLine(renderer, w, h, w, 0); // bottom right to top right
	SDL_RenderDrawLine(renderer, w, h, 0, h); // bottom right to bottom left

	//render sprites
	auto sprView = registry.view<Sprite>();
	for (auto entity : sprView)
	{
		sprView.get(entity).render();
	}

	//render text
	auto txtView = registry.view<Text>();
	for (auto entity : txtView)
	{
		txtView.get(entity).render();
	}

	SDL_RenderPresent(renderer);
}

void Game::cleanEntt(entt::registry& registry)
{
	auto sprView = registry.view<Sprite>();
	for (auto e : sprView)
	{
		sprView.get(e).clean();
	}

	auto txtView = registry.view<Text>();
	for (auto e : txtView)
	{
		txtView.get(e).clean();
	}

	registry.reset();

	LOG("EnTT Cleaned");
}

void Game::cleanSDL()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	TTF_Quit();
	SDL_Quit();

	LOG("SDL Cleaned");
}
