#include "Bullet.h"
#include "Plant.h"
#include "Utils.h"

//CBullet::CBullet() {
//	isStart = false;
//}

CBullet * CBullet::__instance = NULL;
CBullet::CBullet() : CGameObject()
{
	isStart = false;
	//vx = 0.8;
	mario = CMario::GetInstance(0, 0);
	isInitPos = false;
	//label = 0;
}
CBullet *CBullet::GetInstance()
{
	if (__instance == NULL) __instance = new CBullet();
	return __instance;
}
void CBullet::Render()
{
	animation_set->at(0)->Render(x, y);
	RenderBoundingBox();
}

void CBullet::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + BULLET_BBOX_WIDTH;
	b = y + BULLET_BBOX_HEIGHT;
}

void CBullet::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);

	if (y != 0 && !isInitPos)
	{
		if (x > 1670)
			label = 1;
		else
			label = 2;
		isInitPos = true;
	}

	if (GetState() != BULLET_STATE_DIE)
	{
		if (label == 1)
		{
			if (isStart)
			{
				x -= vx;
				if (357.0f - mario->x > 0)
					vx = -0.08f;
				else
					vx = 0.08f;
				vy = +0.05f;

			}
			CPlant* plant = new CPlant();
			if (plant->start1 == true)
			{
				isStart = true;
				x = 357;
				y = 342;
				vx = 0;
			}
			x += dx;
			y += dy;

		}
		if (label == 2)
		{
			if (isStart)
			{

				if (y < 430.0f) {
					x -= vx;
					if (1871.0f - mario->x > 0)
						vx = -0.08f;
					else
						vx = 0.08f;
					vy = +0.05f;
				}
				else
				{
					vx = 0;
					vy = 0;
					y = 900.0f;
				}
			}
			CPlant* plant = new CPlant();
			if (plant->start2 == true)
			{
				isStart = true;
				x = 1871;
				y = 348;
				vx = 0;
			}
			x += dx;
			y += dy;

		}

	}
	
}

void CBullet::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case BULLET_STATE_DIE:
		x = 0.0f;
		y = 0.0f;
		break;
	case BULLET_STATE_LIVE:
		//vy = 0.1;
		break;
	}
}

