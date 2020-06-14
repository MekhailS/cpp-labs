#pragma once

#include "MyButton.h"
#include "MyRectangleWNameColor.h"
#include <memory>
#include <vector>

using namespace std;
class MyMenu;

class MyWindow :
	public enable_shared_from_this<MyWindow>, public MyRectangleWNameColor
{

	friend class MyMenu;

	weak_ptr<MyMenu> mMenu;
	vector<shared_ptr<MyButton>> buttons;


	MyWindow(const MyRectangle& frame, const MyColor& color, const string& name, const weak_ptr<MyMenu> menu) :
		MyRectangleWNameColor(frame, name, color), mMenu(menu) {}

	shared_ptr<MyButton> GetMutableButtonByName(string name);


public:

	void CreateMyButton(const MyRectangle& frame, const string& name, const MyColor& mainMyColor, const MyColor& highlight);

	int GetNumButtons() const { return buttons.size(); }

	shared_ptr<const MyButton> GetIthReadOnlyButton(int i) const;

	shared_ptr<MyButton> GetIthMutableButton(int i);

	shared_ptr<const MyMenu> GetReadOnlyMenu() const { return mMenu.lock(); }

	shared_ptr<MyMenu> GetMutableMenu() { return mMenu.lock(); }

	void Print(HDC hdc) const;
};