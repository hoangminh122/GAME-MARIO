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
		5,
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
	font->DrawTextA(
		CGame::GetInstance()->GetSpriteHandler(),
		text.c_str(),
		-1,
		&rect,
		DT_LEFT,
		D3DCOLOR_ARGB(255, 0, 0, 0)
	);
	
}

void CScores::Render()
{
	//get camera
   int camX = CCamera::GetInstance()->GetPosition().x - CCamera::GetInstance()->GetWidth()/2;
   int camY = CCamera::GetInstance()->GetPosition().y + CCamera::GetInstance()->GetHeight() / 2;

	CMario* mario = CMario::GetInstance(0, 0);


	// draw scores bar
	spriteScores = CSprites::GetInstance()->Get(11101);
	spriteScores->Draw(camX+30, camY+5);

	//ve so diem
	if (font)
	{
		//ve world
		SetRect(&rectScreen,67, CCamera::GetInstance()->GetHeight()+46, 300, CCamera::GetInstance()->GetHeight()+100);
		string strScreen = "1";
		Draw(rectScreen, strScreen);

		//so mang mario
		SetRect(&rectLife, 67, CCamera::GetInstance()->GetHeight() + 54, 100, CCamera::GetInstance()->GetHeight() + 100);
		string strLife = "1";
		Draw(rectLife, strLife);

		//so diem
		SetRect(&rectScores, 90, CCamera::GetInstance()->GetHeight() + 55, 150, CCamera::GetInstance()->GetHeight() + 150);
		string strScores = "0002100";
		Draw(rectScores, strScores);

		//coin 
		SetRect(&rectCoin, 165, CCamera::GetInstance()->GetHeight() + 45, 300, CCamera::GetInstance()->GetHeight() + 100);
		string strCoin = "0";
		Draw(rectCoin, strCoin);

		//time
		SetRect(&rectTime, 160, CCamera::GetInstance()->GetHeight() + 55, 300, CCamera::GetInstance()->GetHeight() + 100);
		string strTime = "000";
		Draw(rectTime, strTime);



	}
}

CScores::~CScores()
{

}