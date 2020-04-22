#include "interact.h"

#include "MyMenu.h"
#include "Script.h"
#include "User.h"
#include <memory>


User user;


bool DrawRectWNameColor(shared_ptr<const MyRectangleWNameColor> object, HDC hdc);
bool DrawHighlightFrame(shared_ptr<const MyRectangleWNameColor> object, MyColor clr, HDC hdc);


void InitSystem(string fileName) {
	Script script(fileName);
	shared_ptr<MyMenu> menu = script.InitMyMenu();
	//here you can set void func(void) on buttons using
	//menu->SetButtonFunc()
	user = User(menu);
	int k = 0;
}


int Interact(HDC hdc, HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    HBRUSH Brush;
    HGDIOBJ hOldBrush;
    PAINTSTRUCT ps;

    static int flagStart = 0;


    switch (message) {
    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case VK_RETURN:
            if (!flagStart) {
                flagStart = 1;
                DrawHighlightFrame(user.GetCurButton(), user.GetCurButton()->GetHighlightColor(), hdc);
                return 0;
            }
            user.GetCurButton()->DoFunc();
            break;
        case VK_LEFT:
            if (flagStart) {
                DrawHighlightFrame(user.GetCurButton(), MyColor(0, 0, 0), hdc);
                user.PrevWindow();
                DrawHighlightFrame(user.GetCurButton(), user.GetCurButton()->GetHighlightColor(), hdc);
            }
            break;

        case VK_RIGHT:
            if (flagStart) {
                DrawHighlightFrame(user.GetCurButton(), MyColor(0, 0, 0), hdc);
                user.NextWindow();
                DrawHighlightFrame(user.GetCurButton(), user.GetCurButton()->GetHighlightColor(), hdc);
            }
            break;

        case VK_UP:
            if (flagStart) {
                DrawHighlightFrame(user.GetCurButton(), MyColor(0, 0, 0), hdc);
                user.PrevButton();
                DrawHighlightFrame(user.GetCurButton(), user.GetCurButton()->GetHighlightColor(), hdc);
            }
            break;

        case VK_DOWN:
            if (flagStart) {
                DrawHighlightFrame(user.GetCurButton(), MyColor(0, 0, 0), hdc);
                user.NextButton();
                DrawHighlightFrame(user.GetCurButton(), user.GetCurButton()->GetHighlightColor(), hdc);
            }
            break;
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        DrawRectWNameColor(user.GetMenu(), hdc);
        do {
            DrawRectWNameColor(user.GetCurWindow(), hdc);
            do {
                DrawRectWNameColor(user.GetCurButton(), hdc);
            } while (user.NextButton());
        } while (user.NextWindow());
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return 0;
}


bool DrawRectWNameColor(shared_ptr<const MyRectangleWNameColor> object, HDC hdc) {
    if (object == nullptr)
        return 0;
    MyColor clr = object->GetGolor();
    MyRectangle rct = object->GetFrame();
    HBRUSH brush = CreateSolidBrush(RGB(clr.Red(), clr.Green(), clr.Blue()));
    SelectObject(hdc, brush);
    Rectangle(hdc, rct.GetLowLeft().GetX(), rct.GetLowLeft().GetY(), rct.GetUpRight().GetX(), rct.GetUpRight().GetY());
    DeleteObject(brush);
    SetBkMode(hdc, TRANSPARENT);
    TextOutA(hdc, (rct.GetLowLeft().GetX() + rct.GetUpRight().GetX() - 6*object->GetName().length()) / 2, rct.GetLowLeft().GetY(),
        object->GetName().c_str(), object->GetName().length());
    return 1;
}


bool DrawHighlightFrame(shared_ptr<const MyRectangleWNameColor> object, MyColor clr, HDC hdc) {
    MyRectangle rct = object->GetFrame();
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(clr.Red(), clr.Green(), clr.Blue()));
    SelectObject(hdc, pen);
    SelectObject(hdc, GetStockObject(NULL_BRUSH));
    Rectangle(hdc, rct.GetLowLeft().GetX(), rct.GetLowLeft().GetY(), rct.GetUpRight().GetX(), rct.GetUpRight().GetY());
    DeleteObject(pen);
    return 0;
}