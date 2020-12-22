#include "MoneyIcon.h"

CMoneyIcon::CMoneyIcon() :CGameObject() {
	mario = CMario::GetInstance(0, 0);
	noMoney = true;
	isInitPos = false;						//trang thai chua khoi tao gia tri
	isMove = false;
	yStatic = y;						//ban dau chua gan gia tri y cho question -> chu y de nham lan
}

void CMoneyIcon::SetMove(bool isMove) {
	this->isMove = isMove;
}

bool CMoneyIcon::GetMove() {
	return this->isMove;
}

void CMoneyIcon::Render()
{
	animation_set->at(0)->Render(x, y);
	RenderBoundingBox();
}

CMoneyIcon::~CMoneyIcon() {

}

void CMoneyIcon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);
	
	if (y != 0 && !isInitPos)
	{
		yStatic = y;
		isInitPos = true;
	}
	
	else if (isMove && noMoney)				//vij tri money ==vi tri mario va cham
	{
		vy -= 0.55f;
		if (y < yStatic - 0.15f)
		{
			noMoney = false;
			isMove = false;
		}
	}
	else
	{
		if (y < yStatic-0.15*dt)
		{
			//y += 1.0f;
			vy = 0.15f;
			//vy += BRICK_GRAVITY * dt;
		}
		else
		{
			vy = 0;
			y = yStatic;
			if (GetState() == MONEY_STATE_DIE_OVER)
			{
				vy = 0;
				y = 600;
				vx = 0;
			}
		}
	}

	x += dx;
	y += dy;
}

void CMoneyIcon::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + MONEY_BBOX_WIDTH;
	b = y + MONEY_BBOX_HEIGHT;
}
