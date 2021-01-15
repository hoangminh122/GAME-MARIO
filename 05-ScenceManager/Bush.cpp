#include "Bush.h"

void CBush::Render()
{
	animation_set->at(0)->Render(x, y);
	RenderBoundingBox();
}
