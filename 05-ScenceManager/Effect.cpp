#include "Effect.h"


CEffect::CEffect(int type_ani)
{
	type = type_ani;
}

void CEffect::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{

}

void CEffect::Render()
{
	if (type == 0)
		ani = 0;
	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox();
}

void CEffect::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + EFFECT_BBOX_WIDTH;
	b = y + EFFECT_BBOX_HEIGHT;

}

