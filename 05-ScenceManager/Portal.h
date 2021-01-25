#pragma once

#include "GameObject.h"

#define PORTAL_SCENE_1	1
#define PORTAL_SCENE_2	2
#define PORTAL_SCENE_4	4

/*
	Object that triggers scene switching
*/
class CPortal : public CGameObject
{

	int width;
	int height; 
public:
	int is_start;
	static int scene_id;	// target scene to switch to 
	CPortal(float l, float t, float r, float b, int scene_id,int isStart = 1);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	int GetSceneId() { return is_start;  }
};