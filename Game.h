#pragma once

#include <list>
#include <queue>
#include <memory>
#include "GameField.h"
#include "Pacman.h"
#include "Ghost.h"

using namespace std;


class Game 
{
	shared_ptr<Pacman> pacman;
	list<shared_ptr<Ghost>> ghostsAlive;
	queue<shared_ptr<Ghost>> ghoststDead;

	int score;
	int time;
};