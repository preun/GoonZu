#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "aStar.h"
#include "animation.h"


enum tagMonsterState{

	//움직이는 상태 
	MON_IDLE, MON_RIGHT, MON_RIGHTDOWN, MON_DOWN,
	MON_LEFTDOWN, MON_LEFT, MON_LEFTUP, MON_UP, MON_RIGHTUP,
	//공격상태
	MON_RIGHT_ATTACK, MON_RIGHTDOWN_ATTACK, MON_DOWN_ATTACK, MON_LEFTDOWN_ATTACK,
	MON_LEFT_ATTACK, MON_LEFTUP_ATTACK, MON_UP_ATTACK, MON_RIGHTUP_ATTACK,
	//피격상태
	MON_DAMAGED
};
class character;

class monsterParent :
	public gameNode
{
protected:

	char plz[111];

	image* _monsterImage; //몬스터 이미지
	animation* _animation; //몬스터 애니메이션
	animation* _animationArray[MON_RIGHTUP_ATTACK + 1]; //몬스터 애니메이션 배열


	int _monsterLevel;	//몬스터 레벨(리스폰 될때마다 랜덤설정)
	//int _dropExp;	//드랍경험치
	//int _dropMoney;	//드랍 돈(리스폰 될떄마다 랜덤설정)

	int _maxHP;		//몬스터 최대 피(리스폰 될떄마다 랜덤설정 

	int _currentHP;	//몬스터 현재 피

	int _damage;		//몬스터 딜(리스폰 될때마다 랜덤설정)
	int _def;		//몬스터 방어력(리스폰 될때마다 랜덤설정)

	bool _isDead;	//몬스터가 죽었냐
	bool _isFirst;	//선공몬스터냐
	int _respondCount;	//몬스터가 죽고 리스폰 시간

	float _x, _y;
	int _renderX, _renderY;	//몬스터가 그려지는 지점을 위한 좌표변수

	int _tileIndexX, _tileIndexY; //몬스터의 현재 타일 좌표
	int _destTileIndexX, _destTileIndexY;	//몬스터의 목표 좌표

	float _angle;

	int _attackDelay;	//몬스터 어택 딜레이

	int _count, _moveCount;	

	tagMonsterState _monsterState;

	tagTile _HuntingPlaceTile[ISOTILEX * ISOTILEY];
	DWORD	_HuntingPlaceAttribute[ISOTILEX * ISOTILEY];
	
	//몬스터 에이스타
	aStar* _aStar;
	//나를 공격한놈이 누군지 알기위한 전방선언 변수
	character* _playPlayer;

	//애니메이션은 나중에 추가
	//회피 명중률 크리같은 스탯은 나중에 추가
public:
	monsterParent();
	~monsterParent();
	//혹시 몰라서 오버로딩
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
		//몬스터의 방어력만큼 데미지 감소시키고
		int tempHP = attacked - _def;
		//감소시킨값이 0보다 작아지면 강제로 받는 피해는 1로 보정
		if (tempHP <= 0) tempHP = 1;
		//현재피 까주고
		_currentHP -= tempHP;
 //피가 0보다 작아지면 몬스터는 사망
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

	int rndLevel(int level);	//리스폰시 몬스터레벨 랜덤설정함수 (원하는 값 주면 -1 ~ +1 사이값 랜덤출력
	int getLevel(){ return _monsterLevel; } //몬스터 레벨 반환

	RECT getMonsterRC(){ return RectMake(CAMERAMANAGER->CameraRelativePointX( _renderX),
		CAMERAMANAGER->CameraRelativePointY(_renderY), _monsterImage->getFrameWidth(), _monsterImage->getFrameHeight());
	}
	//실험용함수들
	void setIsDead(bool isDead){ _isDead = isDead; }
	bool getIsDead(){ return _isDead; }	//몬스터 상태 반환
	
	int getRespondCount(){ return _respondCount; }	//몬스터 리스폰 카운트 반환

	int getTileIndexX(){ return _tileIndexX; }
	int getTileIndexY(){ return _tileIndexY; }

	void HPDraw();
	//int rndExp();	//리스폰시 몬스터경험치 랜덤설정함수(레벨에 따라 설정됨)
	//int rndMoney();	//리스폰시 몬스터돈 랜덤설정함수	  (레벨에 따라 설정됨)
	int rndHP();	//리스폰시 몬스터피 랜덤설정함수	  (레벨에 따라 설정됨)
	int rndDamage();	//리스폰시 몬스터딜 랜덤설정함수(레벨에 따라 설정됨)
	int rndDef();	//리스폰시 몬스터방어력 랜덤설정함수(레벨에 따라 설정됨)
};

