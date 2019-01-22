#include "stdafx.h"
#include "mainGame.h"
#include "character.h"


mainGame::mainGame()
{
}

mainGame::~mainGame()
{
}

HRESULT mainGame::init()			//초기화 함수
{
	gameNode::init(true);

	character* tempCharacter1;
	tempCharacter1 = NULL;
	_vCharacter.push_back(tempCharacter1);

	character* tempCharacter2;
	tempCharacter2 = NULL;
	_vCharacter.push_back(tempCharacter2);

	character* tempCharacter3;
	tempCharacter3 = NULL;
	_vCharacter.push_back(tempCharacter3);
	//씬 넘어가기전에 캐릭터 텍스트 파일 로드하기

	

	SCENEMANAGER->addScene("캐릭터선택", new selectScene);
	SCENEMANAGER->addScene("캐릭터생성", new createCharacterScene);
	SCENEMANAGER->addScene("기본화면", new basicScene);
	SCENEMANAGER->addScene("맵툴", new maptoolScene);
	SCENEMANAGER->addScene("게임시작", new gameScene);
	
	SCENEMANAGER->changeScene("기본화면");
	//SCENEMANAGER->changeScene("맵툴");

	


	return S_OK;
}

void mainGame::release()			//메모리 해제 함수
{
	gameNode::release();

	
}

void mainGame::update()				//연산 함수
{
	gameNode::update();
	
	SCENEMANAGER->update();

}

void mainGame::render()		//그려주는 함수(a.k.a WM_PAINT)
{
	//흰색 도화지 한장~

	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==================== 건들지마라 ======================
	//IMAGEMANAGER->findImage("characterselect")->render(getMemDC());
	

	SCENEMANAGER->render();
	


	//==================== 건들지마라 =======================
	//TIMEMANAGER->render(getMemDC());
	this->getBackBuffer()->render(getHDC(), 0, 0);

}
void mainGame::addImage()		//이미기 추가해주는 함수 이후 이미지는 여기서 add하는걸로
{
	//IMAGEMANAGER->addImage("characterselect","./image/characterselect/캐릭터셀렉.bmp", 800, 600, true, RGB(255, 0, 255));

}
void mainGame::initialization()	//변수들 new선언 및 init 해주는 함수 이후 new 및 init은 여기서 하는걸로
{

}
void mainGame::singletonInit()	//init에서 싱글톤들 세팅해주는 함수 이후 세팅은 여기서 하는걸로		  
{

}