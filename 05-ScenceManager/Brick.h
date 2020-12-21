#pragma once
#include "GameObject.h"

#define BRICK_BBOX_WIDTH_ONE  624
#define BRICK_BBOX_WIDTH_TWO  464
#define BRICK_BBOX_WIDTH_THREE  352
#define BRICK_BBOX_WIDTH_FOUR  80
#define BRICK_BBOX_WIDTH_FIRE  576
#define BRICK_BBOX_WIDTH_SIX  560
#define BRICK_BBOX_WIDTH_COLUMN  32
#define BRICK_BBOX_HEIGHT_COLUMN 48
#define BRICK_BBOX_HEIGHT_COLUMN_SMALL  32
#define BRICK_BBOX_HEIGHT_COLUMN_HIGH  208
#define BRICK_BBOX_HEIGHT 16
#define BRICK_BBOX_WIDTH 16

class CBrick : public CGameObject
{
public:
	bool static moneyIcon;					//trang thai  brick chuyen thanh icon money
	int type;
	bool isInitPos;
	int xStatic;                  //bien luu vi tri x cho tung type brick
	CBrick(int type_ani);
	~CBrick();
	virtual void Render();
	int GetBoundPosition(int type2);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};