#pragma once
#include "gameNode.h"
#include "item.h"

class itemParent :
	public gameNode
{
protected:

	itemType _itemType;				//������ ������ ����
	potionType _potionType;			//���Ǿ������ϰ�� ���� ȸ�������ֳ�
	skillType _skillType;			//����̾������ϰ�� ���� ����� �÷��ֳ�
	statType _statType;				//���� �������ϰ�� ���� ������ �÷��ֳ�
	statLimitType _statLimitType;	//���� �������ϰ�� � ������ ���� ������ �ɷ��ֳ�

	tagItem _item;					//������ ����ü
	/*
	enum itemType{
	TYPE_WEAPON,	//����
	TYPE_ARMOR,		//����
	TYPE_HELMET,	//���
	TYPE_RIGN,		//����
	TYPE_NECK,		//�����
	TYPE_POTION		//����
};

//���� ȸ�� ����
enum potionType{
	POTION_HP,
	POTION_MP
};

//����� �������
enum skillType{
	SKILL_SPEAR
};

//���� ���� ����
enum statType{
	RIGN_STR,
	RIGN_LIFE
};
	*/
	

	/*

���� : ��â ��â
����, ����, �������, ���ݷ�
���� : �谡�� ����, ���� ����
���� ����, ����
���� : �谡�� ����, ���� ����
��������, ����
����� : â�������
��������, � ��� ���
���� : �����ǹ���, �ٷ��ǹ���
��������, �����½��� �� ��ġ
���� : �����뺸��, ��Ȳû�ɿ�
�籺����, ������



	*/

public:
	itemParent();
	~itemParent();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	image* getImage(){ return _item.itemImage; }

	int getMoney(){ return _item.money; }
	itemType getItemType(){ return _itemType; }
	statType getStatType(){	return _statType; }				//���� �������ϰ�� ���� ������ �÷��ֳ�
	//0�̸� HP, 1�̸� MP
	potionType getPotionType(){ return _potionType; }

	//������ �ּҰ��ݷ�, ������ ����, ������ ȸ���� ��
	int getEffect1(){ return _item.effect[0]; }
	//������ �ִ���ݷ�
	int getEffect2(){ return _item.effect[1]; }
	//����� ��������
	int getLimitLevel(){ return _item.limit[0]; }
	//������ ��������
	int getLimitStat(){ return _item.limit[1]; }
	//������ �������
	int getLimitSkill(){ return _item.limit[2]; }
	//������ ����
	int getItemCount(){ return _item.count; }
	void setItemCount(int count){ _item.count += count; }
	/*
	itemType _itemType;				//������ ������ ����
	potionType _potionType;			//���Ǿ������ϰ�� ���� ȸ�������ֳ�
	skillType _skillType;			//����̾������ϰ�� ���� ����� �÷��ֳ�
	statType _statType;				//���� �������ϰ�� ���� ������ �÷��ֳ�
	statLimitType _statLimitType;	//���� �������ϰ�� � ������ ���� ������ �ɷ��ֳ�

	tagItem _item;					//������ ����ü
	*/
};

