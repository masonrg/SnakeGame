#pragma once

#include "../Constants.h"
#include "../Engine/Vector2.h"
#include "../Engine/Logger.h"

enum Direction
{
	up, down, left, right
};

class Transform
{
public:

	struct CellPos {
		int x;
		int y;
		CellPos(int x, int y) { this->x = x; this->y = y; }
	};

	Vector2 position;
	Vector2 scale;
	Direction direction;

	Transform()
	{
		LOG("Transform Created");
		
		position = Vector2(0.0, 0.0);
		scale = Vector2(1.0, 1.0);
		direction = Direction::up;
	}

	Transform(float xpos, float ypos)
	{
		LOG("Transform Created");

		position = Vector2(xpos, ypos);
		scale = Vector2(1.0, 1.0);
		direction = Direction::up;
	}

	Transform(float xpos, float ypos, float xscl, float yscl, Direction facing)
	{
		LOG("Transform Created");

		position = Vector2(xpos, ypos);
		scale = Vector2(xscl, yscl);
		this->direction = facing;
	}

	CellPos getCellPos()
	{
		return CellPos((int)(position.y / SNAKE_CELL_SIZE), (int)(position.x / SNAKE_CELL_SIZE));
	}

	void move()
	{
		switch (direction)
		{
		case up:
			position.y -= SNAKE_CELL_SIZE * scale.y;
			break;
		case down:
			position.y += SNAKE_CELL_SIZE * scale.y;
			break;
		case left:
			position.x -= SNAKE_CELL_SIZE * scale.x;
			break;
		case right:
			position.x += SNAKE_CELL_SIZE * scale.x;
			break;
		default:
			break;
		}
	}
};