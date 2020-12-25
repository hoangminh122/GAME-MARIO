#include "Scores.h"
#include "Camera.h"
#include "Mario.h"
#include "Utils.h"

CScores::CScores()
{
	arrNumberImage[0] = 0;
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
	timeOut = 300;
	timeOutStart = GetTickCount();
	energyCount = 0;
}

void CScores::Update(int _numCardImage,int _score,int _coins,int _energyCount, DWORD dt)
{

	if (GetTickCount() - timeOutStart > 1000)
	{
		timeOut -= 1;
		timeOutStart = GetTickCount();
	}

	this->scores = _score;
	this->coins = _coins;
	this->energyCount = _energyCount;
	this->arrNumberImage[0] = _numCardImage;

}

void CScores::Draw(RECT rect, string text)
{
	font->DrawTextA(
		CGame::GetInstance()->GetSpriteHandler(),
		text.c_str(),
		-1,
		&rect,
		DT_LEFT,
		D3DCOLOR_ARGB(255, 0,0, 10)
	);


	
}

int CScores::SetImageCard(int type) {
	switch (type)
	{
	case 0:
		return 15550;
		break;
	case 1:
		return 15551;
		break;
	case 2:
		return 15552;
		break;
	case 3:
		return 15553;
		break;
	}

}

void CScores::Render()
{
	//get camera
   int camX = CCamera::GetInstance()->GetPosition().x - CCamera::GetInstance()->GetWidth()/2;
   int camY = CCamera::GetInstance()->GetPosition().y + CCamera::GetInstance()->GetHeight() / 2;

	CMario* mario = CMario::GetInstance(0, 0);

	// draw scores bar
	spriteScores = CSprites::GetInstance()->Get(11101);
	spriteScores->Draw(camX+30, camY-35);

	//card image one
	spriteCardOne = CSprites::GetInstance()->Get(SetImageCard(arrNumberImage[0]));
	spriteCardOne->Draw(camX + 190, camY - 35);

	//draw energy fly
	for (int i = 0; i < 6-energyCount; i++)
	{
		spriteScores = CSprites::GetInstance()->Get(91010);
		spriteScores->Draw(camX + 116 -i*8, camY - 28);
	}
	

	//ve so diem
	if (font)
	{
		//ve world
		SetRect(&rectScreen,66, CCamera::GetInstance()->GetHeight()-30, 300, CCamera::GetInstance()->GetHeight()+100);
		string strScreen = "1";
		Draw(rectScreen, strScreen);

		//so mang mario
		SetRect(&rectLife, 66, CCamera::GetInstance()->GetHeight() - 22, 100, CCamera::GetInstance()->GetHeight() + 100);
		string strLife = "1";
		Draw(rectLife, strLife);

		//so diem
		SetRect(&rectScores, 90, CCamera::GetInstance()->GetHeight() -22, 150, CCamera::GetInstance()->GetHeight() + 150);
		string strScores = "0000000";
		if (this->scores != NULL)
		{
			strScores = to_string(this->scores);
			CheckLength(strScores, 6);
		}
		Draw(rectScores, strScores);

		//coin 
		SetRect(&rectCoin, 165, CCamera::GetInstance()->GetHeight() -30, 300, CCamera::GetInstance()->GetHeight() + 100);
		string strCoin = "0";
		if (this->coins != NULL)
		{
			strCoin = to_string(this->coins);
		}
		Draw(rectCoin, strCoin);

		//time
		SetRect(&rectTime, 160, CCamera::GetInstance()->GetHeight() -22, 300, CCamera::GetInstance()->GetHeight() + 100);
		string strTime = "000";
		if (this->timeOut != NULL)
		{
			strTime = to_string(this->timeOut);
			//CheckLength(strTime, 3);
		}
		Draw(rectTime, strTime);



	}
}

void CScores::CheckLength(string &text, int max)
{
	string zero = "0";
	if (text.length() < max)
	{
		do
		{
			text = zero + text;
		} while (text.length() < max);
	}
}

CScores::~CScores()
{

}