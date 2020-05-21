#pragma once

#include <memory>
#include "MyVector.h"
#include "MyColor.h"

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


class Maze;


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

	void SetMoveDirection(DIRECTION direction);

public:

	Entity(const MyVector& s_respawnPoint, int s_maxLives, int s_respawnTime);

	int MakeStep(Maze& maze);

	bool TryRespawn();

	bool Kill();

	void Heal(int addLives);

	void HealFull();

	int GetLives() const;

	MyVector GetPosition() const;

	ENT_STATUS GetStatus() const;

	MyColor GetColor() const;

};