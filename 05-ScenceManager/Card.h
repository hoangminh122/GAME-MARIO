#pragma once
#include "GameObject.h"

#define CARD_BBOX_HEIGHT 27
#define CARD_BBOX_WIDTH 22
#define CARD_BBOX_POS_X_2764 2764.0f
#define CARD_BBOX_POS_X_285   285.0f



class CCard : public CGameObject
{
public:
	static bool isDie;
	int ani;
	CCard();
	~CCard();
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};