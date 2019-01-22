#include "stdafx.h"
#include "pigMonster.h"
#include "character.h"

pigMonster::pigMonster()
{
}


pigMonster::~pigMonster()
{
	
}

HRESULT pigMonster::init()
{
	addImage();
	

	_monsterLevel = rndLevel(2);
	//_dropExp;	//드랍경험치(리스폰 될때마다 랜덤설정)
	//_dropMoney;	//드랍 돈(리스폰 될떄마다 랜덤설정)

	_maxHP = _monsterLevel * 6;		//몬스터 최대 피(리스폰 될떄마다 랜덤설정 
	_currentHP = _maxHP;	//몬스터 현재 피

	_damage = _monsterLevel * 2;		//몬스터 딜(리스폰 될때마다 랜덤설정)
	_def = _monsterLevel * 1;		//몬스터 방어력(리스폰 될때마다 랜덤설정)

	_isDead = false;	//몬스터가 죽었냐
	_respondCount = 0;	//몬스터가 죽고 리스폰 시간

	_playPlayer = NULL;
	return S_OK;
}
HRESULT pigMonster::init(int respond)
{
	addImage();

	_monsterLevel = rndLevel(2);
	//_dropExp;	//드랍경험치(리스폰 될때마다 랜덤설정)
	//_dropMoney;	//드랍 돈(리스폰 될떄마다 랜덤설정)

	_maxHP = _monsterLevel * 6;		//몬스터 최대 피(리스폰 될떄마다 랜덤설정 
	_currentHP = _maxHP;	//몬스터 현재 피

	_damage = _monsterLevel * 4;		//몬스터 딜(리스폰 될때마다 랜덤설정)
	_def = _monsterLevel * 1;		//몬스터 방어력(리스폰 될때마다 랜덤설정)

	_isDead = false;	//몬스터가 죽었냐
	_respondCount = 0;	//몬스터가 죽고 리스폰 시간

	_renderX = _HuntingPlaceTile[respond].getCenterPoint().x - _monsterImage->getFrameWidth() / 2 ;
	_renderY = _HuntingPlaceTile[respond].getCenterPoint().y - _monsterImage->getFrameHeight() / 2;

	_x = _HuntingPlaceTile[respond].getCenterPoint().x;
	_y = _HuntingPlaceTile[respond].getCenterPoint().y;

	_destTileIndexX = _tileIndexX = respond / 20;
	_destTileIndexY = _tileIndexY = respond % 20;

	_attackDelay = 0;
	_playPlayer = NULL;

	_monsterState = MON_IDLE;

	_moveCount = RND->getFromIntTo(100, 300);
	_count = 0;
	_angle = 0;
	
	_aStar = new aStar;
	_aStar->init();

	_idleEffectAnimation = new animation;
	_idleEffectAnimation -> init(IMAGEMANAGER->findImage("돼지기본효과")->getWidth(), IMAGEMANAGER->findImage("돼지기본효과")->getHeight(),
		IMAGEMANAGER->findImage("돼지기본효과")->getFrameWidth(), IMAGEMANAGER->findImage("돼지기본효과")->getFrameHeight());
	_idleEffectAnimation->setDefPlayFrame(true, true);
	_idleEffectAnimation->start();
	_idleEffectAnimation->setFPS(1);

	//기본
	_animationArray[MON_IDLE] = new animation;
	_animationArray[MON_IDLE]->init(IMAGEMANAGER->findImage("돼지기본")->getWidth(), IMAGEMANAGER->findImage("돼지기본")->getHeight(),
		IMAGEMANAGER->findImage("돼지기본")->getFrameWidth(), IMAGEMANAGER->findImage("돼지기본")->getFrameHeight());
	_animationArray[MON_IDLE]->setDefPlayFrame(false, true);
	_animationArray[MON_IDLE]->start();
	_animationArray[MON_IDLE]->setFPS(1);

	//오른쪽 걷기
	_animationArray[MON_RIGHT] = new animation;
	_animationArray[MON_RIGHT]->init(IMAGEMANAGER->findImage("돼지오른쪽")->getWidth(), IMAGEMANAGER->findImage("돼지오른쪽")->getHeight(),
		IMAGEMANAGER->findImage("돼지오른쪽")->getFrameWidth(), IMAGEMANAGER->findImage("돼지오른쪽")->getFrameHeight());
	_animationArray[MON_RIGHT]->setDefPlayFrame(false, true);
	_animationArray[MON_RIGHT]->start();
	_animationArray[MON_RIGHT]->setFPS(1);

	//오른쪽 아래 걷기
	_animationArray[MON_RIGHTDOWN] = new animation;
	_animationArray[MON_RIGHTDOWN]->init(IMAGEMANAGER->findImage("돼지오른쪽아래")->getWidth(), IMAGEMANAGER->findImage("돼지오른쪽아래")->getHeight(),
		IMAGEMANAGER->findImage("돼지오른쪽아래")->getFrameWidth(), IMAGEMANAGER->findImage("돼지오른쪽아래")->getFrameHeight());
	_animationArray[MON_RIGHTDOWN]->setDefPlayFrame(false, true);
	_animationArray[MON_RIGHTDOWN]->start();
	_animationArray[MON_RIGHTDOWN]->setFPS(1);

	//아래 걷기
	_animationArray[MON_DOWN] = new animation;
	_animationArray[MON_DOWN]->init(IMAGEMANAGER->findImage("돼지아래")->getWidth(), IMAGEMANAGER->findImage("돼지아래")->getHeight(),
		IMAGEMANAGER->findImage("돼지아래")->getFrameWidth(), IMAGEMANAGER->findImage("돼지아래")->getFrameHeight());
	_animationArray[MON_DOWN]->setDefPlayFrame(false, true);
	_animationArray[MON_DOWN]->start();
	_animationArray[MON_DOWN]->setFPS(1);

	//왼쪽 아래 걷기
	_animationArray[MON_LEFTDOWN] = new animation;
	_animationArray[MON_LEFTDOWN]->init(IMAGEMANAGER->findImage("돼지왼쪽아래")->getWidth(), IMAGEMANAGER->findImage("돼지왼쪽아래")->getHeight(),
		IMAGEMANAGER->findImage("돼지왼쪽아래")->getFrameWidth(), IMAGEMANAGER->findImage("돼지왼쪽아래")->getFrameHeight());
	_animationArray[MON_LEFTDOWN]->setDefPlayFrame(false, true);
	_animationArray[MON_LEFTDOWN]->start();
	_animationArray[MON_LEFTDOWN]->setFPS(1);

	//왼쪽 걷기
	_animationArray[MON_LEFT] = new animation;
	_animationArray[MON_LEFT]->init(IMAGEMANAGER->findImage("돼지왼쪽")->getWidth(), IMAGEMANAGER->findImage("돼지왼쪽")->getHeight(),
		IMAGEMANAGER->findImage("돼지왼쪽")->getFrameWidth(), IMAGEMANAGER->findImage("돼지왼쪽")->getFrameHeight());
	_animationArray[MON_LEFT]->setDefPlayFrame(false, true);
	_animationArray[MON_LEFT]->start();
	_animationArray[MON_LEFT]->setFPS(1);

	//왼쪽 위 걷기
	_animationArray[MON_LEFTUP] = new animation;
	_animationArray[MON_LEFTUP]->init(IMAGEMANAGER->findImage("돼지왼쪽위")->getWidth(), IMAGEMANAGER->findImage("돼지왼쪽위")->getHeight(),
		IMAGEMANAGER->findImage("돼지왼쪽위")->getFrameWidth(), IMAGEMANAGER->findImage("돼지왼쪽위")->getFrameHeight());
	_animationArray[MON_LEFTUP]->setDefPlayFrame(false, true);
	_animationArray[MON_LEFTUP]->start();
	_animationArray[MON_LEFTUP]->setFPS(1);

	//위 걷기
	_animationArray[MON_UP] = new animation;
	_animationArray[MON_UP]->init(IMAGEMANAGER->findImage("돼지위")->getWidth(), IMAGEMANAGER->findImage("돼지위")->getHeight(),
		IMAGEMANAGER->findImage("돼지위")->getFrameWidth(), IMAGEMANAGER->findImage("돼지위")->getFrameHeight());
	_animationArray[MON_UP]->setDefPlayFrame(false, true);
	_animationArray[MON_UP]->start();
	_animationArray[MON_UP]->setFPS(1);

	//오른쪽 위 걷기
	_animationArray[MON_RIGHTUP] = new animation;
	_animationArray[MON_RIGHTUP]->init(IMAGEMANAGER->findImage("돼지오른쪽위")->getWidth(), IMAGEMANAGER->findImage("돼지오른쪽위")->getHeight(),
		IMAGEMANAGER->findImage("돼지오른쪽위")->getFrameWidth(), IMAGEMANAGER->findImage("돼지오른쪽위")->getFrameHeight());
	_animationArray[MON_RIGHTUP]->setDefPlayFrame(false, true);
	_animationArray[MON_RIGHTUP]->start();
	_animationArray[MON_RIGHTUP]->setFPS(1);

	//오른쪽 공격
	_animationArray[MON_RIGHT_ATTACK] = new animation;
	_animationArray[MON_RIGHT_ATTACK]->init(IMAGEMANAGER->findImage("돼지오른쪽공격")->getWidth(), IMAGEMANAGER->findImage("돼지오른쪽공격")->getHeight(),
		IMAGEMANAGER->findImage("돼지오른쪽공격")->getFrameWidth(), IMAGEMANAGER->findImage("돼지오른쪽공격")->getFrameHeight());
	_animationArray[MON_RIGHT_ATTACK]->setDefPlayFrame(false, true);
	_animationArray[MON_RIGHT_ATTACK]->start();
	_animationArray[MON_RIGHT_ATTACK]->setFPS(1);
	
	//오른쪽 아래 공격
	_animationArray[MON_RIGHTDOWN_ATTACK] = new animation;
	_animationArray[MON_RIGHTDOWN_ATTACK]->init(IMAGEMANAGER->findImage("돼지오른쪽아래공격")->getWidth(), IMAGEMANAGER->findImage("돼지오른쪽아래공격")->getHeight(),
		IMAGEMANAGER->findImage("돼지오른쪽아래공격")->getFrameWidth(), IMAGEMANAGER->findImage("돼지오른쪽아래공격")->getFrameHeight());
	_animationArray[MON_RIGHTDOWN_ATTACK]->setDefPlayFrame(false, true);
	_animationArray[MON_RIGHTDOWN_ATTACK]->start();
	_animationArray[MON_RIGHTDOWN_ATTACK]->setFPS(1);
	
	//아래 공격
	_animationArray[MON_DOWN_ATTACK] = new animation;
	_animationArray[MON_DOWN_ATTACK]->init(IMAGEMANAGER->findImage("돼지아래공격")->getWidth(), IMAGEMANAGER->findImage("돼지아래공격")->getHeight(),
		IMAGEMANAGER->findImage("돼지아래공격")->getFrameWidth(), IMAGEMANAGER->findImage("돼지아래공격")->getFrameHeight());
	_animationArray[MON_DOWN_ATTACK]->setDefPlayFrame(false, true);
	_animationArray[MON_DOWN_ATTACK]->start();
	_animationArray[MON_DOWN_ATTACK]->setFPS(1);
	
	//왼쪽 아래 공격
	_animationArray[MON_LEFTDOWN_ATTACK] = new animation;
	_animationArray[MON_LEFTDOWN_ATTACK]->init(IMAGEMANAGER->findImage("돼지왼쪽아래공격")->getWidth(), IMAGEMANAGER->findImage("돼지왼쪽아래공격")->getHeight(),
		IMAGEMANAGER->findImage("돼지왼쪽아래공격")->getFrameWidth(), IMAGEMANAGER->findImage("돼지왼쪽아래공격")->getFrameHeight());
	_animationArray[MON_LEFTDOWN_ATTACK]->setDefPlayFrame(false, true);
	_animationArray[MON_LEFTDOWN_ATTACK]->start();
	_animationArray[MON_LEFTDOWN_ATTACK]->setFPS(1);
	
	//왼쪽 공격
	_animationArray[MON_LEFT_ATTACK] = new animation;
	_animationArray[MON_LEFT_ATTACK]->init(IMAGEMANAGER->findImage("돼지왼쪽공격")->getWidth(), IMAGEMANAGER->findImage("돼지왼쪽공격")->getHeight(),
		IMAGEMANAGER->findImage("돼지왼쪽공격")->getFrameWidth(), IMAGEMANAGER->findImage("돼지왼쪽공격")->getFrameHeight());
	_animationArray[MON_LEFT_ATTACK]->setDefPlayFrame(false, true);
	_animationArray[MON_LEFT_ATTACK]->start();
	_animationArray[MON_LEFT_ATTACK]->setFPS(1);
	
	//왼쪽 위 공격
	_animationArray[MON_LEFTUP_ATTACK] = new animation;
	_animationArray[MON_LEFTUP_ATTACK]->init(IMAGEMANAGER->findImage("돼지왼쪽위공격")->getWidth(), IMAGEMANAGER->findImage("돼지왼쪽위공격")->getHeight(),
		IMAGEMANAGER->findImage("돼지왼쪽위공격")->getFrameWidth(), IMAGEMANAGER->findImage("돼지왼쪽위공격")->getFrameHeight());
	_animationArray[MON_LEFTUP_ATTACK]->setDefPlayFrame(false, true);
	_animationArray[MON_LEFTUP_ATTACK]->start();
	_animationArray[MON_LEFTUP_ATTACK]->setFPS(1);
	
	//위 공격
	_animationArray[MON_UP_ATTACK] = new animation;
	_animationArray[MON_UP_ATTACK]->init(IMAGEMANAGER->findImage("돼지위공격")->getWidth(), IMAGEMANAGER->findImage("돼지위공격")->getHeight(),
		IMAGEMANAGER->findImage("돼지위공격")->getFrameWidth(), IMAGEMANAGER->findImage("돼지위공격")->getFrameHeight());
	_animationArray[MON_UP_ATTACK]->setDefPlayFrame(false, true);
	_animationArray[MON_UP_ATTACK]->start();
	_animationArray[MON_UP_ATTACK]->setFPS(1);
	
	//오른쪽 위 공격
	_animationArray[MON_RIGHTUP_ATTACK] = new animation;
	_animationArray[MON_RIGHTUP_ATTACK]->init(IMAGEMANAGER->findImage("돼지오른쪽위공격")->getWidth(), IMAGEMANAGER->findImage("돼지오른쪽위공격")->getHeight(),
		IMAGEMANAGER->findImage("돼지오른쪽위공격")->getFrameWidth(), IMAGEMANAGER->findImage("돼지오른쪽위공격")->getFrameHeight());
	_animationArray[MON_RIGHTUP_ATTACK]->setDefPlayFrame(false, true);
	_animationArray[MON_RIGHTUP_ATTACK]->start();
	_animationArray[MON_RIGHTUP_ATTACK]->setFPS(1);



	_animation = _animationArray[MON_IDLE]; //초기값은 돼지 기본

	return S_OK;
}
void pigMonster::addImage()
{
	_idleEffect = IMAGEMANAGER->addFrameImage("돼지기본효과", "./image/monster/pig/돼지idle1.bmp", 114, 30, 3, 1, true, RGB(255, 0, 255));

	_monsterImage = IMAGEMANAGER->addFrameImage("돼지기본", "./image/monster/pig/돼지idle.bmp", 24, 38, 1, 1, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("돼지오른쪽", "./image/monster/pig/돼지right.bmp", 300, 41, 6, 1, true, RGB(255, 0, 255)); //몬스터 이미지
	IMAGEMANAGER->addFrameImage("돼지오른쪽아래", "./image/monster/pig/돼지rightdown.bmp", 168, 39, 4, 1, true, RGB(255, 0, 255)); 
	IMAGEMANAGER->addFrameImage("돼지아래", "./image/monster/pig/돼지down.bmp", 96, 39, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("돼지왼쪽아래", "./image/monster/pig/돼지leftdown.bmp", 168, 38, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("돼지왼쪽", "./image/monster/pig/돼지left.bmp", 300, 41, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("돼지왼쪽위", "./image/monster/pig/돼지leftup.bmp", 168, 50, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("돼지위", "./image/monster/pig/돼지up.bmp", 96, 47, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("돼지오른쪽위", "./image/monster/pig/돼지rightup.bmp", 168, 50, 4, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("돼지오른쪽공격", "./image/monster/pig/돼지rightattack.bmp", 345, 59, 5, 1, true, RGB(255, 0, 255)); //몬스터 이미지
	IMAGEMANAGER->addFrameImage("돼지오른쪽아래공격", "./image/monster/pig/돼지rightdownattack.bmp", 260, 45, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("돼지아래공격", "./image/monster/pig/돼지downattack.bmp", 190, 45, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("돼지왼쪽아래공격", "./image/monster/pig/돼지leftdownattack.bmp", 260, 45, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("돼지왼쪽공격", "./image/monster/pig/돼지leftattack.bmp", 345, 59, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("돼지왼쪽위공격", "./image/monster/pig/돼지leftupattack.bmp", 260, 57, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("돼지위공격", "./image/monster/pig/돼지upattack.bmp", 190, 65, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("돼지오른쪽위공격", "./image/monster/pig/돼지rightupattack.bmp", 260, 57, 5, 1, true, RGB(255, 0, 255));

}
void pigMonster::drawIdleEffect()
{
	if (_monsterState == MON_IDLE)
	{
		_idleEffect->aniRender(getMemDC(), CAMERAMANAGER->CameraRelativePointX(_renderX), CAMERAMANAGER->CameraRelativePointY(_renderY) - 30, _idleEffectAnimation);
	}
}
void pigMonster::release()
{

}
void pigMonster::update()
{
	_animation->frameUpdate(TIMEMANAGER->getElapsedTime() * 5);
	_idleEffectAnimation->frameUpdate(TIMEMANAGER->getElapsedTime());
	//몬스터 상태가 가만이 있는 상태면
	if (_monsterState == MON_IDLE)
	{
		_count++;
	}
	if (_playPlayer != NULL)
	{
		if (_attackDelay < 250) _attackDelay++;
		playerAttack();
	}
	
	mosterActionDecide();
	animationChange();
	//리스폰은 이렇게 하면 될듯
	//몬스터가 죽었으면 리스폰 카운트를 작동시켜라
	//if (_isDead) _respondCount++;

	////몬스터 행동 패턴
	//else
	//{

	//}

	////1천이 넘어가면 몬스터 부활한다.
	//if (_respondCount > 1000)
	//{
	//	init();
	//}
}
void pigMonster::animationChange()
{
	switch (_monsterState)
	{
	case MON_IDLE:
		_monsterImage = IMAGEMANAGER->findImage("돼지기본");
		_animation = _animationArray[MON_IDLE];
		break;
	case MON_RIGHT:
		_monsterImage = IMAGEMANAGER->findImage("돼지오른쪽");
		_animation = _animationArray[MON_RIGHT];
		break;
	case MON_RIGHTDOWN:
		_monsterImage = IMAGEMANAGER->findImage("돼지오른쪽아래");
		_animation = _animationArray[MON_RIGHTDOWN];
		break;
	case MON_DOWN:
		_monsterImage = IMAGEMANAGER->findImage("돼지아래");
		_animation = _animationArray[MON_DOWN];
		break;
	case MON_LEFTDOWN:
		_monsterImage = IMAGEMANAGER->findImage("돼지왼쪽아래");
		_animation = _animationArray[MON_LEFTDOWN];
		break;
	case MON_LEFT:
		_monsterImage = IMAGEMANAGER->findImage("돼지왼쪽");
		_animation = _animationArray[MON_LEFT];
		break;
	case MON_LEFTUP:
		_monsterImage = IMAGEMANAGER->findImage("돼지왼쪽위");
		_animation = _animationArray[MON_LEFTUP];
		break;
	case MON_UP:
		_monsterImage = IMAGEMANAGER->findImage("돼지위");
		_animation = _animationArray[MON_UP];
		break;
	case MON_RIGHTUP:
		_monsterImage = IMAGEMANAGER->findImage("돼지오른쪽위");
		_animation = _animationArray[MON_RIGHTUP];
		break;
		case MON_RIGHT_ATTACK:
			_monsterImage = IMAGEMANAGER->findImage("돼지오른쪽공격");
			_animation = _animationArray[MON_RIGHT_ATTACK];
			break;
		case MON_RIGHTDOWN_ATTACK:
			_monsterImage = IMAGEMANAGER->findImage("돼지오른쪽아래공격");
			_animation = _animationArray[MON_RIGHTDOWN_ATTACK];
			break;
		case MON_DOWN_ATTACK:
			_monsterImage = IMAGEMANAGER->findImage("돼지아래공격");
			_animation = _animationArray[MON_DOWN_ATTACK];
			break;
		case MON_LEFTDOWN_ATTACK:
			_monsterImage = IMAGEMANAGER->findImage("돼지왼쪽아래공격");
			_animation = _animationArray[MON_LEFTDOWN_ATTACK];
			break;
		case MON_LEFT_ATTACK:
			_monsterImage = IMAGEMANAGER->findImage("돼지왼쪽공격");
			_animation = _animationArray[MON_LEFT_ATTACK];
			break;
		case MON_LEFTUP_ATTACK:
			_monsterImage = IMAGEMANAGER->findImage("돼지왼쪽위공격");
			_animation = _animationArray[MON_LEFTUP_ATTACK];
			break;
		case MON_UP_ATTACK:
			_monsterImage = IMAGEMANAGER->findImage("돼지위공격");
			_animation = _animationArray[MON_UP_ATTACK];
			break;
		case MON_RIGHTUP_ATTACK:
			_monsterImage = IMAGEMANAGER->findImage("돼지오른쪽위공격");
			_animation = _animationArray[MON_RIGHTUP_ATTACK];
			break;
	case MON_DAMAGED:
		break;
	default:
		break;
	}
}
//void pigMonster::playerAttack()
//{
//
//}
void pigMonster::deadUpdate()
{
	//카운트만 증가시켜라
	_respondCount++;
}
//void pigMonster::render()
//{
//
//}