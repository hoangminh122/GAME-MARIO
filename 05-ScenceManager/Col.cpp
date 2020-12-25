#include "Col.h"
#include "Utils.h"

CCOL * CCOL::__instance = NULL;
CCOL::CCOL() : CGameObject()
{
	x = 0;
	y = 600;
	isStart = false;
	//vx = 0.8;
	mario = CMario::GetInstance(0, 0);
	isInitPos = false;
	//label = 0;
	//vx = 0.003f;
	isAttack = false;

}
CCOL *CCOL::GetInstance()
{
	if (__instance == NULL) __instance = new CCOL();
	return __instance;
}
void CCOL::Render()
{
	//animation_set->at(0)->Render(x, y);
	RenderBoundingBox();
}

void CCOL::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + COL_BBOX_WIDTH ;
	b = y + COL_BBOX_HEIGHT;
}

void CCOL::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);

	if (GetTickCount() - timeAttack > COL_ATTACK_TIME && timeAttack != 0)
	{
		vx = 0;
		y = 600;
		timeAttack = 0;
	}

	if(isAttack)
	{
		if (mario->vx > 0 || mario->nx > 0)
		{
			x = mario->x + MARIO_TAIL_BIG_ATTACK_BBOX_WIDTH;
			y = mario->y + MARIO_TAIL_BIG_BBOX_HEIGHT / 1.5f;
			vx = 0.06f;
		}
		else
		{
			x = mario->x;
			y = mario->y + MARIO_TAIL_BIG_BBOX_HEIGHT / 1.5f;
			vx = -0.06f;

		}
		
		isAttack = false;
	}
	
	x += dx;
	y += dy;
}
