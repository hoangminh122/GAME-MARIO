#pragma once
#include "GameObject.h"
#include "Mario.h"

#define COIN_BBOX_WIDTH  16
#define COIN_BBOX_HEIGHT 16

#define COIN_LEVEL_100 100
#define COIN_LEVEL_200 200
#define COIN_LEVEL_400 400
#define COIN_LEVEL_800 800
#define COIN_LEVEL_1000 1000
#define COIN_LEVEL_2000 2000
#define COIN_LEVEL_4000 4000
#define COIN_LEVEL_8000 8000
#define COIN_LEVEL_10000 10000

#define COIN_COUNT_Y 0.15f
#define COIN_COUNT_5 5

#define COIN_VY_0_05 0.05f
#define COIN_VY_15 15.0f

#define COIN_POS_Y_600 600.0f

#define COIN_ANI_100 0
#define COIN_ANI_200 1
#define COIN_ANI_400 2
#define COIN_ANI_800 3
#define COIN_ANI_1000 4
#define COIN_ANI_2000 5
#define COIN_ANI_4000 6
#define COIN_ANI_8000 7
#define COIN_ANI_1VP 8


#define COIN_WAITING 300


class CCOIN : public CGameObject
{
public:
	CCOIN();
	~CCOIN();
	static DWORD  timeWait;									//thoi gian cho den luc start
	int ani;
	CMario*  mario;
	static int status;									//trang thai tang diem hay tang coin hay time/.....
	static float xStartMove;					//set lai vi tri ban dau cho coin
	static float yStartMove;
	static bool isMove;
	static bool isInitPosNew;
	float yStatic;
	static int level;

	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};