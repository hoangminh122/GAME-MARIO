
#pragma once
#include <iostream>
#include <string>
#include "Sprites.h"
#include "Game.h"


using namespace std;

class CScores
{
	CSprite* spriteScores;
	ID3DXFont * font = NULL;

public:
	CScores();
	~CScores();
	void Update(DWORD dt);
	void Render();
	void Draw(RECT rect, string text);

};