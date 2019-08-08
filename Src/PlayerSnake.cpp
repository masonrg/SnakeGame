#include "PlayerSnake.h"
#include "Components/SnakeSegments.h"
#include "Components/Transform.h"
#include "Engine/Logger.h"

void processInput(entt::registry & registry, SDL_Event& event)
{
	bool wasChanged = false;
	bool isVertical = false;
	Direction newDirection;

	auto view = registry.view<SnakeHead, Transform>();
	for (auto entity : view)
	{
		auto tmpDir = view.get<Transform>(entity).direction;
		isVertical = tmpDir == Direction::up || tmpDir == Direction::down;
	}

	//Check the input event to see if its a key we care about
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_w:
		case SDLK_UP:
			if (!isVertical)
			{
				newDirection = Direction::up;
				wasChanged = true;
			}
			break;
		case SDLK_s:
		case SDLK_DOWN:
			if (!isVertical)
			{
				newDirection = Direction::down;
				wasChanged = true;
			}
			break;
		case SDLK_a:
		case SDLK_LEFT:
			if (isVertical)
			{
				newDirection = Direction::left;
				wasChanged = true;
			}
			break;
		case SDLK_d:
		case SDLK_RIGHT:
			if (isVertical)
			{
				newDirection = Direction::right;
				wasChanged = true;
			}
			break;
		}
	}

	//if there was directional input, then update the snakehead facing direction and force movement
	if (wasChanged)
	{
		auto view = registry.view<SnakeHead, Transform>();
		for (auto entity : view)
		{
			view.get<SnakeHead>(entity).queuedDir = newDirection;
			view.get<SnakeHead>(entity).forceUpdate();
		}
		//moveSnake(registry);
	}
}

bool updateSnake(entt::registry & registry)
{
	//Check if the head should move
	auto view = registry.view<SnakeHead>();
	for (auto entity : view)
	{
		return view.get(entity).update();
	}

	return false;
}


void moveSnake(entt::registry& registry)
{
	//move the snake, starting with the head then the body then the tail
	//the head moves, the rest follows

	Vector2 nextPos = Vector2();
	Direction nextDir = Direction::up;

	//update the head
	auto headView = registry.view<SnakeHead, Transform>();
	for (auto entity : headView)
	{
		auto& head = headView.get<Transform>(entity);
		head.direction = headView.get<SnakeHead>(entity).queuedDir;

		//record previous position/direction for next segment in the snake
		nextPos = head.position;
		nextDir = head.direction;

		//move the head - orientation already set from player input
		switch (head.direction)
		{
		case up: head.position.y -= SNAKE_CELL_SIZE * head.scale.y; break;
		case down: head.position.y += SNAKE_CELL_SIZE * head.scale.y; break;
		case left: head.position.x -= SNAKE_CELL_SIZE * head.scale.x; break;
		case right: head.position.x += SNAKE_CELL_SIZE * head.scale.x; break;
		default: break;
		}

	}
	
	//update the body
	auto bodyView = registry.view<SnakeBody, Transform>();
	for (auto entity : bodyView)
	{
		auto& body = bodyView.get<Transform>(entity);
		
		Vector2 tmpPos = body.position;
		Direction tmpDir = body.direction;

		body.position = nextPos;
		body.direction = nextDir;

		nextPos = tmpPos;
		nextDir = tmpDir;
	}

	//update the tail
	auto tailView = registry.view<SnakeTail, Transform>();
	for (auto entity : tailView)
	{
		auto& tail = tailView.get<Transform>(entity);

		tail.position = nextPos;
		tail.direction = nextDir;
	}
	
}

void destroySnake(entt::registry & registry)
{
	registry.reset<SnakeHead>();
	registry.reset<SnakeBody>();
	registry.reset<SnakeTail>();
}
