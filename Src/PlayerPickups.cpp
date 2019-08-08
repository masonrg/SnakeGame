#include "PlayerPickups.h"
#include "Engine/Vector2.h"
#include "Constants.h"
#include "Components/Components.h"
#include <vector>

void movePickup(entt::registry & registry)
{
	//we need to place the pickup somewhere valid
	//cell is valid if it is not occupied by the snake, the current pickup, and is within bounds
	
	const int ROWS = SNAKE_CELL_ROWS - 0;
	const int COLS = SNAKE_CELL_COLS - 0;

	bool map[ROWS][COLS];
	
	//initialize all cells to valid
	for (int row = 0; row < ROWS; row++) {
		for (int col = 0; col < COLS; col++) 
		{
			map[row][col] = true;
		}
	}

	//remove current pickup location from valid cells
	auto pickupView = registry.view<Pickup, Transform>();
	for (auto e : pickupView)
	{
		Transform::CellPos cellPos = pickupView.get<Transform>(e).getCellPos();
		if (CELL_IS_VALID(cellPos.x, cellPos.y))
		{
			map[cellPos.x][cellPos.y] = false;
		}
	}

	//remove snake head from valid cells
	auto snakeView = registry.view<SnakePart, Transform>();
	for (auto e : snakeView)
	{
		Transform::CellPos cellPos = snakeView.get<Transform>(e).getCellPos();
		if (CELL_IS_VALID(cellPos.x, cellPos.y))
		{
			map[cellPos.x][cellPos.y] = false;
		}
	}

	//make list of all valid cells
	std::vector<Transform::CellPos> validCells;
	for (int row = 0; row < ROWS; row++) {
		for (int col = 0; col < COLS; col++)
		{
			if (map[row][col])
			{
				validCells.emplace_back(Transform::CellPos(row, col));
			}
		}
	}

	//randomly select a valid cell and move the pickup to that location
	for (auto e : pickupView)
	{
		auto& trans = pickupView.get<Transform>(e);
		int randIndex = rand() % validCells.size();

		auto& randCell = validCells[randIndex];
		trans.position.x = (float)(randCell.y * SNAKE_CELL_SIZE);
		trans.position.y = (float)(randCell.x * SNAKE_CELL_SIZE);

		std::cout << "Pickup moved: " << trans.position << std::endl;
	}
}
