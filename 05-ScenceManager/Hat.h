#pragma once
#include "GameObject.h"


#define HAT_BBOX_HEIGHT 16
#define HAT_BBOX_DIE_HEIGHT 5
#define HAT_BBOX_WIDTH 16

class CHat : public CGameObject
{
public:
	bool noColision;		//ko va cham nua
	bool isDie;			//trang thai chet
	int type;
	bool isInitPos;
	int xStatic;                  //bien luu vi tri x cho tung type brick
	CHat();
	~CHat();
	static CHat * __instance;
	static CHat * GetInstance();
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};