#include "CMushroom.h"
#include "Turle.h"

bool CMushroom::isStart = false;
bool CMushroom::isRun = false;
CMushroom * CMushroom::__instance = NULL;
CMushroom::CMushroom() : CGameObject()
{
	ani = 0;
	vx = 0.0f;
	isStart = false;
	isRun = false;
	isDie = false;

}
CMushroom *CMushroom::GetInstance()
{
	if (__instance == NULL) __instance = new CMushroom();
	return __instance;
}
void CMushroom::Render()
{
	if (state == LEAF_GREEN_STATE)
		ani = 1;
	else
		ani = 0;
	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox();
}

void CMushroom::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + 17;
	b = y + 17;
}

void CMushroom::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);

	if (isRun)
	{
		state = MUSHROOM_STATE;
	}
	if (CTurle::isTreeStart == true)
	{
		state = LEAF_GREEN_STATE;
		x = 646;
		y = 136;

	}
	if (isDie || x < 0)
	{
		x = -17; y = -17;
		vx = 0;
		isRun = false;
		isStart = false;
		return;
	}
	else if (state == MUSHROOM_STATE)
	{
		if (isStart)
		{
			this->x = 220;
			this->y = 52;
			isStart = false;
		}
		

		else if (isRun)
		{
			if (y >= 170)
			{
				//vy = 0.01;
				vx = -0.055;
				y = 170;
				//x -= dx;
			}
			else if (x < 186)
			{
				//x = 0;
				vx = 0;
				y += 0.5*dt;
			}
			else
			{
				y = 52;
				//y += 0.005*dt;
				//x -= 0.4*vx;
				vx = -0.04;
			}
		}
		x += dx;
	}

	
	
}

void CMushroom::SetState(int state)
{
	CGameObject::SetState(state);
	/*switch (state)
	{
	
	case MUSHROOM_STATE:
		vx = -;
	}*/
}