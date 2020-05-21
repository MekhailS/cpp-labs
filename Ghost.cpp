#include "Ghost.h"

#include "Game.h"


Ghost::Ghost(const MyVector& s_respawnPoint,
	int s_defaultMaxLives, int s_defaultRespawnTime,
	GHOST_TYPE s_type, const MyVector& s_jailPos) :
	Entity(s_respawnPoint, 0, s_defaultRespawnTime) {
	jailPos = s_jailPos;
	position = s_jailPos;
	type = s_type;
	status = ENT_DEAD;
	switch (type) {
	case GHOST_CLEVER:
		maxLives = 1.5 * s_defaultMaxLives;
		respawnTime = 1.5 * s_defaultRespawnTime;
		break;
	case GHOST_STUPID:
		maxLives = s_defaultMaxLives;
		respawnTime = s_defaultRespawnTime;
		break;
	case GHOST_RANDOM:
		maxLives = 2 * s_defaultMaxLives;
		respawnTime = 0.5 * s_defaultRespawnTime;
		break;
	}
	lives = maxLives;
}


int Ghost::MakeStep(Maze& maze, const MyVector& pacmanPos) {
	ChooseMove(maze, pacmanPos);
	return(Entity::MakeStep(maze));
}


bool Ghost::Kill() {
	bool toReturn = Entity::Kill();
	position = jailPos;
	return toReturn;
}


void Ghost::MoveToJail() {
	Kill();
	Heal(1);
}


void Ghost::SetStatus(ENT_STATUS newStatus) {
	status = newStatus;
}


MyColor Ghost::GetColor() const {
	if ((status == ENT_FRIGHTENED) || (status == ENT_BOOSTED)) {
		return Entity::GetColor();
	}
	else {
		switch (type) {
		case GHOST_CLEVER:
			return MyColor(248, 179, 248);
			break;

		case GHOST_STUPID:
			return MyColor(248, 179, 79);
			break;

		case GHOST_RANDOM:
			return MyColor(0, 248, 248);
			break;
		}
	}
	return(MyColor(255, 186, 8));
}


void Ghost::ChooseMove(const Maze& maze, const MyVector& pacmanPos) {
	// way to the pacman
	MyVector optimalMove(0, 0);

	// random way not to the wall and different from prev position
	MyVector randomMove(0, 0);

	// way to get away from the pacman
	MyVector escapeMove(0, 0);

	MyVector newPos(0, 0);

	//check if it is dead end
	for (int i = 0; i <= int(STOP); i++) {
		DIRECTION newDirection = DIRECTION(i);
		// if all other ways not valid then rotate
		if (newDirection == STOP) {
			move *= -1;
			return;
		}
		if (getMoveFromDirection(newDirection) == move * -1)
			continue;
		newPos = position + getMoveFromDirection(newDirection);
		// if there is valid pos then break;
		if (maze.GetCellObjByVector(newPos) != CELL_WALL)
			break;
	}

	double curDistance = (position - pacmanPos).GetLen();

	// choose random move
	while (1) {
		DIRECTION newDirection = DIRECTION(rand() % int(STOP));
		randomMove = getMoveFromDirection(newDirection);
		MyVector newPos = position + randomMove;
		CELL_OBJ shit = maze.GetCellObjByVector(newPos);
		if (!((maze.GetCellObjByVector(newPos) == CELL_WALL) || (randomMove == move * -1)))
			break;
	}

	// choose optimal and escape moves
	for (int i = 0; i < int(STOP); i++) {
		DIRECTION newDirection = DIRECTION(i);
		newPos = position + getMoveFromDirection(newDirection);
		double newDistance = (newPos - pacmanPos).GetLen();

		if ((newDistance <= curDistance) && (maze.GetCellObjByVector(newPos) != CELL_WALL))
			optimalMove = getMoveFromDirection(newDirection);

		if ((newDistance > curDistance) && (maze.GetCellObjByVector(newPos) != CELL_WALL))
			escapeMove = getMoveFromDirection(newDirection);
	}

	// if moves were not found then set them random
	if (optimalMove.IsZero())
		optimalMove = randomMove;
	if (escapeMove.IsZero())
		escapeMove = randomMove;

	// set move
	if (status == ENT_DEAD) {
		move = randomMove;
	}
	else if (status == ENT_FRIGHTENED){
		move = escapeMove;
	}
	else {
		switch (type) {
		case GHOST_CLEVER:
			move = optimalMove;
			break;

		case GHOST_RANDOM:
			move = randomMove;
			break;

		case GHOST_STUPID:
			if (curDistance <= 10)
				move = optimalMove;
			else
				move = randomMove;
		}
	}
}
