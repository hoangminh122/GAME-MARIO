#pragma once
#include "GameObject.h"
 
#define BULLET_MARIO_STATE_DIE 0
#define BULLET_BBOX_WIDTH 8
#define BULLET_BBOX_HEIGHT 8
#define MAX_HEIGHT_JUMP_BULLET 30

class CBulletMario : public CGameObject
{
public:
	static bool isStart;
	CBulletMario();
	static CBulletMario * __instance;
	static CBulletMario * GetInstance();
	static float x0;
	static float y0;
	float heightAfter;							//so sang co dan nhay len 1 khoang nhat dinh

public:
	static void setPosition(float x0, float y0);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};