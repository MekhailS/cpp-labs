#pragma once
#include "pch.h"

#include "AbstractObjects.h"


class Brush : public AbstractBrush {
public:

	Brush() :
		AbstractBrush() {}

	Brush(const AbstractBrush& brush) :
		AbstractBrush(brush) {}

	void Draw(Canvas& canvas, const Vector& pos) override {
		canvas.DrawCircle(pos, color, width);
	}
};