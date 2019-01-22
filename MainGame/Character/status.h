#pragma once
#include "gameNode.h"
#include "statusUtil.h"

class status :
	public gameNode
{
	int _level;		//����
	int _exp;		//����ġ

	int _maxHP;		//Ǯ��
	int _currentHP;	//��

	int _maxMP;		//Ǯ ����
	int _currentMP;	//����

	int _str;		//�ٷ�
	int _dex;		//���߷�
	int _int;		//����
	int _life;		//�����
	int _luk;		//������

	int _statBonus;	//�̺й� ����ġ

	int _minAtt;		//�ּ� ���ݷ�
	int _maxAtt;		//�ִ� ���ݷ�

	int _def;		//����


	//10���� ���Ⱥο� ��ư
	RECT _statusButtonRC[LUKMINUS];

	int test1;	//��Ʈ �׽�Ʈ
	int test2;

public:
	status();
	~status();

	HRESULT init();
	void release();
	void update();
	void render();

	//���ȿ����Լ�
	void statusOpen(char* characterName);

	//����ġ ȹ�� �� ����
	void setExp(int exp);

	//���Ⱥй��Լ�			���� �ּҴ�			���� �ִ��			�� ����
	void statusDistribution(int weaponMinAtt, int weaponMaxAtt, int armorDef);
	
	//�������� ��������
	void setStatBonus(int bonus){ _statBonus += bonus; }
	void setStr(int str){ _str += str; }
	int getStr(){ return _str; }

	void setDex(int dex){ _dex += dex; }

	void setInt(int intel){ _int += intel; _maxMP = 30 + (_int - 5) * 4; }		//���½���
	//void setMaxMP(int maxMP){ _maxMP += maxMP; }	//���� �ø��� ��������

	void setLife(int life){ _life += life; _maxHP = 50 + (_life - 5) * 4; }		//����½���	
	//void setMaxHP(int maxHP){ _maxHP += maxHP; }	//����� �ø��� ���� ����

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
		//������ ���¸�ŭ ������ ���ҽ�Ű��
		int tempHP = damage - _def;
		//���ҽ�Ų���� 0���� �۾����� ������ �޴� ���ش� 1�� ����
		if (tempHP < 0) tempHP = 1;
		//������ ���ְ�
		_currentHP -= tempHP;
		//�ǰ� 0���� �۾����� �÷��̾�� ���
		//if (_currentHP < 0)
		//{
		//	_isDead = true;
		//	_playPlayer = NULL;
		//	return;
		//}
	}

	void setLuk(int luck){ _luk += luck; }

	//�⺻ ������ + �� ��ġ + ������ ������ ���ݷ¸�ŭ
	void setMinAtt(int weaponMinAtt){ _minAtt  = 1 + _str/2.5 + weaponMinAtt; }
	void setMaxAtt(int weaponMaxAtt) { _maxAtt = 3 + _str/2.5 + weaponMaxAtt; }
	//�������� �ִ� ������ ��������
	//�ּҰ� �ִ밪 ���̿��� ������ ��������
	int getAtt(){ return RND->getFromIntTo(_minAtt, _maxAtt); }

	int getInt(){ return _int; }

	//�⺻ ���� + ������ ���� ����
	void setDef(int armorDef){ _def = 5 + armorDef; }

	void setDef(int armorDef1, int armorDef2){ _def = 5 + armorDef1 + armorDef2; }

	
	int* getMaxHP(){ return &_maxHP; }
	int* getCurrentHP(){ return &_currentHP; }

	int* getMaxMP(){ return &_maxMP; }
	int* getCurrentMP(){ return &_currentMP; }

	int* getLevel(){ return &_level; }
	int* getExp(){ return &_exp; }


	//void setDef(int armorDef){ _def = 5 + armorDef; }

	//���� �ǰ� ������(�ϴ� ŵ)
	//int getAtt(){ return _att; }	
	//int getDef(){ return _def; }
};