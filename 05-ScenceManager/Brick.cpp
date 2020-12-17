#include "Brick.h"


CBrick::CBrick(int type_ani) 
{
	type = type_ani;
	isInitPos = false;
}

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (y != 0 && !isInitPos)
	{
		xStatic = x;
		isInitPos = true;
	}
}

void CBrick::Render()
{
	if(type ==10)
		animation_set->at(1)->Render(x, y);
	RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
	if (type == 1)
		r = x + BRICK_BBOX_WIDTH_ONE;
	else if (type == 2)
		r = x + BRICK_BBOX_WIDTH_TWO;
	else if (type == 3)
		r = x + BRICK_BBOX_WIDTH_THREE;
	else if (type == 4)
		r = x + BRICK_BBOX_WIDTH_FOUR;
	else if (type == 5)
		r = x + BRICK_BBOX_WIDTH_FIRE;
	else if (type == 6)
		r = x + BRICK_BBOX_WIDTH_SIX;
	else if (type == 7)
	{
		r = x + BRICK_BBOX_WIDTH_COLUMN;
		b = y + BRICK_BBOX_HEIGHT_COLUMN;
	}
	else if (type == 8)
	{
		r = x + BRICK_BBOX_WIDTH_COLUMN;
		b = y + BRICK_BBOX_HEIGHT_COLUMN_SMALL;
	}
	else if (type == 9)
	{
		r = x + BRICK_BBOX_WIDTH_COLUMN;
		b = y + BRICK_BBOX_HEIGHT_COLUMN_HIGH;
	}

	
}

int CBrick::GetBoundPosition(int type2) {
	if (type == 1)
		return BRICK_BBOX_WIDTH_ONE;
	else if (type == 2)
		return BRICK_BBOX_WIDTH_TWO;
	else if (type == 3)
		return BRICK_BBOX_WIDTH_THREE;
	else if (type == 4)
		return BRICK_BBOX_WIDTH_FOUR;
	else if (type == 5)
		return BRICK_BBOX_WIDTH_FIRE;
	else if (type == 6)
		return BRICK_BBOX_WIDTH_SIX;
	else if (type == 7 || type == 8 || type == 9)
	{
		return BRICK_BBOX_WIDTH_COLUMN;
	}
	else
		return BRICK_BBOX_WIDTH;
}
