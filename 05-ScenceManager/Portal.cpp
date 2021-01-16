#include "Portal.h"


int CPortal::is_start = 1;
int CPortal::scene_id =2;
CPortal::CPortal(float l, float t, float r, float b, int scene_id,int is_start1 )
{
	is_start = is_start1;
	this->scene_id = scene_id;
	x = l; 
	y = t;
	width = r - l + 1;
	height = b - t + 1;
}

void CPortal::Render()
{
	RenderBoundingBox();
}

void CPortal::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}