#pragma once
#include <stdlib.h>
#include "MObject.h"
#include "dxinput.h"




#define STATE_IDLE 0
#define STATE_RUNNING 1
#define STATE_SHOOTING 2
#define STATE_RUNNING_N_SHOOTING 3
#define STATE_JUMPING 4
#define STATE_FALLING 5
#define STATE_DASHING 6
//#define STATE_DASHING_N_SHOOTING 7
//#define STATE_JUMPING_N_SHOOTING 8
#define STATE_WALL_SLIDING 9
#define STATE_WALL_KICKING 10
#define STATE_TAKING_DAMAGE 11
#define STATE_DYING 12
#define STATE_INTRO 13
#define ANIM_DELAY 1
#define MEGAMAN_SPEED 5
#define DASH_SPEED 13
#define DASH_DURATION 15
#define JUMP_SPEED 17
#define WALL_JUMP_SPEED 20
#define WALL_DASH_JUMP_SPEED 5
#define WALL_DASH_BOUNCE_SPEED 10
#define GRAVITY -0.25
#define KICK_ANTI_FORCE 5
#define WALL_SLIDE_SPEED -7
#define GROUND_Y 390
#define LEFTWALL_X 0
#define RIGHTWALL_X 227
#define CHARGED_SHOT_LV1_TIME 15
#define CHARGED_SHOT_LV2_TIME 40
#define SHOOTING_ANIMATION_DELAY 10
#define TAKING_DMG_ANIMATION_TIME 20
#define INVULNERABLE_TIME 50
#define HEALING_TIME 20
#define DYING_TIME 20
#define MEGAMAN_MAX_HP 16
#define HIT_GROUND_MARGIN 4
#define HIT_CEIL_MARGIN 4
#define INTRO_DESCEND_SPEED 15

class MainCharacter :
	public MObject
{
	MObject *collideObject;
public:
	MainCharacter();
	MainCharacter(int _x, int _y);
	~MainCharacter();

	void Render();
	void Update();
	//void OnCollision(MObject *otherObj, char* sideCollided);

	Camera *camera;
	void SetCamera(Camera *newCamera);
};
