#include "Card.h"
#include "Portal.h"

bool CCard::isDie = false;
CCard::CCard()
{
	ani = 0;
}

void CCard::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (isDie)
	{
		if (CPortal::scene_id == PORTAL_SCENE_2)
		{
			x = CARD_BBOX_POS_X_2764;
			y = CARD_BBOX_POS_X_285;
		}
		else if (CPortal::scene_id == PORTAL_SCENE_4)
		{
			x = 2500.0f;
			y = 130.0f;

		}
		
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

