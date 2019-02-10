#pragma once

#include <dinput.h>

class dxinput
{
public:
	dxinput();
	~dxinput();

	static int Init_DirectInput(HWND);

	static int InitKeyboard(HWND);
	static void PollKeyboard();
	static int KeyDown(int);
	static void KillKeyboard();

	static int InitMouse(HWND);
	static void PollMouse();
	static int MouseButton(int);
	static int Mouse_X();
	static int Mouse_Y();
	static void KillMouse();
};