#pragma once

#include "Game.h"
#include "framework.h"


#define SQUARE_SIZE 20


void DrawMaze(HDC hdc, const Maze& maze);

void DrawPacman(HDC hdc, const Pacman& pacman);
void DrawCellOnPacman(HDC hdc, const Maze& maze, const Pacman& pacman);

void DrawListGhost(HDC hdc, const list<shared_ptr<const Ghost>> ghostsList);
void DrawCellOnListGhost(HDC hdc, const Maze& maze, const list<shared_ptr<const Ghost>> ghostsList);

void DrawLifes(HDC hdc, const Pacman& pacman);
void DrawScore(HDC hdc, const Pacman& pacman);
