#pragma once
#include "GameObject.h"

#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16

class CBackground : public CGameObject
{
public:
	LPDIRECT3DTEXTURE9 texture;
	CBackground(float x = 0.0f, float y = 0.0f, LPDIRECT3DTEXTURE9 texture = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};