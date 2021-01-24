#pragma once
#include "Mario.h"

class CCamera
{
public:
	bool isInit;
	bool isSetPosStart = false;
	bool isMoving = true;
	CCamera();
	static CCamera* GetInstance();
	void SetPosition(float x, float y);
	D3DXVECTOR3 GetPosition();
	void SetPosition(D3DXVECTOR3 pos);
	void SetWidth(int width);
	void SetHeight(int height);
	int GetWidth();
	int GetHeight();
	void Update(CMario* player);
	void SetMapSize(int width, int height);
	RECT GetBound();
	~CCamera();


private:
	static CCamera* __instance;
	int width, height;					//kich co toi da cua maptile
	int mapWidth, mapHeight;

public :
	D3DXVECTOR3 position;
};