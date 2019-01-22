#include "stdafx.h"
#include "mainGame.h"
#include "character.h"


mainGame::mainGame()
{
}

mainGame::~mainGame()
{
}

HRESULT mainGame::init()			//�ʱ�ȭ �Լ�
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
	//�� �Ѿ������ ĳ���� �ؽ�Ʈ ���� �ε��ϱ�

	

	SCENEMANAGER->addScene("ĳ���ͼ���", new selectScene);
	SCENEMANAGER->addScene("ĳ���ͻ���", new createCharacterScene);
	SCENEMANAGER->addScene("�⺻ȭ��", new basicScene);
	SCENEMANAGER->addScene("����", new maptoolScene);
	SCENEMANAGER->addScene("���ӽ���", new gameScene);
	
	SCENEMANAGER->changeScene("�⺻ȭ��");
	//SCENEMANAGER->changeScene("����");

	


	return S_OK;
}

void mainGame::release()			//�޸� ���� �Լ�
{
	gameNode::release();

	
}

void mainGame::update()				//���� �Լ�
{
	gameNode::update();
	
	SCENEMANAGER->update();

}

void mainGame::render()		//�׷��ִ� �Լ�(a.k.a WM_PAINT)
{
	//��� ��ȭ�� ����~

	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==================== �ǵ������� ======================
	//IMAGEMANAGER->findImage("characterselect")->render(getMemDC());
	

	SCENEMANAGER->render();
	


	//==================== �ǵ������� =======================
	//TIMEMANAGER->render(getMemDC());
	this->getBackBuffer()->render(getHDC(), 0, 0);

}
void mainGame::addImage()		//�̹̱� �߰����ִ� �Լ� ���� �̹����� ���⼭ add�ϴ°ɷ�
{
	//IMAGEMANAGER->addImage("characterselect","./image/characterselect/ĳ���ͼ���.bmp", 800, 600, true, RGB(255, 0, 255));

}
void mainGame::initialization()	//������ new���� �� init ���ִ� �Լ� ���� new �� init�� ���⼭ �ϴ°ɷ�
{

}
void mainGame::singletonInit()	//init���� �̱���� �������ִ� �Լ� ���� ������ ���⼭ �ϴ°ɷ�		  
{

}