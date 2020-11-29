#include "Goomba.h"
#include "Utils.h"

CGoomba::CGoomba()
{
	SetState(GOOMBA_STATE_WALKING);
	isReverse = false;
	//nx = -1;
	mario = CMario::GetInstance(0,0);
}

void CGoomba::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + GOOMBA_BBOX_WIDTH;

	if (this->GetState() == GOOMBA_STATE_DIE)
		bottom = y + GOOMBA_BBOX_HEIGHT_DIE;
	else 	
		bottom = y + GOOMBA_BBOX_HEIGHT;
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);
	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 
	if (vx > 0)
		nx = 1;
	else
		nx = -1;
	if (this->GetState() == GOOMBA_STATE_REVERSE_DIE) {
		if (y > mario->y + 200)
		{
			vy = 0;
			vx = 0;
		}
		else if (y < mario->y - GOOMBA_BBOX_HEIGHT*3)
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
	if (this->GetState() == GOOMBA_STATE_DIE) {
		vy = 0.1f;
		if (y > 500)
			vy = 0;
	}
	x += dx;
	y += dy;

	if ((vx < 0 && x < 0) 
		|| (vx < 0 && x < 400 && x > 320)
		|| (vx < 0 && x < 670 && x > 610) ) {
		 vx = -vx;
	}

	if ((vx > 0 && x > 290 && x <320) 
		|| (vx > 0 && x > 580 && x < 610)
		|| (vx > 0 && x > 800)) {
		vx = -vx;
	}

}

void CGoomba::Render()
{
	int ani = GOOMBA_ANI_WALKING;
	if (this->GetState() == GOOMBA_STATE_DIE) {
		ani = GOOMBA_ANI_DIE;
	}
	animation_set->at(ani)->Render(x,y,255,isReverse);
	RenderBoundingBox();
}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case GOOMBA_STATE_REVERSE_DIE:
			vx = (mario->nx)*0.05f;
			vy = -0.1f;
			break;
		case GOOMBA_STATE_DIE:
			y += GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE + 1;
			vx = 0;
			vy = 0;
			break;
		case GOOMBA_STATE_WALKING: 
			vx = -GOOMBA_WALKING_SPEED;
	}
}
