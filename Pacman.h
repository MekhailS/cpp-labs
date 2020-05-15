#pragma once

#include <memory>
#include "Entity.h"


class Entity;
class Ghost;

class Pacman : public Entity 
{	
	int boostedTime;

public:
	
	bool MakeStep();

	using Entity::SetMoveDirection;

	bool TryRespawn();

	void Kill();

};