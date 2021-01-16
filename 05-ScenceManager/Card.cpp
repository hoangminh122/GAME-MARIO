#include "Card.h"

bool CCard::isDie = false;
CCard::CCard()
{
	ani = 0;
}

void CCard::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (isDie)
	{
		x = 2764.0f ;
		y = 285.0f;

	}
}

void CCard::Render()
{
	if(!isDie)
		animation_set->at(0)->Render(x, y);
	else
	{
		animation_set->at(ani)->Render(x, y);
	}
	if (!isDie)
		RenderBoundingBox();
}

void CCard::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + CARD_BBOX_WIDTH;
	b = y + CARD_BBOX_HEIGHT;

}

