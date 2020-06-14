#pragma once
#include "pch.h"

#include "AbstractObjects.h"
#include "Brush.h"
#include "Eraser.h"
#include "Line.h"
#include "Rectngle.h"
#include "Ellipse.h"

#include "Canvas.h"
#include "UserMenu.h"


enum OPERATION {
	TAP,
	KB_ENTER,
	KB_ARR_UP,
	KB_ARR_DOWN,
	KB_ARR_LEFT,
	KB_ARR_RIGHT
};


enum PANEL_OBJ {
	SETBRUSH,
	ERASE,
	ELLIPSE,
	RECTANGLE,
	LINE,
	SETCOLOR1,
	SETCOLOR2,
	SETCOLOR3,
	SETCOLOR4,
	DEC_SIZE,
	INC_SIZE,
	ZOOM_IN,
	ZOOM_OUT
};


class User {

	shared_ptr<AbstractBrush> instrument;
	Canvas canvas;
	UserMenu usrMenu;

	map<string, PANEL_OBJ> panelDict;


public:

	User(string scriptFileName,
		int canvasHeight = 256, int canvasWidth = 512);

	void Render(HDC hdc) const;

	void DoOperation(HDC hdc, OPERATION op, const Vector& point = Vector());
		
};