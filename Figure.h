#pragma once
#include "pch.h"

#include "BrushAbstract.h"


enum FIGURE_NAME {
	FIG_LINE = 20,
	FIG_ELLIPSE,
	FIG_RECTANGLE
};


class Figure : public BrushAbstract {

	FIGURE_NAME figName;

	// vector of points required for drawing figure
	// example: circle - 2 points, triangle - 3 points
	vector<pair<int, int>> points;


	// returns number of points required for drawing figure
	// example: circle - 2 points, triangle - 3 points
	int GetNumReqPoints(FIGURE_NAME figName) const;
	
	// add new point of figure to points vector
	// return 1 if vector contains enough points for drawing
	// 0 otherwise
	bool UpdatePoints(pair<int, int> newPoint);


public:

	Figure(BrushAbstract& brush, FIGURE_NAME s_figName):
		BrushAbstract(brush), figName(s_figName) {}

	// calls UpdatePoints() with argument point
	// if UpdatePoints() returns 1, draws figure on canvas
	virtual void Draw(Canvas& canvas, const pair<int, int>& point) const;
};