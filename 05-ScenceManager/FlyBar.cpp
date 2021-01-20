#include "FlyBar.h"
#include "Portal.h"


CFlyBar::CFlyBar()
{

}


void CFlyBar::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{

}


void CFlyBar::Render()
{
	
	animation_set->at(0)->Render(x, y);
	RenderBoundingBox();
}

void CFlyBar::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + FLY_BAR_BBOX_WIDTH;
	b = y + FLY_BAR_BBOX_HEIGHT;
	
}


