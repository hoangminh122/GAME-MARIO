#pragma once
#include "GameObject.h"

#define BRICK_BBOX_WIDTH  5
#define BRICK_BBOX_HEIGHT 16

class CBackgroundDie : public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};