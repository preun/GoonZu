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
	//3���� ĳ���� ĭ
	_characterSelectRC[0] = RectMake(118, 54, 179, 355);
	_characterSelectRC[1] = RectMake(311, 54, 179, 355);
	_characterSelectRC[2] = RectMake(504, 54, 179, 355);

	//��ŸƮ ��ư ĭ
	_startRC = RectMake(315, 446, 171, 92);

	//ĳ���� ���� ĭ
	_createCharacterRC = RectMake(114, 558, 136, 25);

	//ĳ���� ���� ĭ
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

				//ĳ���Ͱ� �����Ǿ������� ���� �÷�����
				
			}
		}

		//���� ��ư Ŭ����
		if (PtInRect(&_startRC, _ptMouse))
		{
			//�÷����� ĳ���͸� �������� �ʾ�����
			if (_selectCharacterNumber == NONERC) return;

			//ĳ���Ͱ� �����Ǿ����� �ʴٸ�
			if (_vCharacter[_selectCharacterNumber] == NULL) return;			
			
			_playPlayer = _vCharacter[_selectCharacterNumber];


			if (_playPlayer == NULL) return;

			SCENEMANAGER->changeScene("���ӽ���");
		}

		//ĳ���� ���� Ŭ����
		if (PtInRect(&_createCharacterRC, _ptMouse))
		{
			//ĳ���� ĭ�� �������� �ʾ������
			if (_selectCharacterNumber == NONERC) return;

			if (_vCharacter[_selectCharacterNumber] == NULL)
			{
				_createCharacterNumCount = _selectCharacterNumber;
				SCENEMANAGER->changeScene("ĳ���ͻ���");
			}
			//����ó���� 3���� ĳ���Ͱ� ��� �����Ǿ������
		}

		//ĳ���� ���� Ŭ����
		if (PtInRect(&_deleteCharacterRC, _ptMouse))
		{
			//ĳ���� ĭ�� �������� �ʾ������
			if (_selectCharacterNumber == NONERC) return;

			if (_vCharacter[_selectCharacterNumber] != NULL)
			{
				_vCharacter[_selectCharacterNumber] = NULL;
			}
			//����ó���� ������ ĳ���Ͱ� ���õ��� �ʾ������
			//0���� ĳ�����ϰ��
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


void selectScene::addImage()		//�̹̱� �߰����ִ� �Լ� ���� �̹����� ���⼭ add�ϴ°ɷ�
{
	IMAGEMANAGER->addImage("characterselect","./image/characterselect/ĳ���ͼ���.bmp", 800, 600, true, RGB(255, 0, 255));
}

void selectScene::initialization()	//������ new���� �� init ���ִ� �Լ� ���� new �� init�� ���⼭ �ϴ°ɷ�
{

}

void selectScene::singletonInit()	//init���� �̱���� �������ִ� �Լ� ���� ������ ���⼭ �ϴ°ɷ�		  
{

}
