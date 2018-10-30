#include <stdio.h>
#include "dxgraphics.h"
#include "dxinput.h"
#include "game.h"



LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_DESTROY:
		//release the Direct3D device
		if (d3ddev != NULL) {
			d3ddev->Release();
		}
		//release the Direct3D object
		if (d3d != NULL) {
			d3d->Release();
		}
		//release input objects
		Kill_Keyboard();
		Kill_Mouse();
		if (dinput != NULL) {
			dinput->Release();
		}
		//shutdown function
		Game_End(hWnd);
		//tell Windows to kill this program
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

//ham ho tro khoi dong Window Properties
ATOM MyRegisterClass(HINSTANCE hInstance) {
	//create window class structure
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	//Dien tham so ham vao struct
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "Create_Surface";
	wc.hIconSm = NULL;
	//Dang ky lop cua so
	return RegisterClassEx(&wc);
}

//Dau vao ung dung Window
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	//Dang ky lop cua so
	MyRegisterClass(hInstance);

	//Khoi dong ung dung
	//Luu y: ta da bo qua loi goi InitApplication
	HWND hWnd;
	//Tao 1 cua so
	hWnd = CreateWindow(
		"Create_Surface",	//window class
		"Create Surface",	//title bar
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,	//window style
		CW_USEDEFAULT,	//x position of window
		CW_USEDEFAULT,	//y position of window
		SCREEN_WIDTH,	//width of the window
		SCREEN_HEIGHT,	//height of the window
		NULL,	//parent window
		NULL,	//menu
		hInstance,	//application instance
		NULL	//window parameters
	);

	//Kiem tra loi neu ko tao duoc cua so
	if (!hWnd) {
		return FALSE;
	}

	//Hien thi cua so
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	if (!Init_Direct3D(hWnd, SCREEN_WIDTH, SCREEN_HEIGHT)) {
		return 0;
	}

	if (!Init_DirectInput(hWnd)) {
		MessageBox(hWnd, "Error initializing DirectInput", "Error", MB_OK);
	}

	//Khoi tao game
	if (!Game_Init(hWnd)) {
		MessageBox(hWnd, "Error initializing the game", "Error", MB_OK);
		return 0;
	}

	//Khoi tao am thanh
	/*if (!Init_DirectSound(hWnd))
	{
		MessageBox(hWnd, "Error initialize DirectSond", "Error", MB_OK);
	}*/

	//Vong lap thong diep chinh
	int done = 0;
	while (!done) {
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			//Kiem tra dieu kien thoat
			if (msg.message == WM_QUIT) {
				done = 1;
			}
			//Giai ma thong diep va chuyen lai cho WinProc
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			//xu ly game
			Game_Run(hWnd);
		}
	}

	return msg.wParam;
}