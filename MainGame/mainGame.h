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

	void addImage();		//이미기 추가해주는 함수 이후 이미지는 여기서 add하는걸로
	void initialization();	//변수들 new선언 및 init 해주는 함수 이후 new 및 init은 여기서 하는걸로
	void singletonInit();	//init에서 싱글톤들 세팅해주는 함수 이후 세팅은 여기서 하는걸로


	mainGame();
	~mainGame();
};

