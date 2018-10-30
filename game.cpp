#include "game.h"

#define MARGIN 50;

HRESULT result;

//characters
#define CHAR_HEIGHT 50
#define CHAR_WIDTH 40
#define CHAR_SPEED 10
SPRITE char1;
LPDIRECT3DSURFACE9 character;

//Torch
#define TORCH_HEIGHT 75
#define TORCH_WIDTH 21
SPRITE Torch;
LPDIRECT3DTEXTURE9 Torch_tex;
LPDIRECT3DSURFACE9 Torch_image[7];
LPD3DXSPRITE sprite_handler;

//Boulder
#define BOULDER_HEIGHT 30
#define BOUDLER_WIDTH 30
SPRITE Boulder;
LPDIRECT3DSURFACE9 boulder_image;

//Ball
#define BALL_RADIUS 20
#define BALL_SPEED 7
SPRITE ball;
LPDIRECT3DSURFACE9 ball_image;

//background
LPDIRECT3DSURFACE9 bg;


//timing variable
long start = GetTickCount();

//init the game
int Game_Init(HWND hWnd) {
	char s[20];
	int n;


	//init background
	bg = LoadSurface((char*) "wall.bmp", D3DCOLOR_XRGB(0, 0,0));

	character = LoadSurface((char*) "s.png", D3DCOLOR_XRGB(255,0,255));

	boulder_image = LoadSurface((char*)"boulder.png", D3DCOLOR_XRGB(255, 0, 255));

	ball_image = LoadSurface((char*)"ball.bmp", D3DCOLOR_XRGB(255, 0, 255));

	//init keyboard
	if (!Init_Keyboard(hWnd)) {
		MessageBox(hWnd, "Error initializing the keyboard", "Error", MB_OK);
		return 0;
	}

	//init mouse
	if (!Init_Mouse(hWnd)) {
		MessageBox(hWnd, "Error initializing the mouse", "Error", MB_OK);
		return 0;
	}

	//init torch anim
	for (n = 0; n <= 6; n++)
	{
		sprintf_s(s, "fire%d.bmp", n + 1);
		Torch_image[n] = LoadSurface(s, D3DCOLOR_XRGB(255, 0, 255));
		if (Torch_image == NULL)
			return 0;
	}
	//init torch properties
	Torch.x = 770;
	Torch.y = 110;
	Torch.height = TORCH_HEIGHT;
	Torch.width = TORCH_WIDTH;
	Torch.curframe = 0;
	Torch.lastframe = 6;
	Torch.animdelay = 3;
	Torch.animcount = 0;
	Torch.movex = 0;
	Torch.movey = 0;

	//int character
	char1.x = MARGIN;
	char1.y = SCREEN_HEIGHT / 2;
	char1.height = CHAR_HEIGHT;
	char1.width = CHAR_WIDTH;
	char1.movex = CHAR_SPEED;
	char1.movey = CHAR_SPEED;

	//init boulder
	Boulder.x = SCREEN_WIDTH /2;
	Boulder.y =500;
	Boulder.height = BOULDER_HEIGHT;
	Boulder.width = BOUDLER_WIDTH;

	

	//init sound
	/*sound = LoadSound("Counting.wav");
	if (sound == NULL)
		return 0;
*/

//return okay
	return 1;
}

//the main game loop
void Game_Run(HWND hWnd) {
	//make sure the Direct3D device is valid
	if (d3ddev == NULL) {
		return;
	}

	//update mouse & keyboard
	Poll_Mouse();
	Poll_Keyboard();

	//---UPDATE PER FRAME---
	//after short delay, ready for next frame?
	//this keeps the game running at a steady frame rate
	if (GetTickCount() - start >= 10) {
		//reset timing
		start = GetTickCount();

		//INSERT CODE DOWN HERE

		//move character
		if ( Key_Down(DIK_U)) {
			char1.y -= CHAR_SPEED;
		}
		if (Key_Down(DIK_J)) {
			char1.y += CHAR_SPEED;
		}
		if (Key_Down(DIK_H)) {
			char1.x -= CHAR_SPEED;
		}
		if (Key_Down(DIK_K)) {
			char1.x += CHAR_SPEED;
		}

		//keep char inside the screen
		if (char1.y < (SCREEN_HEIGHT -150))
		{
			char1.y = SCREEN_HEIGHT - 150;
		}
		else if (char1.y > SCREEN_HEIGHT - char1.height)
		{
			char1.y = SCREEN_HEIGHT - char1.height;
		}
		if (char1.x < 0)
		{
			char1.x = 0;
		}
		else if (char1.x > SCREEN_WIDTH - char1.width)
		{
			char1.x = SCREEN_WIDTH - char1.width;
		}

		//keep boulder inside the screen
		if (Boulder.y < (SCREEN_HEIGHT - 150))
		{
			Boulder.y = SCREEN_HEIGHT - 150;
		}
		else if (Boulder.y > SCREEN_HEIGHT - Boulder.height)
		{
			Boulder.y = SCREEN_HEIGHT - Boulder.height;
		}
		if (Boulder.x < 0)
		{
			Boulder.x = 0;
		}
		else if (Boulder.x > SCREEN_WIDTH - Boulder.width)
		{
			Boulder.x = SCREEN_WIDTH - Boulder.width;
		}

		//Speed of the anim
		Torch.animcount++;
		if (Torch.animcount > Torch.animdelay)
		{
			Torch.animcount = 0;
			Torch.curframe++;
			if (Torch.curframe > Torch.lastframe)
			{
				Torch.curframe = 0;
			}
		}		

	
		LPCSTR str;
		SPRITE broadphaseBox = GetSweptBroadphaseBox(char1);

		//dùng broadphase
		if (AABBCheck(broadphaseBox, Boulder)) {
			float normalxBoulder, normalyBoulder; //vector pháp tuyến trên bề mặt paddle (hướng va chạm)
			float collisionTimeBoulder = SweptAABB(char1, Boulder, normalxBoulder, normalyBoulder);
			/*ball.x += ball.movex * collisionTime;
			ball.y += ball.movey * collisionTime;
			float remainingTime = 1.0f - collisionTime;*/
			if (collisionTimeBoulder < 1.0f) {
				if (normalxBoulder == 1.0f) //right
				{
					Boulder.x -= CHAR_SPEED;
					MessageBox(hWnd, "right","Debug",MB_OK);
				}
				if (normalxBoulder < -0.01f) //left
				{
					Boulder.x += CHAR_SPEED; 
					MessageBox(hWnd,"left", "Debug", MB_OK);
					
				}
				if (normalyBoulder > 0.01f) //bottom
				{
					Boulder.y -= CHAR_SPEED;
					MessageBox(hWnd, "Bottom", "Debug", MB_OK);
				}
				if (normalyBoulder < -0.01f) // up
				{
					Boulder.y += CHAR_SPEED;
					//MessageBox(hWnd, "Up", "Debug", MB_OK);
				}
			}
		}

	

		//----
	}
	//-----------------------

	//START RENDERING
	if (d3ddev->BeginScene()) {
		//clear the entire background
		d3ddev->ColorFill(backbuffer, NULL, D3DCOLOR_XRGB(0, 0, 0));
		/*d3ddev->StretchRect(back, NULL, backbuffer, NULL, D3DTEXF_NONE);*/


		/*d3ddev->ColorFill(character, NULL, D3DCOLOR_XRGB(255, 0, 255));*/

		RECT char1Rect;
		char1Rect.left = char1.x;
		char1Rect.top = char1.y;
		char1Rect.right = char1.x + char1.width;
		char1Rect.bottom = char1.y + char1.height;

		RECT TorchRect;
		TorchRect.left = Torch.x;
		TorchRect.top = Torch.y;
		TorchRect.right = Torch.x + Torch.width;
		TorchRect.bottom = Torch.y + Torch.height;

		RECT BoulderRect;
		BoulderRect.left = Boulder.x;
		BoulderRect.top = Boulder.y;
		BoulderRect.right = Boulder.x + Boulder.width;
		BoulderRect.bottom = Boulder.y + Boulder.height;


	
		//drawing background
		RECT bgRect;
		bgRect.left = 0;
		bgRect.top = 0;
		bgRect.right = SCREEN_WIDTH;
		bgRect.bottom = SCREEN_HEIGHT;

		//draw the paddle sprite to back buffer
		d3ddev->StretchRect(bg, NULL, backbuffer, &bgRect, D3DTEXF_NONE);
		d3ddev->StretchRect(character, NULL, backbuffer, &char1Rect, D3DTEXF_NONE);
		d3ddev->StretchRect(boulder_image, NULL, backbuffer, &BoulderRect, D3DTEXF_NONE);
		d3ddev->StretchRect(Torch_image[Torch.curframe], NULL, backbuffer, &TorchRect, D3DTEXF_NONE);


		//stop rendering
		d3ddev->EndScene();
	}

	//display the back buffer on the screen
	d3ddev->Present(NULL, NULL, NULL, NULL);

	//check for escape key (to exit program)
	if (KEY_DOWN(VK_ESCAPE)) {
		PostMessage(hWnd, WM_DESTROY, 0, 0);
	}

	/*if (KEY_DOWN(VK_SPACE))
	{
		PlaySound(sound);
	}
	if (KEY_DOWN(VK_RETURN))
	{
		StopSound(sound);
	}*/
}

void Game_End(HWND hWnd) {
	int n;
	
	bg->Release();
	character->Release();
	for (n = 0; n <= 6; n++)
	{
		Torch_image[n]->Release();
	}
	boulder_image->Release();
}