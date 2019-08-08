#pragma once

#include "../Constants.h"

enum ColliderLayer
{
	CL_none = 0,
	CL_default = 1,
	CL_snakehead = 2,
	CL_snakebody = 4,
	CL_boundary = 8,
	CL_pickup = 16
};

class Collider
{
public:
	ColliderLayer layer;
	SDL_Rect bounds;

	Collider(ColliderLayer layer)
	{
		this->layer = layer;
		bounds.x = 0;
		bounds.y = 0;
		bounds.w = SNAKE_CELL_SIZE;
		bounds.h = SNAKE_CELL_SIZE;
	}

	Collider(ColliderLayer layer, SDL_Rect& rect)
	{
		this->layer = layer;
		setBounds(rect);
	}

	void setBounds(SDL_Rect& rect)
	{
		bounds.x = rect.x;
		bounds.y = rect.y;
		bounds.w = rect.w;
		bounds.h = rect.h;
	}
};