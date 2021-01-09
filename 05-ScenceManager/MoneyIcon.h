#pragma once
#include "GameObject.h"
#include "Mario.h"

#define MONEY_BBOX_WIDTH  14
#define MONEY_BBOX_HEIGHT 14

#define MONEY_STATE_DIE_OVER	160

#define MONEY_GRAVITY	0.002f
class CMoneyIcon : public CGameObject
{
private:
	bool isMove;
public:
	int type;
	CMario*  mario;
	bool noMoney;						//mario da lay money
	bool isInitPos;
	CMoneyIcon(int type_ani);
	float yStatic;
	void SetMove(bool isMove);
	bool GetMove();
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	~CMoneyIcon();
};