#include "Coin.h"
#include "Utils.h"

bool CCOIN::isMove = false;
bool CCOIN::isInitPosNew = false;
float CCOIN::xStartMove = 0;
float CCOIN::yStartMove = 0;
int CCOIN::level = 0;


CCOIN::CCOIN()
{
	mario = CMario::GetInstance(0, 0);
	yStatic = 0;
	//isMove = false;
	//isInitPos = false;
	ani = 0;
}

void CCOIN::Render()
{
	switch (level)
	{
		case 0:
			ani = COIN_ANI_100;
			break;
		case 1:
			ani = COIN_ANI_200;
			break;
		case 2:
			ani = COIN_ANI_400;
			break;
		case 3:
			ani = COIN_ANI_800;
			break;
		case 4:
			ani = COIN_ANI_1000;
			break;
		case 5:
			ani = COIN_ANI_2000;
		case 6:
			ani = COIN_ANI_4000;
			break;
		case 7:
			ani = COIN_ANI_8000;
			break;
		case 8:
			ani = COIN_ANI_1VP;
			break;
		default:
			break;
	}
	animation_set->at(ani)->Render(x, y);
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
			//tang coin tren HUD
			mario->AddScores(100);
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
