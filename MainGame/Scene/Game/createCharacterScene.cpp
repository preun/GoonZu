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
	//견이, 신이, 연이기본
	//견이, 신이, 연이선택
	//견 연 신 순으로
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

void createCharacterScene::addImage()	//이미기 추가해주는 함수 이후 이미지는 여기서 add하는걸로
{
	IMAGEMANAGER->addImage("캐릭터생성", "./image/characterselect/캐릭터생성.bmp", 800, 600, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("견이기본", "./image/characterselect/견이기본.bmp", 175, 353, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("신이기본", "./image/characterselect/신이기본.bmp", 175, 354, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("연이기본", "./image/characterselect/연이기본.bmp", 176, 353, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("견이선택", "./image/characterselect/견이선택.bmp", 175, 354, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("신이선택", "./image/characterselect/신이선택.bmp", 175, 354, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("연이선택", "./image/characterselect/연이선택.bmp", 175, 352, true, RGB(255, 0, 255));
}

void createCharacterScene::initialization()	//변수들 new선언 및 init 해주는 함수 이후 new 및 init은 여기서 하는걸로
{

}

void createCharacterScene::singletonInit()	//init에서 싱글톤들 세팅해주는 함수 이후 세팅은 여기서 하는걸로		  
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
					//견이
				case 0:
					_characterSelect = FIRSTCHAR;
					break;

					//연이
				case 1:
					_characterSelect = SECONDCHAR;
					break;

					//신이
				case 2:
					_characterSelect = THIRDCHAR;
					break;
				default:
					break;
				}
			}
		}

		//이름 입력칸을 클릭했냐
		if (PtInRect(&_nameRC, _ptMouse))
		{
			_isNameInput = true;
		}
		else _isNameInput = false;

		if (PtInRect(&_createRC, _ptMouse))
		{
			//플레이어의 이름을 입력하지 않았으면 리턴
			if (_vCharacterName.size() == 0)
			{
				
				return;
			}

			//3개의 캐릭터중 무언가를 선택했다면
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

				SCENEMANAGER->changeScene("캐릭터선택");
				//switch (_characterSelect)
				//{
				//	//견이
				//case FIRSTCHAR:
				//	_vCharacter[_createCharacterNumCount] = new character;
				//	_vCharacter[_createCharacterNumCount]->init("test", _characterSelect);
				//	break;

				//	//연이
				//case SECONDCHAR:
				//	_characterSelect = SECONDCHAR;
				//	_vCharacter[_createCharacterNumCount] = new character;
				//	_vCharacter[_createCharacterNumCount]->init("test", _characterSelect);
				//	break;

				//	//신이
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
	IMAGEMANAGER->findImage("캐릭터생성")->render(getMemDC());

	characterDraw(_characterSelect);
	//견 연 신
	
	//for (int i = 0; i < 3; i++)
	//	Rectangle(getMemDC(), _characterSelectRC[i].left, _characterSelectRC[i].top, _characterSelectRC[i].right, _characterSelectRC[i].bottom);
	//Rectangle(getMemDC(), _nameRC.left, _nameRC.top, _nameRC.right, _nameRC.bottom);
}

void createCharacterScene::characterDraw(characterSelect num){
	switch (num)
	{
	case FIRSTCHAR:
		IMAGEMANAGER->findImage("견이선택")->render(getMemDC(), 118, 54);
		IMAGEMANAGER->findImage("연이기본")->render(getMemDC(), 311, 54);
		IMAGEMANAGER->findImage("신이기본")->render(getMemDC(), 504, 54);
		break;
	case SECONDCHAR:
		IMAGEMANAGER->findImage("견이기본")->render(getMemDC(), 118, 54);
		IMAGEMANAGER->findImage("연이선택")->render(getMemDC(), 311, 54);
		IMAGEMANAGER->findImage("신이기본")->render(getMemDC(), 504, 54);
		break;
	case THIRDCHAR:
		IMAGEMANAGER->findImage("견이기본")->render(getMemDC(), 118, 54);
		IMAGEMANAGER->findImage("연이기본")->render(getMemDC(), 311, 54);
		IMAGEMANAGER->findImage("신이선택")->render(getMemDC(), 504, 54);
		break;
	case NONECHAR:
		IMAGEMANAGER->findImage("견이기본")->render(getMemDC(), 118, 54);
		IMAGEMANAGER->findImage("연이기본")->render(getMemDC(), 311, 54);
		IMAGEMANAGER->findImage("신이기본")->render(getMemDC(), 504, 54);
		break;
	default:
		break;
	}
}

void createCharacterScene::inputName()
{
	if (_vCharacterName.size() != 0 && KEYMANAGER->isOnceKeyDown(VK_BACK)) _vCharacterName.pop_back();
	//최대 8글자
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