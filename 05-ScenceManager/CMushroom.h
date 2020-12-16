#pragma once
#include "GameObject.h"

#define MUSHROOM_BBOX_WIDTH  16
#define MUSHROOM_BBOX_HEIGHT 16

#define MUSHROOM_STATE_LIVE 100
#define MUSHROOM_STATE_DIE_OVER 300
//#define LEAF_GREEN_STATE 200
//#define MONEY_STATE 300

#define MUSHROOM_ANI 0
//#define LEAF_GREEN_ANI 1
//#define MONEY_ANI 2

#define MUSHROOM_STATE_DIE 200
#define MOSHROOM_GRAVITY 0.005f

class CMushroom : public CGameObject
{

public:
	bool noMushroom;		//mushroom  chi cos duy nhat 1 con
	CMushroom();
	bool isInitPos;
	float xStatic;
	float yStatic;
	bool isMove;
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void SetState(int state);
	
};