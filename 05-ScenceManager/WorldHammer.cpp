#include "WorldHammer.h"

CWorldHammer::CWorldHammer(float left, float right)
{
	x_left = left;
	x_right = right;
	vx = 0.01f;
	isReverse = false;
}

void CWorldHammer::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	x += dx;

	if (x < x_left)
	{
		x = x_left;
		vx = -vx;
		isReverse = false;
	}
	else if (x > x_right)
	{
		x = x_right;
		vx = -vx;
		isReverse = true;
	}
}

void CWorldHammer::Render()
{
	animation_set->at(0)->Render(x, y, 255,false,isReverse);

	RenderBoundingBox();
}

