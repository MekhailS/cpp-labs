#pragma once

#include <memory>
#include "MyVector.h"
#include "Game.h"

using namespace std;

enum ENT_STATUS {
	ENT_AFK,
	ENT_DEAD,
	ENT_FRIGHTENED,
	ENT_BOOSTED,
	ENT_NORMAL
};


class Entity 
{
	MyVector position;
	ENT_STATUS status;
	int speed;	//number of ticks required to move on next cell;
	int lives;

	weak_ptr<Game> myGame;
};