#include "CMushroom.h"
#include "Turle.h"
#include "Utils.h"
#include "BrickTop.h"
#include "Brick.h"
#include "BrickQuestion.h"
#include "BackgroundDie.h"
#include "Plant.h"
#include "Goomba.h"
#include "BackgroundDie.h"
#include "Mario.h"
#include "Portal.h"

CMushroom * CMushroom::_instance = NULL;
CMushroom *CMushroom::GetInstance(int type)
{
	if (_instance == NULL) _instance = new CMushroom(type);
	return _instance;
}
CMushroom::CMushroom(int type_ani) : CGameObject()
{
	type = type_ani;
	ani = MUSHROOM_ANI_RED;
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
	//if (GetState() != MUSHROOM_STATE_DIE_OVER && isMove)
	{
		if (type == MUSHROOM_TYPE_1)
			ani = MUSHROOM_ANI_GREEN;
		else if (type == MUSHROOM_TYPE_2)
			ani = MUSHROOM_ANI_RED;
		animation_set->at(ani)->Render(x, y);
		RenderBoundingBox();
	}
	
}

void CMushroom::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	if (GetState() != MUSHROOM_STATE_DIE_OVER)
	{
		l = x;
		t = y;
		r = x + MUSHROOM_BBOX_WIDTH;
		b = y + MUSHROOM_BBOX_HEIGHT;
	}
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
		vy = -MUSHROOM_BBOX_VY_0_02;
		if(CPortal::scene_id == PORTAL_SCENE_4)
			vy = -MUSHROOM_BBOX_VY_0_095;
		if (y < yStatic- MUSHROOM_BBOX_HEIGHT-1)
		{
			noMushroom = false;			//co 1 com nam ->mario chuan bi bat
			int ramdom = rand() % ((1 - 0) + 1) + 0;  //ramdom 0 va 1 //rand()%((userEnd - userBeg) + 1) + userBeg; 
			if (ramdom == 0)
			{
				vx = -MUSHROOM_BBOX_VX_0_1;
				if (CPortal::scene_id == PORTAL_SCENE_4)
					vx = -MUSHROOM_BBOX_VX_0_03;
			}
			else
			{
				vx = MUSHROOM_BBOX_VX_0_1;
				if (CPortal::scene_id == PORTAL_SCENE_4)
					vx = MUSHROOM_BBOX_VX_0_03;
			}
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

		// block every object first!
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		/*if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;*/



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
				&& !dynamic_cast<CGoomba *>(e->obj)
				)
			{
				vx = -vx;
			}
			else if (e->ny < 0 && dynamic_cast<CBackgroundDie *>(e->obj))	//va cham voi background Die
			{
				vx = -vx;
			}

			//if (dynamic_cast<CMario *>(e->obj)) // if e->obj is question box
			//{
			//	if (e->nx != 0)
			//	{
			//		vx = -0.1f;

			//	}
			//} // if question box
			if (dynamic_cast<CGoomba *>(e->obj)) // if e->obj is question box
			{
				if (e->nx != 0)
				{
					x += dx;
				}
			} // if question box
			if (dynamic_cast<CBrickTop *>(e->obj)) // if e->obj is question box
			{
				CBrickTop* brickTop = dynamic_cast<CBrickTop *>(e->obj);
				if (e->nx != 0)
				{
					x += dx;
					vy += MOSHROOM_GRAVITY * dt;
				}


			} // if question box
			else if (dynamic_cast<CBackgroundDie *>(e->obj)) // if e->obj is question box
			{
				if (e->nx > 0)
				{
					SetState(MUSHROOM_STATE_DIE_OVER);
					noMushroom = true;

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
				else if (e->nx < 0)
				{
					vx = -MUSHROOM_BBOX_VX_0_05;
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
