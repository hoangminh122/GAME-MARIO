#include "Plant.h"
#include "Bullet.h"
#include "Utils.h"

bool CPlant::start = false;
bool CPlant::start1 = false;
bool CPlant::start2 = false;
CPlant::CPlant() : CGameObject()
{
	vy = 0.07;
	ani = 0;
	mario = CMario::GetInstance(0, 0);
	level = PLANT_LEVEL_HIGH;
	SetState(PLANT_STATE_UP);
	isInitPos = false;
}
void CPlant::Render()
{
	if (level == PLANT_LEVEL_HIGH)
	{
		if (y - mario->y > 0)
		{
			if(x- mario->x >0)
				ani = PLANT_ANI_PLANT_HIGH_LEFT_UP;
			else
				ani = PLANT_ANI_PLANT_HIGH_RIGHT_UP;
		}
		else
		{
			if (x - mario->x > 0)
				ani = PLANT_ANI_PLANT_HIGH_LEFT_DOWN;
			else
				ani = PLANT_ANI_PLANT_HIGH_RIGHT_DOWN;
		}
	}
	else if (level == PLANT_LEVEL_MIDDLE)
	{
		if (y - mario->y < 0)
		{
			if (x - mario->x > 0)
				ani = PLANT_ANI_PLANT_MIDDLE_LEFT_UP;
			else
				ani = PLANT_ANI_PLANT_MIDDLE_RIGHT_UP;
		}
		else
		{
			if (x - mario->x > 0)
				ani = PLANT_ANI_PLANT_MIDDLE_LEFT_DOWN;
			else
				ani = PLANT_ANI_PLANT_MIDDLE_RIGHT_DOWN;
		}
	}
	else if (level == PLANT_LEVEL_SMALL)
	{
		if (y - mario->y > 0)
		{
				ani = PLANT_ANI_PLANT_SMALL_UP;
		}
		else
		{
				ani = PLANT_ANI_PLANT_SMALL_DOWN;
		}
	}
	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox();
}

void CPlant::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + PLANT_BBOX_WIDTH;
	b = y + PLANT_BBOX_HEIGHT;
}

void CPlant::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case PLANT_STATE_DIE:
		x = 0.0f;
		y = 0.0f;
		break;
	case PLANT_STATE_LIVE:
		vy = 0.1;
		break;
	}
}

void CPlant::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);
	
	if (y != 0 && !isInitPos)					//ban dau  x=0, y=0 -> loai truong hop nay
	{
		if (x > 1730.0f && x< 1860)
		{
			level = PLANT_LEVEL_SMALL;
		}
		else if(x>1850.0f)
		{
			level = PLANT_LEVEL_MIDDLE;

		}
		else
		{
			level = PLANT_LEVEL_HIGH;

		}
		isInitPos = true;

	}
	
	//
	// TO-DO: make sure Koopas can interact with the world and to each of them too!
	// 
	
	if (GetState() != PLANT_STATE_DIE)
	{
		if (level == PLANT_LEVEL_HIGH)
		{
			//x += 0.1;
			y += 4 * vy;

			if (vy > 0 && y > 380) {
				y = 380; vy = -vy;
			}
			start1 = false;
			if (vy < 0 && y < 336) {
				start1 = true;
				y = 336; vy = -vy;
			}
		}
		else if (level == PLANT_LEVEL_MIDDLE)
		{
			//x += 0.1;
			y += 4 * vy;

			if (vy > 0 && y > 400) {
				y = 400; vy = -vy;
			}
			start2 = false;
			if (vy < 0 && y < 345) {
				start2 = true;
				y = 345; vy = -vy;
			}
		}
		else if (level == PLANT_LEVEL_SMALL)
		{
			//x += 0.1;
			y += 4 * vy;

			if (vy > 0 && y > 400) {
				y = 400; vy = -vy;
			}
			start = false;
			if (vy < 0 && y < 360) {
				start = true;
				y = 360; vy = -vy;
			}
		}
	}

}
