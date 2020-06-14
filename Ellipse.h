#pragma once

#include "AbstractObjects.h"


class Ellipse : public AbstractFigure {
public:

	Ellipse(const AbstractBrush& brush) : AbstractFigure(brush, 2) { }

	void Draw(Canvas& canvas, const Vector& pos) override;
};