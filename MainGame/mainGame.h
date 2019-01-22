#pragma once
#include "gameNode.h"

#include "selectScene.h"
#include "createCharacterScene.h"
#include "basicScene.h"
#include "maptoolScene.h"
#include "gameScene.h"


class mainGame : public gameNode
{
private:

	

public:
	virtual HRESULT init();			
	virtual void release();			
	virtual void update();			
	virtual void render();	

	void addImage();		//�̹̱� �߰����ִ� �Լ� ���� �̹����� ���⼭ add�ϴ°ɷ�
	void initialization();	//������ new���� �� init ���ִ� �Լ� ���� new �� init�� ���⼭ �ϴ°ɷ�
	void singletonInit();	//init���� �̱���� �������ִ� �Լ� ���� ������ ���⼭ �ϴ°ɷ�


	mainGame();
	~mainGame();
};

