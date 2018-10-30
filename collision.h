
#ifndef _COLLISION_H
#define _COLLISION_H

#include <limits>
#include "game.h"

typedef struct {
	int x, y;
	int width, height;
	int movex, movey;
	int curframe, lastframe;
	int animdelay, animcount;
}SPRITE;

bool AABBCheck(SPRITE object, SPRITE otherObject);
SPRITE GetSweptBroadphaseBox(SPRITE object);
float SweptAABB(SPRITE sprite1, SPRITE sprite2, float &normalx, float &normaly);

#endif