#pragma once

#include "AbstractObjects.h"


class Rectngle : public AbstractFigure {
public:
	Rectngle(const AbstractBrush& brush) : AbstractFigure(brush, 2) { }

	void Draw(Canvas& canvas, const Vector& pos) override;
};