#include "BrickTop.h"


CBrickTop::CBrickTop(int type_ani)
{
	type = type_ani;
}
void CBrickTop::Render()
{
	//animation_set->at(0)->Render(x, y);
	RenderBoundingBox();
}

void CBrickTop::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
	if (type == 1)
	{
		r = x + BRICK_BBOX_WIDTH_ORANGE_ONE;
	}
	else if (type == 2)
	{
		r = x + BRICK_BBOX_WIDTH_GREEN_ONE;
	}
	else if (type == 3)
	{
		r = x + BRICK_BBOX_WIDTH_ORANGE_TWO;
	}
	else if (type == 4)
	{
		r = x + BRICK_BBOX_WIDTH_GREEN_TWO;
	}
	else if (type == 5)
	{
		r = x + BRICK_BBOX_WIDTH_GREEN_THREE;
	}

}
