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

//기술 요소
struct magicEle
{
	int needSkillUse;	//요구 기술
	int cooldownTime;	//쿨타임
	int useMP;			//mp소모량

	int minDamage;		//최소 데미지
	int maxDamage;		//최대 데미지

	int inti;			//도력(4당 마공 1)수치

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
	//창술의 기술이고
	_useWeaponType = WEAPON_SPEAR;
	//기술렙 3 이상이여야 쓸수 있다.
	_magicStat.needSkillUse = 3;
	//쿨타임은 3초
	_magicStat.cooldownTime = 300;
	//마나 소모량
	_magicStat.useMP = 10;
	//사용하지 않은상태이므로
	_magicStat.isUsed = _count = 0;

	//최소대미지
	_magicStat.minDamage = 3;
	//최대 대미지
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
