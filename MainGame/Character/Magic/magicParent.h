#pragma once
#include "gameNode.h"
#include "magicElement.h"

class magicParent :
	public gameNode
{
protected:
	//기술이 무슨 무기를 장착해야하냐
	useWeaponType _useWeaponType;
	//기술들의 상태들
	magicEle _magicStat;

	int _count;
public:
	magicParent();
	~magicParent();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	
	//엠피 소모량
	int getUseMP(){ return _magicStat.useMP; }
	//기술 레벨제한수치
	int getNeedSkillUse(){ return _magicStat.needSkillUse; }
	//기술 사용유무
	bool getIsUsed(){ return _magicStat.isUsed; }
	//기술 데미지(지능, 기술레벨)
	int getDamage(int inti){ return RND->getFromIntTo(_magicStat.getDagame(3, inti).x, _magicStat.getDagame(3, inti).y); }

};
/*int needSkillUse;	//요구 기술 제한
	int cooldownTime;	//쿨타임
	int useMP;			//mp소모량

	int minDamage;		//최소 데미지
	int maxDamage;		//최대 데미지

	bool isUsed;

	POINT getDagame(int currentSkill, int inti)
	{
		return
		{
			minDamage + inti / 4 + (currentSkill - needSkillUse)
			, maxDamage + inti / 4 + (currentSkill - needSkillUse)
		};
	}*/
