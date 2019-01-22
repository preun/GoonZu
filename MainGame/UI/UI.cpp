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
	IMAGEMANAGER->addImage("���α׷�����UI", "./image/UI/UI1.bmp", 271, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ǹ�", "./image/UI/hp.bmp", 211, 9, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "./image/UI/mp.bmp", 211, 9, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���", "./image/UI/exp.bmp", 211, 9, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ϴ�UI", "./image/UI/UI2.bmp", 800, 70, true, RGB(255, 0, 255));
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
	//44 35 ��
	//44 50 ����
	IMAGEMANAGER->render("���α׷�����UI", getMemDC(), 0, 0);
	IMAGEMANAGER->render("�ǹ�", getMemDC(), 44, 35, 0, 0, 211 * (float(*_currentHP) / (*_maxHP)), 9);
	IMAGEMANAGER->render("����", getMemDC(), 44, 50, 0, 0, 211 * (float(*_currentMP) / (*_maxMP)), 9);
	IMAGEMANAGER->render("�ϴ�UI", getMemDC(), 0, WINSIZEY - 70);
	//*_exp - _needExp[(*_level) - 1];
	//_needExp[(*_level)] - _needExp[(*_level) - 1];
	//1���̸�
	//if ( (*_level) == 1)
	//	IMAGEMANAGER->render("���"), getMemDC(), 44, 63, 0, 0, 211 * (float(*_exp) / _needExp[0] )

	float tempNeedExp;	//������ �ʿ��� ����ġ(���� X)
	if ((*_level) == 1)
		tempNeedExp = 50;
	else
		tempNeedExp = _needExp[*_level - 1] - _needExp[*_level - 2];


	float tempCurrentExp; //���� ����ִ� ����ġ(���� X)
	if ((*_level) == 1)
		tempCurrentExp = *_exp;
	else
		tempCurrentExp = *_exp - _needExp[*_level - 2];

	

	//float temp1 = float((*_exp) - (_needExp[*_level - 1] - 50));
	//float temp2 = (_needExp[(*_level) - 1]) - (_needExp[*_level - 1] - 50);
	//float temp = temp1 / temp2;
	IMAGEMANAGER->render("���", getMemDC(), 44, 63, 0, 0, 211 * (tempCurrentExp / tempNeedExp), 9);
}