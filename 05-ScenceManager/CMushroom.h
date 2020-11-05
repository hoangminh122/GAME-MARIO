#pragma once
#include "GameObject.h"

#define MUSHROOM_BBOX_WIDTH  17
#define MUSHROOM_BBOX_HEIGHT 17

class CMushroom : public CGameObject
{

public:
	CMushroom();
	static bool isStart;
	static bool isRun;
	bool isDie;
	static CMushroom * __instance;
	static CMushroom * GetInstance();
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};