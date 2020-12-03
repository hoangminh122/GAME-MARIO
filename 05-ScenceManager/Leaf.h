#pragma once
#include "GameObject.h"

#define LEAF_BBOX_WIDTH  16
#define LEAF_BBOX_HEIGHT 12

#define LEAF_STATE_LIVE 100
#define LEAF_STATE_DIE_OVER 300

#define LEAF_ANI 0

#define LEAF_STATE_DIE 200
#define LEAF_GRAVITY 0.005f

class CLeaf : public CGameObject
{

public:
	bool noMushroom;		//mushroom  chi cos duy nhat 1 con
	CLeaf();
	~CLeaf();
	bool isInitPos;
	float xStatic;
	float yStatic;
	bool isMove;
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void SetState(int state);
	
};