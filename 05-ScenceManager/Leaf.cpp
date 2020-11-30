#include "Leaf.h"
#include "Brick.h"

CLeaf::CLeaf() : CGameObject()
{
	noMushroom = true;					//mush co 1 con ->khoi tao chua ra chuong
	isMove = false;
	isInitPos = false;						//trang thai chua khoi tao gia tri
	yStatic = y;						//ban dau chua gan gia tri y cho moshroom -> chu y de nham lan
	xStatic = x;
	SetState(LEAF_STATE_DIE);
}

void CLeaf::Render()
{

	animation_set->at(0)->Render(x, y);
	RenderBoundingBox();
}

void CLeaf::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + LEAF_BBOX_WIDTH;
	b = y + LEAF_BBOX_HEIGHT;
}

void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
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
		vy = -0.02f;
		if (y < yStatic - LEAF_BBOX_HEIGHT - 1)
		{
			SetState(LEAF_STATE_LIVE);
			isMove = false;
		}

	}
	if (GetState() == LEAF_STATE_LIVE)
		vy += LEAF_GRAVITY * dt;					//trong luc




	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (this->GetState() == LEAF_STATE_DIE_OVER)		//kiem tra xem vi tri da duoc khoi tao chua
	{
		x = xStatic;
		y = yStatic;
		vx = 0;
		vy = 0;
	}
	// turn off collision when die 
	else if (this->GetState() != LEAF_STATE_DIE)
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
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];


}

void CLeaf::SetState(int state)
{
	CGameObject::SetState(state);
	/*switch (state)
	{

	case MUSHROOM_STATE:
		vx = -;
	}*/
}

CLeaf::~CLeaf() {

}

	

		