#pragma once
#include "GameObject.h"
#include "Mario.h"

#define BULLET_BBOX_WIDTH 8
#define BULLET_BBOX_HEIGHT 8

#define BULLET_STATE_DIE 123
#define BULLET_STATE_LIVE 124

#define BULLET_POSITION_X_1 1670.0f
#define BULLET_POSITION_X_430 430.0f
#define BULLET_POSITION_X_1871 1871.0f
#define BULLET_POSITION_Y_348 348.0f
#define BULLET_POSITION_Y_900 900.0f
#define BULLET_LABEL_1 1
#define BULLET_LABEL_2 2

#define BULLET_VX_0_08 0.08f
#define BULLET_VY_0_05 0.05f

#define BULLET_POSITION_X_START_1 357.0f
#define BULLET_POSITION_Y_START_1 342.0f


class CBullet : public CGameObject
{
public:
	int label;									//phan biet cac vien dan voi nhau
	bool isStart;
	CBullet();
	CMario* mario;
	int isInitPos;
	static CBullet * __instance;
	static CBullet * GetInstance();
public:
	void SetState(int state);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};