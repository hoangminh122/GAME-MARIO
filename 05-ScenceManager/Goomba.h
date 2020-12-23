#pragma once
#include "GameObject.h"
#include "Mario.h"

#define GOOMBA_WALKING_SPEED 0.05f;


#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 14
#define GOOMBA_RED_HIGH_BBOX_WIDTH 20
#define GOOMBA_RED_HIGH_BBOX_HEIGHT 25
#define GOOMBA_RED_SMALL_BBOX_WIDTH 20
#define GOOMBA_RED_BBOX_HEIGHT 15
#define GOOMBA_BBOX_HEIGHT_DIE 9

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200
#define GOOMBA_STATE_STOP 201
#define GOOMBA_STATE_REVERSE_DIE 300

#define	GOOMBA_LEVEL_NOMAL	1
#define	GOOMBA_LEVEL_RED_HIGH		3
#define	GOOMBA_LEVEL_RED		2

#define GOOMBA_ANI_WALKING 0
#define GOOMBA_ANI_DIE 1
#define GOOMBA_ANI_RED_HIGH_WALKING 2
#define GOOMBA_ANI_RED_SMALL_WALKING 3
#define GOOMBA_ANI_RED_WALKING 4
#define GOOMBA_ANI_RED_DIE 5
//#define GOOMBA_ANI_REVERSE_DIE 2

#define GOOMBA_GRAVITY	0.001f

class CGoomba : public CGameObject
{
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
private:
	int footstep;				//so buoc chan
	int level;
	bool isInitPos;
	float yStatic;
	float xStatic;
	DWORD timePrepareFly;
	bool isFly;
public: 
	int nxx;				//chieu di chuyen goomba
	int ani;
	int GetLevel() { return level; };
	void SetLevel(int l) { level = l; }
	CMario*  mario;
	bool isReverse;						//xoay 180
	CGoomba();
	virtual void SetState(int state);
};