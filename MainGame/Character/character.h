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
	//견 연 신
	GOUN,	//견이
	YOUN,	//연이
	SIN,		//신이
	NONEKIND
};

enum characterAction
{
	//움직이는 상태 
	CHA_IDLE, CHA_RIGHT, CHA_RIGHTDOWN, CHA_DOWN,
	CHA_LEFTDOWN, CHA_LEFT, CHA_LEFTUP, CHA_UP, CHA_RIGHTUP,
	//공격상태
	CHA_RIGHT_ATTACK, CHA_RIGHTDOWN_ATTACK, CHA_DOWN_ATTACK, CHA_LEFTDOWN_ATTACK,
	CHA_LEFT_ATTACK, CHA_LEFTUP_ATTACK, CHA_UP_ATTACK, CHA_RIGHTUP_ATTACK,
	//죽은상태
	CHA_DEATH
};

//플레이어가 있는 장소
enum tagPlace
{
	PLACE_TOWN, PLACE_HUNTING
};

class monsterManager;

class character :
	public gameNode
{
	
	//3개중 어떤 캐릭터이냐
	characterKind _characterKind;
	//캐릭터가 지금 무슨행동이냐
	characterAction _characterAction; 

	//캐릭터 선택화면을 위한 이미지 변수
	image* _selectImage;
	//플레이를 위한 이미지 변수
	image* _playImage;
	//캐릭터 애니메이션
	animation* _animation;
	//애니메이션 전체 담을 변수
	animation* _animationArray[CHA_DEATH + 1];

	RECT _characterRC;

	char _characterName[128];
	char _characterImageName[128];
	//실험용 테스트
	char _test[10];

	//플레이어가 있는 타일 인덱스
	int _tileIndexX, _tileIndexY;
	char _tiletest[111];

	//목적지 인덱스
	int _destTileIndexX, _destTileIndexY;
	//목적지 템프 인덱스
//	POINT _destTempTileIndex;

	//무슨맵에 플레이어가 있냐
	tagPlace _place;
	//포탈 클릭했냐
	bool _clickPotal;


	//이동하기위한 앵글값
	float _angle;
	//캐릭터 중점좌표
	float _x, _y;

	//버그수정을 위한 템프 좌표
	float _tempX, _tempY;


	//인벤토리
	inventory* _inven;
	//인벤토리 열었냐?
	bool _isInvenOpen;
	//인벤내 아이템 클릭했냐
	bool _isClickInvenItem;
	//인벤토리 RC
	RECT _invenRC;

	//장비창
	equip* _equip;
	//장비창 열었냐?
	bool _isEquipOpen;
	//장비창내 아이템 클릭했냐
	bool _isClickEquip;
	//장비창 RC
	RECT _equipRC;

	//플레이어 스탯
	status* _status;
	//스탯창 열었냐?
	bool _isStatusOpen;
	//스탯창 RC 
	RECT _statusRC;

	//플레이어 기술
	magicUI* _magic;
	//기술창 열었냐?
	bool _isMagicOpen;
	//기술창 RC
	RECT _magicRC;

	//플레이어 스킬
	skillUI* _skill;
	//스킬창 열었냐
	bool _isSkillOpen;
	//스킬창 RC
	RECT _skillRC;

	//NPC
	bool _isHosulamNpcClick;
	bool _isJanggumiNpcClick;
	bool _isMusuriNpcClick;

	//전투를 위한 몬스터 변수
	monsterParent* _targetMonster;
	//사냥터의 몬스터 매니저를 받아오기위한 전방선언
	monsterManager* _MM;

	//플레이어가 현재 있는 타일 및 속성
	tagTile _currentPlaceTile[ISOTILEX * ISOTILEY];
	DWORD	_currentPlaceAttribute[ISOTILEX * ISOTILEY];

	

	//플레이어 어택 딜레이 변수
	int _attackDelay;

	//aStar
	aStar* _aStar;

	char _aStarTest[111];
	//프레임 (나중에 키 애니메이션 변경필요)
	int _count;
	int _frameX;
public:
	character();
	~character();

	HRESULT init(const char* test, int characterKindNum);
	void release();
	void update();
	void render();

	void addImage();		//이미기 추가해주는 함수 이후 이미지는 여기서 add하는걸로
	void initialization();	//변수들 new선언 및 init 해주는 함수 이후 new 및 init은 여기서 하는걸로
	void singletonInit();	//init에서 싱글톤들 세팅해주는 함수 이후 세팅은 여기서 하는걸로

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

	//맵 이동시 실행됨
	void setCurrentPlaceTile(tagTile* currentPlaceTile)
	{
		for (int i = 0; i < ISOTILEX * ISOTILEY; ++i)
		{
			_currentPlaceTile[i] = currentPlaceTile[i];
		}

		_x = _currentPlaceTile[0].getCenterPoint().x;
		_y = _currentPlaceTile[0].getCenterPoint().y;
	}
	//이것 또한 실행
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

