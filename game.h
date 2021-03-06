#pragma once
#ifndef _GAME_H
#define _GAME_H

#include <d3d9.h>
#include <stdio.h>
#include <stdlib.h>

#include "MainCharacter.h"
#include "Animation.h"
#include "GameGlobal.h"
#include "dxgraphics.h"
#include "dxinput.h"
#include "collision.h"

//app title
#define APPTITLE "LF2"

//screen setup
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

//macros to read the keyboard asynchronously
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code)((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

//function prototypes
class game
{
public:
	game();
	~game();

	static int Game_Init(HWND);
	static void Game_Run(HWND);
	static void Game_End(HWND);
};
//typedef struct {
//	int x, y;
//	int width, height;
//	int movex, movey;
//	int curframe, lastframe;
//	int animdelay, animcount;
//} SPRITE;

#endif