#include "Hat.h"


CHat::CHat()
{
	
}

void CHat::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	
}

void CHat::Render()
{
	animation_set->at(0)->Render(x, y);
	RenderBoundingBox();
}

void CHat::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + HAT_BBOX_WIDTH;
	b = y + HAT_BBOX_HEIGHT;

}

