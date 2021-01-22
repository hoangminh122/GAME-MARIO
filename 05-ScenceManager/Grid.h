#pragma once
#include <vector>>
#include "GameObject.h"
#include "Camera.h"

//grid cos chieu dai, rong =map va gom nhieu cell . moi cell chua 1 list object
struct Cell
{
	std::vector<CGameObject*> listObj;
};


class CGrid
{
public :
	//width,height cua grid
	int width, height;

	//do lon cua moi cell trong grid
	int cellSize;
	std::vector<Cell> listCells;

	//so cell theo chieu ngang grid
	int numXCells;

	//so cell theo chieu rong grid
	int numYCells;
public:
	CGrid(int width,int height,int cellSize);
	~CGrid();

	//them obj vaof listObjs cua cell thich hop
	void  AddObjToCell(CGameObject* obj);
	void AddObjToCell(CGameObject* obj);

	//Get Cell DUA VAO VI TRI CUAR Cell
	Cell& GetCell(int x, int y);
	Cell& GetCell(D3DXVECTOR3& posObj);

	//Tinh toan cac Obj co the bi va cham (Tinh toan cac cell can dc Update voi vi tri cua camera)
	void CalcColliableObjs(CCamera* camera,vector<LPGAMEOBJECT> objs,vector<LPGAMEOBJECT>& afterObj)



};