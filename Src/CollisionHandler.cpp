#include "CollisionHandler.h"
#include "Constants.h"
#include "CustomEvents.h"

void updateColliders(entt::registry & registry)
{
	auto view = registry.view<Collider, Transform>();
	for (auto entity : view)
	{
		auto& col = view.get<Collider>(entity);
		auto& tran = view.get<Transform>(entity);

		SDL_Rect rect;
		rect.x = (int)tran.position.x;
		rect.y = (int)tran.position.y;
		rect.w = (int)(SNAKE_CELL_SIZE * tran.scale.x);
		rect.h = (int)(SNAKE_CELL_SIZE * tran.scale.y);

		col.setBounds(rect);
	}
}

void checkPlayerCollision(entt::registry & registry)
{
	//get the snake head collider
	Collider* headCollider = nullptr;
	auto headView = registry.view<SnakeHead, Collider>();
	for (auto entity : headView)
	{
		headCollider = &headView.get<Collider>(entity);
	}

	if (headCollider == nullptr)
		return;

	//check the head collider against all other valid colliders
	auto view = registry.view<Collider>();
	for (auto entity : view)
	{
		auto& col = view.get(entity);
		
		//game over collision
		if (col.layer == ColliderLayer::CL_snakebody || col.layer == ColliderLayer::CL_boundary)
		{
			if (SDL_HasIntersection(&headCollider->bounds, &col.bounds) == SDL_TRUE)
			{
				sendEvent(SnakeEvent::EV_endGame);
				break;
			}
		}
		//pickup collision
		else if (col.layer == ColliderLayer::CL_pickup)
		{
			if (SDL_HasIntersection(&headCollider->bounds, &col.bounds) == SDL_TRUE)
			{
				sendEvent(SnakeEvent::EV_pickup);
				break;
			}
		}

	}
}
