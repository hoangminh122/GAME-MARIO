#pragma once
#include "GameObject.h"


#define HAT_BBOX_HEIGHT 16
#define HAT_BBOX_WIDTH 16

class CHat : public CGameObject
{
public:
	int type;
	bool isInitPos;
	int xStatic;                  //bien luu vi tri x cho tung type brick
	CHat();
	~CHat();
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};