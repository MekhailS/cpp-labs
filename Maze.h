#pragma once

#include <vector>
#include <sstream>

#include "MyVector.h"

using namespace std;

enum CELL_OBJ {
	CELL_WALL = -1,
	CELL_EMPTY = 0,
	CELL_FRUIT = 20,
	CELL_ENERGIZER = 10,
	CELL_COIN = 1,
};


class Maze
{
	vector<vector<CELL_OBJ>>maze;

	MyVector spawnGhosts, jailGhosts, spawnPacman;

public:

	Maze(ifstream& fileWithLevel);

	void SetCellObjByVector(const MyVector& v, CELL_OBJ obj);

	CELL_OBJ GetCellObjByVector(const MyVector& v) const;

	MyVector GetValidPos(const MyVector& curPos) const;

	int GetMaxScore() const;

	int GetRightBorder() const;

	int GetUpBorder() const;

	MyVector GetSpawnGhosts() const;

	MyVector GetSpawnPacman() const;

	MyVector GetJailGhosts() const;

};

