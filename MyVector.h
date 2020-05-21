#pragma once
#include <math.h>

class MyVector
{
	double x;
	double y;

public:

	MyVector(double x = 0, double y = 0) :
		x(x), y(y) {}


	double GetX() const { return x; }


	double GetY() const { return y; }


	double GetLen() const { return (sqrt(x * x + y * y)); }


	bool IsZero() const { return(!(x || y)); }


	MyVector GetNormalized() const {
		if (IsZero())
			return(MyVector());
		return (MyVector(*this) * (1 / GetLen()));
	}


	MyVector operator+(const MyVector& vect) const {
		return(MyVector(x + vect.GetX(), y + vect.GetY()));
	}


	MyVector operator-(const MyVector& vect) const {
		return(MyVector(x - vect.GetX(), y - vect.GetY()));
	}


	MyVector operator*(double a) const {
		return(MyVector(x * a, y * a));
	}


	MyVector operator/(double a) const {
		return(MyVector(x / a, y / a));
	}


	MyVector& operator+=(const MyVector& vect) {
		x += vect.GetX();
		y += vect.GetY();
		return *this;
	}


	MyVector& operator*=(double a) {
		x *= a;
		y *= a;
		return *this;
	}


	bool operator==(const MyVector& vect) {
		return ((x == vect.GetX()) && (y == vect.GetY()));
	}

	bool operator!=(const MyVector& vect) {
		return !((x == vect.GetX()) && (y == vect.GetY()));
	}


	bool FitsOutsideMyRectangle(const MyVector& vect) const {
		return ((x <= vect.GetX()) && (y <= vect.GetY()));
	}

	bool FitsInsideMyRectangle(const MyVector& vect) const {
		return ((x >= vect.GetX()) && (y >= vect.GetY()));
	}
};