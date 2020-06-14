#include "Canvas.h"


Vector Canvas::GetEdge() const {
	return (Vector(canvas[0].size(), canvas.size()));
}


bool Canvas::DrawCell(const Vector& cell, const MyColor& color) {
	if (IsCanvas(cell)) {
		canvas[cell.GetY()][cell.GetX()] = color;
		return 1;
	}
	return 0;
}


Canvas::Canvas(int width, int height) {
	vector<MyColor> clr(width, MyColor(255, 255, 255));
	canvas = ColorMatrix(height, clr);
}


void Canvas::Clear() {
	vector<MyColor> clr(GetEdge().GetX(), MyColor(255, 255, 255));
	canvas = ColorMatrix(GetEdge().GetY(), clr);
}


bool Canvas::IsCanvas(const Vector& point) const {
	return ((point < GetEdge()) && (point > Vector()));
}


void Canvas::DrawCircle(const Vector& mid, const MyColor& color, int radius) {
	int x0 = mid.GetX();
	int y0 = mid.GetY();
	for (int delta = 0; delta <= radius; delta++) {
		int hMax = sqrt(pow(radius, 2) - pow((delta), 2));
		for (int h = 0; h <= hMax; h++) {
			DrawCell(Vector(x0 + delta, y0 + h), color);
			DrawCell(Vector(x0 + delta, y0 - h), color);
			DrawCell(Vector(x0 - delta, y0 + h), color);
			DrawCell(Vector(x0 - delta, y0 - h), color);
		}
	}
}


void Canvas::DrawSquare(const Vector& mid, const MyColor& color, int radius) {
	int x0 = mid.GetX();
	int y0 = mid.GetY();
	for (int x = x0 - radius; x <= x0 + radius; x++) {
		int hMax = radius;
		for (int h = 0; h <= hMax; h++) {
			DrawCell(Vector(x, y0 + h), color);
			DrawCell(Vector(x, y0 - h), color);
		}
	}
}


Vector Canvas::GetVector(const Vector& winApiVector) const {
	Vector res = zoomPoint + winApiVector / scale;
	res.Floor();
	return(res);
}


void Canvas::Render(HDC hdc) const{
	HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));
	HPEN pen = CreatePen(PS_SOLID, 8, RGB(0, 0, 0));
	SelectObject(hdc, brush);
	SelectObject(hdc, pen);
	Rectangle(hdc, 0, 0, GetEdge().GetX, GetEdge().GetY());
	DeleteObject(brush);
	DeleteObject(pen);
	for (int y = zoomPoint.GetY(); y < GetEdge().GetY(); y++) {
		for (int x = zoomPoint.GetX(); x < GetEdge().GetX(); x++) {
			PrintOnDesktop(hdc, Vector(x,y));
		}
	}
}


void Canvas::PrintOnDesktop(HDC hdc, const Vector& deskPoint) const {
	Vector pointReal = (deskPoint - zoomPoint) * scale;
	pointReal.Floor();
	auto pixel = canvas[deskPoint.GetY()][deskPoint.GetX()];
	if (scale >= 1) {
		SetPixel(hdc, pointReal.GetX(), pointReal.GetY(), RGB(pixel.Red(), pixel.Green(), pixel.Blue()));
	}
	else {
		for (int y = pointReal.GetY(); y < pointReal.GetY() + scale; y++) {
			for (int x = pointReal.GetX(); x < pointReal.GetX() + scale; x++) {
				if (!((x >= GetEdge().GetX) || (y >= GetEdge().GetY)))
					SetPixel(hdc, x, y, RGB(pixel.Red(), pixel.Green(), pixel.Blue()));
			}
		}
	}
}


void Canvas::ZoomIn() {
	scale *= 2;
}


void Canvas::ZoomOut() {
	if (scale <= 1)
		return;
	scale /= 2;
	Vector newZoomPoint = zoomPoint / (GetEdge() / scale).Floor();
	newZoomPoint *= GetEdge() / scale;
	newZoomPoint.Floor();
}


void Canvas::MoveViewSector(DIRECTION direction) {
	Vector newZoomPoint = zoomPoint;
	Vector delta((direction % 10), (direction / 10));
	newZoomPoint += (GetEdge() / scale) * delta;
	newZoomPoint /= 2;
	if ((newZoomPoint < GetEdge()) && (newZoomPoint > Vector())) {
		zoomPoint = newZoomPoint;
	}
}


void Canvas::LoadDrawing(string fileName) {
	fstream infile(fileName);
	string line;
	int i = 0;
	while (1) {
		getline(infile, line);
		if (!infile) break;
		canvas.push_back(vector<MyColor>());
		istringstream fline(line);
		int j = 0;
		while (1) {
			long int clrs;
			fline >> clrs;
			if (!fline) break;
			canvas[i].push_back(MyColor(clrs));
			j++;
		}
		i++;
	}
}


void Canvas::SaveDrawing(string fileName) const {
	ofstream outfile(fileName);
	for (auto& vect : canvas) {
		for (const MyColor& clr : vect)
			outfile << clr.Red() << clr.Green() << clr.Blue() << " ";
		outfile << endl;
	}
	outfile.close();
}

