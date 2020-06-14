#include "UserMenu.h"

#define AssertNullMyMenu if (menu == nullptr) return


shared_ptr<const MyButton> UserMenu::GetCurButton() const {
	return menu->GetIthReadOnlyWindow(iCurMyWindow)->GetIthReadOnlyButton(iCurMyButton);
}


shared_ptr<const MyWindow> UserMenu::GetCurWindow() const {
	return menu->GetIthReadOnlyWindow(iCurMyWindow);
}


void UserMenu::HighlightButton(HDC hdc) const {
	auto button = GetCurButton();
	button->Highlight(hdc, button->GetHighlightColor());
}


void UserMenu::DeHiglightButton(HDC hdc) const {
	auto button = GetCurButton();
	button->Highlight(hdc, button->GetGolor());
}


void UserMenu::HighlightWindow(HDC hdc) const {
	auto window = GetCurWindow();
	window->Highlight(hdc, MyColor(200, 0, 0));
}


void UserMenu::DeHighlightWindow(HDC hdc) const {
	auto window = GetCurWindow();
	window->Highlight(hdc, window->GetGolor());
}


UserMenu::UserMenu(shared_ptr<MyMenu>& initMyMenu) {
	menu = initMyMenu;
}


UserMenu::UserMenu(string scriptFileName) {
	Script script(scriptFileName);
	menu = script.InitMyMenu();
}


bool UserMenu::NextWindow(HDC hdc) {
	bool overNum = 1;
	AssertNullMyMenu 0;
	DeHighlightWindow(hdc);
	DeHiglightButton(hdc);
	if (iCurMyWindow + 1 == menu->GetNumWindows()) {
		overNum = 0;
		iCurMyWindow = 0;
	}
	else
		iCurMyWindow++;
	iCurMyButton = 0;
	HighlightWindow(hdc);
	HighlightButton(hdc);
	return overNum;
}


bool UserMenu::PrevWindow(HDC hdc) {
	AssertNullMyMenu 0;
	DeHighlightWindow(hdc);
	DeHiglightButton(hdc);
	if (iCurMyWindow == 0)
		iCurMyWindow = menu->GetNumWindows() - 1;
	else
		iCurMyWindow--;
	iCurMyButton = 0;
	HighlightWindow(hdc);
	HighlightButton(hdc);
	return 1;
}


bool UserMenu::NextButton(HDC hdc) {
	bool overNum = 1;
	AssertNullMyMenu 0;
	DeHiglightButton(hdc);
	if (iCurMyButton + 1 == menu->GetIthReadOnlyWindow(iCurMyWindow)->GetNumButtons()) {
		overNum = 0;
		iCurMyButton = 0;
	}
	else
		iCurMyButton++;
	HighlightButton(hdc);
	return overNum;
}


bool UserMenu::PrevButton(HDC hdc) {
	AssertNullMyMenu 0;
	DeHiglightButton(hdc);
	if (iCurMyButton == 0)
		iCurMyButton = menu->GetIthReadOnlyWindow(iCurMyWindow)->GetNumButtons() - 1;
	else
		iCurMyButton--;
	HighlightButton(hdc);
	return 1;
}


pair<string, string> UserMenu::GetIDButton() const {
	AssertNullMyMenu make_pair("", "");
	return GetCurButton()->GetFullName();
}


void UserMenu::Render(HDC hdc) const {
	HighlightWindow(hdc);
	HighlightButton(hdc);
	menu->Print(hdc);
}