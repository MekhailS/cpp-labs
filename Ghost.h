#pragma once

#include "Entity.h"

enum GHOST_TYPE {
	GHOST_CLEVER,
	GHOST_STUPID,
	GHOST_RANDOM
};

class Entity;

class Ghost : 
	public Entity
{
	MyVector jailPos;
	GHOST_TYPE type;

	void ChooseMove(const Maze& maze, const MyVector& pacmanPos);

public:

	Ghost(const MyVector& s_respawnPoint,
		int s_defaultMaxLives, int s_defaultRespawnTime,
		GHOST_TYPE s_type, const MyVector& s_jailPos);

	int MakeStep(Maze& maze, const MyVector& pacmanPos);

	bool Kill();

	void MoveToJail();
	
	void SetStatus(ENT_STATUS newStatus);

	MyColor GetColor() const;

};