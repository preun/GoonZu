//사용하는 무기의 타입은 뭐냐
enum useWeaponType
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
	
	int needSkillUse;	//요구 기술 제한
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
	}


};