#pragma once
#include "GameObject.h"
#include "Mario.h"
#define COL_BBOX_WIDTH  5
#define COL_BBOX_HEIGHT 5

#define COL_STATE_DIE 904

#define COL_ATTACK_TIME 200
class CCOL : public CGameObject
{
public:
	DWORD timeAttack;
	bool isAttack;
	int label;									//phan biet cac vien dan voi nhau
	bool isStart;
	CCOL();
	CMario* mario;
	int isInitPos;
	static CCOL * __instance;
	static CCOL * GetInstance();
public:
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};