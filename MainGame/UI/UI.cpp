#include "stdafx.h"
#include "UI.h"


UI::UI()
{
}


UI::~UI()
{

}
HRESULT UI::init(int* maxHP, int* currentHP, int* maxMP, int* currentMP, int* level, int* exp)
{
	IMAGEMANAGER->addImage("프로그래스바UI", "./image/UI/UI1.bmp", 271, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("피바", "./image/UI/hp.bmp", 211, 9, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("엠바", "./image/UI/mp.bmp", 211, 9, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("경바", "./image/UI/exp.bmp", 211, 9, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("하단UI", "./image/UI/UI2.bmp", 800, 70, true, RGB(255, 0, 255));
	_maxHP = maxHP; _currentHP = currentHP; _maxMP = maxMP; _currentMP = currentMP;
	_level = level; _exp = exp;

	return S_OK;
}
void UI::release()
{

}
void UI::update()
{
}
void UI::render()
{
	//44 35 피
	//44 50 엠피
	IMAGEMANAGER->render("프로그래스바UI", getMemDC(), 0, 0);
	IMAGEMANAGER->render("피바", getMemDC(), 44, 35, 0, 0, 211 * (float(*_currentHP) / (*_maxHP)), 9);
	IMAGEMANAGER->render("엠바", getMemDC(), 44, 50, 0, 0, 211 * (float(*_currentMP) / (*_maxMP)), 9);
	IMAGEMANAGER->render("하단UI", getMemDC(), 0, WINSIZEY - 70);
	//*_exp - _needExp[(*_level) - 1];
	//_needExp[(*_level)] - _needExp[(*_level) - 1];
	//1렙이면
	//if ( (*_level) == 1)
	//	IMAGEMANAGER->render("경바"), getMemDC(), 44, 63, 0, 0, 211 * (float(*_exp) / _needExp[0] )

	float tempNeedExp;	//렙업에 필요한 경험치(누적 X)
	if ((*_level) == 1)
		tempNeedExp = 50;
	else
		tempNeedExp = _needExp[*_level - 1] - _needExp[*_level - 2];


	float tempCurrentExp; //현재 들고있는 경험치(누적 X)
	if ((*_level) == 1)
		tempCurrentExp = *_exp;
	else
		tempCurrentExp = *_exp - _needExp[*_level - 2];

	

	//float temp1 = float((*_exp) - (_needExp[*_level - 1] - 50));
	//float temp2 = (_needExp[(*_level) - 1]) - (_needExp[*_level - 1] - 50);
	//float temp = temp1 / temp2;
	IMAGEMANAGER->render("경바", getMemDC(), 44, 63, 0, 0, 211 * (tempCurrentExp / tempNeedExp), 9);
}