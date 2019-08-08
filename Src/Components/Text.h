#pragma once

#include "SDL_ttf.h"
#include "../TextureManager.h"
#include <string>
#include "../Engine/Logger.h"

class GameOverMainText {};
class GameOverSubText {};
class ScoreText {};

class Text
{
public:
	Text(std::string fontPath, int ptSize, SDL_Color color, int xOffset, int yOffset)
	{
		font = TTF_OpenFont(fontPath.c_str(), ptSize);
		if (font == NULL)
		{
			LOG_SDL_ERROR();
		}

		this->color = color;
		this->xOffset = xOffset;
		this->yOffset = yOffset;

		setText("");
	}

	void setText(std::string text)
	{
		this->text = text;
	}

	void render()
	{
		if (text != "")
		{
			TextureManager::Draw(font, text, color, xOffset, yOffset);
		}
	}

	void clean()
	{
		TTF_CloseFont(font);
	}

private:
	TTF_Font* font;
	SDL_Color color;
	std::string text;
	int xOffset;
	int yOffset;
};