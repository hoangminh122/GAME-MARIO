#pragma once
#include "GameObject.h"

#define BRICK_BBOX_HEIGHT 16
#define BRICK_BBOX_WIDTH 16

class CChangeRoad : public CGameObject
{
public:
	int type;
	bool isInitPos;
	CChangeRoad(int type_ani);
	~CChangeRoad();
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};