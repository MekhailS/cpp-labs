#pragma once

#include "Entity.h"

enum GHOST_TYPE {
	GHOST_CLEVER,
	GHOST_STUPID,
	GHOST_RANDOM
};

class Entity;
class Pacman;

class Ghost : 
	public enable_shared_from_this<Ghost>, public Entity
{
	GHOST_TYPE type;

	void ChooseMove();


public:
	
	void SetStatus(ENT_STATUS newStatus);

	bool MakeStep();

	bool TryRespawn();

	void Kill();

};