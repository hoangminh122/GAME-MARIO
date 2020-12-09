#include "Coin.h"
#include "Utils.h"

bool CCOIN::isMove = false;
bool CCOIN::isInitPosNew = false;
float CCOIN::xStartMove = 0;
float CCOIN::yStartMove = 0;

CCOIN::CCOIN()
{
	yStatic = 0;
	//isMove = false;
	//isInitPos = false;
}

void CCOIN::Render()
{
	animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}

void CCOIN::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);

	if (isInitPosNew)
	{
		DebugOut(L"11111111sahdsghdg00000000\n");
		yStatic = yStartMove;
		y = yStartMove;
		x = xStartMove;
		isInitPosNew = false;
	}
	else if (isMove)
	{
		DebugOut(L"0000000sahdsghdg00000000\n");
		vy -= 0.55f;
		if (y < yStatic - 0.15f)
		{
			isMove = false;
		}
	}
	else
	{
		if (y < yStatic - 0.15*dt)
		{
			
			//y += 1.0f;
			vy = 0.15f;
			//vy += BRICK_GRAVITY * dt;
		}
		else
		{
			vy = 0;
			y = 600;
		}
	}

	x += dx;
	y += dy;
}


void CCOIN::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	/*l = x;
	t = y;
	r = x + COIN_BBOX_WIDTH;
	b = y + COIN_BBOX_HEIGHT;*/
}
