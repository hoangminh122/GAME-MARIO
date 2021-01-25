#pragma once
#include "GameObject.h"

#define MUSHROOM_BBOX_WIDTH  17
#define MUSHROOM_BBOX_HEIGHT 17

#define MUSHROOM_BBOX_VY_0_095 0.095f
#define MUSHROOM_BBOX_VX_0_1 0.1f
#define MUSHROOM_BBOX_VX_0_03 0.03f
#define MUSHROOM_BBOX_VX_0_05 0.05f
#define MUSHROOM_BBOX_VY_0_02 0.02f

#define MUSHROOM_STATE_LIVE 100
#define MUSHROOM_STATE_DIE_OVER 300
//#define LEAF_GREEN_STATE 200
//#define MONEY_STATE 300

#define MUSHROOM_ANI_GREEN 0
#define MUSHROOM_ANI_RED 1
//#define MONEY_ANI 2

#define MUSHROOM_STATE_DIE 200
#define MOSHROOM_GRAVITY 0.005f

#define MUSHROOM_TYPE_1 1
#define MUSHROOM_TYPE_2 2

class CMushroom : public CGameObject
{

public:
	static CMushroom* _instance;
	static CMushroom* GetInstance(int type);
	CMushroom(int type_ani);
	int type;
	int ani;
	bool noMushroom;		//mushroom  chi cos duy nhat 1 con
	bool isInitPos;
	float xStatic;
	float yStatic;
	bool isMove;
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void SetState(int state);
	
};