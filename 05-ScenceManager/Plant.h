#pragma once
#include "GameObject.h"
#include "Mario.h"

#define PLANT_BBOX_WIDTH  15
#define PLANT_BBOX_HEIGHT 23

#define PLANT_STATE_UP 1001
#define PLANT_STATE_DOWN 1002

#define PLANT_LEVEL_HIGH 0
#define PLANT_LEVEL_MIDDLE 1
#define PLANT_LEVEL_SMALL 2

#define PLANT_ANI_PLANT_HIGH_LEFT_UP	2
#define PLANT_ANI_PLANT_HIGH_LEFT_DOWN	0
#define PLANT_ANI_PLANT_HIGH_RIGHT_UP	3
#define PLANT_ANI_PLANT_HIGH_RIGHT_DOWN	1


#define PLANT_ANI_PLANT_MIDDLE_LEFT_UP	4
#define PLANT_ANI_PLANT_MIDDLE_LEFT_DOWN	6
#define PLANT_ANI_PLANT_MIDDLE_RIGHT_UP	5
#define PLANT_ANI_PLANT_MIDDLE_RIGHT_DOWN	7

#define PLANT_ANI_PLANT_SMALL_UP	8
#define PLANT_ANI_PLANT_SMALL_DOWN	9



class CPlant : public CGameObject
{
public:
	int level;
	int ani;
	bool isInitPos;
	CMario* mario;
	static bool start;
	CPlant();
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};