#pragma once
#include "GameObject.h"
//#include "game_map.h"

#define MARIO_WALKING_SPEED		0.1f 
//0.1f
#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_DEFLECT_SPEED 0.2f
#define MARIO_GRAVITY			0.002f
#define MARIO_DIE_DEFLECT_SPEED	 0.5f

#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200
#define MARIO_STATE_JUMP			300
#define MARIO_STATE_DIE				400
#define MARIO_STATE_RUN_RIGHT		500
#define MARIO_STATE_RUN_LEFT		600
#define MARIO_STATE_KICK		900
#define MARIO_STATE_DOWN		910
#define MARIO_STATE_HOLD_TURTLE	930

#define MARIO_STATE_FLY		920

#define MARIO_STATE_FIRE	940

#define MARIO_STATE_ROTATORY_IDLE		700


#define MARIO_ANI_BIG_IDLE_RIGHT		0
#define MARIO_ANI_BIG_IDLE_LEFT			1
#define MARIO_ANI_SMALL_IDLE_RIGHT		2
#define MARIO_ANI_SMALL_IDLE_LEFT			3

#define MARIO_ANI_BIG_WALKING_RIGHT			4
#define MARIO_ANI_BIG_WALKING_LEFT			5
#define MARIO_ANI_SMALL_WALKING_RIGHT		6
#define MARIO_ANI_SMALL_WALKING_LEFT		7
#define MARIO_ANI_SMALL_JUMP_RIGHT		10

#define MARIO_ANI_SMALL_JUMP_LEFT		9
#define MARIO_ANI_SMALL_RUN_LEFT		12
#define MARIO_ANI_SMALL_RUN_RIGHT		11
#define MARIO_ANI_CHANGE_BIG_LEFT		13
#define MARIO_ANI_CHANGE_BIG_RIGHT		14
#define MARIO_ANI_BIG_JUMP_RIGHT		15
#define MARIO_ANI_BIG_JUMP_LEFT		16
#define MARIO_ANI_BIG_RUN_RIGHT		17
#define MARIO_ANI_BIG_RUN_LEFT		18
#define MARIO_ANI_BIG_DOWN_RIGHT		31
#define MARIO_ANI_BIG_DOWN_LEFT		32

#define MARIO_ANI_BIG_KICK_LEFT		20
#define MARIO_ANI_BIG_KICK_RIGHT		19
#define MARIO_ANI_BIG_HOLD_TURTLE_RIGHT		39
#define MARIO_ANI_BIG_HOLD_TURTLE_LEFT		40

#define MARIO_ANI_BIG_FIRE_RIGHT	41
#define MARIO_ANI_BIG_FIRE_LEFT	42
#define MARIO_ANI_BIG_FIRE_WALKING_RIGHT	43
#define MARIO_ANI_BIG_FIRE_WALKING_LEFT	44
#define MARIO_ANI_BIG_FIRE_RUN_RIGHT	45
#define MARIO_ANI_BIG_FIRE_RUN_LEFT	46
#define MARIO_ANI_BIG_FIRE_JUMP_RIGHT	47
#define MARIO_ANI_BIG_FIRE_JUMP_LEFT	48

#define MARIO_ANI_BIG_ONE_LEFT		21
#define MARIO_ANI_BIG_ONE_RIGHT		22

#define MARIO_ANI_BIG_TAIL_IDLE_RIGHT		23
#define MARIO_ANI_BIG_TAIL_IDLE_LEFT		24
#define MARIO_ANI_BIG_TAIL_WALKING_RIGHT		25
#define MARIO_ANI_BIG_TAIL_WALKING_LEFT		26
#define MARIO_ANI_BIG_TAIL_RUN_LEFT		27
#define MARIO_ANI_BIG_TAIL_RUN_RIGHT		28
#define MARIO_ANI_BIG_TAIL_JUMP_RIGHT		30
#define MARIO_ANI_BIG_TAIL_JUMP_LEFT		29

#define MARIO_ANI_BIG_TAIL_ROTATORY_RIGHT		33
#define MARIO_ANI_BIG_TAIL_ROTATORY_LEFT		34
#define MARIO_ANI_BIG_TAIL_DOWN_RIGHT		35
#define MARIO_ANI_BIG_TAIL_DOWN_LEFT		36
#define MARIO_ANI_BIG_TAIL_FLY_RIGHT		37
#define MARIO_ANI_BIG_TAIL_FLY_LEFT		38


#define MARIO_ANI_DIE				8

#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define	MARIO_LEVEL_TAIL_BIG		3
#define	MARIO_LEVEL_FIRE_BIG		4


#define MARIO_BIG_BBOX_WIDTH  15
#define MARIO_BIG_BBOX_HEIGHT 27
#define MARIO_BIG_DOWN_BBOX_HEIGHT 18

#define MARIO_TAIL_BIG_BBOX_WIDTH  21
#define MARIO_TAIL_BIG_BBOX_HEIGHT 28
#define MARIO_TAIL_BIG_DOWN_BBOX_HEIGHT 18
#define MARIO_TAIL_FLY_BIG_BBOX_WIDTH  23
#define MARIO_TAIL_FLY_BIG_BBOX_HEIGHT 29

#define MARIO_SMALL_BBOX_WIDTH  13  //12
#define MARIO_SMALL_BBOX_HEIGHT 15   //24

#define MARIO_UNTOUCHABLE_TIME 5000


class CMario : public CGameObject
{
	int level;
	int untouchable;
	DWORD untouchable_start;
	float start_x;			// initial position of Mario at scene
	float start_y; 
	//GameMap* test;
	int ani;
public: 
	int levelBefore;

	static bool kick;            //mario da chan 
	static int positionXIdle;
	static bool isRotatory;
	bool checkMarioColision;
	static bool isFire;
public: 
	CMario(float x = 0.0f, float y = 0.0f);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();

	void SetState(int state);
	void SetLevel(int l) { level = l; }
	int GetLevel() { return level; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	void Reset();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};