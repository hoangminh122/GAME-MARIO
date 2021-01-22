#pragma once

#include <d3dx9.h>
#include "KeyEventHandler.h"
#include "GameObject.h"

class CScene
{
protected:
	CKeyEventHandler * key_handler;
	int id;
	LPCWSTR sceneFilePath;
	vector<LPGAMEOBJECT> frontObjs;

public: 
	CScene(int id, LPCWSTR filePath);
	vector<LPGAMEOBJECT>* GetFrontObjs() { return &frontObjs; }
	CKeyEventHandler * GetKeyEventHandler() { return key_handler; }
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0; 
};
typedef CScene * LPSCENE;


class CScenceKeyHandler : public CKeyEventHandler
{
public: 
	CScene * scence; 

public:
	virtual void KeyState(BYTE *states) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
	CScenceKeyHandler(CScene *s) :CKeyEventHandler() { scence = s; }
};