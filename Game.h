#pragma once

#include "pch.h"

#include "Entity.h"
#include "Maze.h"
#include "Pacman.h"
#include "Ghost.h"

using namespace std;


enum GAME_STATUS {
	GAME_LOSE,
	GAME_NORMAL,
	GAME_WIN
};


class Game 
{
	
	Pacman pacman;
	list<shared_ptr<Ghost>> ghostsAlive;
	list<shared_ptr<Ghost>> ghostsDeadWRespawn;
	list<shared_ptr<Ghost>> ghostsDead;

	Maze maze;

	int scoreToWin;


	void SetStatusAliveGhosts(ENT_STATUS newStatus);

	bool ConflictPacmanGhosts();

	bool RespawnGhosts();

	void RestartGhosts();

public:
	
	Game(ifstream& fileWithLevel, int defaultMaxLives, int defaultRespawnTime);

	GAME_STATUS Update();

	void SetPacmanDirection(DIRECTION direction);

	void DrawCellsOnEntities(HDC hdc) const;

	void DrawEntities(HDC hdc) const;

	void DrawAll(HDC hdc) const;
};