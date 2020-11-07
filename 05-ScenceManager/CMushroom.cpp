#include "CMushroom.h"
#include "Turle.h"
#include "Utils.h"

bool CMushroom::isMoney = false;
bool CMushroom::isStart = false;
bool CMushroom::isRun = false;
int CMushroom::xBox = 0;
int CMushroom::yBox = 0;
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
	else if (state == MONEY_STATE)
		ani = 2;
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

	if (isMoney)
	{
		state = MONEY_STATE;
	}
	
	if (isDie || x < 0)
	{
		x = 17;
		y = -17;
		vx = 0;
		isRun = false;
		isStart = false;
		isDie = false;
		CTurle::isTreeStart = false;
		state = -1;
		return;
	}    //trang thai die
	if (CTurle::isTreeStart == true)
	{
		state = LEAF_GREEN_STATE;
		x = 646;
		y = 136;

	}	//trang thai la cay
	if (isRun)
	{
		DebugOut(L"is Run \n");
		state = MUSHROOM_STATE;
	}
	
	
	/*else
	{
		state = -1;
		x = 17;
		y = -17;
	}*/
	
	if (state == MONEY_STATE)
	{
		if (isMoney)
		{
			x = xBox;
			y = yBox;
			isMoney = false;
		}
		if (y < yBox - 60)
		{
			 y = -17;
			vx = 0;
			isDie = true;
			return;
		}
		vy = -0.2f;
		y += dy;
		DebugOut(L"ashdgahsg");

	}
	else if (state == MUSHROOM_STATE)
	{
		DebugOut(L"vao nam\n");
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
	}   // trang thai cua nam
	
	
	
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