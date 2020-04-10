#pragma once

#include "MyWindow.h"
#include "MyRectangleWNameColor.h"
#include <memory>
#include <vector>

using namespace std;

class MyMenu:
	public enable_shared_from_this<MyMenu>, public MyRectangleWNameColor 
{

	vector<shared_ptr<MyWindow>> windows;


	shared_ptr<MyWindow> const GetMutableWindowByName(string name);
public:

	MyMenu(const MyRectangle& frame, const string& name, const MyColor& color) :
		MyRectangleWNameColor(frame, name, color) {}


	void CreateMyWindow(const MyRectangle& frame, const string& name, const MyColor& color);


	int GetNumWindows() const { return windows.size(); }


	shared_ptr<const MyWindow> const GetIthReadOnlyWindow(int i) const;


	shared_ptr<MyWindow> const GetIthMutableWindow(int i);


	bool SetButtonFunc(void (*funcToSet)(), string nameMyWindow, string nameMyButton);
};

