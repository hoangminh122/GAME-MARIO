#include "Turle.h"
#include "Mario.h"
#include "Brick.h"
#include "Utils.h"
#include "BrickTop.h"
#include "QuestionBox.h"
#include "WallTurle.h"
#include "BrickQuestion.h"
#include "Goomba.h"
#include "BackgroundDie.h"

bool CTurle::isTreeStart = false;
CTurle::CTurle()
{
	checkCollision = false;
	isHold = false;
	vxx = TURLE_WALKING_SPEED;
	isStop = 0;
	//ani = TURLE_STATE_RUN_DIE;
	ani = TURLE_ANI_WALKING_LEFT;
	SetState(TURLE_STATE_WALKING);
	//SetState(TURLE_STATE_DIE);
	isNoCollision = false;
	timeRunTurle = 0;
	timeDieTurle = 0;
	//tao instance mario dung chung-> chi tao 1 lan vi dungf nhieu
	 mario = CMario::GetInstance(0,0);
}

void CTurle::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + TURLE_BBOX_WIDTH;

	if (this->GetState() == TURLE_STATE_DIE || this->GetState() == TURLE_STATE_RUN_DIE)
		bottom = y + TURLE_BBOX_HEIGHT_DIE;
	
	else
		bottom = y + TURLE_BBOX_HEIGHT;
}

void CTurle::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);


	if (GetTickCount() - timeDieTurle > TURLE_TIME_DIE && timeDieTurle != 0)
	{
		SetState(TURLE_STATE_WALKING);
		y = y - (TURLE_BBOX_HEIGHT - TURLE_BBOX_HEIGHT_DIE);
		vx = 0.1f;
		isHold = false;
		mario->isHold = false;
		timeDieTurle = 0;
	}

	// Simple fall down
	//vy += MARIO_GRAVITY * dt;
	//if (CMario::isDropTurle == true && isHold == true)
	//{
	//	if (CMario::nxx == 1)
	//	{
	//		if (CMario::level == MARIO_LEVEL_BIG || CMario::level == MARIO_LEVEL_FIRE_BIG)
	//			this->x = this->x + MARIO_BIG_BBOX_WIDTH/2 +3.2f;
	//		else if (CMario::level == MARIO_LEVEL_TAIL_BIG)
	//			this->x = this->x + MARIO_TAIL_BIG_BBOX_WIDTH/2+3;
	//		//this->x = this->x + 10;
	//		
	//	}
	//	else 
	//	{
	//		if(CMario::level == MARIO_LEVEL_BIG || CMario::level == MARIO_LEVEL_FIRE_BIG)
	//			this->x = this->x-MARIO_BIG_BBOX_WIDTH/2-4.3f;
	//		else if(CMario::level == MARIO_LEVEL_TAIL_BIG)
	//			this->x = this->x - MARIO_TAIL_BIG_BBOX_WIDTH/2-3;
	//	}
	//	CMario::isDropTurle = false;
	//	isHold = false;
	//}
	//

	if (GetTickCount() - timeRunTurle > MAX_TURLE_TIME_RUN && timeRunTurle != 0)			//fix time gian chay cho rua -> fix tam do chua lam den
	{
		SetState(TURLE_STATE_DIE_OVER);
		timeRunTurle = 0;
	}
	//mario khong cam rua nua tha ra
	if (!mario->isHold  && mario->isMarioDropTurle)
	{
		timeRunTurle = GetTickCount();		//TIME CHAY CUA RUA
		isHold = false;
		vx =(mario->nx) * TURLE_RUN_SPEED;
		SetState(TURLE_STATE_RUN_DIE);
	}
	

	vy += MARIO_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (this->GetState() != TURLE_STATE_DIE_OVER)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		checkCollision = false;
		/*if (this->GetState() == TURLE_STATE_DIE_OVER)
		{
			x = 0;
			y = 0;
		}*/
		//else if (CMario::isHoldTurtle == true && isHold==true)
		//{
		//	if (CMario::level == MARIO_LEVEL_BIG)
		//	{
		//		x = CMario::xx + 8;
		//		y = CMario::yy + 4;								//set lai vi tri cho con rua
		//		
		//	}
		//	else
		//	{
		//		if (CMario::nxx == 1)
		//		{
		//			x = CMario::xx + 15;
		//		}
		//		else
		//			x = CMario::xx+2;
		//		y = CMario::yy + 4;								//set lai vi tri cho con rua
		//	}

		//	
		//}
		/*else
		{
			x += dx;
			y += dy;
		}*/

		//check luc cam rua ko di chuyen
		if (!isHold)
		{
			checkCollision = true; // rua co su va cham
			x += dx;
			y += dy;
		}
		else
		{
			if (mario->nx == 1)				//mario di chuyen qua phai -> set vi tri rua cho hop ly
			{
				if(mario ->GetLevel() > 1)
					x = mario->x + MARIO_BIG_BBOX_WIDTH- MARIO_BIG_BBOX_WIDTH/4;
				else
					x = mario->x + MARIO_BIG_BBOX_WIDTH;
			}
			else
			{
				if (mario->GetLevel() > 1)
					x = mario->x - TURLE_BBOX_WIDTH+ MARIO_BIG_BBOX_WIDTH /4;
				else
				x = mario->x - TURLE_BBOX_WIDTH;
			}

			if (mario->GetLevel() > 1)
				y = mario->y + MARIO_BIG_BBOX_WIDTH/4;
			else
				y = mario->y;
		}
		
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		//if (nx != 0) vx = 0;
		//if (ny != 0) vy = 0;

		

		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			
			if (ny < 0 && e->obj != NULL)
			{
				vy = 0;
			}

			if (dynamic_cast<CWallTurle *>(e->obj)) // if e->obj is brickTop
			{
				if (GetState() == TURLE_STATE_WALKING)
					vx = -vx;
				//rua khong va cham voi CWallTurle chieu tu tren xuong
				if (e->ny < 0)
					y += dy;
				//state run -> vx khong doi
			}
			else if (dynamic_cast<CBrickTop *>(e->obj)) // if e->obj is brickTop
			{
				x += dx;
				isNoCollision = true;
				

			}
			else if (dynamic_cast<CGoomba *>(e->obj)) // if e->obj is brickTop
			{
				x += dx;
				//if (e->nx != 0)
					//isNoCollision = true;
				

			}
			else if (dynamic_cast<CBrick *>(e->obj)) // if e->obj is brickTop
			{
				CBrick *brick = dynamic_cast<CBrick *>(e->obj);			//LOI THUAT TOAN CU CHUA FIX !!!!!.
				x += dx;												//va cham cho rua dao chieu bi loi chua fix .
			}
			else if (dynamic_cast<CBackgroundDie *>(e->obj)) // fix tam dao chieu
			{
				if (e->nx != 0)
					vx = -vx;
			}
			if (dynamic_cast<CBrickQuestion *>(e->obj)) // if e->obj is brickTop
			{
				vx = -vx;
				x += dx;
				/*if (GetState() == TURLE_STATE_RUN_DIE)
					isNoCollision = false;*/
				/*if (e->nx != 0)
					isNoCollision = false;*/
			}
			

			//if (dynamic_cast<CBrickTop *>(e->obj)) // if e->obj is brickTop
			//{
			//	if (this->GetState() == TURLE_STATE_DIE)
			//	{
			//		vx = 0;
			//		vy = 0;
			//	}
			//	else if(this->GetState() == TURLE_STATE_RUN_DIE)
			//		vx = 0.2f;
			//	else
			//		vx = vxx;
			//	if (this->GetState() == TURLE_STATE_WALKING)
			//	{
			//		if (vx < 0 && x < 530) {
			//			//x = 0; 
			//			vxx = -vxx;
			//			vx = vxx;
			//		}

			//		else if (vx > 0 && x > 600) {
			//			//x = 290; 
			//			vxx = -vxx;
			//			vx = vxx;
			//		}
			//	}
			//	

			//} // if brickTop
			//else if (dynamic_cast<CQuestion *>(e->obj)) // if e->obj is CQuestion
			//{
			//	this->isTreeStart = true;
			//}
			//else if (dynamic_cast<CBrick *>(e->obj)) // if e->obj is CQuestion
			//{
			//	if (this->GetState() == TURLE_STATE_DIE)
			//	{
			//		vx = 0;
			//	}
			//	vy = 0;
			//}
			//

			/*if (e->nx != 0 && e->obj != NULL && !isNoCollision)
			{
				vx = -vx;
				x += dx;
				isNoCollision = true;
			}*/
			
			
		}

	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CTurle::Render()
{
	
	if (this->GetState() == TURLE_STATE_DIE) {
		ani = TURLE_ANI_DIE;
	}
	else if (this->GetState() == TURLE_STATE_RUN_DIE) {
		ani = TURLE_ANI_RUN_DIE;
	}
	else if (vx > 0) ani = TURLE_ANI_WALKING_RIGHT;
	else if (vx <= 0) ani = TURLE_ANI_WALKING_LEFT;

	animation_set->at(ani)->Render(x, y);

	RenderBoundingBox(); 
}

void CTurle::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case TURLE_STATE_DIE:
		y += TURLE_BBOX_HEIGHT - TURLE_BBOX_HEIGHT_DIE + 1;
		vx = 0;
		//vy = 0;
		break;
	case TURLE_STATE_WALKING:
		vx = TURLE_WALKING_SPEED;
		break;
	case TURLE_STATE_RUN_DIE:
		//vx = -TURLE_WALKING_SPEED;
		break;
	case TURLE_STATE_DIE_OVER:
		//vx = 0;
		//vy = 0;
		break;
	}

}