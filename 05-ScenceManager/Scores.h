
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


	// man game so may
	RECT rectScreen;

	// so mang mario
	RECT rectLife;
	int time = 200;
	DWORD timeLimit = 0;

	// scores
	RECT rectScores;
	int scores;

	// time
	RECT rectTime;

	// coin
	RECT rectCoin;
	int coins;

public:
	CScores();
	~CScores();
	void CheckLength(string &text, int max);
	void Update(int _score,int _coins,DWORD dt);
	void Render();
	void Draw(RECT rect, string text);

};