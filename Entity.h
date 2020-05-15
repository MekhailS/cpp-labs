#pragma once

#include <memory>
#include "MyVector.h"

using namespace std;

enum ENT_STATUS {
	ENT_AFK,
	ENT_DEAD,
	ENT_FRIGHTENED,
	ENT_BOOSTED,
	ENT_NORMAL
};

enum DIRECTION {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	STOP
};


MyVector getMoveFromDirection(DIRECTION direction);


class Game;


class Entity
{
protected:

	MyVector position;
	ENT_STATUS status;
	int lives;
	int maxLives;
	MyVector respawnPoint;
	MyVector move;
	int respawnTime;

	weak_ptr<Game> myGame;

	void SetMoveDirection(DIRECTION direction);


public:

	bool MakeStep();

	bool TryRespawn();

	void Kill();

	void Heal(int addLives);

	void HealFull();

	MyVector GetPosition() const;

	ENT_STATUS GetStatus() const;

};