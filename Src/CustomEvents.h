#pragma once

#include "SDL.h"

extern Uint32 SNAKE_EVENT_TYPE;

enum SnakeEvent : Sint32
{
	EV_endGame,
	EV_pickup
};

void initEvent();
void sendEvent(SnakeEvent eventCode);