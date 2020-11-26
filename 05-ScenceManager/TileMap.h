#pragma once
#include <vector>
#include "Sprites.h"
#include "Mario.h"
#define CELL_SIZE 150

//using namespace std;

class CTileMap
{
private:
	//listSpites Vector
	vector<LPSPRITE> listSprites;
	int numXTiles;       //so tiles tren hang
	int numYTiles;		//so tiles tren cot

	int idTex;           //id de tao texture

public:
	CTileMap(int idTex, string txtMapPath);
	~CTileMap();
	void Render(CMario* player);
};