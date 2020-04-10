#include "MyMenu.h"


shared_ptr<MyWindow> const MyMenu::GetMutableWindowByName(string name) {
	for (auto& curWnd : windows) {
		if (curWnd->GetName() == name)
			return curWnd;
	}
	return nullptr;
}


void MyMenu::CreateMyWindow(const MyRectangle& frame, const string& name, const MyColor& color) {
	shared_ptr<MyWindow> ptrMyWindow(new MyWindow(frame, color, name, shared_from_this()));
	windows.push_back(ptrMyWindow);
}


shared_ptr<const MyWindow> const MyMenu::GetIthReadOnlyWindow(int i) const {
	if (((abs(i) >= windows.size()) && (i > 0)) || ((abs(i) - 1 >= windows.size()) && (i < 0))) {
		return nullptr;
	}
	if (i < 0)
		i = windows.size() + i;
	return windows[i];
}


shared_ptr<MyWindow> const MyMenu::GetIthMutableWindow(int i) {
	if (((abs(i) >= windows.size()) && (i > 0)) || ((abs(i) - 1 >= windows.size()) && (i < 0))) {
		return nullptr;
	}
	if (i < 0)
		i = windows.size() + i;
	return windows[i];
}


bool MyMenu::SetButtonFunc(void (*funcToSet)(), string nameMyWindow, string nameMyButton) {
	auto wnd = GetMutableWindowByName(nameMyWindow);
	if (wnd != nullptr) {
		auto butt = wnd->GetMutableButtonByName(nameMyButton);
		if (butt != nullptr) {
			butt->SetFuncToDo(funcToSet);
			return 1;
		}
		return 0;
	}
	return 0;
}