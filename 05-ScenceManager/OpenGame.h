#pragma once
#include "GameObject.h"


#define OPEN_GAME_BBOX_HEIGHT 100
#define OPEN_GAME_BBOX_WIDTH 100

class COpenGame : public CGameObject
{
public:
	bool isInitPos;
	int type;
	COpenGame();
	~COpenGame();
	static COpenGame * __instance;
	static COpenGame * GetInstance();
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};