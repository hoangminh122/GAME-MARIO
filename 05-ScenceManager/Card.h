#pragma once
#include "GameObject.h"

#define CARD_BBOX_HEIGHT 27
#define CARD_BBOX_WIDTH 22

class CCard : public CGameObject
{
public:
	CCard();
	~CCard();
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};