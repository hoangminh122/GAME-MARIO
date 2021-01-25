#pragma once
#pragma once
#include "GameObject.h"

#define BRICK_PIECE_ANI_SET	174

#define BRICK_PIECE_SIZE	10
#define BRICK_PIECE_WIDTH	16
#define BRICK_PIECE_HEIGHT	16

#define BRICK_PIECE_TYPE_0	0
#define BRICK_PIECE_TYPE_1	1
#define BRICK_PIECE_TYPE_2	2
#define BRICK_PIECE_TYPE_3	3

#define BRICK_PIECE_HIGH_SPEED_X	0.1f
#define BRICK_PIECE_LOW_SPEED_X		0.08f
#define BRICK_PIECE_HIGH_SPEED_Y	0.3f
#define BRICK_PIECE_LOW_SPEED_Y		0.15f
#define BRICK_PIECE_GRAVITY			0.001f

#define COUNT_NUM_4	4

class CBrickPiece : public CGameObject
{
	//void SetBoundingBox() {};
public:
	//bool isDead;
	//bool isDie;
	static bool isSetuped;
	static int count;
	static CBrickPiece * __instance;
	static CBrickPiece * GetInstance();
	static float xStatic;
	static float yStatic;
	int _type;
	static bool isStart;
	CBrickPiece(int type);
	virtual void Render();
	void SetState(int state);
	int GetBoundPosition(int type2);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};

