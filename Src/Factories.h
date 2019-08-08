#pragma once

#include <entt/entity/registry.hpp>
#include "SDL.h"

entt::entity makeBoundary(entt::registry& registry, float xPos, float yPos, float width, float height);
entt::entity makePickup(entt::registry& registry);
entt::entity makeGameOverText(entt::registry& registry, int ptSize, SDL_Color color);
entt::entity makeScoreText(entt::registry& registry, int ptSize, SDL_Color color);
entt::entity makeSnakeHead(entt::registry& registry, float xPos, float yPos, float xScl, float yScl);
entt::entity makeSnakeTail(entt::registry& registry, float xPos, float yPos, float xScl, float yScl);
entt::entity makeSnakeBody(entt::registry& registry, float xPos, float yPos, float xScl, float yScl);
