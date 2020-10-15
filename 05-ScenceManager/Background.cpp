#include "Background.h"
#include "Game.h"

CBackground::CBackground(float x, float y, LPDIRECT3DTEXTURE9 tex)
{
	this->x = x;
	this->y = y;
	this->texture = tex;
}

void CBackground::Render()
{
	CGame::GetInstance()->Draw(x, y, texture);
	//animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}

void CBackground::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	
}