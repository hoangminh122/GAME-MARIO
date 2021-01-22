#include "Brick.h"
#include "Portal.h"
#include "BrickPiece.h"
#include "Game.h"


bool CBrick::moneyIcon = false;

CBrick::CBrick(int type_ani) 
{
	type = type_ani;
	isInitPos = false;
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
	if(type ==10 && moneyIcon)
		animation_set->at(2)->Render(x, y);
	else if (type == 11 && moneyIcon)
		animation_set->at(3)->Render(x, y);
	else if(type == 10 || type == 11)
		animation_set->at(1)->Render(x, y);
	else if (type == 7)
	{
		animation_set->at(4)->Render(x, y);
	}
	else if (type == 8)
	{
		animation_set->at(5)->Render(x, y);
	}
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
	else if (type == 2)
		r = x + BRICK_BBOX_WIDTH_TWO;
	else if (type == 3)
		r = x + BRICK_BBOX_WIDTH_THREE;
	else if (type == 4)
		r = x + BRICK_BBOX_WIDTH_FOUR;
	else if (type == 5)
		r = x + BRICK_BBOX_WIDTH_FIRE;
	else if (type == 6)
		r = x + BRICK_BBOX_WIDTH_SIX;
	else if (type == 7)
	{
		r = x + BRICK_BBOX_WIDTH_COLUMN;
		b = y + BRICK_BBOX_HEIGHT_COLUMN;
	}
	else if (type == 8)
	{
		r = x + BRICK_BBOX_WIDTH_COLUMN;
		b = y + BRICK_BBOX_HEIGHT_COLUMN_SMALL;
	}
	else if (type == 9)
	{
		r = x + BRICK_BBOX_WIDTH_COLUMN;
		b = y + BRICK_BBOX_HEIGHT_COLUMN_HIGH;
	}
	else if (type == 12)
	{
		r = x + BRICK_BBOX_WIDTH;
		b = y + BRICK_BBOX_HEIGHT_TWO;
	}
	else if (type == 13)
	{
		r = x + BRICK_BBOX_WIDTH;
		b = y + BRICK_BBOX_HEIGHT_BORDER;
	}
	else if (type == 14)
	{
		r = x + BRICK_BBOX_WIDTH_BORDER;
		b = y + BRICK_BBOX_HEIGHT;
	}
	else if (type == 15)
	{
		r = x + BRICK_BBOX_WIDTH_SENCE_START_1_4;
		b = y + BRICK_BBOX_HEIGHT;
	}
	else if (type == 16)
	{
		r = x + BRICK_BBOX_WIDTH_SENCE_1_4;
		b = y + BRICK_BBOX_HEIGHT;
	}

	
}

int CBrick::GetBoundPosition(int type2) {
	if (type == 1)
		return BRICK_BBOX_WIDTH_ONE;
	else if (type == 2)
		return BRICK_BBOX_WIDTH_TWO;
	else if (type == 3)
		return BRICK_BBOX_WIDTH_THREE;
	else if (type == 4)
		return BRICK_BBOX_WIDTH_FOUR;
	else if (type == 5)
		return BRICK_BBOX_WIDTH_FIRE;
	else if (type == 6)
		return BRICK_BBOX_WIDTH_SIX;
	else if (type == 7 || type == 8 || type == 9)
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
	{

		//CGameObject* piece1 = new CBrickPiece();
		//piece1->SetPosition(2020, 334);
		//piece1->Update();
		//piece1->Render();
		//test
		/*for (int i = 0; i < 4; i++)
		{

			CBrickPiece* piece = new CBrickPiece();
			piece->SetPosition(x, y);
			switch (i)
			{
			case 0:
				piece->vx = -BRICK_PIECE_HIGH_SPEED_X;
				piece->vy = -BRICK_PIECE_HIGH_SPEED_Y;
				break;
			case 1:
				piece->vx = BRICK_PIECE_HIGH_SPEED_X;
				piece->vy = -BRICK_PIECE_HIGH_SPEED_Y;
				break;
			case 2:
				piece->vx = -BRICK_PIECE_LOW_SPEED_X;
				piece->vy = -BRICK_PIECE_LOW_SPEED_Y;
				break;
			case 3:
				piece->vx = BRICK_PIECE_LOW_SPEED_X;
				piece->vy = -BRICK_PIECE_LOW_SPEED_Y;
				break;
			default:
				break;
			}
			CGame::GetInstance()->GetCurrentScene()->GetFrontObjs()->push_back(piece);
		}*/
		//CPlayerInfo::GetInstance()->AdjustScore(10);

		break;
		}
	default:
		break;
	}
}