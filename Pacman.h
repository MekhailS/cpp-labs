#pragma once

#include <memory>
#include "Entity.h"


class Entity;
class Ghost;

class Pacman : public Entity 
{	
	int score;
	int boostedTime;

public:

	Pacman(const MyVector& s_respawnPoint,
		int s_maxLives, int s_boostedTime);
	
	int MakeStep(Maze& maze);

	int GetScore() const;

	using Entity::SetMoveDirection;

};