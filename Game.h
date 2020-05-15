#pragma once

#include <list>
#include <queue>
#include <memory>
#include <cstdlib>
#include <ctime>

#include "Entity.h"
#include "Pacman.h"
#include "Ghost.h"

using namespace std;


enum CELL_OBJ {
	CELL_WALL = 0,
	CELL_EMPTY,
	CELL_FRUIT,
	CELL_ENERGIZER,
	CELL_COIN
};


class Game 
{
	
	shared_ptr<Pacman> pacman;
	list<shared_ptr<Ghost>> ghostsAlive;
	list<shared_ptr<Ghost>> ghostsDeadWRespawn;

	list<shared_ptr<Ghost>> ghostsDead;

	vector<vector<CELL_OBJ>>maze;

	int score;
	int time;


	CELL_OBJ GetCellObjByVector(const MyVector& v) const;

	void SetCellObjByVector(const MyVector& v, CELL_OBJ obj);

	void SetStatusAliveGhosts(ENT_STATUS newStatus);

	void RestartNotDeadGhosts();

	
public:

	void Update();


	friend class Entity;
	friend class Pacman;
	friend class Ghost;
};