#include "stdafx.h"
#include "magicUI.h"


magicUI::magicUI()
{
}


magicUI::~magicUI()
{

}

HRESULT magicUI::init()
{
	//_spearUI[0] = IMAGEMANAGER->addImage("마공증폭술", "./image/magic/magicUI/마공증폭술.bmp", 265, 383, true, RGB(255, 0, 255));
	_spearUI[0] = IMAGEMANAGER->addImage("태수신공", "./image/magic/magicUI/태수신공.bmp", 265, 383, true, RGB(255, 0, 255));
	//_spearUI[2] = IMAGEMANAGER->addImage("필살저하술", "./image/magic/magicUI/필살저하술.bmp", 265, 383, true, RGB(255, 0, 255));
	//_spearUI[3] = IMAGEMANAGER->addImage("해룡승천술", "./image/magic/magicUI/해룡승천술.bmp", 265, 383, true, RGB(255, 0, 255));

	//마공증폭술
	//_spearMagic[0] = new addMagicDamage;
	//_spearMagic[0]->init();

	//태수신공
	_spearMagic[0] = new taesusingong;
	_spearMagic[0]->init();

	//필살저하술
	//_spearMagic[2] = new dropCri;
	//_spearMagic[2]->init();
	//
	////해룡승천술
	//_spearMagic[3] = new waterDragonUP;
	//_spearMagic[3]->init();

	_clickIndex = 0;

	//98 , 11 800 600 9 54  12
	//_magicRC[0] = RectMake(544, 171, 98, 11);
	_magicRC[0] = RectMake(544, 183, 98, 11);
	//_magicRC[2] = RectMake(544, 195, 98, 11);
	//_magicRC[3] = RectMake(544, 207, 98, 11);
	
	_useMagic = NULL;
	return S_OK;
}

void magicUI::release()
{

}

void magicUI::update()
{
	//사용할 스킬이 등록되어있지 않다면 업데이트(쿨타임) 돌려라
	if (_useMagic != NULL)
		_useMagic->update();
}
/*필살저하술 해룡승천술*/
void magicUI::render()
{

}
void magicUI::openMagicUI()
{
	//UI창 열리면 무조건 0번으로 초기화
	_spearUI[_clickIndex]->render(getMemDC(), WINSIZEX - 265, WINSIZEY - 483);
}
void magicUI::clickMagicUI(bool isLClick)
{
	for (int i = 0; i < MAXSPEARMAGIC; ++i)
	{
		//RC범위안이냐
		if (PtInRect(&_magicRC[i], _ptMouse))
		{
			//좌클릭이면 이미지 바꾸기
			if (isLClick)
				_clickIndex = i;
			//우클릭이면 스킬체인지
			else
				_useMagic = _spearMagic[i];
			break;
		}
	}
}