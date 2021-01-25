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
		if (x > BULLET_POSITION_X_1)
			label = BULLET_LABEL_1;
		else
			label = BULLET_LABEL_2;
		isInitPos = true;
	}

	if (GetState() != BULLET_STATE_DIE)
	{
		if (label == BULLET_LABEL_1)
		{
			if (isStart)
			{
				x -= vx;
				if (357.0f - mario->x > 0)
					vx = -BULLET_VX_0_08;
				else
					vx = BULLET_VX_0_08;
				vy = +BULLET_VY_0_05;

			}
			CPlant* plant = new CPlant();
			if (plant->start1 == true)
			{
				isStart = true;
				x = BULLET_POSITION_X_START_1;
				y = BULLET_POSITION_Y_START_1;
				vx = 0;
			}
			x += dx;
			y += dy;

		}
		if (label == BULLET_LABEL_2)
		{
			if (isStart)
			{

				if (y < BULLET_POSITION_X_430) {
					x -= vx;
					if (BULLET_POSITION_X_1871 - mario->x > 0)
						vx = -BULLET_VX_0_08;
					else
						vx = BULLET_VX_0_08;
					vy = +BULLET_VY_0_05;
				}
				else
				{
					vx = 0;
					vy = 0;
					y = BULLET_POSITION_Y_900;
				}
			}
			CPlant* plant = new CPlant();
			if (plant->start2 == true)
			{
				isStart = true;
				x = BULLET_POSITION_X_1871;
				y = BULLET_POSITION_Y_348;
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

