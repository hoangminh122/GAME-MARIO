#pragma once
#include "TileMap.h"
#include <fstream>
#include "Textures.h"
#include "Utils.h"
#include <string>
#include "Game.h"


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
			sprite = new CSprite(i,left,top,left+16,top+16,0,0,texture);
			listSprites.push_back(sprite);
		
		}

}

CTileMap::~CTileMap()
{
}
void CTileMap::Render(CMario* player)
{
	//chi ve khung camera, khong ve het
	CGame* game = CGame::GetInstance();
	float  cx, cy;
	player->GetPosition(cx, cy);	//lay vi tri cua mario
	//tinh vi tri topleft va bottonright cua camera

	int xTopLeftCam = (int)cx - game->GetScreenWidth() / 2;  //vi tri tren ben trai cua camera
	int yTopLeftCam = (int)cy - game->GetScreenHeight() / 2;
	int xBotRightCam = (int)cx + game->GetScreenWidth() / 2;
	int yBotRightCam = (int)cy + game->GetScreenHeight() / 2;

	//chia cho width,height cua moi tile nho => vi
	/*int xTopLeft = xTopLeftCam / 16 ;
	int yTopLeft = yTopLeftCam / 16;
	int xBotRight = xBotRightCam / 16;
	int yBotRight = yBotRightCam / 16;*/

	// tính vị trí topleft và botright của cell
	int xTopLeftCell = xTopLeftCam / CELL_SIZE;
	int yTopLeftCell = yTopLeftCam / CELL_SIZE;
	int xBotRightCell = xBotRightCam / CELL_SIZE;
	int yBotRightCell = yBotRightCam / CELL_SIZE;

	// tính vị trí topleft và botright của tile
	int xTopLeft = xTopLeftCell * CELL_SIZE / 16;				//chua
	int yTopLeft = yTopLeftCell * CELL_SIZE / 16;
	int xBotRight = ((xBotRightCell * CELL_SIZE) + CELL_SIZE) / 16;
	int yBotRight = ((yBotRightCell * CELL_SIZE) + CELL_SIZE) / 16;

	if (xBotRight >= numXTiles - 1)
		xBotRight = numXTiles - 1;
	if (yBotRight >= numYTiles - 1)
		yBotRight = numYTiles - 1;

	for (int x = xTopLeft; x <= xBotRight; x++)
	{
		for (int y = yTopLeft; y <= yBotRight; y++)
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