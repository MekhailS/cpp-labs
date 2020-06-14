#pragma once
#include "pch.h"
#include "Canvas.h"


// abstract class for brush, eraser, figure
class AbstractBrush {
protected:

	MyColor color;
	int width;

	AbstractBrush() :
		width(MAX_WIDTH / 2) {}


public:

	virtual void Draw(Canvas& canvas, const Vector& pos) = 0;

	void SetColor(MyColor newColor) {
		color = newColor;
	}

	void IncWidth(int incVal) {
		width += incVal;
		if (width < 1)
			width = 1;
		else if (width > MAX_WIDTH)
			width = MAX_WIDTH;
	}

};


class AbstractFigure: public AbstractBrush {
protected:
	// returns number of poss required for drawing figure
	// example: circle - 2 poss, triangle - 3 poss
	int const reqNumPoints;

	// list of poss required for drawing figure
	// example: circle - 2 poss, triangle - 3 poss
	vector<Vector> points;

	// add new pos of figure to poss vector
	// return 1 if vector contains enough poss for drawing
	// 0 otherwise
	bool UpdateVectors(const Vector& newVector) {
		if (points.size() == reqNumPoints)
			points.clear();
		points.push_back(newVector);
		return (points.size() == reqNumPoints);
	}

	AbstractFigure(const AbstractBrush& brush, int s_reqNumVectors) :
		reqNumPoints(s_reqNumVectors), AbstractBrush(brush) { }
};