#include "stdafx.h"
#include "createCharacterScene.h"
#include "character.h"

createCharacterScene::createCharacterScene()
{
}


createCharacterScene::~createCharacterScene()
{

}

HRESULT createCharacterScene::init()
{
	//����, ����, ���̱⺻
	//����, ����, ���̼���
	//�� �� �� ������
	_characterSelect = NONECHAR;

	_characterSelectRC[0] = RectMake(118, 54, 179, 355);
	_characterSelectRC[1] = RectMake(311, 54, 179, 355);
	_characterSelectRC[2] = RectMake(504, 54, 179, 355);

	_createRC = RectMake(315, 465, 171, 92);

	_nameRC = RectMake(389, 430, 101, 12);

	_isNameInput = false;
	
	//memset(_name, NULL, 8);
	_vCharacterName.clear();

	addImage();
	

	//IMAGEMANAGER->
	return S_OK;
}

void createCharacterScene::addImage()	//�̹̱� �߰����ִ� �Լ� ���� �̹����� ���⼭ add�ϴ°ɷ�
{
	IMAGEMANAGER->addImage("ĳ���ͻ���", "./image/characterselect/ĳ���ͻ���.bmp", 800, 600, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���̱⺻", "./image/characterselect/���̱⺻.bmp", 175, 353, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���̱⺻", "./image/characterselect/���̱⺻.bmp", 175, 354, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���̱⺻", "./image/characterselect/���̱⺻.bmp", 176, 353, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���̼���", "./image/characterselect/���̼���.bmp", 175, 354, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���̼���", "./image/characterselect/���̼���.bmp", 175, 354, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���̼���", "./image/characterselect/���̼���.bmp", 175, 352, true, RGB(255, 0, 255));
}

void createCharacterScene::initialization()	//������ new���� �� init ���ִ� �Լ� ���� new �� init�� ���⼭ �ϴ°ɷ�
{

}

void createCharacterScene::singletonInit()	//init���� �̱���� �������ִ� �Լ� ���� ������ ���⼭ �ϴ°ɷ�		  
{

}

void createCharacterScene::release()
{

}

void createCharacterScene::update()
{
	if (_isNameInput) inputName();

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < 3; i++)
		{
			if (PtInRect(&_characterSelectRC[i], _ptMouse))
			{
				switch (i)
				{
					//����
				case 0:
					_characterSelect = FIRSTCHAR;
					break;

					//����
				case 1:
					_characterSelect = SECONDCHAR;
					break;

					//����
				case 2:
					_characterSelect = THIRDCHAR;
					break;
				default:
					break;
				}
			}
		}

		//�̸� �Է�ĭ�� Ŭ���߳�
		if (PtInRect(&_nameRC, _ptMouse))
		{
			_isNameInput = true;
		}
		else _isNameInput = false;

		if (PtInRect(&_createRC, _ptMouse))
		{
			//�÷��̾��� �̸��� �Է����� �ʾ����� ����
			if (_vCharacterName.size() == 0)
			{
				
				return;
			}

			//3���� ĳ������ ���𰡸� �����ߴٸ�
			if (_characterSelect != NONECHAR)
			{
				
				strcpy(_name, _vCharacterName[0]);
				for (int i = 1; i < _vCharacterName.size(); ++i)
				{
					//_name.append(&_vCharacterName[i]);
					strcat(_name, _vCharacterName[i]);
				}
				_name[_vCharacterName.size()] = NULL;

				_vCharacter[_createCharacterNumCount] = new character;
				_vCharacter[_createCharacterNumCount]->init(_name, _characterSelect);

				SCENEMANAGER->changeScene("ĳ���ͼ���");
				//switch (_characterSelect)
				//{
				//	//����
				//case FIRSTCHAR:
				//	_vCharacter[_createCharacterNumCount] = new character;
				//	_vCharacter[_createCharacterNumCount]->init("test", _characterSelect);
				//	break;

				//	//����
				//case SECONDCHAR:
				//	_characterSelect = SECONDCHAR;
				//	_vCharacter[_createCharacterNumCount] = new character;
				//	_vCharacter[_createCharacterNumCount]->init("test", _characterSelect);
				//	break;

				//	//����
				//case THIRDCHAR:
				//	_characterSelect = THIRDCHAR;
				//	_vCharacter[_createCharacterNumCount] = new character;
				//	_vCharacter[_createCharacterNumCount]->init("test", _characterSelect);
				//	break;
				//default:
				//	break;
				//}
			}
		}
	}
}

void createCharacterScene::render()
{
	IMAGEMANAGER->findImage("ĳ���ͻ���")->render(getMemDC());

	characterDraw(_characterSelect);
	//�� �� ��
	
	//for (int i = 0; i < 3; i++)
	//	Rectangle(getMemDC(), _characterSelectRC[i].left, _characterSelectRC[i].top, _characterSelectRC[i].right, _characterSelectRC[i].bottom);
	//Rectangle(getMemDC(), _nameRC.left, _nameRC.top, _nameRC.right, _nameRC.bottom);
}

void createCharacterScene::characterDraw(characterSelect num){
	switch (num)
	{
	case FIRSTCHAR:
		IMAGEMANAGER->findImage("���̼���")->render(getMemDC(), 118, 54);
		IMAGEMANAGER->findImage("���̱⺻")->render(getMemDC(), 311, 54);
		IMAGEMANAGER->findImage("���̱⺻")->render(getMemDC(), 504, 54);
		break;
	case SECONDCHAR:
		IMAGEMANAGER->findImage("���̱⺻")->render(getMemDC(), 118, 54);
		IMAGEMANAGER->findImage("���̼���")->render(getMemDC(), 311, 54);
		IMAGEMANAGER->findImage("���̱⺻")->render(getMemDC(), 504, 54);
		break;
	case THIRDCHAR:
		IMAGEMANAGER->findImage("���̱⺻")->render(getMemDC(), 118, 54);
		IMAGEMANAGER->findImage("���̱⺻")->render(getMemDC(), 311, 54);
		IMAGEMANAGER->findImage("���̼���")->render(getMemDC(), 504, 54);
		break;
	case NONECHAR:
		IMAGEMANAGER->findImage("���̱⺻")->render(getMemDC(), 118, 54);
		IMAGEMANAGER->findImage("���̱⺻")->render(getMemDC(), 311, 54);
		IMAGEMANAGER->findImage("���̱⺻")->render(getMemDC(), 504, 54);
		break;
	default:
		break;
	}
}

void createCharacterScene::inputName()
{
	if (_vCharacterName.size() != 0 && KEYMANAGER->isOnceKeyDown(VK_BACK)) _vCharacterName.pop_back();
	//�ִ� 8����
	if (_vCharacterName.size() >= 8) return;

	if (KEYMANAGER->isOnceKeyDown('Q'))_vCharacterName.push_back("q");	
	else if (KEYMANAGER->isOnceKeyDown('W'))_vCharacterName.push_back("w");
	else if (KEYMANAGER->isOnceKeyDown('E'))_vCharacterName.push_back("e");
	else if (KEYMANAGER->isOnceKeyDown('R'))_vCharacterName.push_back("r");
	else if (KEYMANAGER->isOnceKeyDown('T'))_vCharacterName.push_back("t");
	else if (KEYMANAGER->isOnceKeyDown('Y'))_vCharacterName.push_back("y");
	else if (KEYMANAGER->isOnceKeyDown('U'))_vCharacterName.push_back("u");
	else if (KEYMANAGER->isOnceKeyDown('I'))_vCharacterName.push_back("i");
	else if (KEYMANAGER->isOnceKeyDown('O'))_vCharacterName.push_back("o");
	else if (KEYMANAGER->isOnceKeyDown('P'))_vCharacterName.push_back("p");
	else if (KEYMANAGER->isOnceKeyDown('A'))_vCharacterName.push_back("a");
	else if (KEYMANAGER->isOnceKeyDown('S'))_vCharacterName.push_back("s");
	else if (KEYMANAGER->isOnceKeyDown('D'))_vCharacterName.push_back("d");
	else if (KEYMANAGER->isOnceKeyDown('F'))_vCharacterName.push_back("f");
	else if (KEYMANAGER->isOnceKeyDown('G'))_vCharacterName.push_back("g");
	else if (KEYMANAGER->isOnceKeyDown('H'))_vCharacterName.push_back("h");
	else if (KEYMANAGER->isOnceKeyDown('J'))_vCharacterName.push_back("j");
	else if (KEYMANAGER->isOnceKeyDown('K'))_vCharacterName.push_back("k");
	else if (KEYMANAGER->isOnceKeyDown('L'))_vCharacterName.push_back("l");
	else if (KEYMANAGER->isOnceKeyDown('Z'))_vCharacterName.push_back("z");
	else if (KEYMANAGER->isOnceKeyDown('X'))_vCharacterName.push_back("x");
	else if (KEYMANAGER->isOnceKeyDown('C'))_vCharacterName.push_back("c");
	else if (KEYMANAGER->isOnceKeyDown('V'))_vCharacterName.push_back("v");
	else if (KEYMANAGER->isOnceKeyDown('B'))_vCharacterName.push_back("b");
	else if (KEYMANAGER->isOnceKeyDown('N'))_vCharacterName.push_back("n");
	else if (KEYMANAGER->isOnceKeyDown('M'))_vCharacterName.push_back("m");
	
	
}