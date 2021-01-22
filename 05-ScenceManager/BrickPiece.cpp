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
	/*CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(1050);
	SetAnimationSet(ani_set);*/
	/*isDie = true;
	isDead = false;*/
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
			if(count == 4)
				isSetuped = false;
		}
		
		switch (_type)
		{
		case 0:
			vx = -BRICK_PIECE_HIGH_SPEED_X;
			vy = -BRICK_PIECE_HIGH_SPEED_Y;
			break;
		case 1:
			vx = BRICK_PIECE_HIGH_SPEED_X;
			vy = -BRICK_PIECE_HIGH_SPEED_Y;
			break;
		case 2:
			vx = -BRICK_PIECE_LOW_SPEED_X;
			vy = -BRICK_PIECE_LOW_SPEED_Y;
			break;
		case 3:
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

	//if (y + BRICK_PIECE_SIZE > 432)
	//{
	//	y = 900;
	//	isStart = false;
	//	//isDead = true;
	//	//DeleteFrontObjs(coObjects);
	//}
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
	r = x + 16;
	b = y + 16;
}
void CBrickPiece::SetState(int state)
{
	CGameObject::SetState(state);
}