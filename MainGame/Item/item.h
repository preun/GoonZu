#pragma once

//�����ε���
enum limitIndex{
	LEVEL_INDEX,
	STAT_INDEX,
	SKILL_INDEX
};

enum effectIndex{
	EFFECT_MINATT,
	EFFECT_MAXATT,
	EFFECT_DEF = 0,
	EFFECT_POTION = 0,
	EFFECT_RING = 0,
	EFFECT_NECK = 0
};

//������ ����
enum itemType{
	TYPE_WEAPON,	//����
	TYPE_ARMOR,		//����
	TYPE_HELMET,	//���
	TYPE_RING,		//����
	TYPE_NECK,		//�����
	TYPE_POTION		//����
};

//���� ȸ�� ����
enum potionType{
	POTION_HP,
	POTION_MP,
	POTION_NONE
};

//����̰� �÷��ִ� ��� & ������ ���� ���� �������
enum skillType{
	SKILL_SWORD,
	SKILL_SPEAR,
	SKILL_AXE,
	SKILL_STAFF,
	SKILL_BOW,
	SKILL_GUN,
	SKILL_NONE
};
/*�� â ���� ������ Ȱ �� */
//���� ���� ����
enum statType{
	RING_STR,
	RING_LIFE,
	RING_NONE
};

//���� �������� Ÿ��
enum statLimitType{
	LIMIT_STR,
	LIMIT_DEX,
	LIMIT_INT,
	LIMIT_LIFE,
	LIMIT_LUK,
	LIMIT_NONE
};
/* image _itemImage;	//�κ� �� ���â�� ���� �̹���
	int _levelLimit;		//���� ��������
	int _statLimit;			//���� ��������
	int _minAtt;		//���� �ּҰ��ݷ�
	int _maxAtt;		//���� �ִ���ݷ�
	int _def;			//�� ����*/
struct tagItem
{
	image* itemImage;	//�������̹���
	int limit[3];		//����, ����, ������� ��
	int effect[2];		//������ ȿ��(����� �ּ�, �ִ� �������� 0���� �ε�����)
	int money;			//�����ǸŰ���
	int invenNumber;	//�κ��丮 ���° ĭ�̳�
	int count;			//�����ֳ�
};

//������ �Ŵ������� �˻��ϱ� ���� �μ����� ����ü
struct tagItemIndex{
	itemType itemtype;	//����Ÿ���̳�
	int index;			//�ش� �������� ���Ϳ��� ��ġ�ϴ� �ε���
};