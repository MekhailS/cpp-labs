#pragma once

#include "MyRectangle.h"
#include <string>

using namespace std;

class MyRectangleWNameColor {

protected:

	MyRectangle mFrame;
	string mName;
	MyColor mColor;


public:

	MyRectangleWNameColor(const MyRectangle& frame, const string& name, const MyColor& color) :
		mFrame(frame), mName(name), mColor(color) {}

	MyRectangle GetFrame() const {
		return mFrame;
	}

	MyColor GetGolor() const {
		return mColor;
	}

	string GetName() const {
		return mName;
	}

	virtual void Print(HDC hdc) const {
		HBRUSH brush = CreateSolidBrush(RGB(mColor.Red(), mColor.Green(), mColor.Blue()));
		SelectObject(hdc, brush);
		Rectangle(hdc, mFrame.GetLowLeft().GetX(), mFrame.GetLowLeft().GetY(), mFrame.GetUpRight().GetX(), mFrame.GetUpRight().GetY());
		DeleteObject(brush);
		SetBkMode(hdc, TRANSPARENT);
		TextOutA(hdc, (mFrame.GetLowLeft().GetX() + mFrame.GetUpRight().GetX() - 6 * mName.length()) / 2, mFrame.GetLowLeft().GetY(), mName.c_str(), mName.length());
	}

	void Highlight(HDC hdc, const MyColor& clr) const {
		HPEN pen = CreatePen(PS_SOLID, 2, RGB(clr.Red(), clr.Green(), clr.Blue()));
		SelectObject(hdc, pen);
		SelectObject(hdc, GetStockObject(NULL_BRUSH));
		Rectangle(hdc, mFrame.GetLowLeft().GetX(), mFrame.GetLowLeft().GetY(), mFrame.GetUpRight().GetX(), mFrame.GetUpRight().GetY());
		DeleteObject(pen);
	}
};