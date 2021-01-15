#include "ChangeRoad.h"


CChangeRoad::CChangeRoad(int type_ani)
{
	type = type_ani;
	isInitPos = false;
}

void CChangeRoad::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (y != 0 && !isInitPos)
	{
		isInitPos = true;
	}
}

void CChangeRoad::Render()
{
	
	animation_set->at(0)->Render(x, y);
	RenderBoundingBox();
}

void CChangeRoad::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}

