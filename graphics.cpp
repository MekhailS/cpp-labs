#include "graphics.h"


void DrawMaze(HDC hdc, const Maze& maze);

void DrawCellByVector(HDC hdc, const Maze& maze, const MyVector& v);

void DrawPacman(HDC hdc, const Pacman& pacman);
void DrawCellOnPacman(HDC hdc, const Maze& maze, const Pacman& pacman);

void DrawListGhost(HDC hdc, const list<shared_ptr<const Ghost>> ghostsList);
void DrawCellOnListGhost(HDC hdc, const Maze& maze, const list<shared_ptr<const Ghost>> ghostsList);
void DrawGhost(HDC hdc, const shared_ptr<const Ghost> ghost);


void DrawMaze(HDC hdc, const Maze& maze) {
    for (int i = 0; i < maze.GetUpBorder(); i++) {
        for (int j = 0; j < maze.GetRightBorder(); j++) {
            DrawCellByVector(hdc, maze, MyVector(i, j));
        }
    }
}


void DrawCellByVector(HDC hdc, const Maze& maze, const MyVector& v) {
    HBRUSH hBrush;
    int quaterOfCell = SQUARE_SIZE / 3;
    int partOfCell = SQUARE_SIZE / 2;

    CELL_OBJ cell = maze.GetCellObjByVector(v);
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


void DrawPacman(HDC hdc, const Pacman& pacman) {
    HBRUSH hBrush;
    MyColor clr = pacman.GetColor();
    MyVector v = pacman.GetPosition();
    hBrush = CreateSolidBrush(RGB(clr.Red(), clr.Green(), clr.Blue()));
    SelectObject(hdc, hBrush);
    Ellipse(hdc, v.GetX() * SQUARE_SIZE, v.GetY() * SQUARE_SIZE,
        v.GetX() * SQUARE_SIZE + SQUARE_SIZE, v.GetY() * SQUARE_SIZE + SQUARE_SIZE);
    DeleteObject(hBrush);
}


void DrawCellOnPacman(HDC hdc, const Maze& maze, const Pacman& pacman) {
    MyVector v = pacman.GetPosition();
    DrawCellByVector(hdc, maze, v);
}


void DrawListGhost(HDC hdc, const list<shared_ptr<const Ghost>> ghostsList) {
    for (auto& ghost : ghostsList) {
        DrawGhost(hdc, ghost);
    }
}


void DrawCellOnListGhost(HDC hdc, const Maze& maze, const list<shared_ptr<const Ghost>> ghostsList) {
    for (auto& ghost : ghostsList) {
        DrawCellByVector(hdc, maze, ghost->GetPosition());
    }
}


void DrawGhost(HDC hdc, const shared_ptr<const Ghost> ghost) {
    HBRUSH hBrush;
    MyColor clr = ghost->GetColor();
    MyVector v = ghost->GetPosition();
    hBrush = CreateSolidBrush(RGB(clr.Red(), clr.Green(), clr.Blue()));
    SelectObject(hdc, hBrush);
    Ellipse(hdc, v.GetX() * SQUARE_SIZE, v.GetY() * SQUARE_SIZE,
        v.GetX() * SQUARE_SIZE + SQUARE_SIZE, v.GetY() * SQUARE_SIZE + SQUARE_SIZE);
    DeleteObject(hBrush);
}


void DrawLifes(HDC hdc, const Pacman& pacman) {
    char numOfLifes[50] = { '\0' };
    char text[50] = "Lifes: ";
    _itoa_s(pacman.GetLives(), numOfLifes, 10);
    strcat_s(text, numOfLifes);

    TextOutA(hdc, 30.0 * SQUARE_SIZE, 0.0 * SQUARE_SIZE, text, strlen(text));
}


void DrawScore(HDC hdc, const Pacman& pacman) {
    char numOfScores[50] = { '\0' };
    char text[50] = "Score: ";
    _itoa_s(pacman.GetScore(), numOfScores, 10);
    strcat_s(text, numOfScores);

    TextOutA(hdc, 30.0 * SQUARE_SIZE, 2.0 * SQUARE_SIZE, text, strlen(text));
}