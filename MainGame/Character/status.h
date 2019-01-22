#pragma once
#include "gameNode.h"
#include "statusUtil.h"

class status :
	public gameNode
{
	int _level;		//레벨
	int _exp;		//경험치

	int _maxHP;		//풀피
	int _currentHP;	//피

	int _maxMP;		//풀 엠피
	int _currentMP;	//엠피

	int _str;		//근력
	int _dex;		//순발력
	int _int;		//도력
	int _life;		//생명력
	int _luk;		//손재주

	int _statBonus;	//미분배 스탯치

	int _minAtt;		//최소 공격력
	int _maxAtt;		//최대 공격력

	int _def;		//방어력


	//10개의 스탯부여 버튼
	RECT _statusButtonRC[LUKMINUS];

	int test1;	//폰트 테스트
	int test2;

public:
	status();
	~status();

	HRESULT init();
	void release();
	void update();
	void render();

	//스탯오픈함수
	void statusOpen(char* characterName);

	//경험치 획득 및 렙업
	void setExp(int exp);

	//스탯분배함수			무기 최소댐			무기 최대댐			방어구 방어력
	void statusDistribution(int weaponMinAtt, int weaponMaxAtt, int armorDef);
	
	//레벨업시 스탯조절
	void setStatBonus(int bonus){ _statBonus += bonus; }
	void setStr(int str){ _str += str; }
	int getStr(){ return _str; }

	void setDex(int dex){ _dex += dex; }

	void setInt(int intel){ _int += intel; _maxMP = 30 + (_int - 5) * 4; }		//도력스탯
	//void setMaxMP(int maxMP){ _maxMP += maxMP; }	//도력 올리면 엠통증가

	void setLife(int life){ _life += life; _maxHP = 50 + (_life - 5) * 4; }		//생명력스탯	
	//void setMaxHP(int maxHP){ _maxHP += maxHP; }	//생명력 올리면 피통 증가

	void reborn(){ _currentHP = _maxHP; }
	void setPotionHP(int HP)
	{
		_currentHP += HP;
		if (_currentHP > _maxHP) _currentHP = _maxHP;
	}
	void setPotionMP(int MP)
	{
		_currentMP += MP;
		if (_currentMP > _maxMP) _currentMP = _maxMP;
	}
	void setCurrentHP(int damage)
	{
		//몬스터의 방어력만큼 데미지 감소시키고
		int tempHP = damage - _def;
		//감소시킨값이 0보다 작아지면 강제로 받는 피해는 1로 보정
		if (tempHP < 0) tempHP = 1;
		//현재피 까주고
		_currentHP -= tempHP;
		//피가 0보다 작아지면 플레이어는 사망
		//if (_currentHP < 0)
		//{
		//	_isDead = true;
		//	_playPlayer = NULL;
		//	return;
		//}
	}

	void setLuk(int luck){ _luk += luck; }

	//기본 데미지 + 힘 수치 + 장착한 무기의 공격력만큼
	void setMinAtt(int weaponMinAtt){ _minAtt  = 1 + _str/2.5 + weaponMinAtt; }
	void setMaxAtt(int weaponMaxAtt) { _maxAtt = 3 + _str/2.5 + weaponMaxAtt; }
	//몬스터한테 주는 데미지 가져오기
	//최소값 최대값 사이에서 랜덤값 가져오기
	int getAtt(){ return RND->getFromIntTo(_minAtt, _maxAtt); }

	int getInt(){ return _int; }

	//기본 방어력 + 장착한 방어구의 방어력
	void setDef(int armorDef){ _def = 5 + armorDef; }

	void setDef(int armorDef1, int armorDef2){ _def = 5 + armorDef1 + armorDef2; }

	
	int* getMaxHP(){ return &_maxHP; }
	int* getCurrentHP(){ return &_currentHP; }

	int* getMaxMP(){ return &_maxMP; }
	int* getCurrentMP(){ return &_currentMP; }

	int* getLevel(){ return &_level; }
	int* getExp(){ return &_exp; }


	//void setDef(int armorDef){ _def = 5 + armorDef; }

	//어택 피격 접근자(일단 킵)
	//int getAtt(){ return _att; }	
	//int getDef(){ return _def; }
};