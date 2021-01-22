#pragma once
#include "GameObject.h"

#define BRICK_BBOX_WIDTH_ONE  624
#define BRICK_BBOX_WIDTH_TWO  464
#define BRICK_BBOX_WIDTH_THREE  352
#define BRICK_BBOX_WIDTH_FOUR  80
#define BRICK_BBOX_WIDTH_FIRE  574
#define BRICK_BBOX_WIDTH_SIX  560
#define BRICK_BBOX_WIDTH_COLUMN  32
#define BRICK_BBOX_HEIGHT_COLUMN 48
#define BRICK_BBOX_HEIGHT_COLUMN_SMALL  32
#define BRICK_BBOX_HEIGHT_COLUMN_HIGH  208
#define BRICK_BBOX_HEIGHT 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_WIDTH_BORDER 2000
#define BRICK_BBOX_HEIGHT_BORDER 435

#define BRICK_BBOX_HEIGHT_SENCE_1_TOP 3
#define BRICK_BBOX_WIDTH_SENCE_1_TOP 300
#define BRICK_BBOX_HEIGHT_SENCE_1_LEFT 300
#define BRICK_BBOX_WIDTH_SENCE_1_LEFT 3
#define BRICK_BBOX_WIDTH_SENCE_START_1_4 160
#define BRICK_BBOX_WIDTH_SENCE_1_4 48


#define BRICK_BBOX_HEIGHT_TWO	192	
#define BRICK_STATE_BREAK   1235


class CBrick : public CGameObject
{
public:
	bool idDied1_4;
	int ani;
	bool static moneyIcon;					//trang thai  brick chuyen thanh icon money
	int type;
	bool isInitPos;
	int xStatic;                  //bien luu vi tri x cho tung type brick
	CBrick(int type_ani);
	~CBrick();
	virtual void Render();
	void SetState(int state);
	int GetBoundPosition(int type2);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};