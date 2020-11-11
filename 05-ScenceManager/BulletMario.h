#pragma once
#include "GameObject.h"

#define BULLET_BBOX_WIDTH 8
#define BULLET_BBOX_HEIGHT 8

class CBulletMario : public CGameObject
{
public:
	bool isStart;
	CBulletMario();
	static CBulletMario * __instance;
	static CBulletMario * GetInstance();
public:
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};