#pragma once

#include <list>
#include <queue>
#include <memory>
#include <cstdlib>
#include <ctime>

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

	const Maze& GetMaze() const;

	const Pacman& GetPacman() const;

	const list<shared_ptr<const Ghost>> GetGhosts() const;

	int GetWinScore() const;

};