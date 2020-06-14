#pragma once

#include "MyMenu.h"
#include "Script.h"



using namespace std;

class UserMenu {

	shared_ptr<MyMenu> menu = nullptr;

	int iCurMyWindow = 0;
	int iCurMyButton = 0;


	shared_ptr<const MyButton> GetCurButton() const;

	shared_ptr<const MyWindow> GetCurWindow() const;

	void HighlightButton(HDC hdc) const;

	void DeHiglightButton(HDC hdc) const;

	void HighlightWindow(HDC hdc) const;

	void DeHighlightWindow(HDC hdc) const;
	

public:

	UserMenu(shared_ptr<MyMenu>& initMyMenu);

	UserMenu(string scriptFileName);

	bool NextWindow(HDC hdc);

	bool PrevWindow(HDC hdc);

	bool NextButton(HDC hdc);

	bool PrevButton(HDC hdc);

	pair<string, string> GetIDButton() const;

	void Render(HDC hdc) const;

};