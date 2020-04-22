#pragma once

#include "MyMenu.h"
#include <memory>
#include <vector>

#define AssertNullMyMenu if (menu == nullptr) return

using namespace std;

class User {

	shared_ptr<MyMenu> menu;

	int iCurMyWindow;
	int iCurMyButton;
	

public:


	User() {
		menu = nullptr;
		iCurMyButton = iCurMyWindow = 0;
	}


	User(shared_ptr<MyMenu>& initMyMenu) {
		iCurMyButton = iCurMyWindow = 0;
		menu = initMyMenu;
	}


	shared_ptr<const MyMenu> GetMenu() const {
		return menu;
	}


	bool NextWindow() {
		bool overNum = 1;
		AssertNullMyMenu 0;
		if (iCurMyWindow + 1 == menu->GetNumWindows()) {
			overNum = 0;
			iCurMyWindow = 0;
		}
		else
			iCurMyWindow++;
		iCurMyButton = 0;
		return overNum;
	}


	bool PrevWindow() {
		AssertNullMyMenu 0;
		if (iCurMyWindow == 0)
			iCurMyWindow = menu->GetNumWindows() - 1;
		else
			iCurMyWindow--;
		iCurMyButton = 0;
		return 1;
	}


	bool NextButton() {
		bool overNum = 1;
		AssertNullMyMenu 0;
		if (iCurMyButton + 1 == menu->GetIthReadOnlyWindow(iCurMyWindow)->GetNumButtons()) {
			overNum = 0;
			iCurMyButton = 0;
		}
		else
			iCurMyButton++;
		return overNum;
	}


	bool PrevButton() {
		AssertNullMyMenu 0;
		if (iCurMyButton == 0)
			iCurMyButton = menu->GetIthReadOnlyWindow(iCurMyWindow)->GetNumButtons() - 1;
		else
			iCurMyButton--;
		return 1;
	}


	shared_ptr<const MyWindow> GetCurWindow() const {
		AssertNullMyMenu nullptr;
		return menu->GetIthReadOnlyWindow(iCurMyWindow);
	}


	shared_ptr<const MyButton> GetCurButton() const {
		AssertNullMyMenu nullptr;
		return menu->GetIthReadOnlyWindow(iCurMyWindow)->GetIthReadOnlyButton(iCurMyButton);
	}
};