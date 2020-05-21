#pragma once

#include "framework.h"
#include <string>


using namespace std;


void InitSystem(string fileName);
int Interact(HDC hdc, HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);