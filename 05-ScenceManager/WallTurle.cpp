#include "WallTurle.h"

void CWallTurle::Render()
{
	//animation_set->at(0)->Render(x, y);
	RenderBoundingBox();
}

void CWallTurle::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + WALL_TURLE_BBOX_WIDTH;
	b = y + WALL_TURLE_BBOX_HEIGHT;
}
