#pragma once

enum GHOST_TYPE {
	GHOST_CLEVER,
	GHOST_STUPID,
	GHOST_RANDOM
};

class Ghost : public Entity 
{
	GHOST_TYPE type;
};