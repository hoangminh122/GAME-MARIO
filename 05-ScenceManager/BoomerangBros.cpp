#include "BoomerangBros.h"
#include "PlayScence.h"
#include "Boomerang.h"

CBoomerangBros::CBoomerangBros(float x)
{
	start_x = x;
	SetState(BOOMERANGBROS_STATE_WALKING);

	SetBoundingBox();
}

void CBoomerangBros::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	// Simple fall down
	
	if (GetState() != BOOMERANGBROS_STATE_DIE)
	{
		// Movement
		if (x <= start_x - BOOMERANGBROS_DISTANCE_X)
			vx = BOOMERANGBROS_WALKING_SPEED;
		else if (x >= start_x + BOOMERANGBROS_DISTANCE_X)
			vx = -BOOMERANGBROS_WALKING_SPEED;

		CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		float distanceX = (x + BOOMERANGBROS_BBOX_WIDTH / 2) - (mario->x + BOOMERANGBROS_BBOX_WIDTH / 2);
		// Follow Mario

		// Throw 1
		if (wait_time != 0 && GetTickCount() - wait_time > BOOMERANGBROS_WAIT_TIME)
		{
			ThrowBoomerang();
			wait_time = 0;
			throw_time = GetTickCount();
		}
		// Throw 2
		if (throw_time != 0 && GetTickCount() - throw_time > BOOMERANGBROS_THROW_TIME)
		{
			ThrowBoomerang();
			throw_time = 0;
			wait_time = GetTickCount();
		}

		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;
		coEvents.clear();

		CalcPotentialCollisions(coObjects, coEvents);

		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// Col logic with other objs	
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];


			// Col-X
			if (e->nx != 0)
			{
				
			}
		}
		// Clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}

void CBoomerangBros::Render()
{
	int ani = BOOMERANGBROS_ANI_WALKING;
	switch (GetState())
	{
	case BOOMERANGBROS_STATE_WALKING: case BOOMERANGBROS_STATE_DIE:
		ani = BOOMERANGBROS_ANI_WALKING;
		break;
	case BOOMERANGBROS_STATE_THROW:
		ani = BOOMERANGBROS_ANI_THROW;
		break;
	default:
		break;
	}

	animation_set->at(0)->Render(x, y);
}

void CBoomerangBros::SetState(int state)
{

	CGameObject::SetState(state);

	switch (state)
	{
	case BOOMERANGBROS_STATE_DIE:
		break;
	default:
		break;
	}
}

void CBoomerangBros::ThrowBoomerang()
{
}

void CBoomerangBros::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + BOOMERANGBROS_BBOX_WIDTH;
	b = t + BOOMERANGBROS_BBOX_HEIGHT;

	CGameObject::GetBoundingBox(l, t, r, b);
}

void CBoomerangBros::SetBoundingBox()
{
	left = x;
	top = y;
	right = left + BOOMERANGBROS_BBOX_WIDTH;
	bottom = top + BOOMERANGBROS_BBOX_HEIGHT;
}
