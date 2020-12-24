#include "Card.h"


CCard::CCard()
{
	
}

void CCard::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	
}

void CCard::Render()
{
	
	animation_set->at(0)->Render(x, y);
	RenderBoundingBox();
}

void CCard::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + CARD_BBOX_WIDTH;
	b = y + CARD_BBOX_HEIGHT;

}

