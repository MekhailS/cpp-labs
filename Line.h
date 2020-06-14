#pragma once

#include "AbstractObjects.h"


class Line : public AbstractFigure {
public:
	Line(const AbstractBrush& brush) : AbstractFigure(brush, 2) { }

	void Draw(Canvas& canvas, const Vector& pos) override;
};