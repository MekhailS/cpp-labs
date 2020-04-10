#pragma once
#include "MyVector.h"
#include <vector>


class MyRectangle
{
	MyVector lowLeft, upRight;

public:

	MyRectangle(const MyVector& a = MyVector(), const MyVector& b = MyVector()) {
		lowLeft = MyVector(fmin(a.GetX(), b.GetX()), fmin(a.GetY(), b.GetY()));
		upRight = MyVector(fmax(a.GetX(), b.GetX()), fmax(a.GetY(), b.GetY()));
	}


	MyRectangle(const std::vector<int>& arr) {
		MyVector a(arr[0], arr[1]);
		MyVector b(arr[2], arr[3]);
		lowLeft = MyVector(fmin(a.GetX(), b.GetX()), fmin(a.GetY(), b.GetY()));
		upRight = MyVector(fmax(a.GetX(), b.GetX()), fmax(a.GetY(), b.GetY()));
	}


	MyVector GetLowLeft() const { return lowLeft; }


	MyVector GetUpRight() const { return upRight; }


	bool SetLowLeft(const MyVector& v) {
		bool doFit = v.FitsInsideMyRectangle(upRight);
		if (doFit)
			lowLeft = v;
		return doFit;
	}


	bool SetUpRight(const MyVector& v) {
		bool doFit = v.FitsOutsideMyRectangle(lowLeft);
		if (doFit)
			upRight = v;
		return doFit;
	}


	bool ContainVectInside(const MyVector& v) const {
		return (v.FitsOutsideMyRectangle(lowLeft) && v.FitsInsideMyRectangle(upRight));
	}

	
	bool ContainMyRectangleInside(const MyRectangle& rect) const {
		return (ContainVectInside(rect.GetLowLeft()) && ContainVectInside(rect.GetUpRight()));
	}

};

