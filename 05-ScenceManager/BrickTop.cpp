#include "BrickTop.h"
#include "Utils.h"

CBrickTop::CBrickTop(int type_ani)
{
	type = type_ani;
	isInitPos = false;
}

void CBrickTop::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (y != 0 && !isInitPos)
	{
		xStatic = x;
		isInitPos = true;
	}
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
	b = y + BRICK_BBOX_HEIGHT_2;
	if (type == BRICK_BBOX_TYPE_1)
	{
		r = x + BRICK_BBOX_WIDTH_ORANGE_ONE;
	}
	else if (type == BRICK_BBOX_TYPE_2)
	{
		r = x + BRICK_BBOX_WIDTH_GREEN_ONE;
	}
	else if (type == BRICK_BBOX_TYPE_3)
	{
		r = x + BRICK_BBOX_WIDTH_ORANGE_TWO;
	}
	else if (type == BRICK_BBOX_TYPE_4)
	{
		r = x + BRICK_BBOX_WIDTH_GREEN_TWO;
	}
	else if (type == BRICK_BBOX_TYPE_5)
	{
		r = x + BRICK_BBOX_WIDTH_GREEN_THREE;
	}

}

int CBrickTop::GetBoundPosition(int type2) {
	if (type == BRICK_BBOX_TYPE_1)
	{
		return BRICK_BBOX_WIDTH_ORANGE_ONE;
	}
	else if (type == BRICK_BBOX_TYPE_2)
	{
		return BRICK_BBOX_WIDTH_GREEN_ONE;
	}
	else if (type == BRICK_BBOX_TYPE_3)
	{
		return BRICK_BBOX_WIDTH_ORANGE_TWO;
	}
	else if (type == BRICK_BBOX_TYPE_4)
	{
		return BRICK_BBOX_WIDTH_GREEN_TWO;
	}
	else if (type == BRICK_BBOX_TYPE_5)
	{
		return BRICK_BBOX_WIDTH_GREEN_THREE;
	}
	return BRICK_BBOX_TYPE_16;
}
