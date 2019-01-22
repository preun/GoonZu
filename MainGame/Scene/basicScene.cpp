#include "stdafx.h"
#include "basicScene.h"


basicScene::basicScene()
{
}


basicScene::~basicScene()
{

}

HRESULT basicScene::init()
{
	_maptoolSelectRC = RectMakeCenter(WINSIZEX / 2 - WINSIZEX / 4, WINSIZEY / 2, 100, 100);
	_gameSelectRC = RectMakeCenter(WINSIZEX / 2 + WINSIZEX / 4, WINSIZEY / 2, 100, 100);

	/*
	SOUNDMANAGER->addSound("���ӽ���ȭ��", "./sounds/���ӽ���ȭ��.mp3", true, false);
	SOUNDMANAGER->addSound("��������1", "./sounds/��������1.mp3", true, true);
	*/
	SOUNDMANAGER->addSound("����", "./bgm/����.mp3", true, false);
	SOUNDMANAGER->addSound("����1", "./bgm/����1.mp3", true, false);
	SOUNDMANAGER->addSound("����2", "./bgm/����2.mp3", true, false);
	SOUNDMANAGER->addSound("�����", "./bgm/�����.mp3", true, false);
	SOUNDMANAGER->addSound("�����1", "./bgm/�����1.mp3", true, false);
	SOUNDMANAGER->addSound("���", "./bgm/���.mp3", true, false);
	SOUNDMANAGER->addSound("ĳ��", "./bgm/ĳ��.mp3", true, true);

	testInt = 0;
	testFloat = 0;
	
	return S_OK;
}
void basicScene::release()
{

}
void basicScene::update()
{
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		//�ִ� 10���� �ѱ��� ���Ѵ�.
		testInt--;

		//testInt = maxLimit(testInt, 10);
		//testInt = minLimit(testInt, -10);
	//	testInt = minMaxLimit(testInt, -10, 10);
		testInt = wrap(testInt, -5, 10);
		
		//testInt = fffffwrap(testInt, -10, 10);

	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		testInt++;

		//testInt = minMaxLimit(testInt, -10, 10);
	}
	if (KEYMANAGER->isOnceKeyDown('3'))
	{
		testFloat -= 0.5;

		//testFloat = maxLimit(testFloat, 5.0f);
		//testFloat = minLimit(testFloat, -5.0f);

		//testFloat = wrap(testFloat, -5.0f, 5.0f);

	}
	if (KEYMANAGER->isOnceKeyDown('4'))
	{
		testFloat += 0.5;
		testFloat = minMaxLimit(testFloat, -5.0f, 5.0f);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_maptoolSelectRC, _ptMouse))
		{
			SCENEMANAGER->changeScene("����");
		}
		else if (PtInRect(&_gameSelectRC, _ptMouse))
		{
			SOUNDMANAGER->play("ĳ��");
			SCENEMANAGER->changeScene("ĳ���ͼ���");
		}
	}
}
void basicScene::render()
{
	char tttt[111];
	sprintf(tttt, "%d, %f", testInt, testFloat);
	TextOut(getMemDC(), 10, 10, tttt, strlen(tttt));
	Rectangle(getMemDC(), _maptoolSelectRC.left, _maptoolSelectRC.top, _maptoolSelectRC.right, _maptoolSelectRC.bottom);
	Rectangle(getMemDC(), _gameSelectRC.left, _gameSelectRC.top, _gameSelectRC.right, _gameSelectRC.bottom);

	TextOut(getMemDC(), WINSIZEX / 2 - WINSIZEX / 4 - 15, WINSIZEY / 2, "����", strlen("����"));
	TextOut(getMemDC(), WINSIZEX / 2 + WINSIZEX / 4 - 30, WINSIZEY / 2, "���ΰ���", strlen("���ΰ���"));
}