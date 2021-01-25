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

#define BRICK_BBOX_WIDTH_SENCE_1_4_TURLE 80


#define BRICK_BBOX_HEIGHT_TWO	192	
#define BRICK_STATE_BREAK   1235

#define idDied1_4_ANI 6
#define BRICK_MONEY_1_1_ANI 2
#define BRICK_MONEY_1_1_DIED_ANI	3 
#define BRICK_TYPE_MONEY_10 10
#define BRICK_TYPE_MONEY_11 11
#define BRICK_TYPE_MONEY_1_4_12 35
#define BRICK_TYPE_MONEY_2 2
#define BRICK_TYPE_MONEY_3 3
#define BRICK_TYPE_MONEY_4 4
#define BRICK_TYPE_MONEY_5 5
#define BRICK_TYPE_MONEY_6 6
#define BRICK_TYPE_MONEY_7 7
#define BRICK_TYPE_MONEY_8 8
#define BRICK_TYPE_MONEY_9 9
#define BRICK_TYPE_MONEY_10 10
#define BRICK_TYPE_MONEY_11 11
#define BRICK_TYPE_MONEY_12 12
#define BRICK_TYPE_MONEY_13 13
#define BRICK_TYPE_MONEY_14 14
#define BRICK_TYPE_MONEY_14 14
#define BRICK_TYPE_MONEY_15 15
#define BRICK_TYPE_MONEY_16 16
#define BRICK_TYPE_MONEY_17 17
#define BRICK_TYPE_MONEY_18 18
#define BRICK_TYPE_MONEY_19 19
#define BRICK_WIDTH_48 19
#define BRICK_WIDTH_BIG 10000

#define BRICK_TYPE_MONEY_20 20
#define BRICK_MONEY_TYPE_7_ANI	4
#define BRICK_MONEY_TYPE_8_ANI	5



class CBrick : public CGameObject
{
public:
	bool idDied1_4;
	int ani;
	bool static moneyIcon;					//trang thai  brick chuyen thanh icon money
	int type;
	bool isInitPos;
	float xStatic;                  //bien luu vi tri x cho tung type brick
	CBrick(int type_ani);
	~CBrick();
	virtual void Render();
	void SetState(int state);
	int GetBoundPosition(int type2);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};