#pragma once
#include "GameObject.h"

#define BACKGROUND_DIE_BBOX_WIDTH 1
#define BACKGROUND_DIE_BBOX_HEIGHT 1

class CBackgroundDie : public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};