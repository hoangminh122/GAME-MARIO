#pragma once
#include "GameObject.h"

#define EFFECT_BBOX_HEIGHT 15
#define EFFECT_BBOX_WIDTH 23

class CEffect : public CGameObject
{
public:
	int type;
	int ani;
	CEffect(int type_ani);
	~CEffect();
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};