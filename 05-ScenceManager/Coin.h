#pragma once
#include "GameObject.h"

#define COIN_BBOX_WIDTH  16
#define COIN_BBOX_HEIGHT 16

class CCOIN : public CGameObject
{
public:
	CCOIN();
	~CCOIN();
	static float xStartMove;					//set lai vi tri ban dau cho coin
	static float yStartMove;
	static bool isMove;
	static bool isInitPosNew;
	float yStatic;

	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};