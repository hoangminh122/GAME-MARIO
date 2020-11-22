#pragma once
#include "Mario.h"

class CCamera
{
public:

	CCamera();
	static CCamera* GetInstance();

	D3DXVECTOR3 GetPosition();
	void SetPosition(D3DXVECTOR3 pos);
	void SetWidth(int width);
	void SetHeight(int height);
	int GetWidth();
	int GetHeight();
	void Update(CMario* player);
	~CCamera();


private:
	static CCamera* __instance;
	int width, height;					//kich co toi da cua maptile
	int mapWidth, mapHeight;

	D3DXVECTOR3 position;
};