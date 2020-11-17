#include "Turle.h"
#include "Mario.h"

bool CTurle::isTreeStart = false;
CTurle::CTurle()
{
	
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
	CGameObject::Update(dt, coObjects);  

	//
	// TO-DO: make sure Koopas can interact with the world and to each of them too!
	// 

	

	if (state == TURLE_STATE_RUN_DIE)
	{
		vx += 0.005f;
		if (x > 637)
		{
			//vx -= 0.05f;
			x -= 15;
			//y = 200;
			vx = 0;
			vy = 0;
			isStop ++;
			//if()
		}
		if (vx > 0 && x > 610) {
			//change state mario kick -> idle
			CMario::kick = false;
			
			//x = 290; 
			vy += 0.01f;
			y = 289;
			if (isStop == 2)
			{
				state = -1;
				y = 336;
				vx = 0;
				vy = 0;
				isTreeStart = true;
			}
		}
	}
	else
	{
		if (vx < 0 && x < 530) {
			//x = 0; 
			vx = -vx;
		}

		if (vx > 0 && x > 600) {
			//x = 290; 
			vx = -vx;
		}
		
	}
	x += dx;
	y += dy;
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