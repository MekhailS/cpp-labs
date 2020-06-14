#pragma once

#include "pch.h"

enum DIRECTION {
	RIGHT = 1,
	LEFT = -1,
	UP = -10,
	DOWN = 10,
};

class Canvas {

	ColorMatrix canvas;
	Vector zoomPoint;
	int scale = 1;

	bool DrawCell(const Vector& cell, const MyColor& color);

	Vector GetEdge() const;

	void PrintOnDesktop(HDC hdc, const Vector& deskPoint) const;

public:

	Canvas(int width, int height);

	bool IsCanvas(const Vector& point) const;

	void Clear();

	void DrawCircle(const Vector& mid, const MyColor& color, int radius);

	void DrawSquare(const Vector& mid, const MyColor& color, int radius);

	// return indexes of cell in canvas 2D vector
	// adjusted for scale and scaleVector
	Vector GetVector(const Vector& winApiVector) const;

	// render canvas using WinApi
	void Render(HDC hdc) const;

	void ZoomIn();

	void ZoomOut();

	void MoveViewSector(DIRECTION direction);

	void LoadDrawing(string fileName);

	void SaveDrawing(string fileName) const;
};