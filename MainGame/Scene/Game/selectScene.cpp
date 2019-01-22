#include "stdafx.h"
#include "selectScene.h"
#include "character.h"

selectScene::selectScene()
{
}


selectScene::~selectScene()
{

}

HRESULT selectScene::init()
{
	addImage();
	//3개의 캐릭터 칸
	_characterSelectRC[0] = RectMake(118, 54, 179, 355);
	_characterSelectRC[1] = RectMake(311, 54, 179, 355);
	_characterSelectRC[2] = RectMake(504, 54, 179, 355);

	//스타트 버튼 칸
	_startRC = RectMake(315, 446, 171, 92);

	//캐릭터 생성 칸
	_createCharacterRC = RectMake(114, 558, 136, 25);

	//캐릭터 삭제 칸
	_deleteCharacterRC = RectMake(260, 558, 136, 25);
	
	_selectCharacterNumber = NONERC;
/*
	_vCharacter[0] = new character;
	_vCharacter[0]->init("abcd", 0);
		
	_vCharacter[1] = new character;
	_vCharacter[1]->init("efgh", 0);*/
	return S_OK;
}

void selectScene::release()
{

}

void selectScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < 3; i++)
		{
			if (PtInRect(&_characterSelectRC[i], _ptMouse))
			{
				switch (i)
				{
				case 0:
					_selectCharacterNumber = FIRSTRC;
					break;
				case 1:
					_selectCharacterNumber = SECONDRC;
					break;
				case 2:
					_selectCharacterNumber = THIRDRC;
					break;
					default:
					break;
				}

				//캐릭터가 생성되어있으면 내가 플레이할
				
			}
		}

		//시작 버튼 클릭시
		if (PtInRect(&_startRC, _ptMouse))
		{
			//플레이할 캐릭터를 선택하지 않았으면
			if (_selectCharacterNumber == NONERC) return;

			//캐릭터가 생성되어있지 않다면
			if (_vCharacter[_selectCharacterNumber] == NULL) return;			
			
			_playPlayer = _vCharacter[_selectCharacterNumber];


			if (_playPlayer == NULL) return;

			SCENEMANAGER->changeScene("게임시작");
		}

		//캐릭터 생성 클릭시
		if (PtInRect(&_createCharacterRC, _ptMouse))
		{
			//캐릭터 칸을 선택하지 않았을경우
			if (_selectCharacterNumber == NONERC) return;

			if (_vCharacter[_selectCharacterNumber] == NULL)
			{
				_createCharacterNumCount = _selectCharacterNumber;
				SCENEMANAGER->changeScene("캐릭터생성");
			}
			//예외처리로 3개의 캐릭터가 모두 생성되었을경우
		}

		//캐릭터 삭제 클릭시
		if (PtInRect(&_deleteCharacterRC, _ptMouse))
		{
			//캐릭터 칸을 선택하지 않았을경우
			if (_selectCharacterNumber == NONERC) return;

			if (_vCharacter[_selectCharacterNumber] != NULL)
			{
				_vCharacter[_selectCharacterNumber] = NULL;
			}
			//예외처리로 삭제할 캐릭터가 선택되지 않았을경우
			//0개의 캐릭터일경우
		}
		

	}

	//sprintf(test, "%d", _character[0]);
}

void selectScene::render()
{
	IMAGEMANAGER->findImage("characterselect")->render(getMemDC());
	//for (int i = 0; i < 3; i++)
	//	Rectangle(getMemDC(), _characterSelectRC[i].left, _characterSelectRC[i].top, _characterSelectRC[i].right, _characterSelectRC[i].bottom);

	//Rectangle(getMemDC(), _startRC.left, _startRC.top, _startRC.right, _startRC.bottom);
	//
	//Rectangle(getMemDC(), _createCharacterRC.left, _createCharacterRC.top, _createCharacterRC.right, _createCharacterRC.bottom);
	//
	//Rectangle(getMemDC(), _deleteCharacterRC.left, _deleteCharacterRC.top, _deleteCharacterRC.right, _deleteCharacterRC.bottom);

	//TextOut(getMemDC(), 10, 10, test, strlen(test));

	//_selectCharacterNumber
	for (int i = 0; i < MAXCHARACTER; ++i)
	{
		if (_vCharacter[i] != NULL)
		{
			//_vCharacter[i]->render(i);
			/*switch (_selectCharacterNumber)*/
			/*{
			case FIRSTRC:
				if (_selectCharacterNumber == i)_vCharacter[i]->selectRender(i, true);
				else if (_selectCharacterNumber == i)_vCharacter[i]->selectRender(i, false);
				break;
			case SECONDRC:
				break;
			case THIRDRC:
				break;
			case NONERC:
				break;
			default:
				break;
			}*/
			if (_selectCharacterNumber == i)_vCharacter[i]->selectRender(i, true);
			else _vCharacter[i]->selectRender(i, false);
		}
	}
}


void selectScene::addImage()		//이미기 추가해주는 함수 이후 이미지는 여기서 add하는걸로
{
	IMAGEMANAGER->addImage("characterselect","./image/characterselect/캐릭터셀렉.bmp", 800, 600, true, RGB(255, 0, 255));
}

void selectScene::initialization()	//변수들 new선언 및 init 해주는 함수 이후 new 및 init은 여기서 하는걸로
{

}

void selectScene::singletonInit()	//init에서 싱글톤들 세팅해주는 함수 이후 세팅은 여기서 하는걸로		  
{

}
