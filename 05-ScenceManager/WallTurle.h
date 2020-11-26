#pragma once
#include "GameObject.h"

#define WALL_TURLE_BBOX_WIDTH  3
#define WALL_TURLE_BBOX_HEIGHT 16

class CWallTurle : public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};