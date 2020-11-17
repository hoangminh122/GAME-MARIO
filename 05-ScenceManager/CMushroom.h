#pragma once
#include "GameObject.h"

#define MUSHROOM_BBOX_WIDTH  17
#define MUSHROOM_BBOX_HEIGHT 17

#define MUSHROOM_STATE 100
#define LEAF_GREEN_STATE 200
#define MONEY_STATE 300

#define MUSHROOM_ANI 0
#define LEAF_GREEN_ANI 1
#define MONEY_ANI 2

class CMushroom : public CGameObject
{

public:
	int ani;
	CMushroom();
	static bool isStart;
	static bool isRun;
	static bool isMoney;
	static float  xBox;
	static float  yBox;

	bool isDie;
	static CMushroom * __instance;
	static CMushroom * GetInstance();
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void SetState(int state);
};