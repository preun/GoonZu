#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "aStar.h"
#include "animation.h"


enum tagMonsterState{

	//�����̴� ���� 
	MON_IDLE, MON_RIGHT, MON_RIGHTDOWN, MON_DOWN,
	MON_LEFTDOWN, MON_LEFT, MON_LEFTUP, MON_UP, MON_RIGHTUP,
	//���ݻ���
	MON_RIGHT_ATTACK, MON_RIGHTDOWN_ATTACK, MON_DOWN_ATTACK, MON_LEFTDOWN_ATTACK,
	MON_LEFT_ATTACK, MON_LEFTUP_ATTACK, MON_UP_ATTACK, MON_RIGHTUP_ATTACK,
	//�ǰݻ���
	MON_DAMAGED
};
class character;

class monsterParent :
	public gameNode
{
protected:

	char plz[111];

	image* _monsterImage; //���� �̹���
	animation* _animation; //���� �ִϸ��̼�
	animation* _animationArray[MON_RIGHTUP_ATTACK + 1]; //���� �ִϸ��̼� �迭


	int _monsterLevel;	//���� ����(������ �ɶ����� ��������)
	//int _dropExp;	//�������ġ
	//int _dropMoney;	//��� ��(������ �ɋ����� ��������)

	int _maxHP;		//���� �ִ� ��(������ �ɋ����� �������� 

	int _currentHP;	//���� ���� ��

	int _damage;		//���� ��(������ �ɶ����� ��������)
	int _def;		//���� ����(������ �ɶ����� ��������)

	bool _isDead;	//���Ͱ� �׾���
	bool _isFirst;	//�������ͳ�
	int _respondCount;	//���Ͱ� �װ� ������ �ð�

	float _x, _y;
	int _renderX, _renderY;	//���Ͱ� �׷����� ������ ���� ��ǥ����

	int _tileIndexX, _tileIndexY; //������ ���� Ÿ�� ��ǥ
	int _destTileIndexX, _destTileIndexY;	//������ ��ǥ ��ǥ

	float _angle;

	int _attackDelay;	//���� ���� ������

	int _count, _moveCount;	

	tagMonsterState _monsterState;

	tagTile _HuntingPlaceTile[ISOTILEX * ISOTILEY];
	DWORD	_HuntingPlaceAttribute[ISOTILEX * ISOTILEY];
	
	//���� ���̽�Ÿ
	aStar* _aStar;
	//���� �����ѳ��� ������ �˱����� ���漱�� ����
	character* _playPlayer;

	//�ִϸ��̼��� ���߿� �߰�
	//ȸ�� ���߷� ũ������ ������ ���߿� �߰�
public:
	monsterParent();
	~monsterParent();
	//Ȥ�� ���� �����ε�
	virtual HRESULT init();
	virtual HRESULT init(int respond);

	virtual void release();
	virtual void update();
	virtual void deadUpdate();
	virtual void render();

	virtual void addImage();
	virtual void drawIdleEffect();
	virtual void animationChange();

	void setPlaceTileAndAtt(tagTile* placeTile, DWORD* placeTileAtt)
	{

		for (int i = 0; i < ISOTILEX * ISOTILEY; ++i)
		{
			_HuntingPlaceTile[i] = placeTile[i];
			_HuntingPlaceAttribute[i] = placeTileAtt[i];
		}
	}

	void setAttackedHP(int attacked){
		//������ ���¸�ŭ ������ ���ҽ�Ű��
		int tempHP = attacked - _def;
		//���ҽ�Ų���� 0���� �۾����� ������ �޴� ���ش� 1�� ����
		if (tempHP <= 0) tempHP = 1;
		//������ ���ְ�
		_currentHP -= tempHP;
 //�ǰ� 0���� �۾����� ���ʹ� ���
		if (_currentHP <= 0)
		{
			_isDead = true;
			SAFE_DELETE(_aStar);
			_playPlayer = NULL;
			return;
		}
	}

	void mosterActionDecide();
	void move(POINT tempPoint);

	virtual void playerAttack();

	void setMemoryAddressLink(character* player){ _playPlayer = player; }

	int getHP(){ return _currentHP; }

	int rndLevel(int level);	//�������� ���ͷ��� ���������Լ� (���ϴ� �� �ָ� -1 ~ +1 ���̰� �������
	int getLevel(){ return _monsterLevel; } //���� ���� ��ȯ

	RECT getMonsterRC(){ return RectMake(CAMERAMANAGER->CameraRelativePointX( _renderX),
		CAMERAMANAGER->CameraRelativePointY(_renderY), _monsterImage->getFrameWidth(), _monsterImage->getFrameHeight());
	}
	//������Լ���
	void setIsDead(bool isDead){ _isDead = isDead; }
	bool getIsDead(){ return _isDead; }	//���� ���� ��ȯ
	
	int getRespondCount(){ return _respondCount; }	//���� ������ ī��Ʈ ��ȯ

	int getTileIndexX(){ return _tileIndexX; }
	int getTileIndexY(){ return _tileIndexY; }

	void HPDraw();
	//int rndExp();	//�������� ���Ͱ���ġ ���������Լ�(������ ���� ������)
	//int rndMoney();	//�������� ���͵� ���������Լ�	  (������ ���� ������)
	int rndHP();	//�������� ������ ���������Լ�	  (������ ���� ������)
	int rndDamage();	//�������� ���͵� ���������Լ�(������ ���� ������)
	int rndDef();	//�������� ���͹��� ���������Լ�(������ ���� ������)
};

