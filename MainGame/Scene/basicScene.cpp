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
	SOUNDMANAGER->addSound("게임시작화면", "./sounds/게임시작화면.mp3", true, false);
	SOUNDMANAGER->addSound("스테이지1", "./sounds/스테이지1.mp3", true, true);
	*/
	SOUNDMANAGER->addSound("마을", "./bgm/마을.mp3", true, false);
	SOUNDMANAGER->addSound("마을1", "./bgm/마을1.mp3", true, false);
	SOUNDMANAGER->addSound("마을2", "./bgm/마을2.mp3", true, false);
	SOUNDMANAGER->addSound("사냥터", "./bgm/사냥터.mp3", true, false);
	SOUNDMANAGER->addSound("사냥터1", "./bgm/사냥터1.mp3", true, false);
	SOUNDMANAGER->addSound("사망", "./bgm/사망.mp3", true, false);
	SOUNDMANAGER->addSound("캐선", "./bgm/캐선.mp3", true, true);

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
		//최대 10값을 넘기지 못한다.
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
			SCENEMANAGER->changeScene("맵툴");
		}
		else if (PtInRect(&_gameSelectRC, _ptMouse))
		{
			SOUNDMANAGER->play("캐선");
			SCENEMANAGER->changeScene("캐릭터선택");
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

	TextOut(getMemDC(), WINSIZEX / 2 - WINSIZEX / 4 - 15, WINSIZEY / 2, "맵툴", strlen("맵툴"));
	TextOut(getMemDC(), WINSIZEX / 2 + WINSIZEX / 4 - 30, WINSIZEY / 2, "메인게임", strlen("메인게임"));
}