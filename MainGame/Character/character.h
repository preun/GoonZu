#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "status.h"
#include "inventory.h"
#include "equip.h"
#include "monsterParent.h"
#include "aStar.h"
#include "magicUI.h"
#include "skillUI.h"
#include "animation.h"

#define ATTACKDELAY 60
enum characterKind
{
	//�� �� ��
	GOUN,	//����
	YOUN,	//����
	SIN,		//����
	NONEKIND
};

enum characterAction
{
	//�����̴� ���� 
	CHA_IDLE, CHA_RIGHT, CHA_RIGHTDOWN, CHA_DOWN,
	CHA_LEFTDOWN, CHA_LEFT, CHA_LEFTUP, CHA_UP, CHA_RIGHTUP,
	//���ݻ���
	CHA_RIGHT_ATTACK, CHA_RIGHTDOWN_ATTACK, CHA_DOWN_ATTACK, CHA_LEFTDOWN_ATTACK,
	CHA_LEFT_ATTACK, CHA_LEFTUP_ATTACK, CHA_UP_ATTACK, CHA_RIGHTUP_ATTACK,
	//��������
	CHA_DEATH
};

//�÷��̾ �ִ� ���
enum tagPlace
{
	PLACE_TOWN, PLACE_HUNTING
};

class monsterManager;

class character :
	public gameNode
{
	
	//3���� � ĳ�����̳�
	characterKind _characterKind;
	//ĳ���Ͱ� ���� �����ൿ�̳�
	characterAction _characterAction; 

	//ĳ���� ����ȭ���� ���� �̹��� ����
	image* _selectImage;
	//�÷��̸� ���� �̹��� ����
	image* _playImage;
	//ĳ���� �ִϸ��̼�
	animation* _animation;
	//�ִϸ��̼� ��ü ���� ����
	animation* _animationArray[CHA_DEATH + 1];

	RECT _characterRC;

	char _characterName[128];
	char _characterImageName[128];
	//����� �׽�Ʈ
	char _test[10];

	//�÷��̾ �ִ� Ÿ�� �ε���
	int _tileIndexX, _tileIndexY;
	char _tiletest[111];

	//������ �ε���
	int _destTileIndexX, _destTileIndexY;
	//������ ���� �ε���
//	POINT _destTempTileIndex;

	//�����ʿ� �÷��̾ �ֳ�
	tagPlace _place;
	//��Ż Ŭ���߳�
	bool _clickPotal;


	//�̵��ϱ����� �ޱ۰�
	float _angle;
	//ĳ���� ������ǥ
	float _x, _y;

	//���׼����� ���� ���� ��ǥ
	float _tempX, _tempY;


	//�κ��丮
	inventory* _inven;
	//�κ��丮 ������?
	bool _isInvenOpen;
	//�κ��� ������ Ŭ���߳�
	bool _isClickInvenItem;
	//�κ��丮 RC
	RECT _invenRC;

	//���â
	equip* _equip;
	//���â ������?
	bool _isEquipOpen;
	//���â�� ������ Ŭ���߳�
	bool _isClickEquip;
	//���â RC
	RECT _equipRC;

	//�÷��̾� ����
	status* _status;
	//����â ������?
	bool _isStatusOpen;
	//����â RC 
	RECT _statusRC;

	//�÷��̾� ���
	magicUI* _magic;
	//���â ������?
	bool _isMagicOpen;
	//���â RC
	RECT _magicRC;

	//�÷��̾� ��ų
	skillUI* _skill;
	//��ųâ ������
	bool _isSkillOpen;
	//��ųâ RC
	RECT _skillRC;

	//NPC
	bool _isHosulamNpcClick;
	bool _isJanggumiNpcClick;
	bool _isMusuriNpcClick;

	//������ ���� ���� ����
	monsterParent* _targetMonster;
	//������� ���� �Ŵ����� �޾ƿ������� ���漱��
	monsterManager* _MM;

	//�÷��̾ ���� �ִ� Ÿ�� �� �Ӽ�
	tagTile _currentPlaceTile[ISOTILEX * ISOTILEY];
	DWORD	_currentPlaceAttribute[ISOTILEX * ISOTILEY];

	

	//�÷��̾� ���� ������ ����
	int _attackDelay;

	//aStar
	aStar* _aStar;

	char _aStarTest[111];
	//������ (���߿� Ű �ִϸ��̼� �����ʿ�)
	int _count;
	int _frameX;
public:
	character();
	~character();

	HRESULT init(const char* test, int characterKindNum);
	void release();
	void update();
	void render();

	void addImage();		//�̹̱� �߰����ִ� �Լ� ���� �̹����� ���⼭ add�ϴ°ɷ�
	void initialization();	//������ new���� �� init ���ִ� �Լ� ���� new �� init�� ���⼭ �ϴ°ɷ�
	void singletonInit();	//init���� �̱���� �������ִ� �Լ� ���� ������ ���⼭ �ϴ°ɷ�

	void mapChange();
	void animationChange();
	void lbuttonEvent();

	void characterActionDecide();
	void move(POINT tempPoint);

	void attack();
	void attacked(int damage);

	void selectRender(int i, bool isSelect);
	void selectAlphabetRender(int i);

	bool getPlayerPlace(){ return _place; }
	bool getClickPotal(){ return _clickPotal; }
	void setClickPotal(bool clickPotal){ _clickPotal = clickPotal; }

	void reborn(){ 
		_animationArray[CHA_DEATH]->start();
		//_animationArray[CHA_DEATH]->setNowPlayIndex(0);
	_characterAction = CHA_IDLE; _status->reborn();
	//_animationArray[CHA_DEATH]->setNowPlayIndex(0);
	}
	
	//void deathAniInit(){ _animationArray[CHA_DEATH]->setNowPlayIndex(0); }


	inventory* getInven(){ return _inven; }

	void makeRC();
	RECT getRC(){ return _characterRC; }

	int getTileIndexX(){ return _tileIndexX; }
	int getTileIndexY(){ return _tileIndexY; }

	bool getHosulamNpcClick(){ return _isHosulamNpcClick; }
	bool getJanggumiNpcClick(){ return _isJanggumiNpcClick; }
	bool getMusuriNpcClick(){ return _isMusuriNpcClick; }

	int* getMaxHP(){ return _status->getMaxHP(); }
	int* getCurrentHP(){ return _status->getCurrentHP(); }

	int* getMaxMP(){ return _status->getMaxMP(); }
	int* getCurrentMP(){ return _status->getCurrentMP(); }

	int* getExp(){ return _status->getExp(); }
	int* getLevel(){ return _status->getLevel(); }

	//�� �̵��� �����
	void setCurrentPlaceTile(tagTile* currentPlaceTile)
	{
		for (int i = 0; i < ISOTILEX * ISOTILEY; ++i)
		{
			_currentPlaceTile[i] = currentPlaceTile[i];
		}

		_x = _currentPlaceTile[0].getCenterPoint().x;
		_y = _currentPlaceTile[0].getCenterPoint().y;
	}
	//�̰� ���� ����
	void setCurrentPlaceAttribute(DWORD* currentPlaceAttribute)
	{
		{
			for (int i = 0; i < ISOTILEX * ISOTILEY; ++i)
			{
				_currentPlaceAttribute[i] = currentPlaceAttribute[i];
			}
		}
	}
	//int getCharacterKind(){ return (int)_characterKind; }

	aStar* getPlayerAStar(){ return _aStar; }
	void setMonsterManagerAddressLink(monsterManager* MM){ _MM = MM; }
};

