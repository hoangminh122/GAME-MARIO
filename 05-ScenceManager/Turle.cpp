#include "Turle.h"
#include "Mario.h"
#include "Brick.h"
#include "Utils.h"
#include "BrickTop.h"

bool CTurle::isTreeStart = false;
CTurle::CTurle()
{
	vxx = TURLE_WALKING_SPEED;
	isStop = 0;
	//ani = TURLE_STATE_RUN_DIE;
	ani = TURLE_ANI_WALKING_LEFT;
	SetState(TURLE_STATE_WALKING);
	//SetState(TURLE_STATE_RUN_DIE);
}

void CTurle::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + TURLE_BBOX_WIDTH;

	if (state == TURLE_STATE_DIE || state == TURLE_STATE_RUN_DIE)
		bottom = y + TURLE_BBOX_HEIGHT_DIE;
	
	else
		bottom = y + TURLE_BBOX_HEIGHT;
}

void CTurle::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	// Simple fall down
	vy += MARIO_GRAVITY * dt;

	

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state != MARIO_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed

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

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;


		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			vx = vxx;
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CBrickTop *>(e->obj)) // if e->obj is brickTop
			{
				vx = vxx;
				if (vx < 0 && x < 530) {
					//x = 0; 
					vxx = -vxx;
					vx = vxx;
				}

				else if (vx > 0 && x > 600) {
					//x = 290; 
					vxx = -vxx;
					vx = vxx;
				}

			} // if brickTop
			
		}

	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CTurle::Render()
{
	
	if (state == TURLE_STATE_DIE) {
		ani = TURLE_ANI_DIE;
	}
	else if (state == TURLE_STATE_RUN_DIE) {
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
		vy = 0;
		break;
	case TURLE_STATE_WALKING:
		vx = TURLE_WALKING_SPEED;
		break;
	case TURLE_STATE_RUN_DIE:
		vx = TURLE_WALKING_SPEED;
		break;
	}

}