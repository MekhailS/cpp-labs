#include "Entity.h"

#include "Maze.h"
#include "Game.h"


Entity::Entity(const MyVector& s_respawnPoint, 
	int s_maxLives, int s_respawnTime) {
	position = respawnPoint = s_respawnPoint;
	lives = maxLives = s_maxLives;
	move = GetMoveFromDirection(STOP);
	respawnTime = s_respawnTime;
	status = ENT_NORMAL;
}


int Entity::MakeStep(Maze& maze) {
	MyVector newPos = maze.GetValidPos(position + move);
	CELL_OBJ cellToStep = maze.GetCellObjByVector(newPos);
	if (cellToStep != CELL_WALL) {
		position = newPos;
		return 1;
	}
	return 0;
}


bool Entity::TryRespawn() {
	if ((status == ENT_DEAD) && (lives > 0)) {
		static int curTicks = 0;
		curTicks++;
		if (curTicks >= respawnTime) {
			status = ENT_NORMAL;
			SetMoveDirection(STOP);
			position = respawnPoint;
			curTicks = 0;
			return 1;
		}
	}
	return 0;
}


bool Entity::Kill(){
	status = ENT_DEAD;
	lives--;
	position = MyVector(0, 0);
	SetMoveDirection(STOP);
	return lives;
}


void Entity::Heal(int addLives) {
	lives += addLives;
	if (lives > maxLives) {
		lives = maxLives;
	}
}


void Entity::HealFull() {
	lives = maxLives;
}


MyVector Entity::GetPosition() const {
	return position;
}


ENT_STATUS Entity::GetStatus() const {
	return status;
}


int Entity::GetLives() const {
	return lives;
}


MyColor Entity::GetColor() const {
	switch (status) {
	case ENT_FRIGHTENED:
		return(MyColor(5, 166, 240));
		break;

	case ENT_BOOSTED:
		return(MyColor(243, 83, 73));
		break;

	default:
		return(MyColor(255, 255, 0));
		break;
	}
}


void Entity::SetMoveDirection(DIRECTION direction) {
	move = GetMoveFromDirection(direction);
}


void Entity::Draw(HDC hdc) const {
	HBRUSH hBrush;
	MyColor clr = GetColor();
	MyVector v = GetPosition();
	hBrush = CreateSolidBrush(RGB(clr.Red(), clr.Green(), clr.Blue()));
	SelectObject(hdc, hBrush);
	Ellipse(hdc, v.GetX() * SQUARE_SIZE, v.GetY() * SQUARE_SIZE,
		v.GetX() * SQUARE_SIZE + SQUARE_SIZE, v.GetY() * SQUARE_SIZE + SQUARE_SIZE);
	DeleteObject(hBrush);
}


MyVector Entity::GetMoveFromDirection(DIRECTION direction) const {
	MyVector move(0, 0);
	switch (direction) {
	case UP:
		move = MyVector(0, 1);
		break;

	case DOWN:
		move = MyVector(0, -1);
		break;

	case RIGHT:
		move = MyVector(1, 0);
		break;

	case LEFT:
		move = MyVector(-1, 0);
		break;

	case STOP:
		move = MyVector(0, 0);
		break;
	}
	return move;
}
