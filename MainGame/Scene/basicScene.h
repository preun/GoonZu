#pragma once
#include "gameNode.h"
class basicScene :
	public gameNode
{
private:

	RECT _maptoolSelectRC;	//���� ����Ʈ RC
	RECT _gameSelectRC;		//���� ���� RC

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

