#pragma once
#include "pch.h"

typedef enum PANEL_OBJ {
	SETBRUSH,
	SETCOLOR1,
	SETCOLOR2,
	SETCOLOR3,
	SETCOLOR4,
	DEC_SIZE,
	INC_SIZE,
	ELLIPSE,
	RECTANGLE,
	LINE,
	ERASE,
	MV_RIGHT,
	MV_LEFT,
	MV_UP,
	MV_DOWN,
	ZOOM_OUT,
	ZOOM_IN
};


class UserPanel {

	vector<PANEL_OBJ> panel;
};