#include "stdafx.h"
#include "highHPPotion.h"


highHPPotion::highHPPotion()
{
}


highHPPotion::~highHPPotion()
{
}
HRESULT highHPPotion::init()
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
	_itemType = TYPE_POTION;
	_potionType = POTION_HP;
	_skillType = SKILL_NONE;
	_statType = RING_NONE;
	_statLimitType = LIMIT_NONE;

	_item.itemImage = IMAGEMANAGER->addImage("��Ȳû�ɿ�", "./image/equip/potion/hea60.bmp", 34, 34, true, RGB(255, 0, 255));

	_item.limit[LEVEL_INDEX] = 0;		//��������
	_item.limit[STAT_INDEX] = 0;		//��������
	_item.limit[SKILL_INDEX] = 0;		//�������

	_item.effect[EFFECT_POTION] = 200;		//�� ����
	_item.effect[EFFECT_MAXATT] = 0;	//

	_item.money = 300;	//���� 500���Ǹ�
	_item.invenNumber = 0; //�ϴ� �κ��� ����
	_item.count = 0;


	return S_OK;
}

void highHPPotion::render()
{

}