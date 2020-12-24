#include "Camera.h"
#include "Game.h"

CCamera* CCamera::__instance = NULL;

CCamera::CCamera() {
	position = D3DXVECTOR3(0, 0, 0);

	width = CGame::GetInstance() -> GetScreenWidth();     //lay chieu dai man hinh game
	height = CGame::GetInstance()-> GetScreenHeight();

}

CCamera* CCamera::GetInstance() {
	if (__instance == NULL)  __instance = new CCamera();
	return __instance;
}


D3DXVECTOR3 CCamera::GetPosition()
{
	return position;
}

void CCamera::SetPosition(D3DXVECTOR3 pos) {
	position = pos;
}

int CCamera::GetHeight() {
	return height;
}

void CCamera::SetWidth(int wid) {
	width = wid;
}

void CCamera::SetHeight(int hei) {
	height = hei;
}

int CCamera::GetWidth() {
	return width;
}

void CCamera::Update(CMario* player) {
	//di chuyen camera follow theo mario
	float cx, cy;         //vi tri cua mario hien tai
	player->GetPosition(cx,cy);
	D3DXVECTOR3 pos = D3DXVECTOR3(cx, cy, 0);
	SetPosition(pos);			//SET vi tri vao thuoc tinh position

	if (GetBound().left < 0)
	{
		//vi position cua Camera::GetInstance() ma chinh giua Camera::GetInstance()
		//luc nay o vi tri goc ben trai cua the gioi thuc
		SetPosition(GetWidth() / 2.0f, GetPosition().y);
	}

	if (GetBound().right > mapWidth)
	{
		//luc nay cham goc ben phai cua the gioi thuc
		SetPosition(mapWidth - GetWidth() / 2.0f, GetPosition().y);
	}

	if (GetBound().top < 0)
	{
		//luc nay cham goc tren the gioi thuc
		SetPosition(GetPosition().x, GetHeight() / 2.0f);
	}

	//if (GetBound().bottom > 500)
	//	/*if (GetBound().bottom > mapHeight / 2)*/
	//{
	//	//luc nay cham day cua the gioi thuc
	//	SetPosition(GetPosition().x, mapHeight - GetHeight() / 2.0f);
	//}

}

void CCamera::SetPosition(float x, float y)
{
	SetPosition(D3DXVECTOR3(x, y, 0));
}


RECT CCamera::GetBound()
{
	RECT bound;

	bound.left = (double)(position.x - width / 2);
	bound.right = (double)(bound.left + width);
	bound.top = (double)(position.y - height / 2);
	bound.bottom = (double)(bound.top + height);

	return bound;
}

void CCamera::SetMapSize(int width, int height)
{
	mapWidth = width;
	mapHeight = height;
}

CCamera::~CCamera() {

}