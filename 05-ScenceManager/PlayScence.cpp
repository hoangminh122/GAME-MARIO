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
#include "Leaf.h"
#include "Coin.h"
#include "Hat.h"
#include "Card.h"
#include "Col.h"
#include "SwitchCol.h"
#include "CardImage.h"
#include "Effect.h"
#include "ChangeRoad.h"
#include "Bush.h"
#include "WorldHammer.h"
#include "CCastHelp.h"
//#include "TileMap.h"

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath):
	CScene(id, filePath)
{
	key_handler = new CPlayScenceKeyHandler(this);
	scores = new CScores();

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
#define OBJECT_TYPE_LEAF	17
#define OBJECT_TYPE_COIN	18
#define OBJECT_TYPE_HAT	100
#define OBJECT_TYPE_CARD	110
#define OBJECT_TYPE_COL	120
#define OBJECT_TYPE_SWITCH_COL	130
#define OBJECT_TYPE_CARD_IMAGE	140
#define OBJECT_TYPE_EFFECT	150
#define OBJECT_TYPE_CHANGE_ROAD	160
#define OBJECT_TYPE_BUSH	170
#define OBJECT_TYPE_HAMMER	180
#define OBJECT_TYPE_CAST_HELP	171

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
	
	int xC = 0;
	int yC = 0;
	if (tokens.size() > 7) 
	{
		xC = atoi(tokens[6].c_str());
		yC = atoi(tokens[7].c_str());
	}

	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return; 
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b,xC,yC,tex);
}

void CPlayScene::_ParseSection_MAP(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return;         // truong hop bo trong

	int idTex = atoi(tokens[1].c_str());  //atoi co nhiem vu chuyen thanh so ngueyn
	int mapWidth = atoi(tokens[2].c_str());
	int mapHeight = atoi(tokens[3].c_str());
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
	for (unsigned int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
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

	for (unsigned int i = 1; i < tokens.size(); i++)
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
	float x = stof(tokens[1].c_str());
	float y = stof(tokens[2].c_str());
	int typeAni = 0;
	int typeGift = 1;
	int left = 0;
	int top = 0;
	int right = 0;
	int bottom = 0;

	int ani_set_id = atoi(tokens[3].c_str());

	if (tokens.size() > 4)
	{
		typeAni = atoi(tokens[4].c_str());
	}
	if (tokens.size() > 5)
	{
		typeGift = atoi(tokens[5].c_str());
	}
	if (tokens.size() > 6)
	{
		top = atoi(tokens[6].c_str());
	}
	if (tokens.size() > 7)
	{
		right = atoi(tokens[7].c_str());
	}
	if (tokens.size() > 8)
	{
		bottom = atoi(tokens[8].c_str());
	}

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

	case OBJECT_TYPE_BRICK: 

		obj = new CBrick(typeAni);
		break;


	case OBJECT_TYPE_BRICKTOP: obj = new CBrickTop(typeAni); break;
	case OBJECT_TYPE_TURLE: obj = new CTurle(typeAni); break;
	case OBJECT_TYPE_WALL_TURLE: obj = new CWallTurle(); break;
	case OBJECT_TYPE_QUESTION_BOX: obj = new CQuestion(typeAni); break;
	case OBJECT_TYPE_MUSHROOM: obj = new CMushroom(typeAni); break;
	case OBJECT_TYPE_PLANT: obj = new CPlant(); break;
	case OBJECT_TYPE_BULLET: obj = new CBullet(); break;
	case OBJECT_TYPE_BULLET_MARIO: obj = new CBulletMario(); break;
	case OBJECT_TYPE_BACKGROUND_DIE: obj = new CBackgroundDie(); break;
	case OBJECT_TYPE_BRICK_QUESTION: obj = new CBrickQuestion(typeAni,typeGift); break;
	case OBJECT_TYPE_MONEY_ICON: obj = new CMoneyIcon(typeAni); break;
	case OBJECT_TYPE_LEAF: obj = new CLeaf(); break;
	case OBJECT_TYPE_COIN: obj = new CCOIN(); break;
	case OBJECT_TYPE_HAT: obj = new CHat(); break;
	case OBJECT_TYPE_CARD: obj = new CCard(); break;
	case OBJECT_TYPE_COL: obj = CCOL::GetInstance(); break;
	case OBJECT_TYPE_SWITCH_COL: obj = new CSwitchCol(typeAni); break;
	//case OBJECT_TYPE_CARD_IMAGE: obj = new CCardImage(typeAni); break;
	case OBJECT_TYPE_EFFECT: obj = new CEffect(typeAni); break;
	case OBJECT_TYPE_CHANGE_ROAD: obj = new CChangeRoad(typeAni, typeGift,top,right,bottom); break;
	case OBJECT_TYPE_BUSH: obj = new CBush(); break;
	case OBJECT_TYPE_HAMMER: obj = new CWorldHammer(158,172); break;
	case OBJECT_TYPE_CAST_HELP: obj = new CCastleHelp(); break;

	case OBJECT_TYPE_PORTAL:
		{	
			float r = stof(tokens[4].c_str());
			float b = stof(tokens[5].c_str());
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

	// update Scores bar
	if (player != NULL)
		scores->Update(player->GetNumCardImage(),player->GetScores(), player->GetCoins(), player->GetEnergyCount(),dt);

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
	for (unsigned int i = 0; i < objects.size(); i++)
		objects[i]->Render();

	scores->Render();
	
}

/*
	Unload current scene
*/
void CPlayScene::Unload()
{
	for (unsigned int i = 0; i < objects.size(); i++)
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
		mario->pressS = true;
		timeJumpStart = GetTickCount();
		break;
	case DIK_A:
		if (mario->GetLevel() == MARIO_LEVEL_TAIL_BIG)    //set truong hop ko cam rua
		{
			CCOL::GetInstance() ->isAttack=true;
			CCOL::GetInstance()->timeAttack = GetTickCount();
		}
		mario->pressA = true;
		mario->timeWaitingAttackNext = GetTickCount();			//set time cho dot tan cong sau
		mario ->timeRotatoryStart = GetTickCount();
		
		break;
	case DIK_T: 
		mario->Reset();
		break;
	case DIK_6:
	{
		mario->x = 548;
		mario->y = 136;
		break;
	}
	case DIK_7:
	{
		mario->x = 1424;
		mario->y = 151;
		break;
	}
	case DIK_8:
	{
		mario->x = 2160;
		mario->y = 250;
		break;
	}
	case DIK_9:
	{
		mario->x = 2261;
		mario->y = 20;
		break;
	}
	case DIK_DOWN:
	{
		if (CPortal::scene_id == 1)
		{
			if (mario->bottom == 1)
				mario->vy += 0.2f;
		}
		break;
	}
	case DIK_UP:
	{
		if (CPortal::scene_id == 1)
		{
			if (mario->top == 1)
				mario->vy -= 0.2f;
		}
		break;
	}
	case DIK_LEFT:
	{
		if (CPortal::scene_id == 1)
		{
			if (mario->left == 1)
				mario->vx -= 0.2f;
		}
		break;
	}
	case DIK_RIGHT:
	{
		if (CPortal::scene_id == 1)
		{
			if (mario->right == 1)
				mario->vx += 0.2f;
		}
		break;
	}
	
	
	}
	
}

void CPlayScenceKeyHandler::OnKeyUp(int KeyCode)
{
	CMario *mario = ((CPlayScene*)scence)->GetPlayer();
	switch (KeyCode)
	{
	case DIK_1:
		mario->SetLevel(MARIO_LEVEL_SMALL);
		mario->SetPosition(mario->x, mario->y + MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT);
		break;
	case DIK_2:
		if (mario->GetLevel() == MARIO_LEVEL_SMALL)
			mario->SetPosition(mario->x, mario->y - (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT));
		else
			mario->SetPosition(mario->x, mario->y);
		mario->SetLevel(MARIO_LEVEL_BIG);
		break;
	case DIK_3:
		if (mario->GetLevel() == MARIO_LEVEL_SMALL)
			mario->SetPosition(mario->x, mario->y -1- (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT));
		else
			mario->SetPosition(mario->x, mario->y - 1);
		mario->SetLevel(MARIO_LEVEL_TAIL_BIG);
		break;
	case DIK_4:
		if (mario->GetLevel() == MARIO_LEVEL_SMALL)
			mario->SetPosition(mario->x, mario->y - (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT));
		else
			mario->SetPosition(mario->x, mario->y - 1);
		mario->SetLevel(MARIO_LEVEL_FIRE_BIG);
		break;
	case DIK_DOWN:
		if (CPortal::scene_id == 1)
		{
			mario->vy = 0.0f;
		}
		else
		{
			mario->SetPosition(mario->x, mario->y - (MARIO_BIG_BBOX_HEIGHT - MARIO_BIG_DOWN_BBOX_HEIGHT));
			mario->SetState(MARIO_STATE_IDLE);
		}
		
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
		mario->pressS = false;
		mario->pressA = false;
		mario->timeWaitingAttackNext = 0;			//xoa trang thai waiting -> bat dau lai
		//mario->isAttackNext = true;								//duoc tan cong
		mario->isRotatory180 = false;
		mario->timeRotatoryStart = 0;
		//mario->timePrepareRunFast = mario->timePrepareRunFast + (mario->saveTimeRunCurrent- mario->timePrepareRunFast);
		break;
	case DIK_S:
		mario->jumpHigher = false;
		break;
	case DIK_UP:
		mario->pressUp = false;
		mario->vy = 0.0f;
		break;
	case DIK_X:
		mario->pressX = true;
		if (mario->level == MARIO_LEVEL_TAIL_BIG)
		{
			mario->SetState(MARIO_STATE_IDLE);
			mario->gravityFly = false;
		}
		break;
		
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
				mario->isRotatory180 = true;
		}
		else if (mario->GetLevel() == MARIO_LEVEL_FIRE_BIG)
		{
			//set position dan mario
			if(mario->nx<0)
				CBulletMario::nxBullet = -1;
			else
				CBulletMario::nxBullet = 1;
			CBulletMario::isStart = true;
			CBulletMario::isSetPosition = true;
			mario->GetPosition(CBulletMario::x0, CBulletMario::y0);

			mario->SetState(MARIO_STATE_BULLET_IDLE);
		}

	}
	if (game->IsKeyDown(DIK_UP))
	{
		if (CPortal::scene_id != 1)
			mario->pressUp = true;
		/*if (CPortal::scene_id == 1)
		{
			if(mario->top == 1)
				mario->vy -= 0.05f;
		}*/
	}
	if (game->IsKeyDown(DIK_X))
	{
		mario->pressX = true;
		if (mario->level == MARIO_LEVEL_TAIL_BIG)
		{
			if (mario->energyFull == true)
			{
				mario->vy = -0.12f;			//0.15
				mario->SetState(MARIO_STATE_FLY);
			}
			else
			{
				mario->gravityFly = true;
				mario->SetState(MARIO_STATE_FLY_SHORT);
			}
			
		}
	}
	// disable control key when Mario die 
	if (mario->GetState() == MARIO_STATE_DIE) return;
	
	if (game->IsKeyDown(DIK_S))
	{
		if (game->IsKeyDown(DIK_UP) && mario->goUpCol)
		{
			mario->vy =- MARIO_JUMP_SPEED_HIGHER_Y;
			mario->SetState(MARIO_STATE_GO_COL);
		}
		else
		{
			//mario->jumpHigher = true;         //dang o trang thai nhan giu phim S
			mario->SetState(MARIO_STATE_JUMP_NORMAL);
			if (GetTickCount() - timeJumpStart > 150 && GetTickCount() - timeJumpStart < 200 && timeJumpStart != 0)
			{
				DebugOut(L"shgdhAAAAAAAAAAAAAAAAAAAAs%dsss%f\n", GetTickCount() - timeJumpStart, mario->vy);
				//if(mario->jumpHigher ==false)
				mario->vy -= MARIO_JUMP_SPEED_HIGHER_Y;
				mario->jumpHigher = true;
			}
		}
	}
	if (mario->GetState() == MARIO_STATE_KICK)
		mario->SetState(MARIO_STATE_KICK);
	else if (game->IsKeyDown(DIK_DOWN))
	{
		if (CPortal::scene_id != 1)
			mario->SetState(MARIO_STATE_DOWN);

	}
	else if (game->IsKeyDown(DIK_RIGHT)) {
		if (CPortal::scene_id != 1)
		{
			mario->nx = 1;
			if (game->IsKeyDown(DIK_A))
			{
				if (mario->GetState() == MARIO_STATE_WALKING)
				{
					mario->timePrepareRunFast = GetTickCount();
					//mario->timePrepareRunFast = GetTickCount()+ mario->saveTimeRunCurrent;							//bat dau dem time chay nhanh
				}
				//cam rua
				if (mario->vx <= MARIO_RUN_NORMAL_SPEED)
					mario->vx += 0.008f;
			}

			else if (game->IsKeyDown(DIK_X))
			{

				if (mario->GetState() == MARIO_STATE_FLY)
				{
					//mario->SetState(MARIO_STATE_FLY);
				}

			}
			else if (mario->vx < MARIO_WALKING_SPEED)
				mario->vx += MARIO_WALKING_ADD_SPEED;

			//phanh
			if (mario->vx < 0)
			{
				if (!mario->isHold)						//nhan giu A ma dang cam rua  trang thai mario cam rua
				{
					mario->SetState(MARIO_STATE_BRAKE);
				}
			}
			else
			{
				if (mario->pressA)						//nhan giu A trang thai mario chay
				{
					if (mario->isHold)						//nhan giu A ma dang cam rua  trang thai mario cam rua
					{
						if (mario->vx > MARIO_WALKING_SPEED)
							mario->SetState(MARIO_STATE_RUN_HOLD_TURTLE);
						else
							mario->SetState(MARIO_STATE_HOLD_TURTLE);

					}
					else if (mario->GetState() == MARIO_STATE_FLY)
					{
						mario->SetState(MARIO_STATE_FLY);
					}
					else if (mario->GetState() == MARIO_STATE_RUN)					//vx > 0.15 ->state PREPARE_FLY
					{
						if (mario->vx >= MARIO_RUN_NORMAL_SPEED - 0.01f)
						{
							/*mario->timePrepareFly = GetTickCount();
							mario->SetState(MARIO_STATE_PREPARE_FLY);*/
						}
					}

					else if (mario->vx > 0 && mario->vx < MARIO_RUN_NORMAL_SPEED && mario->checkMarioColision)											//check truong hop khi van toc >0 va <0.15-> state run 
						mario->SetState(MARIO_STATE_RUN);
				}
				else
				{
					if (mario->GetState() == MARIO_STATE_FLY)
					{
						mario->SetState(MARIO_STATE_FLY);
					}
					else if (mario->checkMarioColision) {			//va cham gach moi co trang thai di bo
						mario->SetState(MARIO_STATE_WALKING);
					}
				}
			}
		}
	}
	else if (game->IsKeyDown(DIK_LEFT)) {
		if (CPortal::scene_id != 1)
		{
			mario->nx = -1;

			if (game->IsKeyDown(DIK_A))
			{
				if (mario->GetState() == MARIO_STATE_WALKING)
				{
					mario->timePrepareRunFast = GetTickCount();		//khi nhan A thi + cdon  1 khoangr thoi gian da chay truoc do
				}
				if (mario->vx >= -MARIO_RUN_NORMAL_SPEED)
					mario->vx -= 0.008f;
			}
			else if (mario->vx > -MARIO_WALKING_SPEED)
				mario->vx -= MARIO_WALKING_ADD_SPEED;

			//phanh
			if (mario->vx > 0) {
				if (!mario->isHold)						//nhan giu A ma dang cam rua  trang thai mario cam rua
				{
					mario->SetState(MARIO_STATE_BRAKE);
				}
			}
			else
			{
				if (mario->pressA)
				{
					if (mario->isHold)						//nhan giu A ma dang cam rua  trang thai mario cam rua
					{
						if (mario->vx < -MARIO_WALKING_SPEED)
							mario->SetState(MARIO_STATE_RUN_HOLD_TURTLE);
						else
							mario->SetState(MARIO_STATE_HOLD_TURTLE);
					}
					else if (mario->GetState() == MARIO_STATE_RUN)					//vx > 0.15 ->state PREPARE_FLY
					{
						if (mario->vx <= -MARIO_RUN_NORMAL_SPEED + 0.01f)
						{
							/*mario->timePrepareFly = GetTickCount();
							mario->SetState(MARIO_STATE_PREPARE_FLY);*/
						}
					}
					else if (mario->vx < 0 && mario->vx > -MARIO_RUN_NORMAL_SPEED && mario->checkMarioColision)
						mario->SetState(MARIO_STATE_RUN);
				}
				else
				{
					if (mario->checkMarioColision)				//va cham gach moi co trang thai di bo
						mario->SetState(MARIO_STATE_WALKING);
				}
			}
		}
		
	}

	else if (mario->checkMarioColision)
	{
		if (mario->pressA && mario->isHold)						//nhan giu A ma dang cam rua  trang thai mario cam rua
		{
			if (mario->vx != 0.0f)
			{
				//mario->SetState(MARIO_STATE_HOLD_TURTLE);
			}
			else
				mario->SetState(MARIO_STATE_HOLD_TURTLE);
		}
		else if (!mario->isRotatory180)
		{
			if (mario->goUpCol && mario->goBottom && mario->vy <=0)
			{
				mario->SetState(MARIO_STATE_GO_COL);
			}
			else
			{
				mario->SetState(MARIO_STATE_IDLE);
				mario->goUpCol = false;
			}

		}
		//chỉnh tốc dộ mario giảm dần -> 0 khi ở trên nên đất
		if (mario->vx > 0 && mario->checkMarioColision == true)
		{
			mario->vx -= MARIO_WALKING_ADD_SPEED;
			if (mario->vx < 0)
				mario->vx = 0.0f;
		}
		if (mario->vx < 0 && mario->checkMarioColision == true)
		{
			mario->vx += MARIO_WALKING_ADD_SPEED;
			if (mario->vx > 0)
				mario->vx = 0.0f;
		}
	
	}
}