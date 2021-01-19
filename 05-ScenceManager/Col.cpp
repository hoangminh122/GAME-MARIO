#include "Col.h"
#include "Utils.h"
#include "Brick.h"
#include "BrickQuestion.h"
#include "Plant.h"
#include "Hat.h"

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
			x = mario->x + MARIO_TAIL_BIG_ATTACK_BBOX_WIDTH/1.5f;
			y = mario->y + MARIO_TAIL_BIG_BBOX_HEIGHT / 1.5f;
			vx = 0.09f;
		}
		else
		{
			x = mario->x+5;
			y = mario->y + MARIO_TAIL_BIG_BBOX_HEIGHT / 1.5f;
			vx = -0.06f;

		}
		
		isAttack = false;
	}
	

	// Simple fall down

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (this->GetState() != COL_STATE_DIE)
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

			if (dynamic_cast<CBrickQuestion *>(e->obj)) // if e->obj is brickTop
			{
				CBrickQuestion* brickQuestion = dynamic_cast<CBrickQuestion *>(e->obj);

				//if (!brickQuestion->isDie)				//chua va cham lan nao
				//{
				brickQuestion->SetMove(true);
				////SET SCORES MOVE
				//CCOIN::xStartMove = brickQuestion->x;
				//CCOIN::yStartMove = brickQuestion->y;
				//CCOIN::isInitPosNew = true;
				////CCOIN::timeWait = GetTickCount();
				//CCOIN::isMove = true;
				//CCOIN::level = 100;

				////SET COINS MOVE
				//CCOIN::status = 1;

			/*}*/
				vy = 0.005f;

			} // if brickTop
			else if (dynamic_cast<CBrick *>(e->obj)) // if e->obj is brickTop
			{
				CBrick* brick = dynamic_cast<CBrick *>(e->obj);
				if (nx != 0)
				{
					if (brick->type == 10)
					{
							brick->y = 600;
					}
					else if (brick->type == 11)
					{
						if (e->nx != 0 && !CHat::GetInstance()->noColision)
						{
							//y = hat->y;
							//CHat::GetInstance()->y = CHat::GetInstance()->y - 16 - 10;
							CHat::GetInstance()->y = 368.0f - 16;
							CHat::GetInstance()->isDie = false;				// HAT song lai
							//y += dy;

						}
						else if (!CHat::GetInstance()->noColision && !CHat::GetInstance()->isDie)
						{
							CBrick::moneyIcon = true;
							CHat::GetInstance()->isDie = true;
							CHat::GetInstance()->y = CHat::GetInstance()->y + 6;
							CHat::GetInstance()->noColision = true;
						}
						//vx +=dx;
					}
				}

			} // if brickTop
			else if (dynamic_cast<CPlant *>(e->obj)) // if e->obj is brickTop
			{
				CPlant* plant = dynamic_cast<CPlant *>(e->obj);
				if (nx != 0)
				{
					plant->SetState(PLANT_STATE_DIE);
				}

			} // if brickTop
			
			
			
			

		}
		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	}

}

