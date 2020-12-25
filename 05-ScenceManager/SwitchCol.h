#pragma once
#include "GameObject.h"

#define SWITCH_COL_BBOX_HEIGHT 16
#define SWITCH_COL_BBOX_WIDTH 32


class CSwitchCol : public CGameObject
{
public:
	int type;
	CSwitchCol(int type_ani);
	~CSwitchCol();
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};