#pragma once
#include "pch.h"

#include "BrushAbstract.h"


class Eraser : public BrushAbstract {
public:

	// draw with white color
	virtual void Draw(Canvas& canvas, const pair<int, int>& point) const;
};