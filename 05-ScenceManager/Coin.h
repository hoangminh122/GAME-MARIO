#pragma once
#include "GameObject.h"
#include "Mario.h"

#define COIN_BBOX_WIDTH  16
#define COIN_BBOX_HEIGHT 16

#define COIN_ANI_100 0
#define COIN_ANI_200 1
#define COIN_ANI_400 2
#define COIN_ANI_800 3
#define COIN_ANI_1000 4
#define COIN_ANI_2000 5
#define COIN_ANI_4000 6
#define COIN_ANI_8000 7
#define COIN_ANI_1VP 8



class CCOIN : public CGameObject
{
public:
	CCOIN();
	~CCOIN();

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