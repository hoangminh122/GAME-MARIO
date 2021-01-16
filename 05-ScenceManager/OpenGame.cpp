#include "OpenGame.h"

COpenGame * COpenGame::__instance = NULL;
COpenGame *COpenGame::GetInstance()
{
	if (__instance == NULL) __instance = new COpenGame();
	return __instance;
}

COpenGame::COpenGame()
{
	isInitPos = false;
	//isShow = false;
}

void COpenGame::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (y != 0 && !isInitPos)
	{
		isInitPos = true;
	}
}

void COpenGame::Render()
{
	animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}

void COpenGame::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + OPEN_GAME_BBOX_WIDTH;
	b = y + OPEN_GAME_BBOX_HEIGHT;

}
