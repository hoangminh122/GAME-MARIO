#pragma once
#include "GameObject.h"

#define BULLET_BBOX_WIDTH  16
#define BULLET_BBOX_HEIGHT 16

class CBullet : public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};