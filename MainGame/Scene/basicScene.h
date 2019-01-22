#pragma once
#include "gameNode.h"
class basicScene :
	public gameNode
{
private:

	RECT _maptoolSelectRC;	//맵툴 셀렉트 RC
	RECT _gameSelectRC;		//게임 진행 RC

	int testInt;
	float testFloat;
public:
	basicScene();
	~basicScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

