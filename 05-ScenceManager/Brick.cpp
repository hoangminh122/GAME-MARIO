#include "Brick.h"
#include "Portal.h"
#include "BrickPiece.h"
#include "Game.h"
#include "Camera.h"


bool CBrick::moneyIcon = false;

CBrick::CBrick(int type_ani) 
{
	type = type_ani;
	isInitPos = false;
	ani = 0;
	idDied1_4 = false;
}

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (y != 0 && !isInitPos)
	{
		xStatic = x;
		isInitPos = true;
	}
}

void CBrick::Render()
{
	if (idDied1_4)
	{
		ani = idDied1_4_ANI;
	}
	else if (type == BRICK_TYPE_MONEY_10 && moneyIcon)
		ani = BRICK_MONEY_1_1_ANI;
	else if (type == BRICK_TYPE_MONEY_11 && moneyIcon)
		ani = BRICK_MONEY_1_1_DIED_ANI;
	else if (type == BRICK_TYPE_MONEY_10 || type == BRICK_TYPE_MONEY_11 || type == BRICK_TYPE_MONEY_1_4_12)
		ani = 1;
	else if (type == BRICK_TYPE_MONEY_7)
	{
		ani = BRICK_MONEY_TYPE_7_ANI;
	}
	else if (type == BRICK_TYPE_MONEY_8)
	{
		ani = BRICK_MONEY_TYPE_8_ANI;
	}
	else if (type == BRICK_TYPE_MONEY_9 || type == BRICK_TYPE_MONEY_20)
	{
		ani = BRICK_MONEY_TYPE_7_ANI;
	}
	
	if(ani != 0)
	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
	if (CPortal::scene_id == 1 && type == 1)
	{
		r = x + BRICK_BBOX_WIDTH_SENCE_1_TOP;
		b = y + BRICK_BBOX_HEIGHT_SENCE_1_TOP;
	}
	else if (CPortal::scene_id == 1 && type == 2)
	{
		r = x + BRICK_BBOX_WIDTH_SENCE_1_LEFT;
		b = y + BRICK_BBOX_HEIGHT_SENCE_1_LEFT;
	}  
	else if (type == 1)
		r = x + BRICK_BBOX_WIDTH_ONE;
	else if (type == BRICK_TYPE_MONEY_2)
		//r = x + 10000;
		r = x + BRICK_BBOX_WIDTH_TWO;
	else if (type == BRICK_TYPE_MONEY_3)
		r = x + BRICK_BBOX_WIDTH_THREE;
	else if (type == BRICK_TYPE_MONEY_4)
		r = x + BRICK_BBOX_WIDTH_FOUR;
	else if (type == BRICK_TYPE_MONEY_5)
		r = x + BRICK_BBOX_WIDTH_FIRE;
	else if (type == BRICK_TYPE_MONEY_6)
		r = x + BRICK_BBOX_WIDTH_SIX;
	else if (type == BRICK_TYPE_MONEY_7)
	{
		r = x + BRICK_BBOX_WIDTH_COLUMN;
		b = y + BRICK_BBOX_HEIGHT_COLUMN;
	}
	else if (type == BRICK_TYPE_MONEY_8)
	{
		r = x + BRICK_BBOX_WIDTH_COLUMN;
		b = y + BRICK_BBOX_HEIGHT_COLUMN_SMALL;
	}
	else if (type == BRICK_TYPE_MONEY_9)
	{
		r = x + BRICK_BBOX_WIDTH_COLUMN;
		b = y + BRICK_BBOX_HEIGHT_COLUMN_HIGH;
	}
	else if (type == BRICK_TYPE_MONEY_12)
	{
		r = x + BRICK_BBOX_WIDTH;
		b = y + BRICK_BBOX_HEIGHT_TWO;
	}
	else if (type == BRICK_TYPE_MONEY_13)
	{
		r = x + BRICK_BBOX_WIDTH;
		b = y + BRICK_BBOX_HEIGHT_BORDER;
	}
	else if (type == BRICK_TYPE_MONEY_14)
	{
		r = x + BRICK_BBOX_WIDTH_BORDER;
		b = y + BRICK_BBOX_HEIGHT;
	}
	else if (type == BRICK_TYPE_MONEY_15)
	{
		r = x + BRICK_BBOX_WIDTH_SENCE_START_1_4;
		b = y + BRICK_BBOX_HEIGHT;
	}
	else if (type == BRICK_TYPE_MONEY_16)
	{
		r = x + BRICK_BBOX_WIDTH_SENCE_1_4;
		b = y + BRICK_BBOX_HEIGHT;
	}
	else if (type == BRICK_TYPE_MONEY_17)
	{
		r = x + BRICK_BBOX_WIDTH_SENCE_1_4_TURLE;
	}
	else if (type == BRICK_TYPE_MONEY_18)			//brick nen dat
		r = x + BRICK_WIDTH_BIG;
	else if (type == BRICK_TYPE_MONEY_19)			//brick man 1-4 end game
	{
		r = x + BRICK_WIDTH_48;
		b = y + BRICK_WIDTH_48;
	}
	else if (type == BRICK_TYPE_MONEY_20)			//brick man 1-4 end game
	{
		r = x + BRICK_BBOX_WIDTH_COLUMN;
		b = y + BRICK_BBOX_HEIGHT_COLUMN+16;
	}

	
}

int CBrick::GetBoundPosition(int type2) {
	if (type == 1)
		return BRICK_BBOX_WIDTH_ONE;
	else if (type == BRICK_TYPE_MONEY_2)
		return BRICK_BBOX_WIDTH_TWO;
	else if (type == BRICK_TYPE_MONEY_3)
		return BRICK_BBOX_WIDTH_THREE;
	else if (type == BRICK_TYPE_MONEY_4)
		return BRICK_BBOX_WIDTH_FOUR;
	else if (type == BRICK_TYPE_MONEY_5)
		return BRICK_BBOX_WIDTH_FIRE;
	else if (type == BRICK_TYPE_MONEY_17)
		return BRICK_BBOX_WIDTH_SENCE_1_4_TURLE;
	else if (type == BRICK_TYPE_MONEY_6)
		return BRICK_BBOX_WIDTH_SIX;
	else if (type == BRICK_TYPE_MONEY_7 || type == BRICK_TYPE_MONEY_8 || type == BRICK_TYPE_MONEY_9)
	{
		return BRICK_BBOX_WIDTH_COLUMN;
	}
	else
		return BRICK_BBOX_WIDTH;
}
void CBrick::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case BRICK_STATE_BREAK:
		break;
	default:
		break;
	}
}