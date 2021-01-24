#pragma once

#include "GameObject.h"

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