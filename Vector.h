#pragma once
#include <math.h>

class Vector
{
	double x;
	double y;

public:

	Vector(double x = 0, double y = 0) :
		x(x), y(y) {}


	double GetX() const { return x; }


	double GetY() const { return y; }


	double GetLen() const { return (sqrt(x * x + y * y)); }


	bool IsZero() const { return(!(x || y)); }


	Vector Floor() {
		x = floor(x);
		y = floor(y);
		return *this;
	}


	Vector GetNormalized() const {
		if (IsZero())
			return(Vector());
		return (Vector(*this) * (1 / GetLen()));
	}


	Vector operator + (const Vector& vect) const {
		return(Vector(x + vect.GetX(), y + vect.GetY()));
	}


	Vector operator - (const Vector& vect) const {
		return(Vector(x - vect.GetX(), y - vect.GetY()));
	}


	Vector operator * (double a) const {
		return(Vector(x * a, y * a));
	}


	Vector operator * (const Vector& vect) const {
		return Vector(x * vect.GetX(), y * vect.GetY());
	}


	Vector operator / (double a) const {
		return(Vector(x / a, y / a));
	}


	Vector operator / (const Vector& vect) const {
		return Vector(x / vect.GetX(), y / vect.GetY());
	}


	Vector& operator += (const Vector& vect) {
		x += vect.GetX();
		y += vect.GetY();
		return *this;
	}


	Vector& operator *= (double a) {
		x *= a;
		y *= a;
		return *this;
	}


	Vector operator *= (const Vector& vect) {
		x *= vect.GetX();
		y *= vect.GetY();
		return *this;
	}


	Vector& operator /= (double a) {
		x /= a;
		y /= a;
		return *this;
	}


	Vector operator /= (const Vector& vect) {
		x /= vect.GetX();
		y /= vect.GetY();
		return *this;
	}


	bool operator == (const Vector& vect) {
		return ((x == vect.GetX()) && (y == vect.GetY()));
	}

	bool operator != (const Vector& vect) {
		return !((x == vect.GetX()) && (y == vect.GetY()));
	}


	bool operator < (const Vector& vect) const {
		return ((x < vect.GetX()) && (y < vect.GetY()));
	}

	bool operator > (const Vector& vect) const {
		return ((x > vect.GetX()) && (y > vect.GetY()));
	}
};