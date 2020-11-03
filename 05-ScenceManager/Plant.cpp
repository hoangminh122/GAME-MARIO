#include "Plant.h"

CPlant::CPlant() : CGameObject()
{
	vy = 0.1;
}
void CPlant::Render()
{
	animation_set->at(0)->Render(x, y);
	RenderBoundingBox();
}

void CPlant::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + PLANT_BBOX_WIDTH;
	b = y + PLANT_BBOX_HEIGHT;
}

void CPlant::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);

	//
	// TO-DO: make sure Koopas can interact with the world and to each of them too!
	// 
	
	//x += 0.1;
	y += vy;

	if (vy > 0 && y > 150) {
		y = 138; vy = -vy;
	}

	if (vy < 0 && y < 112) {
		y = 112; vy = -vy;
	}
}
