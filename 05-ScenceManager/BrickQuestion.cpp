#include "BrickQuestion.h"
#include "Utils.h"
#include "Coin.h"

CBrickQuestion * CBrickQuestion::_instance = NULL;
CBrickQuestion *CBrickQuestion::GetInstance(int type,int type_gift)
{
	if (_instance == NULL) _instance = new CBrickQuestion(type,type_gift);
	return _instance;
}

CBrickQuestion::CBrickQuestion(int type_ani,int type_gift):CGameObject() {
	typeGift = type_gift;
	type = type_ani;
	isInitPos = false;						//trang thai chua khoi tao gia tri
	isMove = false;
	yStatic = y;						//ban dau chua gan gia tri y cho question -> chu y de nham lan
	mario = CMario::GetInstance(0, 0);
	isDie = false;
	ani = 0;
}

void CBrickQuestion::SetMove(bool isMove) {
	this->isMove = isMove;
}

bool CBrickQuestion::GetMove() {
	return this -> isMove;
}

CBrickQuestion::~CBrickQuestion(){
	
}

void CBrickQuestion::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);
	if (y != 0 && !isInitPos)
	{
		yStatic = y;
		isInitPos = true;
	}
	else if (isMove && mario->isHasColBoxQues && !isDie)
	{
		mario->isHasColBoxQues = false;			//khong the va cham cho den khi cham dat
		vy -= BRICK_QUESTION_MOVE_VY_0_15;
		if (y < yStatic - BRICK_QUESTION_MOVE_VY_0_15)
		{
			isMove = false;
			isDie = true;
			//diem di chuyen 
			//SET SCORES MOVE
			CCOIN::xStartMove = x;
			CCOIN::yStartMove = y;
			CCOIN::isInitPosNew = true;
			CCOIN::timeWait = GetTickCount();
			//CCOIN::isMove = true;
			CCOIN::level = 100;

			//SET COINS MOVE
			CCOIN::status = 1;
		}

	}
	else
	{
		if (y < yStatic)
		{
			//y += 1.0f;
			vy = BRICK_QUESTION_MOVE_VY_0_02;
			//vy += BRICK_GRAVITY * dt;
		}
		else
		{
			vy = 0.0f;
			//y = yStatic;
		}
	}

	x += dx;
	y += dy;
}

void CBrickQuestion::Render()
{
	if (isDie)
		ani = 1;
	else if (type == 1)
		ani = BRICK_ANI_2;
	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox();
}

void CBrickQuestion::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + BRICK_QUESTION_BBOX_WIDTH;
	b = y + BRICK_QUESTION_BBOX_HEIGHT;
}

