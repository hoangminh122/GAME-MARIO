#include "ChangeRoad.h"


CChangeRoad::CChangeRoad(int type_ani,int l,int t,int r,int b,int _senceNext)
{
	left = l;
	top = t;
	right = r;
	bottom = b;
	type = type_ani;
	isInitPos = false;
	isLive = true;
	sceneNext = _senceNext;
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
	
	//animation_set->at(0)->Render(x, y);
	RenderBoundingBox();
}

void CChangeRoad::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	if (isLive)
	{
		l = x;
		t = y;
		r = x + BRICK_CHANGE_ROAD_BBOX_WIDTH;
		b = y + BRICK_CHANGE_ROAD_BBOX_WIDTH;
	}
	
}

