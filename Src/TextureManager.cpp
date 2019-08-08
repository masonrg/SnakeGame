#include "TextureManager.h"
#include "Engine/Logger.h"
#include "Constants.h"

void TextureManager::SetDrawColor(Color color)
{
	SDL_SetRenderDrawColor(Game::renderer, color.r, color.g, color.b, color.a);
}

SDL_Texture* TextureManager::LoadTexture(std::string texturePath)
{
	SDL_Surface* tmpSurface = IMG_Load(texturePath.c_str());
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
	if (tex == NULL)
		LOG_SDL_ERROR();

	SDL_FreeSurface(tmpSurface);

	return tex;
}

void TextureManager::Draw(SDL_Texture * texture, SDL_Rect& src, SDL_Rect& dst)
{
	if (SDL_RenderCopy(Game::renderer, texture, &src, &dst))
		LOG_SDL_ERROR();
}

void TextureManager::Draw(SDL_Texture * texture, SDL_Rect& src, SDL_Rect& dst, double rotation)
{
	if (SDL_RenderCopyEx(Game::renderer, texture, &src, &dst, rotation, NULL, SDL_FLIP_NONE))
		LOG_SDL_ERROR();
}

void TextureManager::Draw(TTF_Font* font, std::string text, SDL_Color color, int xOffset, int yOffset)
{
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);

	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);

	int centerX = (SNAKE_SCREEN_WIDTH - texW) / 2 + xOffset;
	int centerY = (SNAKE_SCREEN_HEIGHT - texH) / 2 + yOffset;
	SDL_Rect dstRect = { centerX, centerY, texW, texH };
	SDL_RenderCopy(Game::renderer, texture, NULL, &dstRect);

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}
