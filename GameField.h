#pragma once

#include <vector>

using namespace std;

enum CELL_OBJ {
	CELL_WALL,
	CELL_EMPTY,
	CELL_PACMAN,
	CELL_GHOST,
	CELL_FRUIT,
	CELL_ENERGIZER,
	CELL_COIN,
	CELL_SPAWN_GHOST,
	CELL_SPAWN_PACMAN,
};


class GameField 
{
	vector<vector<CELL_OBJ>>field;
};