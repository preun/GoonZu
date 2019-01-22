#include "stdafx.h"
#include "skillUI.h"


skillUI::skillUI()
{
}


skillUI::~skillUI()
{

}

HRESULT skillUI::init()
{ 
	IMAGEMANAGER->addImage("스킬UI", "./image/magic/skill/기술.bmp", 251, 392, true, RGB(255, 0, 2550));

	return S_OK;
}
void skillUI::release()
{

}
void skillUI::update()
{

}
void skillUI::render()
{

}

void skillUI::openSkillUI()
{
	IMAGEMANAGER->findImage("스킬UI")->render(getMemDC(), WINSIZEX / 2, WINSIZEY / 2 - 200);
}