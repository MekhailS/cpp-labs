#include "Ellipse.h"


void Ellipse::Draw(Canvas& canvas, const Vector& pos) {
	if (UpdateVectors(pos)) {
		int x0 = (points[0].GetX() + points[1].GetX()) / 2;
		int y0 = (points[0].GetY() + points[1].GetY()) / 2;
		int a = abs(points[0].GetX() - x0);
		int b = abs(points[0].GetY() - y0);

		for (int delta = 0; delta <= a; delta++) {
			int x = x0 + delta;
			int h = (b / a) * sqrt(a * a - pow(x - x0, 2));

			canvas.DrawCircle(Vector(x0 + delta, y0 + h), color, width);
			canvas.DrawCircle(Vector(x0 + delta, y0 - h), color, width);
			canvas.DrawCircle(Vector(x0 - delta, y0 + h), color, width);
			canvas.DrawCircle(Vector(x0 - delta, y0 - h), color, width);
		}
		for (int delta = 0; delta <= b; delta++) {
			int y = y0 + delta;
			int h = (a / b) * sqrt(b * b - pow(y - y0, 2));

			canvas.DrawCircle(Vector(x0 + h, y0 + delta), color, width);
			canvas.DrawCircle(Vector(x0 + h, y0 - delta), color, width);
			canvas.DrawCircle(Vector(x0 - h, y0 + delta), color, width);
			canvas.DrawCircle(Vector(x0 - h, y0 - delta), color, width);
		}
	}
}