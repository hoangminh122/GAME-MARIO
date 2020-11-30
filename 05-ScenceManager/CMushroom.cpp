#include "CMushroom.h"
#include "Turle.h"
#include "Utils.h"
#include "BrickTop.h"
#include "Brick.h"
#include "BrickQuestion.h"
#include "BackgroundDie.h"
#include "Plant.h"

CMushroom::CMushroom() : CGameObject()
{
	noMushroom = true;					//mush co 1 con ->khoi tao chua ra chuong
	isMove = false;
	isInitPos = false;						//trang thai chua khoi tao gia tri
	yStatic = y;						//ban dau chua gan gia tri y cho moshroom -> chu y de nham lan
	xStatic = x;
	SetState(MUSHROOM_STATE_DIE);
}
//CMushroom *CMushroom::GetInstance()
//{
//	if (__instance == NULL) __instance = new CMushroom();
//	return __instance;
//}
void CMushroom::Render()
{
	
	animation_set->at(0)->Render(x, y);
	RenderBoundingBox();

	/*if (this->GetState() == LEAF_GREEN_STATE)
		ani = 1;
	else if (this->GetState() == MONEY_STATE)
		ani = 2;
	else
		ani = 0;*/
}

void CMushroom::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + 17;
	b = y + 17;
}

void CMushroom::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);

	if (y != 0 && !isInitPos)
	{
		yStatic = y;
		xStatic = x;
		isInitPos = true;
	}
	else if (isMove)				//vij tri money ==vi tri mario va cham
	{
		vy = -0.02f ;
		if (y < yStatic- MUSHROOM_BBOX_HEIGHT-1)
		{
			noMushroom = false;			//co 1 com nam ->mario chuan bi bat
			int ramdom = rand() % ((1 - 0) + 1) + 0;  //ramdom 0 va 1 //rand()%((userEnd - userBeg) + 1) + userBeg; 
			if (ramdom == 0)
				vx = -0.1f;
			else
				vx = 0.1f;
			SetState(MUSHROOM_STATE_LIVE);
			isMove = false;
		}

	}
	if(GetState() == MUSHROOM_STATE_LIVE)
		vy += MOSHROOM_GRAVITY * dt;					//trong luc


	

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (this->GetState() == MUSHROOM_STATE_DIE_OVER)		//kiem tra xem vi tri da duoc khoi tao chua
	{
		x = xStatic;
		y = yStatic;
		vx = 0;
		vy = 0;
	}
	// turn off collision when die 
	else if (this->GetState() !=	MUSHROOM_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);
	

	// reset untouchable timer if untouchable time has passed

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		//check luc cam rua ko di chuyen
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
			if (e -> nx != 0 && e->obj != NULL  
				&& !dynamic_cast<CBrickTop *>(e->obj)
				&& !dynamic_cast<CBrick *>(e->obj)
				&& !dynamic_cast<CPlant *>(e->obj)
				)
			{
				vx = -vx;
			}
			else if (e->ny < 0 && dynamic_cast<CBackgroundDie *>(e->obj))	//va cham voi background Die
			{
				vx = -vx;
			}


			if (dynamic_cast<CBrickTop *>(e->obj)) // if e->obj is question box
			{
				CBrickTop* brickTop = dynamic_cast<CBrickTop *>(e->obj);
				if (e->nx != 0)
				{
					x += dx;
					vy += MOSHROOM_GRAVITY * dt;
				}


			} // if question box
			
			else if (dynamic_cast<CBrickQuestion *>(e->obj)) // if e->obj is question box
			{
				CBrickQuestion* brickQuestion = dynamic_cast<CBrickQuestion *>(e->obj);
				if (e->nx < 0 )
				{
					x += dx;
				}


			} // if question box
			else if (dynamic_cast<CBrick *>(e->obj)) // if e->obj is question box
			{
				CBrick* brick = dynamic_cast<CBrick *>(e->obj);
				if (e->ny > 0)
				{
					x += dx;
				}


			} // if question box

		}

	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	
	
}

void CMushroom::SetState(int state)
{
	CGameObject::SetState(state);
	/*switch (state)
	{
	
	case MUSHROOM_STATE:
		vx = -;
	}*/
}

/*ani = 0;
	vx = 0.0f;
	isStart = false;
	isRun = false;
	isDie = false;*/


//bool CMushroom::isMoney = false;
//bool CMushroom::isStart = false;
//bool CMushroom::isRun = false;
//float CMushroom::xBox = 0;
//float CMushroom::yBox = 0;
//CMushroom * CMushroom::__instance = NULL;

//if (isMoney)
	//{
	//	this->SetState(MONEY_STATE);
	//}
	//
	//if (isDie || x < 0)
	//{
	//	x = 17;
	//	y = -17;
	//	vx = 0;
	//	isRun = false;
	//	isStart = false;
	//	isDie = false;
	//	CTurle::isTreeStart = false;
	//	this->SetState(-1);
	//	return;
	//}    //trang thai die
	//if (CTurle::isTreeStart == true)
	//{
	//	this->SetState(LEAF_GREEN_STATE);
	//	x = 646;
	//	y = 272;

	//}	//trang thai la cay
	//if (isRun)
	//{
	//	this->SetState(MUSHROOM_STATE);
	//}
	//
	//
	///*else
	//{
	//	state = -1;
	//	x = 17;
	//	y = -17;
	//}*/
	//
	//if (this->GetState() == MONEY_STATE)
	//{
	//	if (isMoney)
	//	{
	//		x = xBox;
	//		y = yBox;
	//		isMoney = false;
	//	}
	//	if (y < yBox - 60)
	//	{
	//		 y = -17;
	//		vx = 0;
	//		isDie = true;
	//		return;
	//	}
	//	vy = -0.2f;
	//	y += dy;

	//}
	//else if (this->GetState() == MUSHROOM_STATE)
	//{
	//	if (isStart)
	//	{
	//		this->x = 220;
	//		this->y = 188;
	//		isStart = false;
	//	}
	//	

	//	else if (isRun)
	//	{
	//		if (y >= 306)
	//		{
	//			//vy = 0.01;
	//			vx = -0.055f;
	//			y =306;
	//			//x -= dx;
	//		}
	//		else if (x < 186)
	//		{
	//			//x = 0;
	//			vx = 0;
	//			y += 0.5f*dt;
	//		}
	//		else
	//		{
	//			y = 188;
	//			//y += 0.005*dt;
	//			//x -= 0.4*vx;
	//			vx = -0.04f;
	//		}
	//	}
	//	x += dx;
	//}   // trang thai cua nam
