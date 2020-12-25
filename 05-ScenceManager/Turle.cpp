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
#include "Leaf.h"
#include "Col.h"


//DWORD CTurle::timeStart = 1;
bool CTurle::isTreeStart = false;
CTurle::CTurle(int type_ani)
{
	int nxx = -1;
	type = type_ani;
	untouchable = 0;
	//color = 1;
	checkCollision = false;
	isHold = false;
	vxx = TURLE_WALKING_SPEED;
	isStop = 0;
	//ani = TURLE_STATE_RUN_DIE;
	ani = TURLE_ANI_WALKING_LEFT;
	//SetState(TURLE_STATE_WALKING);
	//SetState(TURLE_STATE_DIE);
	//SetState(TURLE_STATE_FLY);
	isNoCollision = false;
	timeRunTurle = 0;
	timeDieTurle = 0;
	//tao instance mario dung chung-> chi tao 1 lan vi dungf nhieu
	 mario = CMario::GetInstance(0,0);
	 isReverse = false;
	 //level = TURLE_LEVEL_NO_FLY;
	 isInitPos = false;
	 timeStart = 0;
}

void CTurle::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + TURLE_BBOX_WIDTH;
	bottom = y + TURLE_BBOX_HEIGHT;

	if (level == TURLE_LEVEL_NO_FLY)								//rua chay xanh
	{
		;
	}
	else if (level == TURLE_LEVEL_SMALL)							//mai rua xanh
	{
		if (this->GetState() == TURLE_STATE_DIE || this->GetState() == TURLE_STATE_RUN_DIE)
			bottom = y + TURLE_BBOX_HEIGHT_DIE;

	}
	else if (level == TURLE_LEVEL_FLY)							//rua xanh co canh
	{
		;
	}

	
}

void CTurle::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	//KHOI TAO OBJECT
	if (y > 650)
	{
		SetState(TURLE_STATE_DIE_OVER);
		x = 1419.0f;
		y = 880.0f;				// 280.0f;
		vx = 0; vy = 0;
	}

	if (y != 0 && !isInitPos)
	{
		if (type == TURLE_COLOR_GREEN)						//tao do tren map
		{
			level = TURLE_LEVEL_FLY;
			constTimeStart = (DWORD)x;
			x = 1419.0f;
			y = 280.0f;
			timeStart = GetTickCount();
			color = 1;
		}
		else if (type == TURLE_COLOR_GREEN_NO_FLY)						//tao do tren map
		{
			SetState(TURLE_STATE_WALKING);
			level = TURLE_LEVEL_NO_FLY;
			color = 1;
		}
		else
		{
			SetState(TURLE_STATE_WALKING);
			level = TURLE_LEVEL_NO_FLY;
			color = 2;
			//level = TURLE_LEVEL_SMALL;
		}
			
		isInitPos = true;
	}

	if (GetTickCount() - timeStart > constTimeStart && timeStart != 0 && level == TURLE_LEVEL_FLY)
	{
		//timeStart = GetTickCount();
		SetState(TURLE_STATE_FLY);
		timeStart = 0;
	}

	if (this->GetState() == TURLE_STATE_REVERSE_DIE) {								//TRANG THAI REVERSE KHI BI MARIO QUAT DUOI
		if (y > mario->y + 200)
		{
			vy = 0;
			vx = 0;
		}
		else if (y < mario->y - TURLE_BBOX_HEIGHT * 3)
		{
			vy += 0.05f;
			vx = (mario->nx)*0.08f;
		}
		/*else if(ny == 1)
		{
			vy = -0.1f;
			vx = 0.05f;

		}*/
		isReverse = true;
	}
	if (GetTickCount() - timeDieTurle > TURLE_TIME_DIE && timeDieTurle != 0)
	{
		level = 2;
		SetState(TURLE_STATE_WALKING);
		y = y - (TURLE_BBOX_HEIGHT - TURLE_BBOX_HEIGHT_DIE);
		vx = TURLE_WALKING_SPEED;
		isHold = false;
		mario->isHold = false;
		timeDieTurle = 0;
	}

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
	
	if (this->GetState() != TURLE_STATE_DIE_OVER)
	{
		if (level == TURLE_LEVEL_FLY)
			vy += TURLE_GRAVITY_SLOW * dt;
		else
			vy += TURLE_GRAVITY * dt;
	}
	

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
			if (mario->vx > 0)				//mario di chuyen qua phai -> set vi tri rua cho hop ly    nen dung vx thay cho nx vi co giai doan phanh
			{
				if (mario->GetLevel() == 1)
				{
					x = mario->x + (float)MARIO_SMALL_BBOX_WIDTH - MARIO_BIG_BBOX_WIDTH / 4.0f;
				}
				else if (mario->GetLevel() == 3)
				{
					x = mario->x + (float)MARIO_TAIL_BIG_BBOX_WIDTH -MARIO_BIG_BBOX_WIDTH/3.5f;
				}
				else
				{
					x = mario->x + (float)MARIO_BIG_BBOX_WIDTH - MARIO_BIG_BBOX_WIDTH / 4.0f;
				}
				/*if(mario ->GetLevel() >1)
					x = mario->x + MARIO_BIG_BBOX_WIDTH- MARIO_BIG_BBOX_WIDTH/4;
				else
					x = mario->x + MARIO_BIG_BBOX_WIDTH;*/
			}
			else if (mario->vx < 0)
			{
				if (mario->GetLevel() == 1)
				{
					x = mario->x - (float)TURLE_BBOX_WIDTH + MARIO_BIG_BBOX_WIDTH / 3.5f;
				}
				else if (mario->GetLevel() == 3)
				{
					x = mario->x - (float)TURLE_BBOX_WIDTH + MARIO_BIG_BBOX_WIDTH / 3.5f;
				}
				else
				{
					x = mario->x - (float)TURLE_BBOX_WIDTH + MARIO_BIG_BBOX_WIDTH / 4.0f;
				}
				/*if (mario->GetLevel() > 1)
					x = mario->x - TURLE_BBOX_WIDTH+ MARIO_BIG_BBOX_WIDTH /4;
				else
				x = mario->x - TURLE_BBOX_WIDTH;*/
			}

			if (mario->GetLevel() > 1)
				y = mario->y + MARIO_BIG_BBOX_WIDTH/3.5f;
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

		// block every object first!
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		//if (nx != 0) vx = 0;
		//if (ny != 0) vy = 0;

		

		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			
			if (ny < 0 && e->obj != NULL && GetState() == TURLE_STATE_FLY)
			{
				vy = -0.1f;
				vx = -0.06f;
			}
			else if (ny < 0 && e->obj != NULL)
			{
				vy = 0;
			}

			
			
			else if (dynamic_cast<CGoomba *>(e->obj)) // if e->obj is brickTop
			{
				//x += dx;
				//if (e->nx != 0)
					//isNoCollision = true;
				CGoomba *goomba = dynamic_cast<CGoomba *>(e->obj);
				if (e->nx != 0)
				{
					
					/*if (goomba->GetState() != GOOMBA_STATE_DIE)
					{*/
						goomba->SetState(GOOMBA_STATE_REVERSE_DIE);
						goomba->y += -0.01f;
					//}
				}
				

			}
			if (dynamic_cast<CBrick *>(e->obj)) // if e->obj is brickTop
			{
				CBrick *brick = dynamic_cast<CBrick *>(e->obj);			//LOI THUAT TOAN CU CHUA FIX !!!!!.
				if (GetState() == TURLE_STATE_WALKING)
				{
					if (x + 5 >= brick->xStatic + brick->GetBoundPosition(brick->type)
						|| x+5 <= brick->xStatic
						)
					{
						if (vx > 0)
							x = x - 5;				//loai bo truong hop rua dao chieu tai cho gay ra loi
						else
							x = x + 5;
						vx = -vx;
					}
				}
				if (nx != 0)
					vx = -vx;

				if (brick->type == 10 && nx != 0 && GetState() == TURLE_STATE_RUN_DIE)
					brick->y = 600;
			}
			
			if (dynamic_cast<CBrickQuestion *>(e->obj)) // if e->obj is brickTop
			{
				CBrickQuestion* brickQuestion = dynamic_cast<CBrickQuestion *>(e->obj);
				if (!brickQuestion->isDie)				//chua va cham lan nao
				{
					brickQuestion->SetMove(true);
				}
				x -= 2.0f;
				//vx = -vx;
				//x += dx;
				
				/*if (GetState() == TURLE_STATE_RUN_DIE)
					isNoCollision = false;*/
				/*if (e->nx != 0)
					isNoCollision = false;*/
			}
			if (dynamic_cast<CLeaf *>(e->obj)) // if e->obj is question box
			{
				CLeaf* leaf = dynamic_cast<CLeaf *>(e->obj);
				if (e->nx != 0)
				{
					leaf->y = y - 40;
					//if(leaf ->y > y -30)			//la roi muot hon
					//	leaf->vy = -0.02f;
					leaf->isMove = true;
					vx = -vx;
				}


			} // if question box
			if (dynamic_cast<CCOL *>(e->obj)) // if e->obj is question box
			{
				y -= 5;
				level = TURLE_LEVEL_SMALL;
				isReverse = true;
				vy = -0.3f;
				SetState(TURLE_STATE_DIE);

			} // if question col
			
			if (dynamic_cast<CBrickTop *>(e->obj)) // if e->obj is brickTop
			{
				CBrickTop *brickTop = dynamic_cast<CBrickTop *>(e->obj);
				if (GetState() == TURLE_STATE_WALKING)
				{
					if (x+10>= brickTop->xStatic + brickTop->GetBoundPosition(brickTop->type) 
						|| x <= brickTop->xStatic
						)
					{
						if(vx > 0)
							x = x - 5;				//loai bo truong hop rua dao chieu tai cho gay ra loi
						else
							x = x + 5;
						vx = -vx;
					}
					else
					{
						x += dx;
						isNoCollision = true;
					}
				}
				else
				{
					x += dx;
					isNoCollision = true;
				}
				

			}
			//if (dynamic_cast<CBrick *>(e->obj)) // if e->obj is Backgroud die
			//{
			//	CBrick* brick = dynamic_cast<CBrick *>(e->obj);

			//	if (brick->type == 10 && nx != 0)
			//		brick->y = 600;
			//	//x += dx;
			//	//if(!checkMarioColision)
			//	//y += dy;		
			//} // if brickTop
			
		}

	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CTurle::Render()
{
	if(level == TURLE_LEVEL_NO_FLY)								//rua chay xanh
	{
		if (color == 1)
		{
			if (vx > 0) ani = TURLE_ANI_WALKING_RIGHT;
			else if (vx <= 0) ani = TURLE_ANI_WALKING_LEFT;
		}
		else
		{
			if (vx > 0) ani = TURLE_ANI_RED_WALKING_RIGHT;
			else if (vx <= 0) ani = TURLE_ANI_RED_WALKING_LEFT;
		}
		
	}
	else if (level == TURLE_LEVEL_SMALL)							//mai rua xanh
	{
		if (color == 1)
		{
			if (this->GetState() == TURLE_STATE_DIE)
			{
				ani = TURLE_ANI_DIE;
			}
			else if (this->GetState() == TURLE_STATE_RUN_DIE) {
				ani = TURLE_ANI_RUN_DIE;
			}
		}
		else
		{
			if (this->GetState() == TURLE_STATE_DIE)
			{
				ani = TURLE_ANI_RED_DIE;
			}
			else if (this->GetState() == TURLE_STATE_RUN_DIE) {
				ani = TURLE_ANI_RED_RUN_DIE;
			}
		}
		
	}
	else if (level == TURLE_LEVEL_FLY)							//rua xanh co canh
	{
		if (color == 1)
		{
			if (this->GetState() == TURLE_STATE_FLY)
			{
				ani = TURLE_ANI_FLY;
			}
		}
		

	}

	animation_set->at(ani)->Render(x, y,255,isReverse);

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
	case TURLE_STATE_STOP:
		vx = 0;
		vy = 0;
		break;
	case TURLE_STATE_WALKING:
	{
		if (nxx > 0)
		{
			vx = TURLE_WALKING_SPEED;
		}
		else
			vx = -TURLE_WALKING_SPEED;
	}
		break;
	case TURLE_STATE_RUN_DIE:
		//vx = -TURLE_WALKING_SPEED;
		break;
	case TURLE_STATE_DIE_OVER:
		//vx = 0;
		//vy = 0;
		break;
	case TURLE_STATE_FLY:
		//if(checkCollision)
			//vy = -0.1f;
		//vx = -0.06f;
		break;
	case TURLE_STATE_REVERSE_DIE:
		isReverse = true;
		break;
	}

}