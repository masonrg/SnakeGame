#include "CustomEvents.h"
#include "Engine/Logger.h"

Uint32 SNAKE_EVENT_TYPE = (Uint32)-1;

void initEvent()
{
	SNAKE_EVENT_TYPE = SDL_RegisterEvents(1);
}

void sendEvent(SnakeEvent eventCode)
{
	if (SNAKE_EVENT_TYPE != ((Uint32)-1))
	{
		SDL_Event event;
		SDL_memset(&event, 0, sizeof(event));
		event.type = SNAKE_EVENT_TYPE;
		event.user.code = eventCode;
		event.user.data1 = 0;
		event.user.data2 = 0;
		SDL_PushEvent(&event);
	}
}
