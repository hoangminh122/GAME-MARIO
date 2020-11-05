#pragma once
#include "GameObject.h"

#define BULLET_BBOX_WIDTH 8
#define BULLET_BBOX_HEIGHT 8

class CBullet : public CGameObject
{
public:
	bool isStart;
	CBullet();
	static CBullet * __instance;
	static CBullet * GetInstance();
public:
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};