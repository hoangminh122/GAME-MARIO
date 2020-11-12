#include "BulletMario.h"
#include "Plant.h"
#include "Utils.h"
#include "BrickTop.h"
#include "Brick.h"

//CBullet::CBullet() {
//	isStart = false;
//}
bool CBulletMario::isStart = false;
float CBulletMario::x0 = 0;
float CBulletMario::y0 = 0;
void CBulletMario::setPosition(float x0, float y0) {
	x0 = x0;
	y0 = y0;
}
CBulletMario * CBulletMario::__instance = NULL;
CBulletMario::CBulletMario() : CGameObject()
{
	isStart = false;
	state = -1;
}
CBulletMario *CBulletMario::GetInstance()
{
	if (__instance == NULL) __instance = new CBulletMario();
	return __instance;
}
void CBulletMario::Render()
{
	animation_set->at(0)->Render(x, y);
	RenderBoundingBox();
}

void CBulletMario::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + BULLET_BBOX_WIDTH;
	b = y + BULLET_BBOX_HEIGHT;
}

void CBulletMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);
	DebugOut(L"IS sTART%d \n", this->vx);
	if (isStart)
	{
		this->x = x0 + 10;
		this->y = y0 + 3;
		vx = 0.08f;
		vy = 0.05f;
		isStart = false;

	}

	// Simple fall down

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state != BULLET_MARIO_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);


	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			
			if (dynamic_cast<CBrick *>(e->obj)) // if e->obj is brickTop
			{
				DebugOut(L" dan trung brick top");
				//vx = 0;
				vy = -vy;
				/*if (e->ny > 0)
					this->y = y - 0.5;*/

			} // if brickTop
			else if (dynamic_cast<CBrickTop *>(e->obj)) // if e->obj is brickTop
			{
				DebugOut(L" dan trung brick top");
				//vx = 0;
				vy = -vy;
				/*if (e->ny > 0)
					this->y = y - 0.5;*/

			} // if brickTop

		}
		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	}

}

