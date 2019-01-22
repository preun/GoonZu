#pragma once
#include "gameNode.h"
#include "magicElement.h"

class magicParent :
	public gameNode
{
protected:
	//����� ���� ���⸦ �����ؾ��ϳ�
	useWeaponType _useWeaponType;
	//������� ���µ�
	magicEle _magicStat;

	int _count;
public:
	magicParent();
	~magicParent();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	
	//���� �Ҹ�
	int getUseMP(){ return _magicStat.useMP; }
	//��� �������Ѽ�ġ
	int getNeedSkillUse(){ return _magicStat.needSkillUse; }
	//��� �������
	bool getIsUsed(){ return _magicStat.isUsed; }
	//��� ������(����, �������)
	int getDamage(int inti){ return RND->getFromIntTo(_magicStat.getDagame(3, inti).x, _magicStat.getDagame(3, inti).y); }

};
/*int needSkillUse;	//�䱸 ��� ����
	int cooldownTime;	//��Ÿ��
	int useMP;			//mp�Ҹ�

	int minDamage;		//�ּ� ������
	int maxDamage;		//�ִ� ������

	bool isUsed;

	POINT getDagame(int currentSkill, int inti)
	{
		return
		{
			minDamage + inti / 4 + (currentSkill - needSkillUse)
			, maxDamage + inti / 4 + (currentSkill - needSkillUse)
		};
	}*/
