#pragma once
#include "pch.h"

#include "AbstractObjects.h"


class Eraser : public AbstractBrush {
public:

	Eraser(const AbstractBrush& brush) : AbstractBrush(brush) {}

	void Draw(Canvas& canvas, const Vector& pos) override {
		canvas.DrawCircle(pos, MyColor(255, 255, 255), width);
	}
};