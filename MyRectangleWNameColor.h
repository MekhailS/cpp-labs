#pragma once

#include "MyRectangle.h"
#include "MyColor.h"
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
};