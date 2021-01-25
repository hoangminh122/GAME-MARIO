#include "BrickPiece.h"

CBrickPiece * CBrickPiece::__instance = NULL;
CBrickPiece *CBrickPiece::GetInstance()
{
	if (__instance == NULL) __instance = new CBrickPiece(1);
	return __instance;
}
bool CBrickPiece::isStart = false;
bool CBrickPiece::isSetuped = false;
float CBrickPiece::xStatic = 0.0f;
float CBrickPiece::yStatic = 0.0f;
int CBrickPiece::count = 0;
CBrickPiece::CBrickPiece(int type)
{
	xStatic = x;
	yStatic = y;
	_type = type;
	isSetuped = false;
	count = 0;
	isStart = false;
}

void CBrickPiece::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	if (isStart)
	{
		if (isSetuped)
		{
			x = xStatic;
			y = yStatic;
			count++;
			if(count == COUNT_NUM_4)
				isSetuped = false;
		}
		
		switch (_type)
		{
		case BRICK_PIECE_TYPE_0:
			vx = -BRICK_PIECE_HIGH_SPEED_X;
			vy = -BRICK_PIECE_HIGH_SPEED_Y;
			break;
		case BRICK_PIECE_TYPE_1:
			vx = BRICK_PIECE_HIGH_SPEED_X;
			vy = -BRICK_PIECE_HIGH_SPEED_Y;
			break;
		case BRICK_PIECE_TYPE_2:
			vx = -BRICK_PIECE_LOW_SPEED_X;
			vy = -BRICK_PIECE_LOW_SPEED_Y;
			break;
		case BRICK_PIECE_TYPE_3:
			vx = BRICK_PIECE_LOW_SPEED_X;
			vy = -BRICK_PIECE_LOW_SPEED_Y;
			break;
		default:
			break;
		}
		vy += BRICK_PIECE_GRAVITY * dt;
		x += dx;
		y += dy;
	}

}

void CBrickPiece::Render()
{
	//if(isStart)
		animation_set->at(0)->Render(x, y);
}
void CBrickPiece::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + BRICK_PIECE_WIDTH;
	b = y + BRICK_PIECE_HEIGHT;
}
void CBrickPiece::SetState(int state)
{
	CGameObject::SetState(state);
}