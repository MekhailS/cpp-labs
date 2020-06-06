#pragma once

#include "pch.h"

enum DIRECTION {
	UP,
	DOWN,
	RIGHT,
	LEFT
};

class Canvas {

	vector<vector<MyColor>> canvas;
	pair<int, int> scalePoint;
	int scale;

public:

	bool DrawCell(const pair<int, int>& cell, MyColor& color);

	// return indexes of cell in canvas 2D vector
	// adjusted for scale and scalePoint
	pair<int, int> GetPoint(pair<int, int> winApiPoint) const;

	// render canvas using WinApi
	void Render();

	void ZoomIn();

	void ZoomOut();

	void MoveViewSector(DIRECTION direction);

	void LoadDrawing(string fileName);

	void SaveDrawing(string fileName);
};