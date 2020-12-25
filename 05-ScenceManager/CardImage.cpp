//#include "CardImage.h"
//#include "Utils.h"
//#include "Camera.h"
//
//CCardImage::CCardImage(int type_ani) : CGameObject()
//{
//	isInitPos = false;
//	type = type_ani;
//	
//}
//
//void CCardImage::Render()
//{
//	//animation_set->at(0)->Render(x, y);
//	//RenderBoundingBox();
//}
//
//void CCardImage::GetBoundingBox(float &l, float &t, float &r, float &b)
//{
//	l = x;
//	t = y;
//	r = x + CARD_IMAGE_BBOX_WIDTH;
//	b = y + CARD_IMAGE_BBOX_HEIGHT;
//}
//
//void CCardImage::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
//{
//	CGameObject::Update(dt, coObjects);
//
//	if (y != 0 && !isInitPos)
//	{
//	
//		x = 2325;
//		y = 347;
//		isInitPos = true;
//	}
//	//get camera
//	int camX = CCamera::GetInstance()->GetPosition().x - CCamera::GetInstance()->GetWidth() / 2;
//	int camY = CCamera::GetInstance()->GetPosition().y + CCamera::GetInstance()->GetHeight() / 2;
//
//	x = (int)camX + 190;
//	y = (int)camY - 35;
//}
//
