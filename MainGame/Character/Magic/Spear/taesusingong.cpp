#include "stdafx.h"
#include "taesusingong.h"


taesusingong::taesusingong()
{

}


taesusingong::~taesusingong()
{

}
/*enum useWeaponType
{
	WEAPON_SPEAR,
	WEAPON_SWORD,
	WEAPON_AXE,
	WEAPON_STAFF,
	WEAPON_BOW,
	WEAPON_GUN,
};

//��� ���
struct magicEle
{
	int needSkillUse;	//�䱸 ���
	int cooldownTime;	//��Ÿ��
	int useMP;			//mp�Ҹ�

	int minDamage;		//�ּ� ������
	int maxDamage;		//�ִ� ������

	int inti;			//����(4�� ���� 1)��ġ

	POINT getDagame(int currentSkill)
	{
		return
		{
			minDamage + inti / 4 + (currentSkill - needSkillUse)
			, maxDamage + inti / 4 + (currentSkill - needSkillUse)
		};
	}
};_magicStat*/
HRESULT taesusingong::init()
{
	//â���� ����̰�
	_useWeaponType = WEAPON_SPEAR;
	//����� 3 �̻��̿��� ���� �ִ�.
	_magicStat.needSkillUse = 3;
	//��Ÿ���� 3��
	_magicStat.cooldownTime = 300;
	//���� �Ҹ�
	_magicStat.useMP = 10;
	//������� ���������̹Ƿ�
	_magicStat.isUsed = _count = 0;

	//�ּҴ����
	_magicStat.minDamage = 3;
	//�ִ� �����
	_magicStat.maxDamage = 6;


	return S_OK;
}

void taesusingong::release()
{

}

void taesusingong::update()
{

}

void taesusingong::render()
{

}
