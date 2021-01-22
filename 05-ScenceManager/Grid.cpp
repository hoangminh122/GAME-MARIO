#include "Grid.h"


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



CGrid::~CGrid()
{

}
