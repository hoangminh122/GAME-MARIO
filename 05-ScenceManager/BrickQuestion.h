#pragma once
#include "GameObject.h"
#include "Mario.h"

#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16

#define  BRICK_ANI_DIE	1
#define BRICK_GRAVITY	0.002f
class CBrickQuestion : public CGameObject
{
private :
	bool isMove;
public:
	int ani;
	CMario*  mario;
	bool isInitPos;							//khoi tao gia tri ban dau y -> luu vao yStatic
	CBrickQuestion();
	float yStatic;
	void SetMove(bool isMove);
	bool GetMove();
	bool isDie;						//trang thai box da co su va cham 1 lan->chet
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	~CBrickQuestion();
};