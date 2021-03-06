#pragma once
#include "GameObject.h"

#define BRICK_BBOX_HEIGHT 10
#define BRICK_BBOX_WIDTH 10

class CChangeRoad : public CGameObject
{
public:
	bool isLive;
	int type;
	int left;
	int right;
	int top;
	int bottom;
	int sceneNext;
	bool isInitPos;
	CChangeRoad(int type_ani,int l,int t, int r,int b,int _sceneNext);
	~CChangeRoad();
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};