#pragma once

#include "../Constants.h"
#include "Transform.h"

class SnakeHead
{
public:
	Direction queuedDir;
	float moveDelaySecs = 0.085f;
	
	bool update() 
	{ 
		framesSinceLastMove++;

		if (framesSinceLastMove > SNAKE_FPS * moveDelaySecs)
		{
			framesSinceLastMove = 0;
			return true;
		}
		else
		{
			return false;
		}
	}

	void forceUpdate()
	{
		framesSinceLastMove = (int)(SNAKE_FPS * moveDelaySecs) + 1;
	}

private:
	int framesSinceLastMove = 0;
};

class SnakeTail{};

class SnakeBody{};

class SnakePart{};