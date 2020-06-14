#include "MyWindow.h"


shared_ptr<MyButton> MyWindow::GetMutableButtonByName(string name) {
	for (auto& curButt : buttons) {
		if (curButt->GetName() == name)
			return curButt;
	}
	return nullptr;
}


void MyWindow::CreateMyButton(const MyRectangle& frame, const string& name, const MyColor& mainMyColor, const MyColor& highlight) {
	shared_ptr<MyButton> ptrMyButton(new MyButton(frame, mainMyColor, highlight, name, shared_from_this()));
	buttons.push_back(ptrMyButton);
}


shared_ptr<const MyButton> MyWindow::GetIthReadOnlyButton(int i) const {
	if (((abs(i) >= buttons.size()) && (i > 0)) || ((abs(i) - 1 >= buttons.size()) && (i < 0))) {
		return nullptr;
	}
	if (i < 0)
		i = buttons.size() + i;
	return buttons[i];
}


shared_ptr<MyButton> MyWindow::GetIthMutableButton(int i) {
	if (((abs(i) >= buttons.size()) && (i > 0)) || ((abs(i) - 1 >= buttons.size()) && (i < 0))) {
		return nullptr;
	}
	if (i < 0)
		i = buttons.size() + i;
	return buttons[i];
}


void MyWindow::Print(HDC hdc) const {
	MyRectangleWNameColor::Print(hdc);
	for (auto& button : buttons) {
		button->Print(hdc);
	}
}