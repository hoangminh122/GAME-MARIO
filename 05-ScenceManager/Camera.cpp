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

D3DXVECTOR3 CCamera::GetPosition() {
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



}


CCamera::~CCamera() {

}