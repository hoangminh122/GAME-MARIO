#include "Plant.h"
#include "Bullet.h"
#include "Utils.h"

bool CPlant::start = false;
CPlant::CPlant() : CGameObject()
{
	vy = 0.1;
	ani = 0;
	mario = CMario::GetInstance(0, 0);
	level = PLANT_LEVEL_HIGH;
	SetState(PLANT_STATE_UP);
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
		if (y - mario->y > 0)
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
		if (GetState() == PLANT_STATE_UP)
		{
			if (x - mario->x > 0)
				ani = PLANT_ANI_PLANT_SMALL_LEFT_UP;
			else
				ani = PLANT_ANI_PLANT_SMALL_RIGHT_UP;
		}
		else
		{
			if (x - mario->x > 0)
				ani = PLANT_ANI_PLANT_SMALL_LEFT_DOWN;
			else
				ani = PLANT_ANI_PLANT_SMALL_RIGHT_DOWN;
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

void CPlant::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);
	

	
	//
	// TO-DO: make sure Koopas can interact with the world and to each of them too!
	// 
	
	//x += 0.1;
	y +=4*vy;

	if (vy > 0 && y > 400) {
		y = 400; vy = -vy;
	}
	start = false;
	if (vy < 0 && y < 342) {
		start = true;
		y = 342; vy = -vy;
	}

}
