#pragma once

#define CELL_IS_VALID(x,y) ((x) >= 0 && (x) < SNAKE_CELL_ROWS && (y) >= 0 && (y) < SNAKE_CELL_COLS)

static const int SNAKE_FPS = 30;

static const int SNAKE_SCREEN_WIDTH = 800;
static const int SNAKE_SCREEN_HEIGHT = 640;
static const int SNAKE_CELL_SIZE = 32;
static const int SNAKE_CELL_ROWS = SNAKE_SCREEN_HEIGHT / SNAKE_CELL_SIZE;
static const int SNAKE_CELL_COLS = SNAKE_SCREEN_WIDTH / SNAKE_CELL_SIZE;