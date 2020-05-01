#pragma once

#include <memory>
#include "Entity.h"

enum DIRECTION {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Pacman : public Entity 
{
	DIRECTION moveDirection;
};