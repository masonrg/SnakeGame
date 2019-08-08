#pragma once

#include <iostream>
#include "SDL.h"

#if DEBUG == 1
#define LOG(x) std::cout << (x) << std::endl
#define LOG_ERROR(x) std::cout << "ERROR: " << (x) << std::endl;
#define LOG_SDL_ERROR() std::cout << "SDL_ERROR: " << SDL_GetError() << std::endl;
#else
#define LOG(x)
#define LOG_ERROR(x);
#define LOG_SDL_ERROR();
#endif