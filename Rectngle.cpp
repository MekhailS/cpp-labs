#include "Rectngle.h"


void Rectngle::Draw(Canvas& canvas, const Vector& pos) {
	if (UpdateVectors(pos)) {
		array<int, 2> x = { points[0].GetX(), points[1].GetX() };
		array<int, 2> y = { points[0].GetY(), points[1].GetY() };

		for (int x_cur = x[0];; x_cur += sign(x[1] - x[0])) {
			canvas.DrawSquare(Vector(x_cur, y[0]), color, width);
			canvas.DrawSquare(Vector(x_cur, y[1]), color, width);
			if (x_cur == x[1])
				break;
		}
		for (int y_cur = y[0];; y_cur += sign(y[1] - y[0])) {
			canvas.DrawSquare(Vector(x[0], y_cur), color, width);
			canvas.DrawSquare(Vector(x[1], y_cur), color, width);
			if (y_cur == y[1])
				break;
		}
	}
}