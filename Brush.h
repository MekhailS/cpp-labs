#pragma once
#include "pch.h"

#include "BrushAbstract.h"


class Brush : public BrushAbstract {
public:

	virtual void Draw(Canvas& canvas, const pair<int, int>& point) const;
};