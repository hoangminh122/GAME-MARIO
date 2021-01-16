#pragma once
#include "GameObject.h"


#define TEXT_END_GAME_BBOX_HEIGHT 30
#define TEXT_END_GAME_BBOX_WIDTH 50

class CTextEndGame : public CGameObject
{
public:
	static bool isShow;
	bool isInitPos;
	int type;
	CTextEndGame();
	~CTextEndGame();
	static CTextEndGame * __instance;
	static CTextEndGame * GetInstance();
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};