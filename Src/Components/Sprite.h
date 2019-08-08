#pragma once

#include "SDL.h"
#include "../TextureManager.h"
#include "Transform.h"
#include "../Engine/Logger.h"
#include "../Constants.h"

class Sprite 
{
public:
	SDL_Texture* texture;
	SDL_Rect srcRect;
	SDL_Rect dstRect;
	Direction direction;

	Sprite(std::string texturePath)
	{
		std::string str = "Sprite Constructed: " + texturePath;
		LOG(str.c_str());

		srcRect.x = srcRect.y = 0;
		srcRect.w = srcRect.h = SNAKE_CELL_SIZE;
		dstRect.x = dstRect.y = 0;
		dstRect.w = dstRect.h = SNAKE_CELL_SIZE;

		direction = Direction::up;
		
		texture = TextureManager::LoadTexture(texturePath);
	}

	void update(Transform& transform)
	{
		//positioning
		dstRect.x = (int)transform.position.x;
		dstRect.y = (int)transform.position.y;

		//scaling
		dstRect.w = (int)(srcRect.w * transform.scale.x);
		dstRect.h = (int)(srcRect.h * transform.scale.y);

		//facing direction
		direction = transform.direction;
	}

	void render()
	{
		switch (direction)
		{
		case up:
			TextureManager::Draw(texture, srcRect, dstRect);
			break;
		case down:
			TextureManager::Draw(texture, srcRect, dstRect, 180.0);
			break;
		case left:
			TextureManager::Draw(texture, srcRect, dstRect, 270.0);
			break;
		case right:
			TextureManager::Draw(texture, srcRect, dstRect, 90.0);
			break;
		default:
			LOG("Failed to render sprite");
			break;
		}
	}

	void clean()
	{
		SDL_DestroyTexture(texture);
	}
};