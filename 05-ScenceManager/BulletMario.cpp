#include "BulletMario.h"
#include "Plant.h"
#include "Utils.h"
#include "BrickTop.h"
#include "Brick.h"
#include "Goomba.h"
#include "Game.h"
#include "Mario.h"
#include "BackgroundDie.h"
#include "Turle.h"


//CBullet::CBullet() {
//	isStart = false;
//}
int CBulletMario::nxBullet = 1;
bool CBulletMario::isSetPosition = false;
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
	this->SetState(-1);
	heightAfter = 0;
	isDie = true;
	isBullet = false;
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

	if (nextStart - timeStart > 5000)
	{
		isDie = true;
		isBullet = false;
		nextStart = timeStart = 0;
	}
	if (isStart)
	{
		if (((rand() % 2) + 1) == 1)
		{
			isBullet = true;
		}
		else
			isBullet = false;
	}
	if (isDie && isBullet)
	{
		timeStart = GetTickCount();                        //time bat dau ban dan
		nextStart = GetTickCount();
		if (nxBullet == 1)
			this->x = x0 + 10;
		else
			this->x = x0 - 10;
		this->y = y0 + 3;
		if (nxBullet == 1)
		{
			vx = 0.13f;
			
		}
		else 
			vx = -0.11f;
		vy = 0.1f;
		isDie = false;									//dan van con song
		if(isBullet)
			isStart = false;							

	}
	else if (isDie)
	{
		this->x = 0;
		this->y = 0;
		vy = 0;
		vx = 0;
		isBullet = false;
	}
	else if (isBullet)															//check xem dan co dang con song khong
	{
		nextStart = GetTickCount();
		CGame *game = CGame::GetInstance();
		if (nxBullet == 1 && x > CMario::xRealTime + game->GetScreenWidth() / 2
			|| nxBullet == -1 && x < CMario::xRealTime - game->GetScreenWidth() / 2
			|| CMario::xx <0)
		{
			isDie = true;
			isBullet = false;
		}
	}
	
	// Simple fall down

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (this->GetState() != BULLET_MARIO_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);


	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		if (heightAfter - y > MAX_HEIGHT_JUMP_BULLET)
		{
			vy = -vy-0.01f;
			heightAfter = y;
		}
		
		else if (vx == 0.0f)
		{
			isDie = true;
			isBullet = false;
		}

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
			heightAfter = y;
			LPCOLLISIONEVENT e = coEventsResult[i];

			
			if (dynamic_cast<CBrick *>(e->obj)) // if e->obj is brickTop
			{
				//vx = 0;
				vy = -vy;
				/*if (e->ny > 0)
					this->y = y - 0.5;*/

			} // if brickTop
			else if (dynamic_cast<CGoomba *>(e->obj)) // if e->obj is Goomba 
			{

				CGoomba *goomba = dynamic_cast<CGoomba *>(e->obj);
				goomba->SetState(GOOMBA_STATE_DIE);
				isDie = true;
				isStart = false;
				// jump on top >> kill Goomba and deflect a bit 
				
				
			} // if Goomba
			else if (dynamic_cast<CBrickTop *>(e->obj)) // if e->obj is brickTop
			{
				//vx = 0;
				vy = -vy;
				/*if (e->ny > 0)
					this->y = y - 0.5;*/

			} // if brickTop
			else if (dynamic_cast<CTurle *>(e->obj)) // if e->obj is brickTop
			{
				CTurle *turle = dynamic_cast<CTurle *>(e->obj);
				turle->SetState(TURLE_STATE_DIE_OVER);
			} // if brickTop
			else if (dynamic_cast<CBackgroundDie *>(e->obj)) // if e->obj is brickTop
			{
				isDie = true;
				isStart = false;
				isBullet = false;

			} // if background die
			else
			{
				if (e->ny != 0)
					vy = -vy;
				else if (e->nx != 0)
					vx = -vx;
				
			}

		}
		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	}

}

