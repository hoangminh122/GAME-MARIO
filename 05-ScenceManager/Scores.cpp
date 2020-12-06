#include "Scores.h"
#include "Camera.h"
#include "Mario.h"

CScores::CScores()
{
	//create font
	//muon hien chu phai hoi tao font cho no
	D3DXCreateFont(
		CGame::GetInstance()->GetDirect3DDevice(),
		10,
		10,
		FW_NORMAL,
		1,
		false,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY,
		FF_DONTCARE,
		L"Arial",
		&font
	);

}

void CScores::Update(DWORD dt)
{
}

void CScores::Draw(RECT rect, string text)
{
	
}

void CScores::Render()
{
	//get camera
   int camX = CCamera::GetInstance()->GetPosition().x - CCamera::GetInstance()->GetWidth()/2;
   int camY = CCamera::GetInstance()->GetPosition().y + CCamera::GetInstance()->GetHeight() / 2;

	CMario* mario = CMario::GetInstance(0, 0);


	// draw scores bar
	spriteScores = CSprites::GetInstance()->Get(11101);
	spriteScores->Draw(camX+30, camY);
}

CScores::~CScores()
{

}