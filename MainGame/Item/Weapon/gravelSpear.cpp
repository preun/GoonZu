#include "stdafx.h"
#include "gravelSpear.h"


gravelSpear::gravelSpear()
{
}


gravelSpear::~gravelSpear()
{
}
HRESULT gravelSpear::init()
{
	/*
	itemType _itemType;				//������ ������ ����
	potionType _potionType;			//���Ǿ������ϰ�� ���� ȸ�������ֳ�
	skillType _skillType;			//����̾������ϰ�� ���� ����� �÷��ֳ�
	statType _stayType;				//���� �������ϰ�� ���� ������ �÷��ֳ�
	statLimitType _statLimitType;	//���� �������ϰ�� � ������ ���� ������ �ɷ��ֳ�

	tagItem _item;					//������ ����ü
	image* itemImage;	//�������̹���
	int limit[3];		//����, ����, ������� ��
	int effect[2];		//������ ȿ��(����� �ּ�, �ִ� �������� 0���� �ε�����)
	int money;			//�����ǸŰ���
	int invenNumber;	//�κ��丮 ���° ĭ�̳�
	int count;			//�����ֳ�
	*/
	_itemType = TYPE_WEAPON;
	_potionType = POTION_NONE;
	_skillType = SKILL_SPEAR;
	_statType = RING_NONE;
	_statLimitType = LIMIT_STR;

	_item.itemImage = IMAGEMANAGER->addImage("��â", "./image/equip/spear/Spe01.bmp", 34, 34, true, RGB(255, 0, 255));

	_item.limit[LEVEL_INDEX] = 0;		//��������
	_item.limit[STAT_INDEX] = 0;		//��������
	_item.limit[SKILL_INDEX] = 0;		//�������

	_item.effect[EFFECT_MINATT] = 12;		//�� ����
	_item.effect[EFFECT_MAXATT] = 16;	//

	_item.money = 1000;	//���� 500���Ǹ�
	_item.invenNumber = 0; //�ϴ� �κ��� ����
	_item.count = 0;


	return S_OK;
}

void gravelSpear::render()
{

}