//����ϴ� ������ Ÿ���� ����
enum useWeaponType
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
	
	int needSkillUse;	//�䱸 ��� ����
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
	}


};