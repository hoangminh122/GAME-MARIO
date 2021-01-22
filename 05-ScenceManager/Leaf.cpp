#include "Leaf.h"
#include "Brick.h"


CLeaf * CLeaf::__instance = NULL;
CLeaf *CLeaf::GetInstance()
{
	if (__instance == NULL) __instance = new CLeaf();
	return __instance;
}
CLeaf::CLeaf() : CGameObject()
{
	isLive = false;						//isLive = true -> mario co the an
	noMushroom = true;					//mush co 1 con ->khoi tao chua ra chuong
	isMove = false;
	isInitPos = false;						//trang thai chua khoi tao gia tri
	yStatic = y;						//ban dau chua gan gia tri y cho moshroom -> chu y de nham lan
	xStatic = x;
	SetState(LEAF_STATE_DIE);
	timeToggleVx = 0;
	isStartTime = true;						//trang thai dem h san sang
	//vxToggle = 0.1f;
	vxToggle = 0.006f;
	ani = 0;
}

void CLeaf::Render()
{
	if (GetState() != LEAF_STATE_DIE_OVER && isMove)
	{
		if (vxToggle > 0)
			ani = 0;
		else
			ani = 1;
		animation_set->at(ani)->Render(x, y);
		RenderBoundingBox();
	}
}

void CLeaf::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	if (GetState() != LEAF_STATE_DIE_OVER)
	{
		l = x;
		t = y;
		r = x + LEAF_BBOX_WIDTH;
		b = y + LEAF_BBOX_HEIGHT;
	}
}

void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);

	

	if (GetTickCount() - timeToggleVx > 500 && timeToggleVx != 0)
	{
		vxToggle = -vxToggle;
		isStartTime = true;
		timeToggleVx = 0;
	}

	if (y != 0 && !isInitPos)
	{
		//y = y - 30;
		yStatic = y;
		xStatic = x;
		isInitPos = true;
	}
	else if (isMove)				//vij tri money ==vi tri mario va cham
	{

		if(isStartTime)
			timeToggleVx = GetTickCount();				//bat dau dem h la roi
		isStartTime = false;								//dang dem h
		isLive = true;
		vy += 0.000005f * dt;
		vx = vxToggle * dt;
		/*vy = 0.03f;
		vx = vxToggle ;*/
		//if (y < yStatic - LEAF_BBOX_HEIGHT - 1)
		//{
		//	//SetState(LEAF_STATE_LIVE);
		//	//isMove = false;
		//}

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
		isLive = false;
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
	switch (state)
	{

	case LEAF_STATE_DIE_OVER:
		break;
	}
}

CLeaf::~CLeaf() {

}

	

		