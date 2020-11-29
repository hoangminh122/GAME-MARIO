#include <iostream>
#include <fstream>

#include "PlayScence.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "QuestionBox.h"
#include "Plant.h"
#include "Bullet.h"
#include "BulletMario.h"
#include "BackgroundDie.h"
#include "Camera.h"
#include "WallTurle.h"
#include "BrickQuestion.h"
#include "MoneyIcon.h"
//#include "TileMap.h"

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath):
	CScene(id, filePath)
{
	key_handler = new CPlayScenceKeyHandler(this);
}

/*
	Load scene resources from scene file (textures, sprites, animations and objects)
	See scene1.txt, scene2.txt for detail format specification
*/

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS	6
#define SCENE_SECTION_MAP	7


#define OBJECT_TYPE_MARIO	0
#define OBJECT_TYPE_BRICK	1
#define OBJECT_TYPE_GOOMBA	2
#define OBJECT_TYPE_TURLE	3
#define OBJECT_TYPE_BRICKTOP	4

#define OBJECT_TYPE_MUSHROOM	8
#define OBJECT_TYPE_QUESTION_BOX	9
#define OBJECT_TYPE_PLANT	10
#define OBJECT_TYPE_BULLET	11
#define OBJECT_TYPE_BULLET_MARIO	12
#define OBJECT_TYPE_BACKGROUND_DIE	15
#define OBJECT_TYPE_WALL_TURLE	13
#define OBJECT_TYPE_BRICK_QUESTION	14
#define OBJECT_TYPE_MONEY_ICON	16



#define OBJECT_TYPE_PORTAL	50

#define MAX_SCENE_LINE 1024


void CPlayScene::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
}

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return; 
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_MAP(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return;         // truong hop bo trong

	int idTex = atoi(tokens[1].c_str());  //atoi co nhiem vu chuyen thanh so ngueyn
	float mapWidth = atoi(tokens[2].c_str());
	float mapHeight = atoi(tokens[3].c_str());
	map = new CTileMap(idTex, tokens[0]);
	CCamera::GetInstance()->SetMapSize(mapWidth, mapHeight);
	
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void CPlayScene::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	int ani_set_id = atoi(tokens[0].c_str());

	LPANIMATION_SET s = new CAnimationSet();

	CAnimations *animations = CAnimations::GetInstance();

	for (int i = 1; i < tokens.size(); i++)
	{
		int ani_id = atoi(tokens[i].c_str());
		
		LPANIMATION ani = animations->Get(ani_id);
		s->push_back(ani);
	}

	CAnimationSets::GetInstance()->Add(ani_set_id, s);
}

/*
	Parse a line in section [OBJECTS] 
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());

	int ani_set_id = atoi(tokens[3].c_str());

	CAnimationSets * animation_sets = CAnimationSets::GetInstance();

	CGameObject *obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		if (player!=NULL) 
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = CMario::GetInstance(x,y); 
		player = (CMario*)obj;  

		DebugOut(L"[INFO] Player object created!\n");
		break;
	case OBJECT_TYPE_GOOMBA: obj = new CGoomba(); break;
	case OBJECT_TYPE_BRICK: obj = new CBrick(); break;
	case OBJECT_TYPE_BRICKTOP: obj = new CBrickTop(); break;
	case OBJECT_TYPE_TURLE: obj = new CTurle(); break;
	case OBJECT_TYPE_WALL_TURLE: obj = new CWallTurle(); break;
	case OBJECT_TYPE_QUESTION_BOX: obj = new CQuestion; break;
	case OBJECT_TYPE_MUSHROOM: obj = new CMushroom(); break;
	case OBJECT_TYPE_PLANT: obj = new CPlant(); break;
	case OBJECT_TYPE_BULLET: obj = new CBullet(); break;
	case OBJECT_TYPE_BULLET_MARIO: obj = new CBulletMario(); break;
	case OBJECT_TYPE_BACKGROUND_DIE: obj = new CBackgroundDie(); break;
	case OBJECT_TYPE_BRICK_QUESTION: obj = new CBrickQuestion(); break;
	case OBJECT_TYPE_MONEY_ICON: obj = new CMoneyIcon(); break;


	case OBJECT_TYPE_PORTAL:
		{	
			float r = atof(tokens[4].c_str());
			float b = atof(tokens[5].c_str());
			int scene_id = atoi(tokens[6].c_str());
			obj = new CPortal(x, y, r, b, scene_id);
		}
		break;
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);

	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

	obj->SetAnimationSet(ani_set);
	objects.push_back(obj);
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;					

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[TEXTURES]") { section = SCENE_SECTION_TEXTURES; continue; }
		if (line == "[SPRITES]") { 
			section = SCENE_SECTION_SPRITES; continue; }
		if (line == "[ANIMATIONS]") { 
			section = SCENE_SECTION_ANIMATIONS; continue; }
		if (line == "[ANIMATION_SETS]") { 
			section = SCENE_SECTION_ANIMATION_SETS; continue; }
		if (line == "[OBJECTS]") { 
			section = SCENE_SECTION_OBJECTS; continue; }
		if (line == "[MAP]") {
			section = SCENE_SECTION_MAP; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }	

		//
		// data section
		//
		switch (section)
		{ 
			case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
			case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
			case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
			case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
			case SCENE_SECTION_MAP: _ParseSection_MAP(line); break;
		}
	}

	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return; 

	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx, cy);

	CGame* game = CGame::GetInstance();
	cx -= game->GetScreenWidth() / 2;
	cy -= game->GetScreenHeight() / 2;

	CGame::GetInstance()->SetCamPos(cx, cy);
	CCamera::GetInstance()->Update(player);




	/*CGame *game = CGame::GetInstance();
	cy -= game->GetScreenHeight()/1.1;
	if (cx <= game->GetScreenWidth() / 2)
	{
		cx = 0.0f;
		cy = 236.0f;
	}
		
	else if (CMario::isRotatory)
	{
		cx = CMario::positionXIdle;
		cx -= game->GetScreenWidth() / 2;
	}
	else
		cx -= game->GetScreenWidth() / 2;
	if (cy <=136)
		cy -= game->GetScreenHeight() / 2;
	else
		cy = 236.0f;
*/


}

void CPlayScene::Render()
{
	if (map != NULL)
	{
		map->Render(player);				//load map len
	}
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();
}

/*
	Unload current scene
*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	CMario *mario = ((CPlayScene*)scence)->GetPlayer();
	switch (KeyCode)
	{
	case DIK_S:
		timeJumpStart = GetTickCount();
		/*if(mario->checkMarioColision == true)
			mario->vy = -0.15f;*/
		break;
	case DIK_A:
		//mario->SetState(MARIO_STATE_BULLET_IDLE);
		mario->pressA = true;
		//mario->isHold = true;   //cam rua
		mario->timeWaitingAttackNext = GetTickCount();			//set time cho dot tan cong sau
		mario ->timeRotatoryStart = GetTickCount();
		break;

	case DIK_T: 
		mario->Reset();
		break;
	//case DIK_N:											//cam rua
	//	mario->SetState(MARIO_STATE_IDLE);
	//	mario->isHoldTurtle = false;
	//	break;
	//case DIK_B:
	//	mario->kick = true;
	//	mario->SetState(MARIO_STATE_KICK);
	//	//turle->SetState(TURLE_STATE_RUN_DIE);
	}
}

void CPlayScenceKeyHandler::OnKeyUp(int KeyCode)
{
	CMario *mario = ((CPlayScene*)scence)->GetPlayer();
	switch (KeyCode)
	{
	case DIK_1:
		mario->SetLevel(MARIO_LEVEL_SMALL);
		mario->SetPosition(mario->x, mario->y+ MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT);
		break;
	case DIK_2:
		if (mario->GetLevel() == MARIO_LEVEL_SMALL)
			mario->SetPosition(mario->x, mario->y - (MARIO_BIG_BBOX_HEIGHT + MARIO_SMALL_BBOX_HEIGHT));
		else
			mario->SetPosition(mario->x, mario->y);
		mario->SetLevel(MARIO_LEVEL_BIG);
		break;
	case DIK_3:
		if (mario->GetLevel() == MARIO_LEVEL_SMALL)
			mario->SetPosition(mario->x, mario->y - (MARIO_BIG_BBOX_HEIGHT + MARIO_SMALL_BBOX_HEIGHT));
		else
			mario->SetPosition(mario->x, mario->y-1);
		mario->SetLevel(MARIO_LEVEL_TAIL_BIG);
		break;
	case DIK_4:
		if (mario->GetLevel() == MARIO_LEVEL_SMALL)
			mario->SetPosition(mario->x, mario->y - (MARIO_BIG_BBOX_HEIGHT + MARIO_SMALL_BBOX_HEIGHT));
		else
			mario->SetPosition(mario->x, mario->y-1);
		mario->SetLevel(MARIO_LEVEL_FIRE_BIG);
		break;
	case DIK_DOWN:
		mario->SetPosition(mario->x, mario->y -1- (MARIO_BIG_BBOX_HEIGHT+MARIO_BIG_DOWN_BBOX_HEIGHT));
		break;
	case DIK_D:
		mario->SetPosition(mario->x, mario->y - 120);
		break;
	case DIK_A:
		if (mario->isHold)
		{
			mario->isMarioDropTurle = true;
			mario->timeKickStart = GetTickCount();
			mario->isHold = false;      //khong cam rua
		}
		mario->isHold = false;      //khong cam rua
		mario->pressA = false;
		mario->timeWaitingAttackNext = 0;			//xoa trang thai waiting -> bat dau lai
		//mario->isAttackNext = true;								//duoc tan cong
		mario->isRotatory180 = true;


		break;
	case DIK_S:
		mario->jumpHigher = false;
		break;
	//case DIK_B:											//da rua
	//	mario->SetState(MARIO_STATE_IDLE);
	//	mario->kick = false;
	//	break;

	//case DIK_C:
	//	if (mario->level == MARIO_LEVEL_TAIL_BIG)
	//	{
	//		if (CMario::energyFly < 0)
	//			CMario::energyFly = 20;
	//	}
	//	break;
	}

}

void CPlayScenceKeyHandler::KeyState(BYTE *states)
{
	CGame *game = CGame::GetInstance();
	CMario *mario = ((CPlayScene*)scence)->GetPlayer();
	if (game->IsKeyDown(DIK_A)) {
		if (mario->isHold)
		{
			mario->SetState(MARIO_STATE_HOLD_TURTLE);
		}
		else if (mario->GetLevel() == MARIO_LEVEL_TAIL_BIG )    //set truong hop ko cam rua
		{
			if (!mario->isRotatory180)       //xet xem mario co dang quay ko ->san sang
			{
				//mario->timeRotatoryStart = GetTickCount();        //time quay duoi dung yen mario
				//mario->timeWaitingAttackNext = GetTickCount();
				mario->isRotatory180 = true;
				//mario->SetState(MARIO_STATE_ROTATORY_IDLE);

			}
			
		}
		else if (mario->GetLevel() == MARIO_LEVEL_FIRE_BIG)
		{
			mario->SetState(MARIO_STATE_BULLET_IDLE);
		}

	}
	// disable control key when Mario die 
	if (mario->GetState() == MARIO_STATE_DIE) return;
	
	if (mario->GetState() == MARIO_STATE_KICK)
		mario->SetState(MARIO_STATE_KICK);
	else if (game->IsKeyDown(DIK_S))
	{
		mario->jumpHigher = true;         //dang o trang thai nhan giu phim S
		mario->SetState(MARIO_STATE_JUMP_NORMAL);
		if (GetTickCount() - timeJumpStart > 150 && GetTickCount() - timeJumpStart < 200 && timeJumpStart != 0)
		{
			mario->vy -= MARIO_JUMP_SPEED_HIGHER_Y;
		}
	}
	//else if (game->IsKeyDown(DIK_C))
	//{
	//	DebugOut(L"STATE     %d\n", mario->GetState());
	//	if (mario->level == MARIO_LEVEL_TAIL_BIG)
	//	{
	//		CMario::energyFly--;
	//		if (CMario::energyFly > 0)
	//			mario->SetState(MARIO_STATE_FLY);
	//	}

	//}
	//
	//else if (game->IsKeyDown(DIK_X))
	//{
	//	mario->SetState(MARIO_STATE_ROTATORY_IDLE);

	//}
	//else if (game->IsKeyDown(DIK_N))
	//{
	//	if (mario->isHoldTurtle == false)
	//	{
	//		if (mario->nx == 1)
	//			mario->vx = 0.01f;
	//		else
	//			mario->vx = -0.01f;
	//		mario->SetState(MARIO_STATE_HOLD_TURTLE);
	//		if(mario->nx == 1)
	//			mario->xx = mario->x;
	//		else 
	//			mario->xx = mario->x-15;
	//		mario->yy = mario->y;
	//	}
	//	else if (game->IsKeyDown(DIK_RIGHT)) {
	//		/*if (game->IsKeyDown(DIK_A))
	//		{
	//			CMario::isBullet = true;
	//		}*/
	//		if (game->IsKeyDown(DIK_Z))
	//		{
	//			if (mario->GetLevel() == MARIO_LEVEL_TAIL_BIG)
	//			{
	//				if (CMario::energyFly < 200)
	//					CMario::energyFly += 5;
	//			}
	//			mario->SetState(MARIO_STATE_RUN_RIGHT);
	//		}
	//		else
	//		{
	//			mario->SetState(MARIO_STATE_WALKING);
	//			mario->vx = MARIO_WALKING_SPEED;											//cai nay fix tam. chua xu ly kip
	//		}
	//	}
	//	else if (game->IsKeyDown(DIK_LEFT)) {
	//		/*if (game->IsKeyDown(DIK_A))
	//		{
	//			CMario::isBullet = true;
	//		}*/
	//		if (game->IsKeyDown(DIK_Z))
	//		{
	//			if (mario->GetLevel() == MARIO_LEVEL_TAIL_BIG)
	//			{
	//				if (CMario::energyFly < 200)
	//					CMario::energyFly += 5;
	//			}
	//			mario->SetState(MARIO_STATE_RUN_LEFT);
	//		}
	//		else
	//		{
	//			mario->SetState(MARIO_STATE_WALKING);
	//			mario->vx = -MARIO_WALKING_SPEED;
	//		}
	//	}
	//}
	else if (game->IsKeyDown(DIK_DOWN))
	{
		mario->SetState(MARIO_STATE_DOWN);

	}
	else if (game->IsKeyDown(DIK_RIGHT)) {
		mario->nx = 1;
		if (game->IsKeyDown(DIK_A))
		{
			//cam rua
			if (mario->vx < MARIO_RUN_NORMAL_SPEED)
				mario->vx += 0.008f;
		}
		else if (mario->vx < MARIO_WALKING_SPEED)
			mario->vx += MARIO_WALKING_ADD_SPEED;

		//phanh
		if (mario->vx < 0)
		{
			mario->SetState(MARIO_STATE_BRAKE);
		}
		else
		{
			//if (mario->pressA && mario->isHold)						//nhan giu A ma dang cam rua  trang thai mario cam rua
			//{
			//	mario->SetState(MARIO_STATE_HOLD_TURTLE);
			//}
			if (mario->pressA)						//nhan giu A trang thai mario chay
			{
				if (mario->isHold)						//nhan giu A ma dang cam rua  trang thai mario cam rua
				{
					mario->SetState(MARIO_STATE_RUN_HOLD_TURTLE);
				}
				//else if (mario->GetLevel() == MARIO_LEVEL_TAIL_BIG && !mario->isRotatory180)    //check xem mario da san sang quay chua
				//{
				//	mario->SetState(MARIO_STATE_ROTATORY_IDLE);
				//}
				else 
					mario->SetState(MARIO_STATE_RUN);
			}
			else
			{
				if (mario->isHold)						//nhan giu A ma dang cam rua  trang thai mario cam rua
				{
					mario->SetState(MARIO_STATE_WALKING_HOLD_TURTLE);
				}
				else 
					mario->SetState(MARIO_STATE_WALKING);
			}
		}
		
	}
	else if (game->IsKeyDown(DIK_LEFT)) {
		mario->nx = -1;

		if (game->IsKeyDown(DIK_A))
		{
			if (mario->vx > -MARIO_RUN_NORMAL_SPEED)
				mario->vx -= 0.008f;
		}
		else if (mario->vx > -MARIO_WALKING_SPEED)
			mario->vx -= MARIO_WALKING_ADD_SPEED;

		//phanh
		if (mario->vx > 0)
			mario->SetState(MARIO_STATE_BRAKE);
		else
		{
			//if (mario->pressA && mario->isHold)						//nhan giu A ma dang cam rua  trang thai mario cam rua
			//{
			//	mario->SetState(MARIO_STATE_HOLD_TURTLE);
			//}
			if (mario->pressA)
			{
				if (mario->isHold)						//nhan giu A ma dang cam rua  trang thai mario cam rua
				{
					mario->SetState(MARIO_STATE_RUN_HOLD_TURTLE);
				}
				//xoay duoi tan cong cua mario
				//else if (mario->GetLevel() == MARIO_LEVEL_TAIL_BIG && !mario->isRotatory180)    //check xem mario da san sang quay chua
				//{

				//	mario->SetState(MARIO_STATE_ROTATORY_IDLE);
				//}
				else
					mario->SetState(MARIO_STATE_RUN);
			}
			else
			{
				if (mario->isHold)						//nhan giu A ma dang cam rua  trang thai mario cam rua
				{
					mario->SetState(MARIO_STATE_WALKING_HOLD_TURTLE);
				}
				else
					mario->SetState(MARIO_STATE_WALKING);
			}
		}

		
	}
	
	
	/*else if (game->IsKeyDown(DIK_A)) {
		mario->SetState(MARIO_STATE_BULLET_IDLE);
	}
	*/

	else if(mario->checkMarioColision)
	{
		if (mario->pressA && mario->isHold)						//nhan giu A ma dang cam rua  trang thai mario cam rua
		{
			if(mario->vx != 0.0f)
				mario->SetState(MARIO_STATE_RUN_HOLD_TURTLE);
			else
				mario->SetState(MARIO_STATE_HOLD_TURTLE);
		}
		else if(!mario->isRotatory180)
			mario->SetState(MARIO_STATE_IDLE);
		//chỉnh tốc dộ mario giảm dần -> 0 khi ở trên nên đất
		if (mario->vx > 0 && mario ->checkMarioColision == true)
		{
			mario->vx -= MARIO_WALKING_ADD_SPEED;
			if (mario->vx < 0)
				mario->vx = 0.0f;
		}
		if(mario->vx < 0 && mario->checkMarioColision == true)
		{
			mario->vx += MARIO_WALKING_ADD_SPEED;
			if (mario->vx > 0)
				mario->vx = 0.0f;
		}

	//	//if (game->IsKeyDown(DIK_V))
	//	//{
	//	//	/*mario->levelBefore = mario->GetLevel();
	//	//	DebugOut(L"okaaaa%d\n",mario->levelBefore);*/

	//	//	mario->SetLevel(MARIO_LEVEL_FIRE_BIG);
	//	//	mario->isFire = true;
	//	//}
	//	//else
	//	//{
	//	
	//	
	}
}