#pragma once

#include "GameObject.h"
#include "Mario.h"

#define TURLE_WALKING_SPEED 0.01f;
#define TURLE_RUN_SPEED 0.2f;

#define TURLE_BBOX_WIDTH 16
#define TURLE_BBOX_HEIGHT 26
#define TURLE_BBOX_HEIGHT_DIE 15

#define TURLE_STATE_WALKING 100
#define TURLE_STATE_DIE 200
#define TURLE_STATE_STOP	201
#define TURLE_STATE_RUN_DIE 300
#define TURLE_STATE_DIE_OVER 400
#define TURLE_STATE_REVERSE_DIE	500
#define TURLE_STATE_FLY	600


#define TURLE_ANI_WALKING_LEFT 0
#define TURLE_ANI_WALKING_RIGHT 1
#define TURLE_ANI_DIE 2
#define TURLE_ANI_RUN_DIE 3
#define TURLE_ANI_FLY 4
#define TURLE_ANI_RED_WALKING_LEFT 5
#define TURLE_ANI_RED_WALKING_RIGHT 8
#define TURLE_ANI_RED_DIE 7
#define TURLE_ANI_RED_RUN_DIE 6



#define MAX_TURLE_TIME_RUN	3000
#define TURLE_TIME_DIE	10000

#define TURLE_LEVEL_SMALL 1
#define TURLE_LEVEL_NO_FLY 2
#define TURLE_LEVEL_FLY 3

#define TURLE_COLOR_GREEN 1
#define TURLE_COLOR_RED 2
#define TURLE_COLOR_GREEN_NO_FLY 3

#define TURLE_JUMP_DEFLECT_SPEED 0.2f
#define TURLE_GRAVITY 0.002f
#define TURLE_GRAVITY_SLOW 0.0003f

class CTurle : public CGameObject
{
	
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();

public:
	int nxx;                     //xac ding chieu 
	CTurle(int type_ani);
	int type;
	int untouchable;
	 DWORD timeStart;			//rua bat dau nhay cach nhau 1s
	 DWORD constTimeStart;
	int color;
	bool isInitPos;
	int level;
	bool isReverse;				//Trang thai reverse
	DWORD timeDieTurle;			//time gian mario song lai tu die->walking
	bool checkCollision;		//kiem tra va cham cua rua voi mat dat, ..
	CMario* mario;				//tao instance mario
	DWORD timeRunTurle;						//max time gian chay cuar rua
	bool isNoCollision;								// bo qua su va cham neu can
	bool isHold;										//TRANG thai cam rua cho tung con phan biet
	float vxx;											//van toc rua 
	int ani;
	int isStop;
	static bool isTreeStart;
	CTurle();
	virtual void SetState(int state);
};