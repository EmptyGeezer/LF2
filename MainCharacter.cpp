#include "MainCharacter.h"



MainCharacter::MainCharacter(int _x, int _y)
{
	x = _x;
	y = _y;
	tag = (char*)"main";
	anim = new Animation(75, 0, 6, ANIM_DELAY + 10);

	char s[50];
	for (int i = 0; i < 75; i++) {
		sprintf_s(s, "sprites/fire%d.png", i);
		anim->sprite[i] = new Sprite(s);
	}
}


MainCharacter::~MainCharacter()
{
}

void MainCharacter::SetCamera(Camera * newCamera)
{
	this->camera = newCamera;
}

void MainCharacter::Render() 
{
	D3DXVECTOR2 translation = D3DXVECTOR2(x + movex * dirRight, y + movey);
	D3DXVECTOR2 translate = D3DXVECTOR2(GameGlobal::wndWidth / 2 - GameGlobal::camera->position.x, GameGlobal::wndHeight / 2 - GameGlobal::camera->position.y);
	D3DXVECTOR2 combined = translation + translate;

	D3DXVECTOR2 scale = D3DXVECTOR2(1 * dirRight, 1);
	//center = D3DXVECTOR3(width / 2, height / 2, 0);
	D3DXMatrixTransformation2D(&matrix, NULL, 0, &scale, NULL,
		NULL, &combined);

	MObject::Update();
	MObject::Render();
}