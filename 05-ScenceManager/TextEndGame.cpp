#include "TextEndGamer.h"

bool CTextEndGame::isShow = false;
CTextEndGame * CTextEndGame::__instance = NULL;
CTextEndGame *CTextEndGame::GetInstance()
{
	if (__instance == NULL) __instance = new CTextEndGame();
	return __instance;
}

CTextEndGame::CTextEndGame()
{
	isInitPos = false;
	//isShow = false;
}

void CTextEndGame::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (y != 0 && !isInitPos)
	{
		isInitPos = true;
	}
}

void CTextEndGame::Render()
{
	if(isShow == true)
		animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}

void CTextEndGame::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + TEXT_END_GAME_BBOX_WIDTH;
	b = y + TEXT_END_GAME_BBOX_HEIGHT;
	
}
