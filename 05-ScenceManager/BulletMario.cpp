#include "BulletMario.h"
#include "Plant.h"
#include "Utils.h"

//CBullet::CBullet() {
//	isStart = false;
//}

CBulletMario * CBulletMario::__instance = NULL;
CBulletMario::CBulletMario() : CGameObject()
{
	isStart = false;
	//vx = 0.8;
}
CBulletMario *CBulletMario::GetInstance()
{
	if (__instance == NULL) __instance = new CBulletMario();
	return __instance;
}
void CBulletMario::Render()
{
	animation_set->at(0)->Render(x, y);
	RenderBoundingBox();
}

void CBulletMario::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + BULLET_BBOX_WIDTH;
	b = y + BULLET_BBOX_HEIGHT;
}

void CBulletMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	//CGameObject::Update(dt, coObjects);

	//if (isStart)
	//{
	//	x -= vx;
	//	vx = -0.08f;
	//	vy = +0.05f;

	//}
	//CPlant* plant = new CPlant();
	//if (plant->start == true)
	//{
	//	isStart = true;
	//	DebugOut(L"bat dau", plant->start);
	//	x = 350;
	//	y = 112;
	//	vx = 0;
	//}
	//x += dx;
	//y += dy;
	///*if (y > 200) {
	//	isStart = false;
	//}*/

}

