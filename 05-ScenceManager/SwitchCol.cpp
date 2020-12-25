#include "SwitchCol.h"


CSwitchCol::CSwitchCol(int type_ani)
{
	type = type_ani;
}

void CSwitchCol::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	
}

void CSwitchCol::Render()
{
	
	//animation_set->at(1)->Render(x, y);
	RenderBoundingBox();
}

void CSwitchCol::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + SWITCH_COL_BBOX_WIDTH;
	b = y + SWITCH_COL_BBOX_HEIGHT;

}
