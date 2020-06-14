#include "User.h"


User::User(string scriptFileName,
	int canvasHeight = 256, int canvasWidth = 512) :
	usrMenu(scriptFileName), canvas(canvasWidth, canvasHeight),
	instrument(new Brush()) {
	panelDict = {
	{"SETBRUSH", SETBRUSH},
	{"ERASE", ERASE},
	{"ELLIPSE", ELLIPSE},
	{"RECTANGLE", RECTANGLE},
	{"LINE", LINE},
	{"SETCOLOR1", SETCOLOR1},
	{"SETCOLOR2", SETCOLOR2},
	{"SETCOLOR3", SETCOLOR3},
	{"SETCOLOR4", SETCOLOR4},
	{"DEC_SIZE", DEC_SIZE},
	{"INC_SIZE", INC_SIZE},
	{"ZOOM_INT", ZOOM_IN},
	{"ZOOM_OUT", ZOOM_OUT}
	};
}


void User::Render(HDC hdc) const {
	canvas.Render(hdc);
	usrMenu.Render(hdc);
}


void User::DoOperation(HDC hdc, OPERATION op, const Vector& point = Vector()) {
	switch(op) {
		case TAP:
			if (canvas.IsCanvas(point)) {
				instrument->Draw(canvas, canvas.GetVector(point));
				canvas.Render(hdc);
			}
			break;

		case KB_ENTER:
		{
			pair<string, string> buttonID = usrMenu.GetIDButton();
			string windowName, buttonName = buttonID.first;
			string buttonName = buttonID.second;

			if (windowName == "PANEL") {
				switch (panelDict[buttonName]) {
				case SETBRUSH:
					instrument = shared_ptr<AbstractBrush>(new Brush(*instrument));
					break;

				case ERASE:
					instrument = shared_ptr<AbstractBrush>(new Eraser(*instrument));
					break;

				case ELLIPSE:
					instrument = shared_ptr<AbstractBrush>(new Ellipse(*instrument));
					break;

				case RECTANGLE:
					instrument = shared_ptr<AbstractBrush>(new Rectngle(*instrument));
					break;

				case LINE:
					instrument = shared_ptr<AbstractBrush>(new Line(*instrument));
					break;

				case SETCOLOR1:
					instrument->SetColor(MyColor(255, 0, 0));
					break;

				case SETCOLOR2:
					instrument->SetColor(MyColor(0, 255, 0));
					break;

				case SETCOLOR3:
					instrument->SetColor(MyColor(0, 0, 255));
					break;

				case SETCOLOR4:
					instrument->SetColor(MyColor());
					break;

				case DEC_SIZE:
					instrument->IncWidth(-1);
					break;

				case INC_SIZE:
					instrument->IncWidth(1);
					break;

				case ZOOM_IN:
					canvas.ZoomIn();
					canvas.Render(hdc);
					break;

				case ZOOM_OUT:
					canvas.ZoomOut();
					canvas.Render(hdc);
					break;
				}
			}
			else if (windowName == "MAIN") {
				if (buttonName == "CLEAR") {
					canvas.Clear();
				}
			}
			else if (windowName == "SAVE") {
				canvas.SaveDrawing(buttonName);
			}
			else if (windowName == "LOAD") {
				canvas.LoadDrawing(buttonName);
			}
			break;
		}

		case KB_ARR_DOWN:
			usrMenu.NextButton(hdc);
			break;

		case KB_ARR_UP:
			usrMenu.PrevButton(hdc);
			break;

		case KB_ARR_LEFT:
			usrMenu.PrevWindow(hdc);
			break;

		case KB_ARR_RIGHT:
			usrMenu.NextWindow(hdc);
			break;
	}
}