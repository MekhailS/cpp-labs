#pragma once

#include "MyRectangleWNameColor.h"
#include "MyColor.h"
#include <memory>

using namespace std;
class MyWindow;

	
class MyButton :
	public MyRectangleWNameColor
{

	friend class MyWindow;
	friend class MyMenu;

	MyColor mHighlight;

	void (*funcToDo)();

	weak_ptr<MyWindow> mWindow;


	MyButton(const MyRectangle& frame, const MyColor& mainMyColor, const MyColor& highlight,
		const string& name, const weak_ptr<MyWindow> window) :
		MyRectangleWNameColor(frame, name, mainMyColor), mHighlight(highlight), mWindow(window), funcToDo(NULL) {}

public:


	MyColor GetHighlightColor() const {
		return mHighlight;
	}


	shared_ptr<const MyWindow> GetReadOnlyWindow() const {
		return mWindow.lock();
	}


	shared_ptr<MyWindow> GetMutableWindow() const {
		return mWindow.lock();
	}


	void DoFunc() const {
		if (funcToDo != nullptr)
			funcToDo();
	}
};