#pragma once
#pragma once
#include "GameObject.h"

#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_WIDTH_ORANGE_ONE  48							//type 3 o nang 16x3
#define BRICK_BBOX_WIDTH_ORANGE_TWO  64							//type 4 o nang 16x4
#define BRICK_BBOX_WIDTH_GREEN_TWO   96							//type 6 o nang 16x6
#define BRICK_BBOX_WIDTH_GREEN_ONE  80							//type 5 o nang 16x5
#define BRICK_BBOX_WIDTH_GREEN_THREE  112							//type 7 o nang 16x7

#define BRICK_BBOX_HEIGHT 16

class CBrickTop : public CGameObject
{
public:
	int type;
	CBrickTop(int type_ani);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};