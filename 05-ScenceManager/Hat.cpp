#include "Hat.h"


CHat::CHat()
{
	noColision = false;
	isDie = true;
}

void CHat::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	/*if (isDie)
	{

	}*/
	CGameObject::Update(dt, coObjects);
	x += dx;
	y += dy;

}

void CHat::Render()
{
	if(!isDie)
		animation_set->at(0)->Render(x, y);
	else
		animation_set->at(1)->Render(x, y);
	RenderBoundingBox();
}

void CHat::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + HAT_BBOX_WIDTH;
	b = y + HAT_BBOX_HEIGHT;
	if (isDie)
		b = y + HAT_BBOX_DIE_HEIGHT;

}

