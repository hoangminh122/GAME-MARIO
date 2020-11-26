﻿#pragma once
#include "GameObject.h"
//#include "game_map.h"

#define MARIO_WALKING_SPEED		0.1f 
#define MARIO_WALKING_ADD_SPEED	0.005f 
#define MARIO_RUN_NORMAL_SPEED	0.15f 
#define MARIO_JUMP_SPEED_Y		0.45f
#define MARIO_JUMP_SPEED_HIGHER_Y		0.1f
#define MARIO_JUMP_DEFLECT_SPEED 0.2f
#define MARIO_GRAVITY			0.002f
#define MARIO_DIE_DEFLECT_SPEED	 0.5f
#define MARIO_STATE_IDLE			0
//#define MARIO_STATE_WALKING_RIGHT	100
//#define MARIO_STATE_WALKING_LEFT	200
#define MARIO_STATE_WALKING		200
#define MARIO_STATE_JUMP_HIGH	100
#define MARIO_STATE_JUMP_NORMAL	300
#define MARIO_STATE_DIE				400
//#define MARIO_STATE_RUN_RIGHT		500
#define MARIO_STATE_RUN		600
#define MARIO_STATE_KICK		900
#define MARIO_STATE_DOWN		910
#define MARIO_STATE_HOLD_TURTLE	930
#define MARIO_STATE_BULLET_IDLE	950
//#define MARIO_STATE_BULLET_RUN	950
#define MARIO_STATE_BRAKE	960
#define MARIO_STATE_FLY		920
#define MARIO_STATE_FIRE	940
#define MARIO_STATE_ROTATORY_IDLE		700



#define MARIO_ANI_SMALL_IDLE_RIGHT		2
#define MARIO_ANI_SMALL_IDLE_LEFT			3
#define MARIO_ANI_SMALL_WALKING_RIGHT		6
#define MARIO_ANI_SMALL_WALKING_LEFT		7
#define MARIO_ANI_SMALL_JUMP_RIGHT		10
#define MARIO_ANI_SMALL_JUMP_LEFT		9
#define MARIO_ANI_SMALL_RUN_LEFT		12
#define MARIO_ANI_SMALL_RUN_RIGHT		11
#define MARIO_ANI_SMALL_BRAKE_RIGHT		63
#define MARIO_ANI_SMALL_BRAKE_LEFT		64
#define MARIO_ANI_SMALL_HOLD_TURLE_RIGHT	73
#define MARIO_ANI_SMALL_HOLD_TURLE_LEFT		74
#define MARIO_ANI_SMALL_KICK_RIGHT	75
#define MARIO_ANI_SMALL_KICK_LEFT	76


#define MARIO_ANI_BIG_IDLE_RIGHT		0
#define MARIO_ANI_BIG_IDLE_LEFT			1
#define MARIO_ANI_BIG_WALKING_RIGHT			4
#define MARIO_ANI_BIG_WALKING_LEFT			5
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
#define MARIO_ANI_BIG_FIRE_BULLET_RIGHT	49
#define MARIO_ANI_BIG_FIRE_BULLET_LEFT	50
#define MARIO_ANI_BIG_FIRE_BRAKE_RIGHT	67
#define MARIO_ANI_BIG_FIRE_BRAKE_LEFT	68
#define MARIO_ANI_BIG_FIRE_KICK_RIGHT	69
#define MARIO_ANI_BIG_FIRE_KICK_LEFT	70
#define MARIO_ANI_BIG_FIRE_HOLD_TURLE_RIGHT	71
#define MARIO_ANI_BIG_FIRE_HOLD_TURLE_LEFT	72


#define MARIO_ANI_BIG_BRAKE_RIGHT		21
#define MARIO_ANI_BIG_BRAKE_LEFT		22

#define MARIO_ANI_BIG_TAIL_IDLE_RIGHT		23
#define MARIO_ANI_BIG_TAIL_IDLE_LEFT		24
#define MARIO_ANI_BIG_TAIL_WALKING_RIGHT		25
#define MARIO_ANI_BIG_TAIL_WALKING_LEFT		26
#define MARIO_ANI_BIG_TAIL_RUN_LEFT		28
#define MARIO_ANI_BIG_TAIL_RUN_RIGHT		27
#define MARIO_ANI_BIG_TAIL_JUMP_RIGHT		30
#define MARIO_ANI_BIG_TAIL_JUMP_LEFT		29

#define MARIO_ANI_BIG_TAIL_ROTATORY_RIGHT		33
#define MARIO_ANI_BIG_TAIL_ROTATORY_LEFT		34
#define MARIO_ANI_BIG_TAIL_DOWN_RIGHT		35
#define MARIO_ANI_BIG_TAIL_DOWN_LEFT		36
#define MARIO_ANI_BIG_TAIL_FLY_RIGHT		37
#define MARIO_ANI_BIG_TAIL_FLY_LEFT		38
#define MARIO_ANI_BIG_TAIL_HOLD_TURTLE_RIGHT	51
#define MARIO_ANI_BIG_TAIL_HOLD_TURTLE_LEFT	52
//#define MARIO_ANI_BIG_TAIL_WALKING_HOLD_TURTLE_LEFT	53
//#define MARIO_ANI_BIG_TAIL_WALKING_HOLD_TURTLE_LEFT	54
//#define MARIO_ANI_BIG_TAIL_RUN_HOLD_TURTLE_LEFT	55
//#define MARIO_ANI_BIG_TAIL_RUN_HOLD_TURTLE_LEFT	56
#define MARIO_ANI_BIG_TAIL_FLY_LIMIT_RIGHT	57
#define MARIO_ANI_BIG_TAIL_FLY_LIMIT_LEFT	58
#define MARIO_ANI_BIG_TAIL_FLY_FALLING_RIGHT	59
#define MARIO_ANI_BIG_TAIL_FLY_FALLING_LEFT	60
#define MARIO_ANI_BIG_TAIL_KICK_TURLE_RIGHT	61
#define MARIO_ANI_BIG_TAIL_KICK_TURLE_LEFT	62
#define MARIO_ANI_BIG_TAIL_BRAKE_RIGHT	65
#define MARIO_ANI_BIG_TAIL_BRAKE_LEFT	66


#define MARIO_ANI_DIE				8

#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define	MARIO_LEVEL_TAIL_BIG		3
#define	MARIO_LEVEL_FIRE_BIG		4


#define MARIO_BIG_BBOX_WIDTH  15
#define MARIO_BIG_BBOX_HEIGHT 27
#define MARIO_BIG_DOWN_BBOX_HEIGHT 18
#define MARIO_BIG_KICK_WIDTH	21

#define MARIO_TAIL_BIG_BBOX_WIDTH  22
#define MARIO_TAIL_BIG_BBOX_HEIGHT 28
#define MARIO_TAIL_BIG_DOWN_BBOX_HEIGHT 18
#define MARIO_TAIL_FLY_BIG_BBOX_WIDTH   18       //23
#define MARIO_TAIL_FLY_BIG_BBOX_HEIGHT 29

#define MARIO_SMALL_BBOX_WIDTH  13  //12
#define MARIO_SMALL_BBOX_HEIGHT 15   //24

#define MARIO_JUMP_HIGHER_TIME 7000
#define MARIO_UNTOUCHABLE_TIME 5000
#define MARIO_KICK_TIME 500


class CMario : public CGameObject
{
	int untouchable;
	DWORD untouchable_start;
	float start_x;			// initial position of Mario at scene
	float start_y; 
	//GameMap* test;
	int ani;
public: 
	DWORD timeKickStart;			//time da rua
	bool pressA;				//giu phim A
	DWORD timeJumpStart;
	bool jumpHigher;			//mario jump cao hơn khi giữ S
	int static level;
	bool static isDropTurle;        //fix xu ly khi tha rua de khong bi va cham
	bool static isHoldTurtle;
	float static xx;				//gia tri static x cua mario
	float static vxx;				//gia tri static x cua mario
	float static vyy;

	float static yy;		
	int static nxx;				//check truing hop nx = 0 xem mario xoay huong nao
	int static energyFly;									//nang luong bay time 
	static bool isBullet;								//Kiem tra xem no co dang o trang thai ban dan khong khi dang chay, nhay
	static float xRealTime;
	int levelBefore;									//level truoc do
	bool isStateFly;									//trang thai dang bay tren khong

	static bool kick;            //mario da chan 
	static float positionXIdle;
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