#include "CMushroom.h"


bool CMushroom::isStart = false;
bool CMushroom::isRun = false;
CMushroom * CMushroom::__instance = NULL;
CMushroom::CMushroom() : CGameObject()
{
	vx = -0.02f;
	isStart = true;
	isRun = true;
	isDie = false;
}
CMushroom *CMushroom::GetInstance()
{
	if (__instance == NULL) __instance = new CMushroom();
	return __instance;
}
void CMushroom::Render()
{
	animation_set->at(0)->Render(x, y);
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
	
	if (isStart)
	{
		this->x = 220;
		this->y = 52;
		isStart = false;
	}
	if (isDie || x < 0)
	{
		x = 0; y = 0;
		vx = 0;
		isRun = false;
		isStart = false;
		return;
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