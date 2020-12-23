#include "BackgroundDie.h"

void CBackgroundDie::Render()
{
	//animation_set->at(0)->Render(x, y);
	RenderBoundingBox();
}

void CBackgroundDie::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + BACKGROUND_DIE_BBOX_WIDTH;
	b = y + BACKGROUND_DIE_BBOX_HEIGHT;
}
