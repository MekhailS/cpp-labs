#include "Maze.h"


Maze::Maze(ifstream& fileWithLevel) {

	string line;
	int i, j;

	for (i = 0; getline(fileWithLevel, line); i++) {
		maze.push_back(vector<CELL_OBJ>(line.length()));
		for (j = 0; j < line.size(); j++) {
			switch (line[j]) {
			case int('#') :
				maze[i][j] = CELL_WALL;
				break;

			case int('.') :
				maze[i][j] = CELL_COIN;
				break;

			case int('$') :
				maze[i][j] = CELL_ENERGIZER;
				break;

			case int('F'):
				maze[i][j] = CELL_FRUIT;
				break;

			case int('J') :
				maze[i][j] = CELL_EMPTY;
				jailGhosts = MyVector(i, j);
				break;

			case int('P') :
				maze[i][j] = CELL_EMPTY;
				spawnPacman = MyVector(i, j);
				break;

			case int('S') :
				maze[i][j] = CELL_EMPTY;
				spawnGhosts = MyVector(i, j);
				break;

			default:
				maze[i][j] = CELL_EMPTY;
				break;

			}
		}
	}
}


void Maze::SetCellObjByVector(const MyVector& v, CELL_OBJ obj) {
	maze[v.GetX()][v.GetY()] = obj;
}


MyVector Maze::GetValidPos(const MyVector& curPos) const {
	MyVector validPos;
	MyVector upRight = MyVector(GetUpBorder() - 1, GetRightBorder() - 1);
	MyVector downLeft = MyVector(0, 0);
	if (upRight.FitsInsideMyRectangle(curPos) && (downLeft.FitsOutsideMyRectangle(curPos)))
		validPos = curPos;
	else {
		if (curPos.GetX() > GetUpBorder() - 1)
			validPos = MyVector(0, curPos.GetY());
		else if (curPos.GetX() < 0)
			validPos = MyVector(GetUpBorder() - 1, curPos.GetY());

		if (curPos.GetY() > GetRightBorder() - 1)
			validPos = MyVector(curPos.GetX(), 0);
		else if (curPos.GetY() < 0)
			validPos = MyVector(curPos.GetX(), GetRightBorder() - 1);
	}
	return validPos;
}


CELL_OBJ Maze::GetCellObjByVector(const MyVector& v) const {
	MyVector upRight = MyVector(GetUpBorder() - 1, GetRightBorder() - 1);
	MyVector downLeft = MyVector(0, 0);
	if (!(upRight.FitsInsideMyRectangle(v) && (downLeft.FitsOutsideMyRectangle(v))))
		return CELL_EMPTY;
	return maze[v.GetX()][v.GetY()];
}


int Maze::GetMaxScore() const {
	int maxScore = 0;
	for (auto& mazeLine : maze) {
		for (auto& mazeCell : mazeLine) {
			if (mazeCell != CELL_WALL)
				maxScore += int(mazeCell);
		}
	}
	return maxScore;
}


MyVector Maze::GetSpawnGhosts() const {
	return spawnGhosts;
}


MyVector Maze::GetSpawnPacman() const {
	return spawnPacman;
}


MyVector Maze::GetJailGhosts() const {
	return jailGhosts;
}


int Maze::GetRightBorder() const {
	return maze[0].size();
}


int Maze::GetUpBorder() const {
	return maze.size();
}


void Maze::DrawCellByVector(HDC hdc, const MyVector& v) const {
	HBRUSH hBrush;
	int quaterOfCell = SQUARE_SIZE / 3;
	int partOfCell = SQUARE_SIZE / 2;

	CELL_OBJ cell = GetCellObjByVector(v);
	if (cell != CELL_WALL) {
		hBrush = CreateSolidBrush(RGB(255, 255, 255));
		SelectObject(hdc, hBrush);
		Rectangle(hdc, v.GetX() * SQUARE_SIZE, v.GetY() * SQUARE_SIZE,
			v.GetX() * SQUARE_SIZE + SQUARE_SIZE, v.GetY() * SQUARE_SIZE + SQUARE_SIZE);
		DeleteObject(hBrush);
	}
	switch (cell) {
	case CELL_COIN:
		hBrush = CreateSolidBrush(RGB(193, 0, 32));
		SelectObject(hdc, hBrush);
		Ellipse(hdc, v.GetX() * SQUARE_SIZE + quaterOfCell, v.GetY() * SQUARE_SIZE + quaterOfCell,
			v.GetX() * SQUARE_SIZE + SQUARE_SIZE - quaterOfCell, v.GetY() * SQUARE_SIZE + SQUARE_SIZE - quaterOfCell);
		DeleteObject(hBrush);
		break;

	case CELL_ENERGIZER:
		hBrush = CreateSolidBrush(RGB(0, 107, 60));
		SelectObject(hdc, hBrush);
		Rectangle(hdc, v.GetX() * SQUARE_SIZE + quaterOfCell, v.GetY() * SQUARE_SIZE + quaterOfCell,
			v.GetX() * SQUARE_SIZE + SQUARE_SIZE - quaterOfCell, v.GetY() * SQUARE_SIZE + SQUARE_SIZE - quaterOfCell);
		DeleteObject(hBrush);
		break;

	case CELL_FRUIT:
		hBrush = CreateSolidBrush(RGB(255, 0, 0));
		SelectObject(hdc, hBrush);
		Rectangle(hdc, v.GetX() * SQUARE_SIZE + quaterOfCell, v.GetY() * SQUARE_SIZE + quaterOfCell,
			v.GetX() * SQUARE_SIZE + SQUARE_SIZE - quaterOfCell, v.GetY() * SQUARE_SIZE + SQUARE_SIZE - quaterOfCell);
		DeleteObject(hBrush);
		break;

	case CELL_WALL:
		hBrush = CreateSolidBrush(RGB(0, 0, 0));
		SelectObject(hdc, hBrush);
		Rectangle(hdc, v.GetX() * SQUARE_SIZE, v.GetY() * SQUARE_SIZE,
			v.GetX() * SQUARE_SIZE + SQUARE_SIZE, v.GetY() * SQUARE_SIZE + SQUARE_SIZE);
		DeleteObject(hBrush);
		break;
	}
}


void Maze::DrawMaze(HDC hdc) const {
	for (int i = 0; i < GetUpBorder(); i++) {
		for (int j = 0; j < GetRightBorder(); j++) {
			DrawCellByVector(hdc, MyVector(i, j));
		}
	}
}