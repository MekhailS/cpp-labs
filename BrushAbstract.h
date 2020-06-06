#pragma once
#include "pch.h"
#include "Canvas.h"


// abstract class for brush, eraser, figure
class BrushAbstract {
protected:

	MyColor color;
	int width;

	BrushAbstract() :
		width(MAX_WIDTH / 2) {}
	
public:


	virtual void Draw(Canvas& canvas, const pair<int, int>& point) const = 0;

	void SetColor(MyColor newColor) {
		color = newColor;
	}

	void operator ++ () {
		if (width < MAX_WIDTH) width++;
	}

	void operator -- () {
		if (width) width--;
	}

};