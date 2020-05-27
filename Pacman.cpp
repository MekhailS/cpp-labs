#include "Pacman.h"

#include "Ghost.h"
#include "Game.h"


Pacman::Pacman(const MyVector& s_respawnPoint,
	int s_maxLives, int s_boostedTime):
	Entity(s_respawnPoint, s_maxLives, 0) {
	score = 0;
	boostedTime = s_boostedTime;
}


int Pacman::MakeStep(Maze& maze) {
	static int curTicks = 0;

	int toReturn = Entity::MakeStep(maze);
	CELL_OBJ cellToStep = maze.GetCellObjByVector(position);

	if (toReturn) {
		switch (cellToStep) {

		case CELL_COIN:
			score++;
			maze.SetCellObjByVector(position, CELL_EMPTY);
			break;

		case CELL_ENERGIZER:
			score += 10;
			status = ENT_BOOSTED;
			curTicks = 0;
			maze.SetCellObjByVector(position, CELL_EMPTY);
			toReturn = 2;
			break;

		case CELL_FRUIT:
			Heal(1);
			score += 20;
			maze.SetCellObjByVector(position, CELL_EMPTY);
			break;

		}
	}

	if (status == ENT_BOOSTED) {
		curTicks++;
		if (curTicks >= boostedTime) {
			status = ENT_NORMAL;
			curTicks = 0;

			toReturn = 3;
		}
	}
	return toReturn;
}


int Pacman::GetScore() const {
	return score;
}


void Pacman::DrawLifes(HDC hdc) const {
	char numOfLifes[50] = { '\0' };
	char text[50] = "Lifes: ";
	_itoa_s(GetLives(), numOfLifes, 10);
	strcat_s(text, numOfLifes);

	TextOutA(hdc, 30.0 * SQUARE_SIZE, 0.0 * SQUARE_SIZE, text, strlen(text));
}


void Pacman::DrawScore(HDC hdc) const {
	char numOfScores[50] = { '\0' };
	char text[50] = "Score: ";
	_itoa_s(GetScore(), numOfScores, 10);
	strcat_s(text, numOfScores);

	TextOutA(hdc, 30.0 * SQUARE_SIZE, 2.0 * SQUARE_SIZE, text, strlen(text));
}


void Pacman::Draw(HDC hdc) const {
	Entity::Draw(hdc);
	DrawLifes(hdc);
	DrawScore(hdc);
}
