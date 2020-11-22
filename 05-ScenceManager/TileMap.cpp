#pragma once
#include "TileMap.h"
#include <fstream>
#include "Textures.h"
#include "Utils.h"
#include <string>


CTileMap::CTileMap(int idTex, string txtMapPath)
{
	//string path = "textures/map/man1/" + txtMapPath;
	DebugOut(L"SDFSDFSDDDFSFSDF%s\n", txtMapPath);
	string xxx = txtMapPath;
		fstream fs;
		fs.open(txtMapPath);

		fs >> numXTiles;
		fs >> numYTiles;

		//TAO NEW LIST TILE SPRITE
		vector<int> listTiles(numXTiles * numYTiles);
		//luu cac tile trong file txt vao vector tren

		for (int i = 0; i < listTiles.size(); i++)
		{
			fs >> listTiles[i];
		}

		//lay texture ra tu file playscence
		LPDIRECT3DTEXTURE9 texture = CTextures::GetInstance()->Get(idTex);

		//lấy so number tile của tilemap1-1 theo hang 
		D3DSURFACE_DESC desc;
		texture->GetLevelDesc(0, &desc);  //luu desc lai de lay width , height maptile
		int numCol = desc.Width / 16;   //so tile cos trong tilemap hang ngang

		LPSPRITE sprite;  
		int tileIndex;								//gia tri so trong file tilemap.txt
		int xIndex, yIndex, left, top;				//xIndex : la vi tri cuar sprite trong tilemap
													
		//Tao doi tuong sprite theo listTiles
		for (int i = 0; i < listTiles.size(); i++)
		{
			tileIndex = listTiles[i];
			yIndex = tileIndex / numCol;				//vi tri theo y mang 2 chieu
			xIndex = tileIndex - yIndex * numCol;		//VI SAO: Ta se lay gia tri do - so hang đã full
			left = xIndex * 16;					
			top = yIndex * 16;

			//push sprite vao vector
			sprite = new CSprite(i,left,top,left+16,top+16,texture);
			listSprites.push_back(sprite);
		
		}

}

CTileMap::~CTileMap()
{
}
void CTileMap::Render(CMario* player)
{
	for (int x = 0; x < 17; x++)
	{
		for (int y = 0; y < 27; y++)
		{
			int xDrawIndex, yDrawIndex, xDraw, yDraw, i;
			i = x + y * numXTiles;
			yDrawIndex = i / numXTiles;
			xDrawIndex = i - yDrawIndex * numXTiles;
			xDraw = xDrawIndex * 16;
			yDraw = yDrawIndex * 16;

			//D3DXVECTOR2 trans = D3DXVECTOR2(floor(game->GetScreenWidth() / 2 - cx), floor(game->GetScreenHeight() / 2 - cy));
			listSprites[i]->Draw(xDraw, yDraw);
		}
	}
}