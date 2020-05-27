#pragma once

#include "pch.h"

#include "Entity.h"


class Entity;
class Ghost;

class Pacman : public Entity 
{	
	int score;
	int boostedTime;


	void DrawLifes(HDC hdc) const;

	void DrawScore(HDC hdc) const;

public:

	Pacman(const MyVector& s_respawnPoint,
		int s_maxLives, int s_boostedTime);
	
	int MakeStep(Maze& maze);

	int GetScore() const;

	using Entity::SetMoveDirection;

	void Draw(HDC hdc) const;
};