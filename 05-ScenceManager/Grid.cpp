#include "Grid.h"
#include "Game.h"

CGrid::CGrid(int width, int height, int cellSize) :width(width), height(height), cellSize(cellSize)
{
	numXCells = ceil((float)this->width / cellSize);
	numYCells = ceil((float)this->height / cellSize);

	//resize laij listCell , so luong phan tu trong listCell
	listCells.resize(numXCells*numYCells);
}

void CGrid::AddObjToCell(CGameObject * obj)
{
	float x, y;
	obj->GetPosition(x, y);
	Cell& cell = GetCell(x, y);
	cell.listObj.push_back(obj);
}

Cell& CGrid::GetCell(int x, int y)
{
	if (x < 0) x = 0;
	if (x >= numXCells) x = numXCells;
	if (y < 0) y = 0;
	if (y >= numYCells) y = numYCells;

	return listCells[x+y*numXCells];
}

Cell& CGrid::GetCell(D3DXVECTOR3& posObj)
{
	int cellX = posObj.x / cellSize;
	int cellY = posObj.y / cellSize;

	return GetCell(cellX, cellY);
}

void CGrid::CalcColliableObjs(CCamera* camera, vector<LPGAMEOBJECT>& objs, vector<LPGAMEOBJECT>& afterObjs)
{
	//tinh vi tri cua topleft va botright cua camera
	int xTopLeftCamera = camera->GetPosition().x - CGame::GetInstance()->GetScreenWidth() / 2;
	int yTopLeftCamera = camera->GetPosition().y - CGame::GetInstance()->GetScreenHeight() / 2;
	int xBotRightCamera = camera->GetPosition().x + CGame::GetInstance()->GetScreenWidth() / 2;
	int yBotRightCamera = camera->GetPosition().y + CGame::GetInstance()->GetScreenHeight() / 2;

	//tinh vij tri topleft va botright cua cell
	int xTopLeftCell = xTopLeftCamera / cellSize;
	int yTopLeftCell = yTopLeftCamera / cellSize;
	int xBotRightCell = xBotRightCamera / cellSize;
	int yBotRightCell = yBotRightCamera / cellSize;

}

CGrid::~CGrid()
{

}
