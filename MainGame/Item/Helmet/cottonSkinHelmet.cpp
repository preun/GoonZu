#include "stdafx.h"
#include "cottonSkinHelmet.h"


cottonSkinHelmet::cottonSkinHelmet()
{
}


cottonSkinHelmet::~cottonSkinHelmet()
{
}
HRESULT cottonSkinHelmet::init()
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
	_itemType = TYPE_HELMET;
	_potionType = POTION_NONE;
	_skillType = SKILL_NONE;
	_statType = RING_NONE;
	_statLimitType = LIMIT_NONE;

	_item.itemImage = IMAGEMANAGER->addImage("��������", "./image/equip/helmet/Hmt10.bmp", 34, 34, true, RGB(255, 0, 255));

	_item.limit[LEVEL_INDEX] = 6;		//��������
	_item.limit[STAT_INDEX] = 0;		//��������
	_item.limit[SKILL_INDEX] = 0;		//�������

	_item.effect[EFFECT_DEF] = 10;		//�� ����
	_item.effect[EFFECT_MAXATT] = 0;	//

	_item.money = 2500;	//���� 500���Ǹ�
	_item.invenNumber = 0; //�ϴ� �κ��� ����
	_item.count = 0;


	return S_OK;
}

void cottonSkinHelmet::render()
{

}