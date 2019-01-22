#include "stdafx.h"
#include "lifeRing.h"


lifeRing::lifeRing()
{
}


lifeRing::~lifeRing()
{
}
HRESULT lifeRing::init()
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
	_itemType = TYPE_RING;
	_potionType = POTION_NONE;
	_skillType = SKILL_NONE;
	_statType = RING_LIFE;
	_statLimitType = LIMIT_NONE;

	_item.itemImage = IMAGEMANAGER->addImage("�����ǹ���", "./image/equip/ring/Rng05.bmp", 34, 34, true, RGB(255, 0, 255));

	_item.limit[LEVEL_INDEX] = 10;		//��������
	_item.limit[STAT_INDEX] = 0;		//��������
	_item.limit[SKILL_INDEX] = 0;		//�������

	_item.effect[EFFECT_RING] = 10;		//�� ����
	_item.effect[EFFECT_MAXATT] = 0;	//

	_item.money =5000;	//���� 500���Ǹ�
	_item.invenNumber = 0; //�ϴ� �κ��� ����
	_item.count = 0;


	return S_OK;
}

void lifeRing::render()
{

}