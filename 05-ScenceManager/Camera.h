#pragma once
#include "Mario.h"

#define CAMERA_POS_X_200	200.0f
#define CAMERA_POS_X_130	130.0f
#define CAMERA_POS_Y_180	180.0f
#define CAMERA_POS_X_125	125.0f
#define CAMERA_POS_Y_80	80.0f
#define CAMERA_COUNT_100	100
#define CAMERA_POS_MARIO_COL_150	150.0f
#define CAMERA_COUNT_1_4	1.4f


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