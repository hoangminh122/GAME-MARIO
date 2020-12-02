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
#include "Brick.h"
#include "WallTurle.h"
#include "BrickQuestion.h"
#include "MoneyIcon.h"
#include "Leaf.h"
#include "BackgroundDie.h"
#include "Brick.h"


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

CMario * CMario::__instance = NULL;
CMario *CMario::GetInstance(float x, float y)
{
	if (__instance == NULL) __instance = new CMario(x,y);
	return __instance;
}

CMario::CMario(float x, float y) : CGameObject()
{
	levelBefore = 1;
	//level = MARIO_LEVEL_SMALL;
//	level = MARIO_LEVEL_BIG;
	level = MARIO_LEVEL_BIG;
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
	jumpHigher = false;
	pressA = false;
	timeKickStart = 0;
	isHold = false;
	isMarioDropTurle = false;
	timeRotatoryStart = 0;
	isRotatory180 = false;
	timeWaitingAttackNext = 0;
	isAttackNext = true;
	isHasColBoxQues = true;
	timePrepareFly = 0;
	energyFull = false;
	timePrepareRunFast = 0;
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	//truong hop mario tha rua ko cam nua -> da luon
	if (isMarioDropTurle )
	{
		//timeKickStart = GetTickCount();   //TIME DA CUA MARIO
		SetState(MARIO_STATE_KICK);
	}

	//if(isHoldTurtle)						//xu ly vi tri mario cam rua chay 
	//{
	//	if (this->GetState() == MARIO_STATE_IDLE)
	//	{
	//		if (vx > 0)
	//		{
	//			xx = this->x;
	//			yy = this->y;
	//		}
	//		
	//	}

	//}
	//DebugOut(L"SHDGFDSGsssssssssssssss%f\n", vy);
	// Simple fall down
	/*if (vy >= -0.001f && vy <= 0)
		vy -= vy;*/

	/*if (vy >= -0.02f && vy <= 0 && checkMarioColision == false  && vy <0)
	{*/
		

	/*	DebugOut(L"SHDGFDSGssssssssssssssssssF\n");
		vy += -0.1f;

	}*/
	//if (GetTickCount() - timeWaitingAttackNext > 500 && timeWaitingAttackNext != 0 && GetLevel() == MARIO_LEVEL_TAIL_BIG)
	//{
	//	//isAttackNext = false;  //mario ko duoc phep tan cong next
	//	//if(GetState() != MARIO_STATE_RUN)
	//	//isRotatory180 = true;
	//}
	if (GetTickCount() - timePrepareRunFast > MARIO_RUN_FAST_TIME && timePrepareRunFast != 0)
	{
		SetState(MARIO_STATE_PREPARE_FLY);
		timePrepareRunFast = 0;
	}
	if (GetTickCount() - timePrepareFly > MARIO_RUN_FAST_TIME && timePrepareFly != 0)
	{
		energyFull = true;
		//SetState(MARIO_STATE_FLY);
		timePrepareFly = 0;
	}

	if (GetTickCount() - timeKickStart > MARIO_KICK_TIME && timeKickStart!=0)
	{
		SetState(MARIO_STATE_IDLE);
		isMarioDropTurle = false;  //mario da rua xong hoan tat
		timeKickStart = 0;
	}
	if (GetTickCount() - timeRotatoryStart < 220 && timeRotatoryStart != 0)
	{
		SetState(MARIO_STATE_ROTATORY_IDLE);
	}
	else if (GetLevel() == MARIO_LEVEL_TAIL_BIG)
	{
		if(GetState() == MARIO_STATE_RUN)
			isRotatory180 = true;
		else
		{
			isRotatory180 = false;
			if(vx == 0.0f)									//chi co trang thai dung yen khi giu phim A ko xoay duoi dc
				SetState(MARIO_STATE_IDLE);
		}
	}

	if (this->isStateFly == true && checkMarioColision == false && this->energyFly < 20)
		//vy += 0.0009f*dt;
		vy += -0.07f;
	else
		vy += MARIO_GRAVITY * dt;
	/*else if (checkMarioColision == true)
	{

	}*/
	

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (this->GetState() !=MARIO_STATE_DIE)
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
		if (vy != 0)
			checkMarioColision = false;
		x += dx; 
		y += dy;
	}
	else
	{
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

		/*if (nx != 0)
		{
			vx = 0;
		}
		else if (ny != 0) {
			vy = 0;
		}*/

		
		if (ny < 0 && vy >= 0 )
		{
			checkMarioColision = true;
			jumpHigher = true;
			isHasColBoxQues = true;   //cham dat
		}
		

		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			
			//phan nay sua lai phan va cham voi vat the lam cho mario dung yen
			if (ny < 0)
			{
					vy = 0;
			}

			//di chuyen tren nen dat van toc khac 0:checkMarioColision == false
			if (nx != 0 && checkMarioColision == false)
			{
				vx = 0;
			}

			if (dynamic_cast<CWallTurle *>(e->obj)) // if e->obj is brickTop
			{
				if (e->nx != 0)
					x += dx;
				if (e->ny != 0)
					y += dy;
			}

			//if (dynamic_cast<CMushroom *>(e->obj)) // if e->obj is mushroom
			//{
			//	CMushroom *mushroom = dynamic_cast<CMushroom *>(e->obj);
			//	mushroom->isDie = true;
			//	/*mushroom->x = -17;
			//	mushroom->y = -17;*/
			//	if (mushroom->ani == LEAF_GREEN_ANI)
			//	{
			//		if (level == MARIO_LEVEL_SMALL)
			//		{
			//			level = MARIO_LEVEL_BIG;
			//		}
			//		else if (level = MARIO_LEVEL_BIG)
			//		{
			//			level = MARIO_LEVEL_TAIL_BIG;
			//		}
			//		
			//	}
			//	else if (mushroom->ani == MUSHROOM_ANI)
			//	{
			//		this->y = 286;
			//		this->level = MARIO_LEVEL_BIG;
			//	}
			//	
			//} // if mushroom
			else if (dynamic_cast<CPlant *>(e->obj)) // if e->obj is plant
			{
				if (GetLevel() < 1)
				{
					SetState(MARIO_STATE_DIE);
				}
				else
				{
					SetLevel(GetLevel() - 1);
				}

				
			} // if plant
			else if (dynamic_cast<CBrickQuestion *>(e->obj)) // if e->obj is question box
			{
				CBrickQuestion* brickQuestion = dynamic_cast<CBrickQuestion *>(e->obj);
				if (e->ny > 0)
				{
					brickQuestion->SetMove(true);
				}


			} // if question box
			else if (dynamic_cast<CMoneyIcon *>(e->obj)) // if e->obj is question box
			{
				CMoneyIcon* moneyIcon = dynamic_cast<CMoneyIcon *>(e->obj);
				if (e->ny > 0)
				{
					moneyIcon->SetMove(true);
				}


			} // if question box
			else if (dynamic_cast<CLeaf *>(e->obj)) // if e->obj is question box
			{
				CLeaf* leaf = dynamic_cast<CLeaf *>(e->obj);
					leaf->SetState(LEAF_STATE_DIE_OVER);
					if (GetLevel() == MARIO_LEVEL_SMALL)
						SetPosition(x, y - (MARIO_BIG_BBOX_HEIGHT + MARIO_SMALL_BBOX_HEIGHT));
					else
						SetPosition(x, y - 2);
					SetLevel(GetLevel() + 1);


			} // if question box
			else if (dynamic_cast<CGoomba *>(e->obj)) // if e->obj is Goomba 
			{
				
				CGoomba *goomba = dynamic_cast<CGoomba *>(e->obj);

				// jump on top >> kill Goomba and deflect a bit 
				if (e->ny < 0)
				{
					if (goomba->GetState()!= GOOMBA_STATE_DIE)
					{

						if (goomba->GetLevel() > 1)
						{
							goomba -> SetLevel(goomba->GetLevel() - 1);
							vy = -0.2f;
						}
						else
						{
							vy = -MARIO_JUMP_DEFLECT_SPEED;
							goomba->SetState(GOOMBA_STATE_DIE);
						}
					}
				}
				else if (e->nx != 0)
				{
					if (this->GetState() == MARIO_STATE_ROTATORY_IDLE && GetLevel() == MARIO_LEVEL_TAIL_BIG)
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
							if (GetLevel()>1)
							{
								vy = -0.001f;
								SetLevel(GetLevel() - 1);

							}
							else 
								SetState(MARIO_STATE_DIE);
						}
					}
				}
			} // if Goomba
			else if (dynamic_cast<CBullet *>(e->obj)) // if e->obj is Bullet
			{
				CBullet *bullet = dynamic_cast<CBullet *>(e->obj);
				if (bullet->GetState() != GOOMBA_STATE_DIE)
				{
					if (GetLevel() > 1)
					{
						vy = -0.001f;
						SetLevel(GetLevel() - 1);

					}
					else
						SetState(MARIO_STATE_DIE);
				}

			} // if bullet dan bay
			//
			//else if (dynamic_cast<CQuestion *>(e->obj)) // if e->obj is Question 
			//{
			//	if (e->ny > 0)
			//	{
			//		CQuestion *question = dynamic_cast<CQuestion *>(e->obj);

			//		question->isQuestion = false;
			//		//xet position mushrooom
			//		CMushroom::xBox = question->x;
			//		CMushroom::yBox = question->y;
			//		if (question->x == 220)
			//		{
			//			CMushroom* mushroom = CMushroom::GetInstance();
			//			CMushroom::isStart = true;
			//			CMushroom::isRun = true;
			//			//mushroom->SetState(MUSHROOM_STATE);


			//		}
			//		else
			//		{
			//			CMushroom::isMoney = true;
			//		}

			//	}

			//	//question->isQuestion = false;
			//	//if (question -> x == 220)
			//	//	question -> ani = 2;
			//	//if (question -> ani == 2) {
			//	//	if (!question -> mushroomRun) 
			//	//	{
			//	//		question -> mushroomRun = true ;
			//	//	}
			//	//	else
			//	//	{
			//	//		//DebugOut(L" ccccc xuat hienc cccccccc :\n") ;
			//	//		question->delMushroom = true ;
			//	//		this->level = MARIO_LEVEL_BIG ;
			//	//		
			//	//		//delete question;
			//	//	}
			//	//}
			//	
			//} // if box question
			else if (dynamic_cast<CBrickTop *>(e->obj)) // if e->obj is brickTop
			{
				if (e->ny > 0)
				{
					y += dy;
				}
				if (e -> nx != 0)
					x += dx;
					//vx +=dx;

			} // if brickTop
			//else if (dynamic_cast<CBackgroundDie *>(e->obj)) // if e->obj is Backgroud die
			//{
			//	x += dx;
			//	//if(!checkMarioColision)
			//	if(e->ny!=0)
			//		y += dy;
			//} // if brickTop
			//else if (dynamic_cast<CBrick *>(e->obj)) // if e->obj is Backgroud die
			//{
			//	
			////x += dx;
			////if(!checkMarioColision)
			//y += dy;
			//} // if brickTop
			else if (dynamic_cast<CMushroom *>(e->obj)) // if e->obj is Backgroud die
			{

				CMushroom* mushroom = dynamic_cast<CMushroom *>(e->obj);
				if (!mushroom->noMushroom)								//mario tang level
				{
					mushroom->SetState(MUSHROOM_STATE_DIE_OVER);
					mushroom->noMushroom = true;
					if (GetLevel() == MARIO_LEVEL_SMALL)
						SetPosition(x, y - (MARIO_BIG_BBOX_HEIGHT + MARIO_SMALL_BBOX_HEIGHT));
					else
						SetPosition(x,y-2);
					SetLevel(GetLevel() + 1);

				}
				else if (e->ny > 0)										//mario va cham huong len
				{
						mushroom->isMove = true;
				}
				

			} // if mushroom
			//va cham gach nen phai nam sau va cham brick top
			/*else if (dynamic_cast<CBrick *>(e->obj))
			{
			if (e->nx != 0)
				x += dx;
			}*/
			else if (dynamic_cast<CTurle *>(e->obj)) // if e->obj is TURLE
			{
				CTurle *turle = dynamic_cast<CTurle *>(e->obj);
				if (e->ny < 0)
				{
					if (turle->GetState() == TURLE_STATE_WALKING)
					{
						turle->x = this->x;
						turle->y = this->y;

						//mario nhay len 1 doan nho
						vy += -0.35f;
						vx += this->nx*0.15f;
						turle->timeDieTurle = GetTickCount();       //bat dau tinh time chet rua
						turle->SetState(TURLE_STATE_DIE);
					}
					else if (turle->GetState() == TURLE_STATE_DIE || turle->GetState() == TURLE_STATE_DIE_OVER)
					{
						//giam level mario
						SetLevel(GetLevel() - 1);
						if (GetLevel() < 1)
						{
							SetState(MARIO_STATE_DIE);
						}
					}


				}
				else if (e->nx != 0)
				{
					if (this->GetState() == MARIO_STATE_ROTATORY_IDLE && GetLevel() == MARIO_LEVEL_TAIL_BIG)
					{
						if (turle->GetState() != TURLE_STATE_REVERSE_DIE)
						{
							turle->SetState(TURLE_STATE_REVERSE_DIE);
							vy = -TURLE_JUMP_DEFLECT_SPEED;
							untouchable = -1;

						}

					}
					else if (GetLevel() < 1)
					{
						SetState(MARIO_STATE_DIE);
					}
					else
					{
						//truong hop mario gio chan da
						if (turle->GetState() == TURLE_STATE_DIE)
						{
							//trang thai cam rua
							if (pressA == true)
							{
								isHold = true;  //trang thai cam cua mario
								SetState(MARIO_STATE_HOLD_TURTLE);
								//set con rua dang duoc cam boi mario
								turle->isHold = true;
							}
							else
							{
								turle->timeRunTurle = GetTickCount();		//TIME CHAY CUA RUA
								timeKickStart = GetTickCount();   //TIME DA CUA MARIO
								SetState(MARIO_STATE_KICK);
								//rua chay theo chieu nguoc mario tranh va cham voi mario, chu y nx o day la trong ham va cham
								turle->vx = -nx * TURLE_RUN_SPEED;
								turle->SetState(TURLE_STATE_RUN_DIE);
							}
							
						}
						//truong hop binh thuong -> bi chet
						else
							SetLevel(GetLevel() - 1);
					}
					

					
				}
			}


			//	else if (e->nx != 0)
			//	{
			//		/*if (this->nx > 0)
			//			vx = 0.01f;
			//		else
			//			vx = -0.01f;*/
			//		if (turle->ani == TURLE_ANI_DIE)
			//		{
			//			//turle->SetState(TURLE_STATE_RUN_DIE);
			//			if (kick == true)
			//			{
			//				this->vx = 0.015;
			//				turle->SetState(TURLE_STATE_RUN_DIE);
			//			}
			//			else if (this->GetState() == MARIO_STATE_HOLD_TURTLE)
			//			{
			//				
			//				isHoldTurtle = true;
			//				turle->isHold = true;
			//			}
			//			//this->kick = true;
			//			//this->SetState(MARIO_STATE_KICK);
			//		}
			//		else
			//		{
			//			if (untouchable == 0)
			//			{
			//				if (turle->GetState() != TURLE_STATE_DIE)
			//				{
			//					if (level > MARIO_LEVEL_SMALL)
			//					{
			//						level = MARIO_LEVEL_SMALL;
			//						StartUntouchable();
			//					}
			//					else
			//						SetState(MARIO_STATE_DIE);
			//				}
			//			}
			//		}

			//		
			//	}


			//} // if TURLE
			//
			//mario ko va cham voi CWallTurle
			
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
	if (this->GetState() == MARIO_STATE_DIE)
		ani = MARIO_ANI_DIE;
	else if (level == MARIO_LEVEL_BIG)
	{
		if (vx == 0)
		{
			if (nx > 0) {


				if (this->GetState() == MARIO_STATE_KICK) {
					ani = MARIO_ANI_BIG_KICK_RIGHT;
				}
				else if (this->GetState() == MARIO_STATE_DOWN)
				{
					ani = MARIO_ANI_BIG_DOWN_RIGHT;
				}
				else if (this->GetState() == MARIO_STATE_JUMP_NORMAL) {
					ani = MARIO_ANI_BIG_JUMP_RIGHT;
				}
				else if (this->GetState() == MARIO_STATE_HOLD_TURTLE) {
					ani = MARIO_ANI_BIG_HOLD_TURTLE_RIGHT;
				}
				else {
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
				if (this->GetState() == MARIO_STATE_KICK) {
					ani = MARIO_ANI_BIG_KICK_LEFT;
				}
				else if (this->GetState() == MARIO_STATE_DOWN)
				{
					ani = MARIO_ANI_BIG_DOWN_LEFT;
				}
				else if (this->GetState() == MARIO_STATE_JUMP_NORMAL) {
					ani = MARIO_ANI_BIG_JUMP_LEFT;
				}
				else if (this->GetState() == MARIO_STATE_HOLD_TURTLE) {
					ani = MARIO_ANI_BIG_HOLD_TURTLE_LEFT;
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
			if (this->GetState() == MARIO_STATE_JUMP_NORMAL && checkMarioColision == false)                    //ANI JUMP RIGHT
				ani = MARIO_ANI_BIG_JUMP_RIGHT;
			else if (this->GetState() == MARIO_STATE_BRAKE)
			{
				ani = MARIO_ANI_BIG_BRAKE_RIGHT;
			}
			
			else if (this->GetState() == MARIO_STATE_RUN_HOLD_TURTLE)		//TRANG THAI CAM RUA PHAI O TREN TRANG THAI CHAY -> MUC DO UU TIEN
			{
				ani = MARIO_ANI_BIG_RUN_HOLD_TURTLE_RIGHT;
			}
			else if (this->GetState() == MARIO_STATE_RUN)
			{
				ani = MARIO_ANI_BIG_RUN_RIGHT;
			}
			else if (this->GetState() == MARIO_STATE_PREPARE_FLY)
			{
				ani = MARIO_ANI_BIG_PREPARE_FLY_RIGHT;
			}
			else
			{
				ani = MARIO_ANI_BIG_WALKING_RIGHT;
			}
				
		}
		else
		{
			nxx = -1;
			if (this->GetState() == MARIO_STATE_JUMP_NORMAL && checkMarioColision == false)				   //ANI JUMP LEFT
				ani = MARIO_ANI_BIG_JUMP_LEFT;
			else if (this->GetState() == MARIO_STATE_BRAKE)
			{
				ani = MARIO_ANI_BIG_BRAKE_LEFT;
			}
			else if (this->GetState() == MARIO_STATE_PREPARE_FLY)
			{
				ani = MARIO_ANI_BIG_PREPARE_FLY_LEFT;
			}
			else if (this->GetState() == MARIO_STATE_RUN_HOLD_TURTLE)		//TRANG THAI CAM RUA PHAI O TREN TRANG THAI CHAY -> MUC DO UU TIEN
			{
				ani = MARIO_ANI_BIG_RUN_HOLD_TURTLE_LEFT;
			}
			else if (this->GetState() == MARIO_STATE_RUN)
			{
				ani = MARIO_ANI_BIG_RUN_LEFT;
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
				if (this->GetState() == MARIO_STATE_JUMP_NORMAL) {
					ani = MARIO_ANI_BIG_FIRE_JUMP_RIGHT;
				}
				if (this->GetState() == MARIO_STATE_KICK && kick == true) {
					ani = MARIO_ANI_BIG_FIRE_KICK_RIGHT;
				}
				else if (this->GetState() == MARIO_STATE_HOLD_TURTLE) {
					ani = MARIO_ANI_BIG_FIRE_HOLD_TURLE_RIGHT;
				}
				else if (this->GetState() == MARIO_STATE_BULLET_IDLE)	//isBullet ==false :kiem tra truong hop mario khong state run,jump
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
				if (this->GetState() == MARIO_STATE_JUMP_NORMAL) {
					ani = MARIO_ANI_BIG_FIRE_JUMP_LEFT;
				}
				else if (this->GetState() == MARIO_STATE_HOLD_TURTLE) {
					ani = MARIO_ANI_BIG_FIRE_HOLD_TURLE_LEFT;
				}
				else if (this->GetState() == MARIO_STATE_KICK && kick == true) {
					ani = MARIO_ANI_BIG_FIRE_KICK_LEFT;
				}
				else if (this->GetState() == MARIO_STATE_BULLET_IDLE)
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
			if (this->GetState() == MARIO_STATE_JUMP_NORMAL && checkMarioColision == false)                    //ANI JUMP RIGHT
				ani = MARIO_ANI_BIG_FIRE_JUMP_RIGHT;
			else if (this->GetState() == MARIO_STATE_KICK && kick == true) {
				ani = MARIO_ANI_BIG_FIRE_KICK_RIGHT;
			}
			else if (this->GetState() == MARIO_STATE_BRAKE)
				ani = MARIO_ANI_BIG_FIRE_BRAKE_RIGHT;
			else if (this->GetState() == MARIO_STATE_RUN)
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
			if (this->GetState() == MARIO_STATE_JUMP_NORMAL && checkMarioColision == false)				   //ANI JUMP LEFT
				ani = MARIO_ANI_BIG_FIRE_JUMP_LEFT;
			else if (this->GetState() == MARIO_STATE_KICK && kick == true) {
				ani = MARIO_ANI_BIG_FIRE_KICK_LEFT;
			}
			else if (this->GetState() == MARIO_STATE_BRAKE)
				ani = MARIO_ANI_BIG_FIRE_BRAKE_LEFT;
			else if (this->GetState() == MARIO_STATE_RUN)
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
			if (this->GetState() == MARIO_STATE_KICK) {
				ani = MARIO_ANI_BIG_TAIL_KICK_TURLE_RIGHT;
			}
			else if (this->GetState() == MARIO_STATE_JUMP_NORMAL) {
				ani = MARIO_ANI_BIG_TAIL_JUMP_RIGHT;
			}
			else if (this->GetState() == MARIO_STATE_FLY)
			{
				ani = MARIO_ANI_BIG_TAIL_FLY_RIGHT;
			}
			else if (this->GetState() == MARIO_STATE_KICK && kick == true) {
				ani = MARIO_ANI_BIG_TAIL_KICK_TURLE_RIGHT;
			}
			else if (this->GetState() == MARIO_STATE_ROTATORY_IDLE)
			{
				//isRotatory = true;
				//this->x = positionXIdle;
				ani = MARIO_ANI_BIG_TAIL_ATTACK_ROTATORY_RIGHT;
				//this->x -= 6;
			}
			else if (this->GetState() == MARIO_STATE_HOLD_TURTLE) {
				ani = MARIO_ANI_BIG_TAIL_HOLD_TURTLE_RIGHT;
			}
			else if (this->GetState() == MARIO_STATE_DOWN)
			{
				ani = MARIO_ANI_BIG_TAIL_DOWN_RIGHT;
			}
			else {
				
				if(this->isStateFly == true && checkMarioColision == false)
					ani = MARIO_ANI_BIG_TAIL_FLY_FALLING_RIGHT;
				else
				{
					//this->isStateFly == false;
					positionXIdle = x;
					ani = MARIO_ANI_BIG_TAIL_IDLE_RIGHT;
					/*if (isRotatory)
					{
						this->x = positionXIdle;
						isRotatory = false;

					}*/
				}
				
			}

		}
		else
		{
			if (this->GetState() == MARIO_STATE_KICK) {
				ani = MARIO_ANI_BIG_TAIL_KICK_TURLE_LEFT;
			}
			else if (this->GetState() == MARIO_STATE_JUMP_NORMAL) {
				ani = MARIO_ANI_BIG_TAIL_JUMP_LEFT;
			}
			else if (this->GetState() == MARIO_STATE_KICK && kick == true) {
				ani = MARIO_ANI_BIG_TAIL_KICK_TURLE_LEFT;
			}
			else if (this->GetState() == MARIO_STATE_FLY)
			{
				ani = MARIO_ANI_BIG_TAIL_FLY_LEFT;
			}
			else if (this->GetState() == MARIO_STATE_DOWN)
			{
				ani = MARIO_ANI_BIG_TAIL_DOWN_LEFT;
			}
			else if (this->GetState() == MARIO_STATE_ROTATORY_IDLE)
			{
				/*isRotatory = true;
				this->x = positionXIdle;*/
				ani = MARIO_ANI_BIG_TAIL_ATTACK_ROTATORY_LEFT;
				//this->x -= 6;
			}
			else if (this->GetState() == MARIO_STATE_HOLD_TURTLE) {
				ani = MARIO_ANI_BIG_TAIL_HOLD_TURTLE_LEFT;
			}
			else
			{
				//positionXIdle = x;
				ani = MARIO_ANI_BIG_TAIL_IDLE_LEFT;
				/*if (isRotatory)
				{
					this->x = positionXIdle;
					isRotatory = false;

				}*/
			}
		}
	}
	else if (vx > 0)
	{
		
		if (this->GetState() == MARIO_STATE_JUMP_NORMAL && checkMarioColision == false)                    //ANI JUMP RIGHT
			ani = MARIO_ANI_BIG_TAIL_JUMP_RIGHT;
		else if (this->GetState() == MARIO_STATE_ROTATORY_IDLE && this->GetLevel() == MARIO_LEVEL_TAIL_BIG)
		{
			ani = MARIO_ANI_BIG_TAIL_ATTACK_ROTATORY_RIGHT;
		}
		else if (this->GetState() == MARIO_STATE_RUN)
		{
			positionXIdle = x;
			ani = MARIO_ANI_BIG_TAIL_RUN_RIGHT;
		}
		else if (this->GetState() == MARIO_STATE_KICK && kick == true) {
			ani = MARIO_ANI_BIG_TAIL_KICK_TURLE_RIGHT;
		}
		else if (this->GetState() == MARIO_STATE_BRAKE)
			ani = MARIO_ANI_BIG_TAIL_BRAKE_RIGHT;
		else if (this->GetState() == MARIO_STATE_PREPARE_FLY)
		{
			ani = MARIO_ANI_BIG_TAIL_PREPARE_FLY_RIGHT;
		}
		else if (this->GetState() == MARIO_STATE_FLY && checkMarioColision == false)
		{
			if (this->energyFly > 20)
				ani = MARIO_ANI_BIG_TAIL_FLY_RIGHT;
			else
				ani = MARIO_ANI_BIG_TAIL_FLY_LIMIT_RIGHT;
		}
		else if (this->GetState() == MARIO_STATE_RUN_HOLD_TURTLE)		//TRANG THAI CAM RUA PHAI O TREN TRANG THAI CHAY -> MUC DO UU TIEN
		{
			ani = MARIO_ANI_BIG_TAIL_RUN_HOLD_TURTLE_RIGHT;
		}
		else
		{
			ani = MARIO_ANI_BIG_TAIL_WALKING_RIGHT;
		}
	}
	else
	{
		if (this->GetState() == MARIO_STATE_ROTATORY_IDLE)
		{
			ani = MARIO_ANI_BIG_TAIL_ATTACK_ROTATORY_RIGHT;
		}
		if (this->GetState() == MARIO_STATE_JUMP_NORMAL && checkMarioColision == false)				   //ANI JUMP LEFT
			ani = MARIO_ANI_BIG_TAIL_JUMP_LEFT;
		else if (this->GetState() == MARIO_STATE_RUN)
		{
			positionXIdle = x;
			ani = MARIO_ANI_BIG_TAIL_RUN_LEFT;
		}
		else if (this->GetState() == MARIO_STATE_BRAKE)
			ani = MARIO_ANI_BIG_TAIL_BRAKE_LEFT;
		else if (this->GetState() == MARIO_STATE_PREPARE_FLY)
		{
			ani = MARIO_ANI_BIG_TAIL_PREPARE_FLY_LEFT;
		}
		else if (this->GetState() == MARIO_STATE_KICK && kick == true) {
			ani = MARIO_ANI_BIG_TAIL_KICK_TURLE_LEFT;
		}
		else if (this->GetState() == MARIO_STATE_FLY && checkMarioColision == false)
		{

			if (this->energyFly > 20)
				ani = MARIO_ANI_BIG_TAIL_FLY_LEFT;
			else
				ani = MARIO_ANI_BIG_TAIL_FLY_LIMIT_LEFT;
		}
		else if (this->GetState() == MARIO_STATE_RUN_HOLD_TURTLE)		//TRANG THAI CAM RUA PHAI O TREN TRANG THAI CHAY -> MUC DO UU TIEN
		{
			ani = MARIO_ANI_BIG_TAIL_RUN_HOLD_TURTLE_LEFT;
		}
		else
		{
			ani = MARIO_ANI_BIG_TAIL_WALKING_LEFT;
		}
	}

	//ani = MARIO_ANI_BIG_TAIL_IDLE_RIGHT;
	}
	else if (level == MARIO_LEVEL_SMALL)
	{
		if (vx == 0)
		{
			if (nx > 0) {
				if (this->GetState() == MARIO_STATE_JUMP_NORMAL) {
					ani = MARIO_ANI_SMALL_JUMP_RIGHT;
				}
				else if (this->GetState() == MARIO_STATE_KICK) {
					ani = MARIO_ANI_SMALL_KICK_RIGHT;
				}
				else if (this->GetState() == MARIO_STATE_HOLD_TURTLE)
				{
					ani = MARIO_ANI_SMALL_HOLD_TURLE_RIGHT;
				}
				else
					ani = MARIO_ANI_SMALL_IDLE_RIGHT;
			}
			else 
			{
				if (this->GetState() == MARIO_STATE_JUMP_NORMAL) {
					ani = MARIO_ANI_SMALL_JUMP_LEFT;
				}
				else if (this->GetState() == MARIO_STATE_KICK) {
					ani = MARIO_ANI_SMALL_KICK_LEFT;
				}
				else if (this->GetState() == MARIO_STATE_HOLD_TURTLE)
				{
					ani = MARIO_ANI_SMALL_HOLD_TURLE_LEFT;
				}
				else
					ani = MARIO_ANI_SMALL_IDLE_LEFT;
			}
		}
		else if (vx > 0) 
		{
			
			if(this->GetState() == MARIO_STATE_JUMP_NORMAL && checkMarioColision == false)                    //ANI JUMP RIGHT
				ani = MARIO_ANI_SMALL_JUMP_RIGHT;
			else if(this->GetState() == MARIO_STATE_BRAKE)
				ani = MARIO_ANI_SMALL_BRAKE_RIGHT;
			else if (this->GetState() == MARIO_STATE_RUN_HOLD_TURTLE)
			{
				ani = MARIO_ANI_SMALL_RUN_HOLD_TURTLE_RIGHT;
			}
			else if (this->GetState() == MARIO_STATE_RUN)
			{
				ani = MARIO_ANI_SMALL_RUN_RIGHT;
			}
			else
				ani = MARIO_ANI_SMALL_WALKING_RIGHT;

		}
		else 
		{
			if (this->GetState() == MARIO_STATE_JUMP_NORMAL && checkMarioColision == false)				   //ANI JUMP LEFT
				ani = MARIO_ANI_SMALL_JUMP_LEFT;
			else if (this->GetState() == MARIO_STATE_BRAKE)
				ani = MARIO_ANI_SMALL_BRAKE_LEFT;
			else if (this->GetState() == MARIO_STATE_RUN_HOLD_TURTLE)
			{
				ani = MARIO_ANI_SMALL_RUN_HOLD_TURTLE_LEFT;
			}
			else if (this->GetState() == MARIO_STATE_RUN)
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
	case MARIO_STATE_WALKING:
		break; 
	case MARIO_STATE_RUN:
		break;
	case MARIO_STATE_JUMP_NORMAL:
		if(checkMarioColision == true && jumpHigher == true)
			vy = -MARIO_JUMP_SPEED_Y;
		break;
	case MARIO_STATE_IDLE:
		/*if(checkMarioColision == true)
			vy = 0;*/
		//vx = 0;
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
		vx = 0;
		break;
	case MARIO_STATE_HOLD_TURTLE:
		//vx = 0.01;
		//vx = 0;
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
		if (this->GetState() == MARIO_STATE_DOWN)
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
		right = x + MARIO_TAIL_BIG_BBOX_WIDTH;
		bottom = y + MARIO_TAIL_BIG_BBOX_HEIGHT;
		if (this->GetState() == MARIO_STATE_DOWN)
			bottom = y + MARIO_TAIL_BIG_DOWN_BBOX_HEIGHT;
		else if (this->GetState() == MARIO_STATE_ROTATORY_IDLE)
		{
			right = x + MARIO_TAIL_BIG_ATTACK_BBOX_HEIGHT;
		}
		else
			bottom = y + MARIO_TAIL_BIG_BBOX_HEIGHT;
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
	SetLevel(MARIO_LEVEL_TAIL_BIG);
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}

