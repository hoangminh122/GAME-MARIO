#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Portal.h"
#include "BrickTop.h"
#include "QuestionBox.h"
#include "Bullet.h"
#include "CMushroom.h"
#include "Plant.h"
#include "Turle.h"
#include "BulletMario.h"

int CMario::level = 1;
bool CMario::isDropTurle = false;
float CMario::vxx = 0.0f;
int CMario::nxx = 0;
float CMario::vyy = 0.0f;
bool CMario::isHoldTurtle = false;
float CMario::xx = 0.0f;
float CMario::yy = 0.0f;
int CMario::energyFly = 20;
bool CMario::kick = false;
bool CMario::isRotatory = false;
float CMario::positionXIdle = 0;
bool CMario::isFire = false;
float CMario::xRealTime = 0;
bool CMario::isBullet = false;
CMario::CMario(float x, float y) : CGameObject()
{
	levelBefore = 1;
	//this->CheckToMap(test->game_map_);
	level = MARIO_LEVEL_SMALL;
//	level = MARIO_LEVEL_BIG;
	//level = MARIO_LEVEL_TAIL_BIG;
	untouchable = 0;
	SetState(MARIO_STATE_IDLE);

	start_x = x; 
	start_y = y; 
	this->x = x; 
	this->y = y; 
	checkMarioColision = false;
	//ani = MARIO_ANI_SMALL_IDLE_RIGHT;
	 ani= MARIO_ANI_BIG_IDLE_LEFT;
	//ani = MARIO_ANI_BIG_TAIL_IDLE_LEFT;
	//positionXIdle = 0;
	isStateFly = false;
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	if(isHoldTurtle)						//xu ly vi tri mario cam rua chay 
	{
		if (state == MARIO_STATE_IDLE)
		{
			if (vx > 0)
			{
				xx = this->x;
				yy = this->y;
			}
			
		}
		else if (state == MARIO_STATE_WALKING_RIGHT)
		{
				xx = this->x;
				yy = this->y;
		}
		else if (state == MARIO_STATE_WALKING_LEFT)
		{
			xx = this->x - MARIO_BIG_BBOX_WIDTH;
			yy = this->y;
		}

	}
	// Simple fall down
	vy += MARIO_GRAVITY*dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state!=MARIO_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	// No collision occured, proceed normally
	if (coEvents.size()==0)
	{
		xRealTime = x;
		checkMarioColision = false;
		x += dx; 
		y += dy;
	}
	else
	{
		checkMarioColision = true;									//mario co va cham
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0; 
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
		//if (rdx != 0 && rdx!=dx)
		//	x += nx*abs(rdx); 
		
		// block every object first!
		x += min_tx*dx + nx*0.4f;
		y += min_ty*dy + ny*0.4f;

		if (nx!=0) vx = 0;
		if (ny!=0) vy = 0;


		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			
			if (dynamic_cast<CMushroom *>(e->obj)) // if e->obj is mushroom
			{
				DebugOut(L"kill nam");
				CMushroom *mushroom = dynamic_cast<CMushroom *>(e->obj);
				mushroom->isDie = true;
				/*mushroom->x = -17;
				mushroom->y = -17;*/
				if (mushroom->ani == LEAF_GREEN_ANI)
				{
					DebugOut(L"an nam ssssssssssssssssssssssssssssssssssssssssss\n");

					if (level == MARIO_LEVEL_SMALL)
					{
						level = MARIO_LEVEL_BIG;
					}
					else if (level = MARIO_LEVEL_BIG)
					{
						level = MARIO_LEVEL_TAIL_BIG;
					}
					
				}
				else if (mushroom->ani == MUSHROOM_ANI)
				{
					this->y = 286;
					this->level = MARIO_LEVEL_BIG;
				}
				
			} // if mushroom
			else if (dynamic_cast<CPlant *>(e->obj)) // if e->obj is plant
			{
				if (level > MARIO_LEVEL_SMALL)
				{
					level = MARIO_LEVEL_SMALL;
				}
				else 
					SetState(MARIO_STATE_DIE);

				
			} // if plant
			else if (dynamic_cast<CGoomba *>(e->obj)) // if e->obj is Goomba 
			{
				
				CGoomba *goomba = dynamic_cast<CGoomba *>(e->obj);

				// jump on top >> kill Goomba and deflect a bit 
				if (e->ny < 0)
				{
					

					if (goomba->GetState()!= GOOMBA_STATE_DIE)
					{
						goomba->SetState(GOOMBA_STATE_DIE);
						vy = -MARIO_JUMP_DEFLECT_SPEED;
					}
				}
				else if (e->nx != 0)
				{
					DebugOut(L"gomga nx %d,mario nx %f\n",goomba->nx,this->nxx);
					if (this->state == MARIO_STATE_ROTATORY_IDLE && goomba->nx != this->nxx )
					{
						if (goomba->GetState() != GOOMBA_STATE_DIE)
						{
							goomba->SetState(GOOMBA_STATE_REVERSE_DIE);
							vy = -MARIO_JUMP_DEFLECT_SPEED;
							untouchable = -1;

						}

					}
					if (untouchable==0)
					{
						if (goomba->GetState()!=GOOMBA_STATE_DIE)
						{
							if (level > MARIO_LEVEL_SMALL)
							{
								level = MARIO_LEVEL_SMALL;
							}
							else 
								SetState(MARIO_STATE_DIE);
						}
					}
				}
			} // if Goomba
			else if (dynamic_cast<CBullet *>(e->obj)) // if e->obj is Bullet
			{
				DebugOut(L" dan ban trung%d\n",this->level);
				if (level > MARIO_LEVEL_SMALL)
				{
					DebugOut(L" dan ban trung level %d\n",this->level);
					level = MARIO_LEVEL_SMALL;
					//StartUntouchable();
				}
				else
					SetState(MARIO_STATE_DIE);

			} // if bullet dan bay
			else if (dynamic_cast<CQuestion *>(e->obj)) // if e->obj is Question 
			{
				if (e->ny > 0)
				{
					CQuestion *question = dynamic_cast<CQuestion *>(e->obj);

					question->isQuestion = false;
					//xet position mushrooom
					CMushroom::xBox = question->x;
					CMushroom::yBox = question->y;
					if (question->x == 220)
					{
						CMushroom* mushroom = CMushroom::GetInstance();
						CMushroom::isStart = true;
						CMushroom::isRun = true;
						//mushroom->SetState(MUSHROOM_STATE);

						DebugOut(L" ccccc xuat hienc cccccccc :\n");

					}
					else
					{
						CMushroom::isMoney = true;
						DebugOut(L" ismoney ===true :\n");
					}

				}

				//question->isQuestion = false;
				//if (question -> x == 220)
				//	question -> ani = 2;
				//if (question -> ani == 2) {
				//	if (!question -> mushroomRun) 
				//	{
				//		question -> mushroomRun = true ;
				//	}
				//	else
				//	{
				//		//DebugOut(L" ccccc xuat hienc cccccccc :\n") ;
				//		question->delMushroom = true ;
				//		this->level = MARIO_LEVEL_BIG ;
				//		
				//		//delete question;
				//	}
				//}
				
			} // if box question
			else if (dynamic_cast<CBrickTop *>(e->obj)) // if e->obj is brickTop
			{
				//DebugOut(L" kill brick top");
				if (e->ny > 0)
					this->y = y - 0.5f;

			} // if brickTop
			else if (dynamic_cast<CTurle *>(e->obj)) // if e->obj is TURLE
			{
				CTurle *turle = dynamic_cast<CTurle *>(e->obj);
				if (e->ny < 0)
				{
					if (turle->state == TURLE_STATE_WALKING)
					{
						turle->x = this->x;
						turle->y = this->y;

						this->x -= 28;
						this->y -= 2;

						this->vy = -0.4f;
						DebugOut(L" kill CON RUA");
						turle->SetState(TURLE_STATE_DIE);
					}
					else
					{
						;
					}
					
				}
				else if (e->nx != 0)
				{
					/*if (this->nx > 0)
						vx = 0.01f;
					else
						vx = -0.01f;*/
					if (turle->ani == TURLE_ANI_DIE)
					{
						DebugOut(L"555555555555555555555\n");
						//turle->SetState(TURLE_STATE_RUN_DIE);
						if (kick == true)
						{
							this->vx = 0.015;
							turle->SetState(TURLE_STATE_RUN_DIE);
						}
						else if (this->GetState() == MARIO_STATE_HOLD_TURTLE)
						{
							
							isHoldTurtle = true;
							turle->isHold = true;
							DebugOut(L"shgsdhgdhfg state%d\n",this->state);
						}
						//this->kick = true;
						//this->SetState(MARIO_STATE_KICK);
					}
					else
					{
						DebugOut(L"kill 2");
						if (untouchable == 0)
						{
							if (turle->GetState() != TURLE_STATE_DIE)
							{
								if (level > MARIO_LEVEL_SMALL)
								{
									level = MARIO_LEVEL_SMALL;
									StartUntouchable();
								}
								else
									SetState(MARIO_STATE_DIE);
							}
						}
					}

					
				}


			} // if TURLE
			
			
			else if (dynamic_cast<CPortal *>(e->obj))
			{
				CPortal *p = dynamic_cast<CPortal *>(e->obj);
				CGame::GetInstance()->SwitchScene(p->GetSceneId());
			}
		}
	
}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	//Map* map = new Map();
	
}

void CMario::Render()
{
	/*int ani = MARIO_ANI_SMALL_IDLE_RIGHT; */            
	if (state == MARIO_STATE_DIE)
		ani = MARIO_ANI_DIE;
	else if (level == MARIO_LEVEL_BIG)
	{
		if (vx == 0)
		{
			if (nx > 0) {


				if (state == MARIO_STATE_KICK && kick == true) {
					ani = MARIO_ANI_BIG_KICK_RIGHT;
				}
				else if (state == MARIO_STATE_DOWN)
				{
					ani = MARIO_ANI_BIG_DOWN_RIGHT;
				}
				else if (state == MARIO_STATE_JUMP) {
					ani = MARIO_ANI_BIG_JUMP_RIGHT;
				}
				else if (state == MARIO_STATE_HOLD_TURTLE) {
					ani = MARIO_ANI_BIG_HOLD_TURTLE_RIGHT;
				}
				else {
					DebugOut(L"trang thai %d\n",state);
					ani = MARIO_ANI_BIG_IDLE_RIGHT;

				}
				/*
				try {
					if (state == MARIO_STATE_JUMP) {
						DebugOut(L"vao day jump");
						ani = MARIO_ANI_SMALL_JUMP_LEFT;
					}
				}
				catch (exception e) { ; }*/

			}
			else
			{
				if (state == MARIO_STATE_KICK) {
					DebugOut(L"da rua 2222");
					ani = MARIO_ANI_BIG_KICK_RIGHT;
				}
				else if (state == MARIO_STATE_DOWN)
				{
					ani = MARIO_ANI_BIG_DOWN_LEFT;
				}
				else if (state == MARIO_STATE_HOLD_TURTLE) {
					ani = MARIO_ANI_BIG_HOLD_TURTLE_LEFT;
				}
				else if (state == MARIO_STATE_JUMP) {
					ani = MARIO_ANI_BIG_JUMP_LEFT;
				}
				else
				{
					ani = MARIO_ANI_BIG_IDLE_LEFT;

				}
			}
		}
		else if (vx > 0)
		{
			nxx = 1;
			DebugOut(L"vao111");
			if (state == MARIO_STATE_JUMP && checkMarioColision == false)                    //ANI JUMP RIGHT
				ani = MARIO_ANI_BIG_FIRE_JUMP_RIGHT;
			else if (state == MARIO_STATE_RUN_RIGHT)
			{
				ani = MARIO_ANI_BIG_RUN_RIGHT;
			}
			else if (state == MARIO_STATE_HOLD_TURTLE) {
				ani = MARIO_ANI_BIG_HOLD_TURTLE_RIGHT;
			}
			else if (state == MARIO_STATE_KICK && kick == true) {
				ani = MARIO_ANI_BIG_KICK_RIGHT;
			}
			else
			{
				ani = MARIO_ANI_BIG_WALKING_RIGHT;
			}
				
		}
		else
		{
			nxx = -1;
			DebugOut(L"vao2222");
			if (state == MARIO_STATE_JUMP && checkMarioColision == false)				   //ANI JUMP LEFT
				ani = MARIO_ANI_BIG_JUMP_LEFT;
			else if (state == MARIO_STATE_RUN_LEFT)
			{
				ani = MARIO_ANI_BIG_RUN_LEFT;
			}
			else if (state == MARIO_STATE_HOLD_TURTLE) {
				ani = MARIO_ANI_BIG_HOLD_TURTLE_LEFT;
			}
			else
			{
				ani = MARIO_ANI_BIG_WALKING_LEFT;
			}
		}
	}
	else if (level == MARIO_LEVEL_FIRE_BIG)
	{
		if (vx == 0)
		{
			if (nx > 0) {
				if (state == MARIO_STATE_JUMP) {
					ani = MARIO_ANI_BIG_FIRE_JUMP_RIGHT;
				}
				else if (state == MARIO_STATE_BULLET_IDLE)	//isBullet ==false :kiem tra truong hop mario khong state run,jump
				{
					//set position dan mario
					CBulletMario::nxBullet = 1;
					CBulletMario::isStart = true;
					CBulletMario::isSetPosition = true;
					this->GetPosition(CBulletMario::x0, CBulletMario :: y0);
					ani = MARIO_ANI_BIG_FIRE_BULLET_RIGHT;
				}
				
				else {
					ani = MARIO_ANI_BIG_FIRE_RIGHT;
				}

			}
			else
			{
				if (state == MARIO_STATE_JUMP) {
					ani = MARIO_ANI_BIG_FIRE_JUMP_LEFT;
				}
				
				else if (state == MARIO_STATE_BULLET_IDLE)
				{
					//set position dan mario
					CBulletMario::nxBullet = -1;
					CBulletMario::isStart = true;
					CBulletMario::isSetPosition = true;
					this->GetPosition(CBulletMario::x0, CBulletMario::y0);
					ani = MARIO_ANI_BIG_FIRE_BULLET_LEFT;
				}
				else
				{
					ani = MARIO_ANI_BIG_FIRE_LEFT;
					
				}
			}
		}
		else if (vx > 0)
		{
			nxx = 1;								//mario huong ben phai

			/*if (isBullet) {
				CBulletMario::nxBullet = 1;
				CBulletMario::isStart = true;
				CBulletMario::isSetPosition = true;
				this->GetPosition(CBulletMario::x0, CBulletMario::y0);
			}*/
			if (state == MARIO_STATE_JUMP && checkMarioColision == false)                    //ANI JUMP RIGHT
				ani = MARIO_ANI_BIG_FIRE_JUMP_RIGHT;
			else if (state == MARIO_STATE_RUN_RIGHT)
			{
				ani = MARIO_ANI_BIG_FIRE_RUN_RIGHT;
			}
			else
				ani = MARIO_ANI_BIG_FIRE_WALKING_RIGHT;
		}
		else
		{
			nxx = -1;          //mario huong ben trai

			/*if (isBullet) {
				CBulletMario::nxBullet = -1;
				CBulletMario::isStart = true;
				CBulletMario::isSetPosition = true;
				this->GetPosition(CBulletMario::x0, CBulletMario::y0);
			}*/
			if (state == MARIO_STATE_JUMP && checkMarioColision == false)				   //ANI JUMP LEFT
				ani = MARIO_ANI_BIG_FIRE_JUMP_LEFT;
			else if (state == MARIO_STATE_RUN_LEFT)
			{
					ani = MARIO_ANI_BIG_FIRE_RUN_LEFT;
			}
			else
				ani = MARIO_ANI_BIG_FIRE_WALKING_LEFT;
		}

		//ani = MARIO_ANI_BIG_TAIL_IDLE_RIGHT;
	}
	else if (level == MARIO_LEVEL_TAIL_BIG)
	{
	if (vx == 0)
	{
		if (nx > 0) {
			if (state == MARIO_STATE_JUMP) {
				ani = MARIO_ANI_BIG_TAIL_JUMP_RIGHT;
			}
			else if (state == MARIO_STATE_FLY)
			{
				ani = MARIO_ANI_BIG_TAIL_FLY_RIGHT;
			}
			else if (state == MARIO_STATE_ROTATORY_IDLE)
			{
				isRotatory = true;
				this->x = positionXIdle + 6;
				ani = MARIO_ANI_BIG_TAIL_ROTATORY_LEFT;
				//this->x -= 6;
			}
			else if (state == MARIO_STATE_DOWN)
			{
				ani = MARIO_ANI_BIG_TAIL_DOWN_RIGHT;
			}
			else {
				
				if(this->isStateFly == true && checkMarioColision == false)
					ani = MARIO_ANI_BIG_TAIL_FLY_FALLING_RIGHT;
				else
				{
					this->isStateFly == false;
					positionXIdle = x;
					ani = MARIO_ANI_BIG_TAIL_IDLE_RIGHT;
					if (isRotatory)
					{
						this->x = positionXIdle - 6;
						isRotatory = false;

					}
				}
				
			}

		}
		else
		{
			if (state == MARIO_STATE_JUMP) {
				ani = MARIO_ANI_BIG_TAIL_JUMP_LEFT;
			}
			else if (state == MARIO_STATE_FLY)
			{
				ani = MARIO_ANI_BIG_TAIL_FLY_LEFT;
			}
			else if (state == MARIO_STATE_DOWN)
			{
				ani = MARIO_ANI_BIG_TAIL_DOWN_LEFT;
			}
			else if (state == MARIO_STATE_ROTATORY_IDLE)
			{
				isRotatory = true;
				this->x = positionXIdle - 6;
				ani = MARIO_ANI_BIG_TAIL_ROTATORY_RIGHT;
				//this->x -= 6;
			}
			else
			{
				positionXIdle = x;
				ani = MARIO_ANI_BIG_TAIL_IDLE_LEFT;
				if (isRotatory)
				{
					this->x = positionXIdle + 6;
					isRotatory = false;

				}
			}
		}
	}
	else if (vx > 0)
	{
		if (state == MARIO_STATE_JUMP && checkMarioColision == false)                    //ANI JUMP RIGHT
			ani = MARIO_ANI_BIG_TAIL_JUMP_RIGHT;
		else if (state == MARIO_STATE_RUN_RIGHT)
		{
			positionXIdle = x;
			ani = MARIO_ANI_BIG_TAIL_RUN_RIGHT;
		}
		else if (state == MARIO_STATE_ROTATORY_IDLE)
		{
			isRotatory = true;
			this->x = positionXIdle + 6;
			ani = MARIO_ANI_BIG_TAIL_ROTATORY_RIGHT;
			//this->x -= 6;
		}
		else if (state == MARIO_STATE_FLY && checkMarioColision == false)
		{
			if (this->energyFly > 20)
				ani = MARIO_ANI_BIG_TAIL_FLY_RIGHT;
			else
				ani = MARIO_ANI_BIG_TAIL_FLY_LIMIT_RIGHT;
		}
		else
		{
			positionXIdle = x;
			ani = MARIO_ANI_BIG_TAIL_WALKING_RIGHT;
			if (isRotatory)
			{
				this->x = positionXIdle - 6;
				isRotatory = false;

			}

		}
	}
	else
	{
		if (state == MARIO_STATE_JUMP && checkMarioColision == false)				   //ANI JUMP LEFT
			ani = MARIO_ANI_BIG_TAIL_JUMP_LEFT;
		else if (state == MARIO_STATE_RUN_LEFT)
		{
			positionXIdle = x;
			ani = MARIO_ANI_BIG_TAIL_RUN_LEFT;
		}
		else if (state == MARIO_STATE_ROTATORY_IDLE)
		{
			isRotatory = true;
			this->x = positionXIdle - 6;
			ani = MARIO_ANI_BIG_TAIL_ROTATORY_RIGHT;
			//this->x -= 6;
		}
		else if (state == MARIO_STATE_FLY && checkMarioColision == false)
		{

			if (this->energyFly > 20)
				ani = MARIO_ANI_BIG_TAIL_FLY_LEFT;
			else
				ani = MARIO_ANI_BIG_TAIL_FLY_LIMIT_LEFT;
		}
		else
		{
			positionXIdle = x;
			ani = MARIO_ANI_BIG_TAIL_WALKING_LEFT;
			if (isRotatory)
			{
				this->x = positionXIdle + 6;
				isRotatory = false;

			}
		}
	}

	//ani = MARIO_ANI_BIG_TAIL_IDLE_RIGHT;
	}
	else if (level == MARIO_LEVEL_SMALL)
	{
		if (vx == 0)
		{
			//DebugOut(L"vao1111%d",state);
			/*if (state == MARIO_STATE_JUMP) {
				DebugOut(L"vaossssss");
				ani = MARIO_ANI_SMALL_JUMP_RIGHT;
			}*/
			if (nx > 0) {
				if (state == MARIO_STATE_JUMP) {
					ani = MARIO_ANI_SMALL_JUMP_RIGHT;
				}
				else
					ani = MARIO_ANI_SMALL_IDLE_RIGHT;
				/*
				try {
					if (state == MARIO_STATE_JUMP) {
						DebugOut(L"vao day jump");
						ani = MARIO_ANI_SMALL_JUMP_LEFT;
					}
				}
				catch (exception e) { ; }*/
				
			}
			else 
			{
				if (state == MARIO_STATE_JUMP) {
					ani = MARIO_ANI_SMALL_JUMP_LEFT;
				}
				else
					ani = MARIO_ANI_SMALL_IDLE_LEFT;
			}
		}
		else if (vx > 0) 
		{
			
			if(state == MARIO_STATE_JUMP && checkMarioColision == false)                    //ANI JUMP RIGHT
				ani = MARIO_ANI_SMALL_JUMP_RIGHT;
			else if (state == MARIO_STATE_RUN_RIGHT)
			{
				ani = MARIO_ANI_SMALL_RUN_RIGHT;
			}
			else
				ani = MARIO_ANI_SMALL_WALKING_RIGHT;
		}
		else 
		{
			if (state == MARIO_STATE_JUMP && checkMarioColision == false)				   //ANI JUMP LEFT
				ani = MARIO_ANI_SMALL_JUMP_LEFT;
			else if (state == MARIO_STATE_RUN_LEFT)
			{
				ani = MARIO_ANI_SMALL_RUN_LEFT;
			}
			else
				ani = MARIO_ANI_SMALL_WALKING_LEFT;
		}
	}

	int alpha = 255;
	if (untouchable) alpha = 128;

	animation_set->at(ani)->Render(x, y, alpha);

	RenderBoundingBox();
}

void CMario::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case MARIO_STATE_WALKING_RIGHT:
		vx = MARIO_WALKING_SPEED;
		nx = 1;
		nxx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT: 
		vx = -MARIO_WALKING_SPEED;
		nx = -1;
		nxx = -1;
		break;
	case MARIO_STATE_RUN_LEFT:
		vx = -0.2f;
		nx = -1;
		nxx = -1;
		break;
	case MARIO_STATE_RUN_RIGHT:
		vx = 0.2f;
		nx = 1;
		nxx = 1;
		break;
	case MARIO_STATE_JUMP:
		// TODO: need to check if Mario is *current* on a platform before allowing to jump again
		if (checkMarioColision == true) {
			//DebugOut(L"va cham");
			vy = -MARIO_JUMP_SPEED_Y;
			//vy = -0.7;
			break;
		}
		else 
		{
			//DebugOut(L" khong va cham");
			//vy = -0.1;//
			break;
		}
	case MARIO_STATE_IDLE: 
		vx = 0;
		break;
	case MARIO_STATE_BULLET_IDLE:
		vx = 0;
		break;
	case MARIO_STATE_DOWN:
		vx = 0;
		break;
	case MARIO_STATE_ROTATORY_IDLE:
		vx = 0;
		break;
	case MARIO_STATE_KICK:
		//vx = 0.01;
		break;
	case MARIO_STATE_HOLD_TURTLE:
		//vx = 0.01;
		break;
	case MARIO_STATE_FLY:
	{
		this->isStateFly = true;
		vy = -0.1f;
		if(nxx > 0)
			vx = 0.04f;
		else
			vx = -0.04f;
		break;
	}
		vy = -0.1f;
		vx = 0.04f;
		break;
	case MARIO_STATE_DIE:
		vy = -MARIO_DIE_DEFLECT_SPEED;
		break;
	}
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y; 
	/*right = x + MARIO_BIG_BBOX_WIDTH;
	bottom = y + MARIO_BIG_BBOX_HEIGHT;*/
	if (level == MARIO_LEVEL_BIG)
	{
		/*if (state == MARIO_STATE_KICK)
			right = x + MARIO_BIG_KICK_WIDTH;
		else*/
			right = x + MARIO_BIG_BBOX_WIDTH;
		if (state == MARIO_STATE_DOWN)
			bottom = y + MARIO_BIG_DOWN_BBOX_HEIGHT;
		else
			bottom = y + MARIO_BIG_BBOX_HEIGHT;
	}
	else if (level == MARIO_LEVEL_FIRE_BIG)
	{
		right = x + MARIO_BIG_BBOX_WIDTH;
		bottom = y + MARIO_BIG_BBOX_HEIGHT;
	}
	else if(level == MARIO_LEVEL_TAIL_BIG)
	{
		right = x + MARIO_BIG_BBOX_WIDTH;
		bottom = y + MARIO_BIG_BBOX_HEIGHT;
		if (state == MARIO_STATE_DOWN)
			bottom = y + MARIO_TAIL_BIG_DOWN_BBOX_HEIGHT;
		else if (state == MARIO_STATE_ROTATORY_IDLE)
		{
			right = x + MARIO_TAIL_FLY_BIG_BBOX_WIDTH;
		}
		else
			bottom = y + MARIO_BIG_BBOX_HEIGHT;
	}
	else
	{
		right = x + MARIO_SMALL_BBOX_WIDTH;
		bottom = y + MARIO_SMALL_BBOX_HEIGHT;

	}
}

/*
	Reset Mario status to the beginning state of a scene
*/
void CMario::Reset()
{
	SetState(MARIO_STATE_IDLE);
	SetLevel(MARIO_LEVEL_BIG);
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}

