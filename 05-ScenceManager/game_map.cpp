
#include "game_map.h"
#include "Game.h"
#define BACKGROUND_TEXTURE_PATH1 L"0.png"
#include "Background.h"

#include "PlayScence.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"

void GameMap::LoadMap(char* name)
{
	FILE *fp = NULL;
	fopen_s(&fp, name, "rb");
	if (fp == NULL)
	{
		return;
	}

	game_map_.max_x_ = 0;    //set start x  = 0 positon
	game_map_.max_y_ = 0;    //set start x  = 0 positon
	for (int i = 0; i < MAX_MAP_Y; i++)
	{
		for (int j = 0; j < MAX_MAP_X; j++)
		{
			fscanf_s(fp, "%d", &game_map_.tile[i][j]);
			int val = game_map_.tile[i][j];

			if (val > 0)
			{
				if (j > game_map_.max_x_)
				{
					game_map_.max_x_ = j;
				}

				if (i > game_map_.max_y_)
				{
					game_map_.max_y_ = i;
				}
			}
		}
	}

	game_map_.max_x_ = (game_map_.max_x_ + 1) * TILE_SIZE;
	game_map_.max_y_ = (game_map_.max_y_ + 1) * TILE_SIZE;


	game_map_.start_x_ = 0;              //start_x_   length position x
	game_map_.start_y_ = 0;
	game_map_.file_name_ = name;
	fclose(fp);
	DebugOut(L"[ERR] game_map max_x_: %d\n", game_map_.max_x_/ TILE_SIZE );
	DebugOut(L"[ERR] game_map max__: %d\n", game_map_.max_y_ / TILE_SIZE);
	DebugOut(L"[ERR] game_map_ game_map_ game_map_ 0: %d\n", game_map_.tile[1][1]);
}

void GameMap::LoadTiles()
{
	char file_img[30];
	FILE* fp = NULL;

	for (int i = 0; i < MAX_TILE; i++)
	{
		sprintf_s(file_img, "map/%d.png", i);
		fopen_s(&fp, file_img, "rb");
		if (fp == NULL)
		{
			continue;
		}
		fclose(fp);

		//CBackground* s = new CBackground(1.3f, 1.0f, BACKGROUND_TEXTURE_PATH1);
		CGame * game = CGame::GetInstance();
		LPDIRECT3DTEXTURE9 texBackground = game->LoadTexture(BACKGROUND_TEXTURE_PATH1);
		//tile_map[i] = new CBackground(10.0f,10.0f, texBackground);
		//tile_map[i].Render()// tile_map[i].LoadImg(file_img,screen);

	}
}

void GameMap::DrawMap(LPDIRECT3DTEXTURE9* d3dtt) {
	/*CBackground* brick = new CBackground(100, 5, d3dtt);
				brick->SetPosition(100, 100);
				brick->Render();
*/

	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;

	int map_x = 0;
	int map_y = 0;

	map_x = game_map_.start_x_ / TILE_SIZE;

	x1 = (game_map_.start_x_%TILE_SIZE)*-1;
	x2 = x1 + CGame::GetInstance()->GetScreenHeight() + (x1 == 0 ? 0 : TILE_SIZE);
	//x2 = 64 * 4;

	map_y = game_map_.start_y_ / TILE_SIZE;
	y1 = (game_map_.start_y_%TILE_SIZE)*-1;
	y2 = y1 + CGame::GetInstance()->GetScreenWidth() + (y1 == 0 ? 0 : TILE_SIZE);
	//y2 = 64 * 3;

	for (int i = y1; i < y2; i += TILE_SIZE)
	{

		map_x = game_map_.start_x_ / TILE_SIZE;
		for (int j = x1; j < x2; j += TILE_SIZE)
		{
			int val = game_map_.tile[map_x][map_y];
			if (val > 0) {
				/*brick = new CBackground(100, 5, *d3dtt);
				brick = new CBackground(100, 5, *d3dtt);
				brick = new CBackground(100, 5, *d3dtt);
				brick = new CBackground(100, 5, *d3dtt);*/
				//tile_map[1] = new CBackground(10, 10, *d3dtt);
				//brick->SetPosition(100, 100);
				//tile_map[1]->Render();
				try {
					tile_map[i] = new CBackground(1, 0, 0, 64, 64, *d3dtt);

					//tile_map[1]->SetPosition(10, 10);
					tile_map[i]->Draw(j, i, 255);
				}
				catch (exception e)
				{

				}

				//tile_map[val].SetReact(j,i)   //set vi tri
				//tile_map[val].Render(screen)  //render
			}
			map_x++;
		}
		map_y++;
	}
}
