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
	//_spearUI[0] = IMAGEMANAGER->addImage("����������", "./image/magic/magicUI/����������.bmp", 265, 383, true, RGB(255, 0, 255));
	_spearUI[0] = IMAGEMANAGER->addImage("�¼��Ű�", "./image/magic/magicUI/�¼��Ű�.bmp", 265, 383, true, RGB(255, 0, 255));
	//_spearUI[2] = IMAGEMANAGER->addImage("�ʻ����ϼ�", "./image/magic/magicUI/�ʻ����ϼ�.bmp", 265, 383, true, RGB(255, 0, 255));
	//_spearUI[3] = IMAGEMANAGER->addImage("�ط��õ��", "./image/magic/magicUI/�ط��õ��.bmp", 265, 383, true, RGB(255, 0, 255));

	//����������
	//_spearMagic[0] = new addMagicDamage;
	//_spearMagic[0]->init();

	//�¼��Ű�
	_spearMagic[0] = new taesusingong;
	_spearMagic[0]->init();

	//�ʻ����ϼ�
	//_spearMagic[2] = new dropCri;
	//_spearMagic[2]->init();
	//
	////�ط��õ��
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
	//����� ��ų�� ��ϵǾ����� �ʴٸ� ������Ʈ(��Ÿ��) ������
	if (_useMagic != NULL)
		_useMagic->update();
}
/*�ʻ����ϼ� �ط��õ��*/
void magicUI::render()
{

}
void magicUI::openMagicUI()
{
	//UIâ ������ ������ 0������ �ʱ�ȭ
	_spearUI[_clickIndex]->render(getMemDC(), WINSIZEX - 265, WINSIZEY - 483);
}
void magicUI::clickMagicUI(bool isLClick)
{
	for (int i = 0; i < MAXSPEARMAGIC; ++i)
	{
		//RC�������̳�
		if (PtInRect(&_magicRC[i], _ptMouse))
		{
			//��Ŭ���̸� �̹��� �ٲٱ�
			if (isLClick)
				_clickIndex = i;
			//��Ŭ���̸� ��ųü����
			else
				_useMagic = _spearMagic[i];
			break;
		}
	}
}