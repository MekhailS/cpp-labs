#pragma once
#include "..\pch.h"
#include <vector>


class MyRectangle
{
	Vector lowLeft, upRight;

public:

	MyRectangle(const Vector& a = Vector(), const Vector& b = Vector()) {
		lowLeft = Vector(fmin(a.GetX(), b.GetX()), fmin(a.GetY(), b.GetY()));
		upRight = Vector(fmax(a.GetX(), b.GetX()), fmax(a.GetY(), b.GetY()));
	}


	MyRectangle(const std::vector<int>& arr) {
		Vector a(arr[0], arr[1]);
		Vector b(arr[2], arr[3]);
		lowLeft = Vector(fmin(a.GetX(), b.GetX()), fmin(a.GetY(), b.GetY()));
		upRight = Vector(fmax(a.GetX(), b.GetX()), fmax(a.GetY(), b.GetY()));
	}


	Vector GetLowLeft() const { return lowLeft; }


	Vector GetUpRight() const { return upRight; }


	bool ContainVectInside(const Vector& v) const {
		return (v > lowLeft) && ((v < upRight));
	}

	
	bool ContainMyRectangleInside(const MyRectangle& rect) const {
		return (ContainVectInside(rect.GetLowLeft()) && ContainVectInside(rect.GetUpRight()));
	}

};

