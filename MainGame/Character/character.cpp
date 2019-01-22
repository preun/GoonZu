#include "stdafx.h"
#include "character.h"
#include "monsterManager.h"

character::character()
{
}


character::~character()
{

}

HRESULT character::init(const char* test,int characterKindNum)
{
	
	_characterKind = (characterKind)characterKindNum;

	switch (_characterKind)
	{
	case GOUN:
		strcpy(_characterName, "견이");
		break;
	case YOUN:
		strcpy(_characterName, "연이");
		break;
	case SIN:
		strcpy(_characterName, "신이");
		break;
	case NONEKIND:
		break;
	default:
		break;
	}
	//기본으로 **생성선택 초기화됨
	strcpy(_characterImageName, _characterName);
	strcat(_characterImageName, "생성선택");

	addImage();
	
	strcpy(_test, test);

	//초기 인덱스 좌표는 10, 10
	_tileIndexX = _tileIndexY = _destTileIndexX = _destTileIndexY =0;
	//초기 장소는 마을
	_place = PLACE_TOWN;
	_clickPotal = false;

	//초기상태는 아이들
	_characterAction = CHA_IDLE;

	_frameX = 0;
	_count = 0;
	_angle = 0;
	
	_x = _currentPlaceTile[_tileIndexX * ISOTILEX + _tileIndexY].getCenterPoint().x;
	_y = _currentPlaceTile[_tileIndexX * ISOTILEX + _tileIndexY].getCenterPoint().y;
	_tempX = _x; _tempY = _y;

	_isHosulamNpcClick = _isJanggumiNpcClick = _isMusuriNpcClick = false;

	_status = new status;
	_status->init();
	_isStatusOpen = false;
	_statusRC = RectMake(0, 100, 260, 448);

	_inven = new inventory;
	_inven->init();
	_isInvenOpen = _isClickInvenItem = false;
	_invenRC = RectMake(WINSIZEX - 153, 100, 153, 331);

	_equip = new equip;
	_equip->init();
	_isEquipOpen = _isClickEquip = false;
	_equipRC = RectMake(260, 100, 233, 254);

	_equip->setStatusMemorryLink(_status);
	_equip->setInventoryMemorryLink(_inven);
	_inven->setEquipMemoryAdressLink(_equip);

	_aStar = new aStar;
	_aStar->init();

	_MM = NULL;
	_targetMonster = NULL;

	_attackDelay = 0;

	_magic = new magicUI;
	_magic->init();
	_isMagicOpen = false;
	_magicRC = RectMake(WINSIZEX - 265, WINSIZEY - 483, 265, 383);

	_skill = new skillUI;
	_skill->init();
	_isSkillOpen = false;

	//기본
	_animationArray[CHA_IDLE] = new animation;
	_animationArray[CHA_IDLE]->init(IMAGEMANAGER->findImage("연이idle")->getWidth(), IMAGEMANAGER->findImage("연이idle")->getHeight(),
		IMAGEMANAGER->findImage("연이idle")->getFrameWidth(), IMAGEMANAGER->findImage("연이idle")->getFrameHeight());
	_animationArray[CHA_IDLE]->setDefPlayFrame(false, true);
	_animationArray[CHA_IDLE]->start();
	_animationArray[CHA_IDLE]->setFPS(1);

	//오른쪽 걷기
	_animationArray[CHA_RIGHT] = new animation;
	_animationArray[CHA_RIGHT]->init(IMAGEMANAGER->findImage("연이오른쪽")->getWidth(), IMAGEMANAGER->findImage("연이오른쪽")->getHeight(),
		IMAGEMANAGER->findImage("연이오른쪽")->getFrameWidth(), IMAGEMANAGER->findImage("연이오른쪽")->getFrameHeight());
	_animationArray[CHA_RIGHT]->setDefPlayFrame(false, true);
	_animationArray[CHA_RIGHT]->start();
	_animationArray[CHA_RIGHT]->setFPS(1);
	
	//오른쪽 아래 걷기
	_animationArray[CHA_RIGHTDOWN] = new animation;
	_animationArray[CHA_RIGHTDOWN]->init(IMAGEMANAGER->findImage("연이오른쪽아래")->getWidth(), IMAGEMANAGER->findImage("연이오른쪽아래")->getHeight(),
		IMAGEMANAGER->findImage("연이오른쪽아래")->getFrameWidth(), IMAGEMANAGER->findImage("연이오른쪽아래")->getFrameHeight());
	_animationArray[CHA_RIGHTDOWN]->setDefPlayFrame(false, true);
	_animationArray[CHA_RIGHTDOWN]->start();
	_animationArray[CHA_RIGHTDOWN]->setFPS(1);
	
	//아래 걷기
	_animationArray[CHA_DOWN] = new animation;
	_animationArray[CHA_DOWN]->init(IMAGEMANAGER->findImage("연이아래")->getWidth(), IMAGEMANAGER->findImage("연이아래")->getHeight(),
		IMAGEMANAGER->findImage("연이아래")->getFrameWidth(), IMAGEMANAGER->findImage("연이아래")->getFrameHeight());
	_animationArray[CHA_DOWN]->setDefPlayFrame(false, true);
	_animationArray[CHA_DOWN]->start();
	_animationArray[CHA_DOWN]->setFPS(1);
	
	//왼쪽 아래 걷기
	_animationArray[CHA_LEFTDOWN] = new animation;
	_animationArray[CHA_LEFTDOWN]->init(IMAGEMANAGER->findImage("연이왼쪽아래")->getWidth(), IMAGEMANAGER->findImage("연이왼쪽아래")->getHeight(),
		IMAGEMANAGER->findImage("연이왼쪽아래")->getFrameWidth(), IMAGEMANAGER->findImage("연이왼쪽아래")->getFrameHeight());
	_animationArray[CHA_LEFTDOWN]->setDefPlayFrame(false, true);
	_animationArray[CHA_LEFTDOWN]->start();
	_animationArray[CHA_LEFTDOWN]->setFPS(1);
	
	//왼쪽 걷기
	_animationArray[CHA_LEFT] = new animation;
	_animationArray[CHA_LEFT]->init(IMAGEMANAGER->findImage("연이왼쪽")->getWidth(), IMAGEMANAGER->findImage("연이왼쪽")->getHeight(),
		IMAGEMANAGER->findImage("연이왼쪽")->getFrameWidth(), IMAGEMANAGER->findImage("연이왼쪽")->getFrameHeight());
	_animationArray[CHA_LEFT]->setDefPlayFrame(false, true);
	_animationArray[CHA_LEFT]->start();
	_animationArray[CHA_LEFT]->setFPS(1);
	
	//왼쪽 위 걷기
	_animationArray[CHA_LEFTUP] = new animation;
	_animationArray[CHA_LEFTUP]->init(IMAGEMANAGER->findImage("연이왼쪽위")->getWidth(), IMAGEMANAGER->findImage("연이왼쪽위")->getHeight(),
		IMAGEMANAGER->findImage("연이왼쪽위")->getFrameWidth(), IMAGEMANAGER->findImage("연이왼쪽위")->getFrameHeight());
	_animationArray[CHA_LEFTUP]->setDefPlayFrame(false, true);
	_animationArray[CHA_LEFTUP]->start();
	_animationArray[CHA_LEFTUP]->setFPS(1);
	
	//위 걷기
	_animationArray[CHA_UP] = new animation;
	_animationArray[CHA_UP]->init(IMAGEMANAGER->findImage("연이위")->getWidth(), IMAGEMANAGER->findImage("연이위")->getHeight(),
		IMAGEMANAGER->findImage("연이위")->getFrameWidth(), IMAGEMANAGER->findImage("연이위")->getFrameHeight());
	_animationArray[CHA_UP]->setDefPlayFrame(false, true);
	_animationArray[CHA_UP]->start();
	_animationArray[CHA_UP]->setFPS(1);
	
	//오른쪽 위 걷기
	_animationArray[CHA_RIGHTUP] = new animation;
	_animationArray[CHA_RIGHTUP]->init(IMAGEMANAGER->findImage("연이오른쪽위")->getWidth(), IMAGEMANAGER->findImage("연이오른쪽위")->getHeight(),
		IMAGEMANAGER->findImage("연이오른쪽위")->getFrameWidth(), IMAGEMANAGER->findImage("연이오른쪽위")->getFrameHeight());
	_animationArray[CHA_RIGHTUP]->setDefPlayFrame(false, true);
	_animationArray[CHA_RIGHTUP]->start();
	_animationArray[CHA_RIGHTUP]->setFPS(1);

	//오른쪽 공격
	_animationArray[CHA_RIGHT_ATTACK] = new animation;
	_animationArray[CHA_RIGHT_ATTACK]->init(IMAGEMANAGER->findImage("연이오른쪽공격")->getWidth(), IMAGEMANAGER->findImage("연이오른쪽공격")->getHeight(),
		IMAGEMANAGER->findImage("연이오른쪽공격")->getFrameWidth(), IMAGEMANAGER->findImage("연이오른쪽공격")->getFrameHeight());
	_animationArray[CHA_RIGHT_ATTACK]->setDefPlayFrame(false, true);
	_animationArray[CHA_RIGHT_ATTACK]->start();
	_animationArray[CHA_RIGHT_ATTACK]->setFPS(1);

	//오른쪽 아래 공격
	_animationArray[CHA_RIGHTDOWN_ATTACK] = new animation;
	_animationArray[CHA_RIGHTDOWN_ATTACK]->init(IMAGEMANAGER->findImage("연이오른쪽아래공격")->getWidth(), IMAGEMANAGER->findImage("연이오른쪽아래공격")->getHeight(),
		IMAGEMANAGER->findImage("연이오른쪽아래공격")->getFrameWidth(), IMAGEMANAGER->findImage("연이오른쪽아래공격")->getFrameHeight());
	_animationArray[CHA_RIGHTDOWN_ATTACK]->setDefPlayFrame(false, true);
	_animationArray[CHA_RIGHTDOWN_ATTACK]->start();
	_animationArray[CHA_RIGHTDOWN_ATTACK]->setFPS(1);

	//아래 공격
	_animationArray[CHA_DOWN_ATTACK] = new animation;
	_animationArray[CHA_DOWN_ATTACK]->init(IMAGEMANAGER->findImage("연이아래공격")->getWidth(), IMAGEMANAGER->findImage("연이아래공격")->getHeight(),
		IMAGEMANAGER->findImage("연이아래공격")->getFrameWidth(), IMAGEMANAGER->findImage("연이아래공격")->getFrameHeight());
	_animationArray[CHA_DOWN_ATTACK]->setDefPlayFrame(false, true);
	_animationArray[CHA_DOWN_ATTACK]->start();
	_animationArray[CHA_DOWN_ATTACK]->setFPS(1);

	//왼쪽 아래 공격
	_animationArray[CHA_LEFTDOWN_ATTACK] = new animation;
	_animationArray[CHA_LEFTDOWN_ATTACK]->init(IMAGEMANAGER->findImage("연이왼쪽아래공격")->getWidth(), IMAGEMANAGER->findImage("연이왼쪽아래공격")->getHeight(),
		IMAGEMANAGER->findImage("연이왼쪽아래공격")->getFrameWidth(), IMAGEMANAGER->findImage("연이왼쪽아래공격")->getFrameHeight());
	_animationArray[CHA_LEFTDOWN_ATTACK]->setDefPlayFrame(false, true);
	_animationArray[CHA_LEFTDOWN_ATTACK]->start();
	_animationArray[CHA_LEFTDOWN_ATTACK]->setFPS(1);

	//왼쪽 공격
	_animationArray[CHA_LEFT_ATTACK] = new animation;
	_animationArray[CHA_LEFT_ATTACK]->init(IMAGEMANAGER->findImage("연이왼쪽공격")->getWidth(), IMAGEMANAGER->findImage("연이왼쪽공격")->getHeight(),
		IMAGEMANAGER->findImage("연이왼쪽공격")->getFrameWidth(), IMAGEMANAGER->findImage("연이왼쪽공격")->getFrameHeight());
	_animationArray[CHA_LEFT_ATTACK]->setDefPlayFrame(false, true);
	_animationArray[CHA_LEFT_ATTACK]->start();
	_animationArray[CHA_LEFT_ATTACK]->setFPS(1);

	//왼쪽 위 공격
	_animationArray[CHA_LEFTUP_ATTACK] = new animation;
	_animationArray[CHA_LEFTUP_ATTACK]->init(IMAGEMANAGER->findImage("연이왼쪽위공격")->getWidth(), IMAGEMANAGER->findImage("연이왼쪽위공격")->getHeight(),
		IMAGEMANAGER->findImage("연이왼쪽위공격")->getFrameWidth(), IMAGEMANAGER->findImage("연이왼쪽위공격")->getFrameHeight());
	_animationArray[CHA_LEFTUP_ATTACK]->setDefPlayFrame(false, true);
	_animationArray[CHA_LEFTUP_ATTACK]->start();
	_animationArray[CHA_LEFTUP_ATTACK]->setFPS(1);

	//위 공격
	_animationArray[CHA_UP_ATTACK] = new animation;
	_animationArray[CHA_UP_ATTACK]->init(IMAGEMANAGER->findImage("연이위공격")->getWidth(), IMAGEMANAGER->findImage("연이위공격")->getHeight(),
		IMAGEMANAGER->findImage("연이위공격")->getFrameWidth(), IMAGEMANAGER->findImage("연이위공격")->getFrameHeight());
	_animationArray[CHA_UP_ATTACK]->setDefPlayFrame(false, true);
	_animationArray[CHA_UP_ATTACK]->start();
	_animationArray[CHA_UP_ATTACK]->setFPS(1);

	//오른쪽 위 공격
	_animationArray[CHA_RIGHTUP_ATTACK] = new animation;
	_animationArray[CHA_RIGHTUP_ATTACK]->init(IMAGEMANAGER->findImage("연이오른쪽위공격")->getWidth(), IMAGEMANAGER->findImage("연이오른쪽위공격")->getHeight(),
		IMAGEMANAGER->findImage("연이오른쪽위공격")->getFrameWidth(), IMAGEMANAGER->findImage("연이오른쪽위공격")->getFrameHeight());
	_animationArray[CHA_RIGHTUP_ATTACK]->setDefPlayFrame(false, true);
	_animationArray[CHA_RIGHTUP_ATTACK]->start();
	_animationArray[CHA_RIGHTUP_ATTACK]->setFPS(1);

	_animationArray[CHA_DEATH] = new animation;
	_animationArray[CHA_DEATH]->init(IMAGEMANAGER->findImage("연이죽음")->getWidth(), IMAGEMANAGER->findImage("연이죽음")->getHeight(),
		IMAGEMANAGER->findImage("연이죽음")->getFrameWidth(), IMAGEMANAGER->findImage("연이죽음")->getFrameHeight());
	_animationArray[CHA_DEATH]->setDefPlayFrame(false, false);
	_animationArray[CHA_DEATH]->start();
	_animationArray[CHA_DEATH]->setFPS(1);

	_animation = _animationArray[CHA_IDLE]; //초기값은 연이 기본

	//_skillRC = RectMake();

	return S_OK;
}

void character::release()
{

}

void character::update()
{
	//죽었다면 업데이트 돌지마라
	if (*_status->getCurrentHP() <= 0)
	{
		_characterAction = CHA_DEATH;
		_playImage = IMAGEMANAGER->findImage("연이죽음");
		_animation = _animationArray[CHA_DEATH];
		_animation->frameUpdate(TIMEMANAGER->getElapsedTime() * 3);
		//_animation->start();
		return;
	}

	_animation->frameUpdate(TIMEMANAGER->getElapsedTime() * 5);

	animationChange();
	if (_attackDelay <ATTACKDELAY) _attackDelay++;

	if (KEYMANAGER->isOnceKeyDown('C'))
	{
		if (_isStatusOpen)	_isStatusOpen = false;
		else _isStatusOpen = true;
	}
	if (KEYMANAGER->isOnceKeyDown('I'))
	{
		if (_isInvenOpen) _isInvenOpen = false;
		else _isInvenOpen = true;
	}
	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		if (_isEquipOpen) _isEquipOpen = false;
		else _isEquipOpen = true;
	}
	if (KEYMANAGER->isOnceKeyDown('M'))
	{
		if (_isMagicOpen) _isMagicOpen = false;
		else _isMagicOpen = true;
	}
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		if (_isSkillOpen) _isSkillOpen = false;
		else _isSkillOpen = true;
	}
	//F1퀵슬롯
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		int tempPotion = _inven->quickF1();
		//MP
		if (tempPotion < 0)
		{
			_status->setPotionMP(abs(tempPotion));
		}
		else
		{
			_status->setPotionHP(tempPotion);
		}
	}
	//F2퀵슬롯
	else if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{

	}
	//F3퀵슬롯
	else if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{

	}
	//F4퀵슬롯
	else if (KEYMANAGER->isOnceKeyDown(VK_F4))
	{

	}
	//F5퀵슬롯
	else if (KEYMANAGER->isOnceKeyDown(VK_F5))
	{

	}

	//디버깅용으로 3 누르면 경험치 상승 
	if (_isStatusOpen) _status->update();
	//실험용
	if (_isInvenOpen) _inven->update();

	//if (_isMagicOpen) _magic->update();

	//프레임(키애니매니져화)?
	//_count++;
	//if (_count % 10 == 0)
	//{
	//	_frameX++;
	//	if (_frameX >= IMAGEMANAGER->findImage("연이idle")->getMaxFrameX()) _frameX = 0;
	//	_count = 0;
	//}

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		if (_isClickEquip) _isClickEquip = false;
		else if (_isClickInvenItem) _isClickInvenItem = false;
		else if (_isMagicOpen && PtInRect(&_magicRC, _ptMouse)) _magic->clickMagicUI(false);
		//스킬사용
		else
		{
			if (_MM != NULL)
			{				
					if (_magic->getUseMagic() != NULL && !_magic->getUseMagic()->getIsUsed())
					{
						_targetMonster = _MM->findClickMonster();

						if (_targetMonster == NULL) NULL;

						_targetMonster->setMemoryAddressLink(_playPlayer);

						//_targetMonster->setAttackedHP(_magic->getUseMagic()->getDamage(_status->getInt()));

						_targetMonster->setAttackedHP(0);

						POINT tempTargetMonsterPoint;
						tempTargetMonsterPoint = _currentPlaceTile[_targetMonster->getTileIndexX() * ISOTILEX + _targetMonster->getTileIndexY()].getCenterPoint();
						EFFECTMANAGER->play("벼락", tempTargetMonsterPoint.x,
							tempTargetMonsterPoint.y - 121 / 2);//- IMAGEMANAGER->findImage();
					}
				
			}
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		lbuttonEvent();
	}
	//캐릭터 행동 방향 정하기
	characterActionDecide();
	attack();
	_magic->update();
	
}
void character::characterActionDecide()
{
	POINT tempPoint;
	if (_targetMonster != NULL)
	{
		//tempPoint.x = tempPoint.y = 21;
		//타겟몬스터가 있으면 aStar로 갈 타일 찾고 
		//if (tempPoint.x != _tileIndexX && tempPoint.y != _tileIndexY)
		//{
		_aStar->setTiles(_tileIndexX, _tileIndexY, _targetMonster->getTileIndexX(), _targetMonster->getTileIndexY(), _currentPlaceTile);
		tempPoint = _aStar->getNextTile();
		//}
		//몬스터와 한칸차이면 거기멈춰 공격!
		if (tempPoint.x == -1 && tempPoint.y == -1 )
		{
			if (_targetMonster->getTileIndexX() == _tileIndexX && _targetMonster->getTileIndexY() > _tileIndexY)
			{
				_characterAction = CHA_RIGHTDOWN_ATTACK;
			}
			//x축은 같고 y축이 갈 곳이 더 작으면 왼쪽 위로 가야한다.
			else if (_targetMonster->getTileIndexX() == _tileIndexX && _targetMonster->getTileIndexY() < _tileIndexY)
			{
				_characterAction = CHA_LEFTUP_ATTACK;
			}
			//y축은 같고 x축이 갈 곳이 더 크면 왼쪽 아래로 가야한다.
			else if (_targetMonster->getTileIndexX() > _tileIndexX && _targetMonster->getTileIndexY() == _tileIndexY)
			{
				_characterAction = CHA_LEFTDOWN_ATTACK;
			}
			//y축은 같고 x축이 갈 곳이 더 크면 오른쪽 위로 가야한다.
			else if (_targetMonster->getTileIndexX() < _tileIndexX && _targetMonster->getTileIndexY() == _tileIndexY)
			{
				_characterAction = CHA_RIGHTUP_ATTACK;
			}
			//갈곳이 나랑 같은줄이면서 내가 왼쪽에 있으면 오른쪽으로 가야한다.
			else if (_targetMonster->getTileIndexX() < _tileIndexX && _targetMonster->getTileIndexY() > _tileIndexY)
			{
				_characterAction = CHA_RIGHT_ATTACK;
			}
			//갈곳이 나랑 같은줄이면서 내가 오른쪽에 있으면 왼쪽으로 가야한다.
			else if (_targetMonster->getTileIndexX() > _tileIndexX && _targetMonster->getTileIndexY() < _tileIndexY)
			{
				_characterAction = CHA_LEFT_ATTACK;
			}
			//갈곳이 나랑 같은줄이면서 내가 위쪽에 있으면 아래쪽으로 가야한다.
			else if (_targetMonster->getTileIndexX() > _tileIndexX && _targetMonster->getTileIndexY() > _tileIndexY)
			{
				_characterAction = CHA_DOWN_ATTACK;
			}
			//갈곳이 나랑 같은줄이면서 내가 아래쪽에 있으면 위로 가야한다.
			else if (_targetMonster->getTileIndexX() < _tileIndexX && _targetMonster->getTileIndexY() < _tileIndexY)
			{
				_characterAction = CHA_UP_ATTACK;
			}
			//tempPoint = PointMake(_tileIndexX, _tileIndexY);
			//_characterAction = characterAction(_characterAction + 8);
			//switch (_characterAction)
			//{
			//case CHA_IDLE:
			//	break;
			//case CHA_RIGHT:
			//	_characterAction = CHA_RIGHT_ATTACK;
			//	break;
			//case CHA_RIGHTDOWN:
			//	_characterAction = CHA_RIGHTDOWN_ATTACK;
			//	break;
			//case CHA_DOWN:
			//	_characterAction = CHA_DOWN_ATTACK;
			//	break;
			//case CHA_LEFTDOWN:
			//	_characterAction = CHA_LEFTDOWN_ATTACK;
			//	break;
			//case CHA_LEFT:
			//	_characterAction = CHA_LEFT_ATTACK;
			//	break;
			//case CHA_LEFTUP:
			//	_characterAction = CHA_LEFTUP_ATTACK;
			//	break;
			//case CHA_UP:
			//	_characterAction = CHA_UP_ATTACK;
			//	break;
			//case CHA_RIGHTUP:
			//	_characterAction = CHA_RIGHTUP_ATTACK;
			//	break;
			//default:
			//	break;
			//}
			return;
		}
		//sprintf(_aStarTest, "%d, %d", tempPoint.x, tempPoint.y);
		//_aStar->init();

		//x축은 같고 y축이 갈 곳이 더 크면 오른쪽 아래로 가야한다.
		//if (tempPoint.x != _tileIndexX && tempPoint.y != _tileIndexY)
		//{
			if (tempPoint.x == _tileIndexX && tempPoint.y > _tileIndexY)
			{
				_characterAction = CHA_RIGHTDOWN;
			}
			//x축은 같고 y축이 갈 곳이 더 작으면 왼쪽 위로 가야한다.
			else if (tempPoint.x == _tileIndexX && tempPoint.y < _tileIndexY)
			{
				_characterAction = CHA_LEFTUP;
			}
			//y축은 같고 x축이 갈 곳이 더 크면 왼쪽 아래로 가야한다.
			else if (tempPoint.x > _tileIndexX && tempPoint.y == _tileIndexY)
			{
				_characterAction = CHA_LEFTDOWN;
			}
			//y축은 같고 x축이 갈 곳이 더 크면 오른쪽 위로 가야한다.
			else if (tempPoint.x < _tileIndexX && tempPoint.y == _tileIndexY)
			{
				_characterAction = CHA_RIGHTUP;
			}
			//갈곳이 나랑 같은줄이면서 내가 왼쪽에 있으면 오른쪽으로 가야한다.
			else if (tempPoint.x < _tileIndexX && tempPoint.y > _tileIndexY)
			{
				_characterAction = CHA_RIGHT;
			}
			//갈곳이 나랑 같은줄이면서 내가 오른쪽에 있으면 왼쪽으로 가야한다.
			else if (tempPoint.x > _tileIndexX && tempPoint.y < _tileIndexY)
			{
				_characterAction = CHA_LEFT;
			}
			//갈곳이 나랑 같은줄이면서 내가 위쪽에 있으면 아래쪽으로 가야한다.
			else if (tempPoint.x > _tileIndexX && tempPoint.y > _tileIndexY)
			{
				_characterAction = CHA_DOWN;
			}
			//갈곳이 나랑 같은줄이면서 내가 아래쪽에 있으면 위로 가야한다.
			else if (tempPoint.x < _tileIndexX && tempPoint.y < _tileIndexY)
			{
				_characterAction = CHA_UP;
			}
		//}
	}
	//타겟몬스터가 없으면 그냥 이동이다.
	else
	{
		//내가 서있는곳과 목적지가 같으면 움직일 필요가 없다.
		if (_tileIndexX == _destTileIndexX && _tileIndexY == _destTileIndexY)
		{
			_characterAction = CHA_IDLE;
			return;
		}

		//다르다면 이동을 해야하니 A스타 호출을 한다.

		_aStar->setTiles(_tileIndexX, _tileIndexY, _destTileIndexX, _destTileIndexY, _currentPlaceTile);
		tempPoint = _aStar->getNextTile();

		//바로 한칸차이다. 
		if (tempPoint.x == -1 && tempPoint.y == -1) tempPoint = PointMake(_destTileIndexX, _destTileIndexY);
		if (tempPoint.x == _tileIndexX && tempPoint.y > _tileIndexY)
		{
			_characterAction = CHA_RIGHTDOWN;
		}
		//x축은 같고 y축이 갈 곳이 더 작으면 왼쪽 위로 가야한다.
		else if (tempPoint.x == _tileIndexX && tempPoint.y < _tileIndexY)
		{
			_characterAction = CHA_LEFTUP;
		}
		//y축은 같고 x축이 갈 곳이 더 크면 왼쪽 아래로 가야한다.
		else if (tempPoint.x > _tileIndexX && tempPoint.y == _tileIndexY)
		{
			_characterAction = CHA_LEFTDOWN;
		}
		//y축은 같고 x축이 갈 곳이 더 크면 오른쪽 위로 가야한다.
		else if (tempPoint.x < _tileIndexX && tempPoint.y == _tileIndexY)
		{
			_characterAction = CHA_RIGHTUP;
		}
		//갈곳이 나랑 같은줄이면서 내가 왼쪽에 있으면 오른쪽으로 가야한다.
		else if (tempPoint.x < _tileIndexX && tempPoint.y > _tileIndexY)
		{
			_characterAction = CHA_RIGHT;
		}
		//갈곳이 나랑 같은줄이면서 내가 오른쪽에 있으면 왼쪽으로 가야한다.
		else if (tempPoint.x > _tileIndexX && tempPoint.y < _tileIndexY)
		{
			_characterAction = CHA_LEFT;
		}
		//갈곳이 나랑 같은줄이면서 내가 위쪽에 있으면 아래쪽으로 가야한다.
		else if (tempPoint.x > _tileIndexX && tempPoint.y > _tileIndexY)
		{
			_characterAction = CHA_DOWN;
		}
		//갈곳이 나랑 같은줄이면서 내가 아래쪽에 있으면 위로 가야한다.
		else if (tempPoint.x < _tileIndexX && tempPoint.y < _tileIndexY)
		{
			_characterAction = CHA_UP;
		}



	}
	_angle = getAngle(_currentPlaceTile[_tileIndexX * ISOTILEX + _tileIndexY].getCenterPoint().x,
		_currentPlaceTile[_tileIndexX * ISOTILEX + _tileIndexY].getCenterPoint().y,
		_currentPlaceTile[tempPoint.x * ISOTILEX + tempPoint.y].getCenterPoint().x,
		_currentPlaceTile[tempPoint.x * ISOTILEX + tempPoint.y].getCenterPoint().y);
	move(tempPoint);
}
void character::animationChange()
{
	switch (_characterAction)
	{
	case CHA_IDLE:
		_playImage = IMAGEMANAGER->findImage("연이idle");
		_animation = _animationArray[CHA_IDLE];
		break;
	case CHA_RIGHT:
		_playImage = IMAGEMANAGER->findImage("연이오른쪽");
		_animation = _animationArray[CHA_RIGHT];
		break;
	case CHA_RIGHTDOWN:
		_playImage = IMAGEMANAGER->findImage("연이오른쪽아래");
		_animation = _animationArray[CHA_RIGHTDOWN];
		break;
	case CHA_DOWN:
		_playImage = IMAGEMANAGER->findImage("연이아래");
		_animation = _animationArray[CHA_DOWN];
		break;
	case CHA_LEFTDOWN:
		_playImage = IMAGEMANAGER->findImage("연이왼쪽아래");
		_animation = _animationArray[CHA_LEFTDOWN];
		break;
	case CHA_LEFT:
		_playImage = IMAGEMANAGER->findImage("연이왼쪽");
		_animation = _animationArray[CHA_LEFT];
		break;
	case CHA_LEFTUP:
		_playImage = IMAGEMANAGER->findImage("연이왼쪽위");
		_animation = _animationArray[CHA_LEFTUP];
		break;
	case CHA_UP:
		_playImage = IMAGEMANAGER->findImage("연이위");
		_animation = _animationArray[CHA_UP];
		break;
	case CHA_RIGHTUP:
		_playImage = IMAGEMANAGER->findImage("연이오른쪽위");
		_animation = _animationArray[CHA_RIGHTUP];
		break;
	case CHA_RIGHT_ATTACK:
		_playImage = IMAGEMANAGER->findImage("연이오른쪽공격");
		_animation = _animationArray[CHA_RIGHT_ATTACK];
		break;
	case CHA_RIGHTDOWN_ATTACK:
		_playImage = IMAGEMANAGER->findImage("연이오른쪽아래공격");
		_animation = _animationArray[CHA_RIGHTDOWN_ATTACK];
		break;
	case CHA_DOWN_ATTACK:
		_playImage = IMAGEMANAGER->findImage("연이아래공격");
		_animation = _animationArray[CHA_DOWN_ATTACK];
		break;
	case CHA_LEFTDOWN_ATTACK:
		_playImage = IMAGEMANAGER->findImage("연이왼쪽아래공격");
		_animation = _animationArray[CHA_LEFTDOWN_ATTACK];
		break;
	case CHA_LEFT_ATTACK:
		_playImage = IMAGEMANAGER->findImage("연이왼쪽공격");
		_animation = _animationArray[CHA_LEFT_ATTACK];
		break;
	case CHA_LEFTUP_ATTACK:
		_playImage = IMAGEMANAGER->findImage("연이왼쪽위공격");
		_animation = _animationArray[CHA_LEFTUP_ATTACK];
		break;
	case CHA_UP_ATTACK:
		_playImage = IMAGEMANAGER->findImage("연이위공격");
		_animation = _animationArray[CHA_UP_ATTACK];
		break;
	case CHA_RIGHTUP_ATTACK:
		_playImage = IMAGEMANAGER->findImage("연이오른쪽위공격");
		_animation = _animationArray[CHA_RIGHTUP_ATTACK];
		break;
	case CHA_DEATH:
		_playImage = IMAGEMANAGER->findImage("연이죽음");
		_animation = _animationArray[CHA_DEATH];
		break;
	default:
		break;
	}
}
void character::move(POINT tempPoint)
{
	

		if (CHA_IDLE < _characterAction && _characterAction < CHA_RIGHT_ATTACK)
		{
			if (PtInRect(&RectMakeCenter(_currentPlaceTile[tempPoint.x * ISOTILEX + tempPoint.y].getCenterPoint().x,
				_currentPlaceTile[tempPoint.x * ISOTILEX + tempPoint.y].getCenterPoint().y,
				10, 10), PointMake(_x, _y)))
				/*_currentPlaceTile[_destTileIndexX * ISOTILEX + _destTileIndexY].getCenterPoint().x - 1 < _x
				&& _x < _currentPlaceTile[_destTileIndexX * ISOTILEX + _destTileIndexY].getCenterPoint().x + 1
				&& _currentPlaceTile[_destTileIndexX * ISOTILEX + _destTileIndexY].getCenterPoint().y - 1 < _y
				&& _y < _currentPlaceTile[_destTileIndexX * ISOTILEX + _destTileIndexY].getCenterPoint().y + 1)*/
			{
				//_characterAction = CHA_IDLE;
				_x = _currentPlaceTile[tempPoint.x * ISOTILEX + tempPoint.y].getCenterPoint().x;
				_y = _currentPlaceTile[tempPoint.x * ISOTILEX + tempPoint.y].getCenterPoint().y;
				//_tempX = _x; _tempY = _y;
				_tileIndexX = tempPoint.x;
				_tileIndexY = tempPoint.y;

				//POINT tempPoint1 = _aStar->getTile();
				//_aStar->removeFirstTile();
				//_destTempTileIndex = tempPoint1;

			}
			else
			{
				_x += cos(_angle) * 2;
				_y += -sin(_angle) * 2;
			}

			////내가 밟고있는 타일 인덱스와 갈곳의 인덱스가 같아지면
			////	if (_tileIndexX == _destTileIndexX && _tileIndexY == _destTileIndexY)
			//if (PtInRect(&RectMakeCenter(_currentPlaceTile[_destTileIndexX * ISOTILEX + _destTileIndexY].getCenterPoint().x,
			//	_currentPlaceTile[_destTileIndexX * ISOTILEX + _destTileIndexY].getCenterPoint().y,
			//	10, 10), PointMake(_x, _y)))
			//	/*_currentPlaceTile[_destTileIndexX * ISOTILEX + _destTileIndexY].getCenterPoint().x - 1 < _x
			//	&& _x < _currentPlaceTile[_destTileIndexX * ISOTILEX + _destTileIndexY].getCenterPoint().x + 1
			//	&& _currentPlaceTile[_destTileIndexX * ISOTILEX + _destTileIndexY].getCenterPoint().y - 1 < _y
			//	&& _y < _currentPlaceTile[_destTileIndexX * ISOTILEX + _destTileIndexY].getCenterPoint().y + 1)*/
			//{
			//	_characterAction = CHA_IDLE;
			//	_x = _currentPlaceTile[_destTileIndexX * ISOTILEX + _destTileIndexY].getCenterPoint().x;
			//	_y = _currentPlaceTile[_destTileIndexX * ISOTILEX + _destTileIndexY].getCenterPoint().y;
			//	_tempX = _x; _tempY = _y;
			//	_tileIndexX = _destTileIndexX;
			//	_tileIndexY = _destTileIndexY;
			//}
			//else{
			//	_x += cos(_angle) * 2;
			//	_y += -sin(_angle) * 2;
			//	if (getDistance(_tempX, _tempY, _x, _y) >= (TILESIZE / 2))
			//	{
			//		for (int i = 0; i < ISOTILEX * ISOTILEY; ++i)
			//		{
			//			//if ( ==)
			//			POINT tempPoint[4];
			//			//if ( PtInRect(&_tiles[i].rc, _ptMouse) )
			//			for (int j = 0; j < 4; ++j)
			//			{
			//				tempPoint[j] = CAMERAMANAGER->CameraRelativePoint(_currentPlaceTile[i].point[j]);
			//			}
			//			HRGN rgn = CreatePolygonRgn(_currentPlaceTile[i].point, 4, 1);
			//			//HRGN rgn = CreatePolygonRgn(_tiles[i].point, 4, 1);
			//			if (PtInRegion(rgn, _x, _y))
			//			{
			//				_tileIndexX = i / ISOTILEX;
			//				_tileIndexY = i % ISOTILEX;

			//				_tempX = _x; _tempY = _y;
			//				//타일계로 이동시 쓸것
			//				//_tempX = _currentPlaceTile[_tileIndexX * ISOTILEX + _tileIndexY].getCenterPoint().x;
			//				//_tempY = _currentPlaceTile[_tileIndexX * ISOTILEX + _tileIndexY].getCenterPoint().y;

			//				DeleteObject(rgn);
			//				DeleteObject(tempPoint);
			//				break;
			//			}
			//			//temp = _tileIN;
			//			DeleteObject(rgn);
			//			DeleteObject(tempPoint);
			//		}
			//	}
			//}


		}
		makeRC();
}
void character::attack()
{
	//캐릭터의 행동은 어택하는 상황이도 어택 딜레이가 50을 넘겼으면 때릴 수 있다.
	if (CHA_RIGHT_ATTACK <= _characterAction && _characterAction <= CHA_RIGHTUP_ATTACK && _attackDelay >= ATTACKDELAY)
	{
		//딜레이는 다시 0으로 돌려주고
		_attackDelay = 0;
		//플레이어가 때리는순간 몬스터는 플레이어한테 반격한다.
		_targetMonster->setMemoryAddressLink(_playPlayer);
		_targetMonster->setAttackedHP(_status->getAtt());
		if (_targetMonster->getIsDead())
		{
			_status->setExp(_targetMonster->getLevel() * 10);
			_destTileIndexX = _tileIndexX;
			_destTileIndexY = _tileIndexY;
			_targetMonster = NULL;
			_characterAction = CHA_IDLE;
		}
	}
}
void character::attacked(int damage)
{
	_status->setCurrentHP(damage);
}
void character::lbuttonEvent(){
	//좌클릭 했는데 그곳이 스탯UI다 -> 스탯분배
	//방어력은 아이템 장착하면 오르도록 만들기ㅊ
	if (_ptMouse.x > WINSIZEX || _ptMouse.y > WINSIZEY) return;
	//인벤토리나 장착아이템 클릭을 안하면서 스탯창 눌렀을경우
	if (!_isClickInvenItem && !_isClickEquip && _isStatusOpen && PtInRect(&_statusRC, _ptMouse))
	{
		//스탯분배하자
		_status->statusDistribution(
			_equip->getWeponAtt().x, _equip->getWeponAtt().y, 5);
	}

	//인벤토리 오픈상태에서 인벤토리를 클릭했으면 해당 처리해주는 함수호출
	else if (!_isClickEquip && _isInvenOpen && PtInRect(&_invenRC, _ptMouse))
	{
		/*아이템 들고 있는상태에서 클릭시 위치 바꾸기(false반환)
		  아이템 들고 있지 않으면 아이템 들기(true반환)*/
		_isClickInvenItem = _inven->inventoryClick(_isClickInvenItem);
	}

	//인벤에서 아이템 클릭하고 장비탭이 열려있는상태에서 장비탭 눌렀다면
	else if (_isClickInvenItem && _isEquipOpen && PtInRect(&_equipRC, _ptMouse))
	{
		//아이템 장착(정상 장착시 fasle 반환)
		_isClickInvenItem = _equip->equipInstall(_inven->getClickItem(), _inven->getClickItemParent());
	}

	//인벤토리에서 아이템을 클릭한 상태에서 장비탭과 인벤토리 이외를 클릭했다면 아이템 버리기
	else if (_isClickInvenItem &&( (!_isInvenOpen ||  !PtInRect(&_invenRC, _ptMouse) )|| (!_isEquipOpen || !PtInRect(&_equipRC, _ptMouse)) ))
	{
		//버려라
		_isClickInvenItem = _inven->inventoryItemDrop();
	}

	//인벤에서 클릭하지 않은 상태에서 장착아이템을 클릭했을경우
	else if (!_isClickInvenItem && _isEquipOpen && PtInRect(&_equipRC, _ptMouse))
	{
		_isClickEquip = _equip->equipUnInstall(_isClickEquip);
	}

	//장비창 열어 클릭한상태에서 인벤 클릭하면 인벤토리에 다시 돌아온다.
	//equip = treu, invenitem = false, open 둘다 true
	else if (_isClickEquip && _isInvenOpen && PtInRect(&_invenRC, _ptMouse))
	{
		_isClickEquip = _inven->inventoryClick(_equip->getClickItem());
	}
	
	//기술창 열려있고 아이템을 클릭하지 않은 상태에서 기술창 선택시 
	else if (_isMagicOpen && !_isClickInvenItem && !_isClickEquip && PtInRect(&_magicRC, _ptMouse))
	{
		_magic->clickMagicUI(true);
	}
	//그 외의 클릭처리는 이동이라 판단(이후 몬스터 추가시 공격)
	else 
	{
		//몬스터 클릭
		//MM에 값이 담겨있다면 사냥터이다. 
		if (_MM != NULL)
		{
			//내가 클릭하면 타겟 몬스터가 일로 담긴다.
			_targetMonster = _MM->findClickMonster();
			//이것저것 수행
			//1. 타겟과의 위치 판단하여 그 위치에 따른 한칸차이까지 이동(A* 적용시키기)
			/*while (1)
			{
			
			}*/
			

					//POINT tempPoint =
				//		_aStar->getNextTile(_tileIndexX, _tileIndexY, _targetMonster->getTileIndexX(), _targetMonster->getTileIndexY());
					//sprintf(_aStarTest, "aaa", tempPoint.x, tempPoint.y);
				
			
				//타겟몬스터의 좌표를 임시로 저장하고
				//int tempX = _targetMonster->getTileIndexX();
				//int tempY = _targetMonster->getTileIndexY();

				////타겟 몬스터 기준 맨 왼쪽 좌표까지 가는중에 플레이어가 있다면 플레이어는 오른쪽으로 이동해야한다.
				//while (tempX != ISOTILEX - 1 && tempY !=0 && _characterAction==CHA_IDLE)
				//{
				//	tempX++;
				//	tempY--;
				//	if (tempX == _tileIndexX && tempY == _tileIndexY)
				//	{
				//		//캐릭터 행동은 오른쪽으로 걸어감
				//		_characterAction = CHA_RIGHT;
				//		//캐릭터 목적지는 타겟 몬스터의 바로 왼쪽칸
				//		_destTileIndexX = _targetMonster->getTileIndexX() + 1;
				//		_destTileIndexY = _targetMonster->getTileIndexY() - 1;
				//		_angle =
				//			getAngle(_currentPlaceTile[_tileIndexX * ISOTILEX + _tileIndexY].getCenterPoint().x,
				//			_currentPlaceTile[_tileIndexX * ISOTILEX + _tileIndexY].getCenterPoint().y,
				//			_currentPlaceTile[_destTileIndexX * ISOTILEX + _destTileIndexY].getCenterPoint().x,
				//			_currentPlaceTile[_destTileIndexX * ISOTILEX + _destTileIndexY].getCenterPoint().y);
				//		break;
				//	}					
				//}

				//tempX = _targetMonster->getTileIndexX();
				//tempY = _targetMonster->getTileIndexY();
				////타겟 몬스터 기준 맨 오른쪽 좌표까지 가는중에 플레이어가 있다면 플레이어는 왼쪽으로 이동해야한다.
				//while (tempX != 0 && tempY != ISOTILEY - 1 && _characterAction == CHA_IDLE)
				//{
				//	tempX--;
				//	tempY++;
				//	if (tempX == _tileIndexX && tempY == _tileIndexY)
				//	{
				//		//캐릭터 행동은 왼쪽으로 걸어감
				//		_characterAction = CHA_LEFT;
				//		//캐릭터 목적지는 타겟 몬스터의 바로 오른쪽칸
				//		_destTileIndexX = _targetMonster->getTileIndexX() - 1;
				//		_destTileIndexY = _targetMonster->getTileIndexY() + 1;
				//		_angle =
				//			getAngle(_currentPlaceTile[_tileIndexX * ISOTILEX + _tileIndexY].getCenterPoint().x,
				//			_currentPlaceTile[_tileIndexX * ISOTILEX + _tileIndexY].getCenterPoint().y,
				//			_currentPlaceTile[_destTileIndexX * ISOTILEX + _destTileIndexY].getCenterPoint().x,
				//			_currentPlaceTile[_destTileIndexX * ISOTILEX + _destTileIndexY].getCenterPoint().y);
				//		break;
				//	}
				//}

				//tempX = _targetMonster->getTileIndexX();
				//tempY = _targetMonster->getTileIndexY();
				////타겟 몬스터 기준 맨 위 좌표까지 가는중에 플레이어가 있다면 플레이어는 아래으로 이동해야한다.
				//while (tempX != 0 && tempY != 0 && _characterAction == CHA_IDLE)
				//{
				//	tempX--;
				//	tempY--;
				//	if (tempX == _tileIndexX && tempY == _tileIndexY)
				//	{
				//		//캐릭터 행동은 아래로로 걸어감
				//		_characterAction = CHA_DOWN;
				//		//캐릭터 목적지는 타겟 몬스터의 바로 위칸
				//		_destTileIndexX = _targetMonster->getTileIndexX() - 1;
				//		_destTileIndexY = _targetMonster->getTileIndexY() - 1;
				//		_angle =
				//			getAngle(_currentPlaceTile[_tileIndexX * ISOTILEX + _tileIndexY].getCenterPoint().x,
				//			_currentPlaceTile[_tileIndexX * ISOTILEX + _tileIndexY].getCenterPoint().y,
				//			_currentPlaceTile[_destTileIndexX * ISOTILEX + _destTileIndexY].getCenterPoint().x,
				//			_currentPlaceTile[_destTileIndexX * ISOTILEX + _destTileIndexY].getCenterPoint().y);
				//		break;
				//	}
				//}

				//tempX = _targetMonster->getTileIndexX();
				//tempY = _targetMonster->getTileIndexY();
				////타겟 몬스터 기준 맨 아래 좌표까지 가는중에 플레이어가 있다면 플레이어는 위로 이동해야한다.
				//while (tempX != ISOTILEY - 1 && tempY != ISOTILEY - 1 && _characterAction == CHA_IDLE)
				//{
				//	tempX++;
				//	tempY++;
				//	if (tempX == _tileIndexX && tempY == _tileIndexY)
				//	{
				//		//캐릭터 행동은 위로 걸어감
				//		_characterAction = CHA_UP;
				//		//캐릭터 목적지는 타겟 몬스터의 바로 위칸
				//		_destTileIndexX = _targetMonster->getTileIndexX() + 1;
				//		_destTileIndexY = _targetMonster->getTileIndexY() + 1;
				//		_angle =
				//			getAngle(_currentPlaceTile[_tileIndexX * ISOTILEX + _tileIndexY].getCenterPoint().x,
				//			_currentPlaceTile[_tileIndexX * ISOTILEX + _tileIndexY].getCenterPoint().y,
				//			_currentPlaceTile[_destTileIndexX * ISOTILEX + _destTileIndexY].getCenterPoint().x,
				//			_currentPlaceTile[_destTileIndexX * ISOTILEX + _destTileIndexY].getCenterPoint().y);
				//		break;
				//	}
				//}

//				sprintf(_tiletest, "%d, %d", tempX, tempY);
				//맨 
				//for (;tempX == _targetMonster->getTileIndexX() && _targetMonster->getTileIndexY(); )
				//{
				//	//맨 좌측에서
				//	if ()
				//	tempX--; tempY++;
				//}
			
			//2. 전투시작
			//2-1. 전투 딜레이 및 스킬 등 이것저것

		}

		//타겟된 몬스터가 없다면 단순 타일 이동이므로
		if (_targetMonster == NULL)
		{
			//타일 검출 및 이동
			for (int i = 0; i < ISOTILEX * ISOTILEY; ++i)
			{

				/*RECT temp;

				RECT tempCameraRC = RectMake(MAPTOOLCAMERAMANAGER->CameraRelativePoint(_cameraRC).x,
				MAPTOOLCAMERAMANAGER->CameraRelativePoint(_cameraRC).y,
				TILEWINSIZEX, TILEWINSIZEY);

				RECT tempTileRC = RectMake(MAPTOOLCAMERAMANAGER->CameraRelativePoint(_tiles[i].renderPoint).x,
				MAPTOOLCAMERAMANAGER->CameraRelativePoint(_tiles[i].renderPoint).y,
				IMAGEMANAGER->findImage("mapTiles")->getFrameWidth(), IMAGEMANAGER->findImage("mapTiles")->getFrameHeight());

				if (!IntersectRect(&temp, &tempCameraRC, &tempTileRC)) continue;*/

				POINT tempPoint[4];
				//if ( PtInRect(&_tiles[i].rc, _ptMouse) )
				for (int j = 0; j < 4; ++j)
				{
					tempPoint[j] = CAMERAMANAGER->CameraRelativePoint(_currentPlaceTile[i].point[j]);
				}
				HRGN rgn = CreatePolygonRgn(tempPoint, 4, 1);
				//HRGN rgn = CreatePolygonRgn(_tiles[i].point, 4, 1);
				if (PtInRegion(rgn, _ptMouse.x, _ptMouse.y))
				{
					//마우스 클릭시 순간이동 코드
					//_tileIndexX = i / ISOTILEX;
					//_tileIndexY = i % ISOTILEY;

					if (_currentPlaceTile[i].obj == OBJ_MUSURI)
					{
						if (_isMusuriNpcClick) _isMusuriNpcClick = false;
						else _isMusuriNpcClick = true;
						_isHosulamNpcClick = _isJanggumiNpcClick = false;
						break;
					}
					else if (_currentPlaceTile[i].obj == OBJ_JANGGUMI)
					{
						if (_isJanggumiNpcClick) _isJanggumiNpcClick = false;
						else _isJanggumiNpcClick = true;

						_isHosulamNpcClick = _isMusuriNpcClick = false;
						break;
					}
					else if (_currentPlaceTile[i].obj == OBJ_HOSULAM)
					{
						if (_isHosulamNpcClick) _isHosulamNpcClick = false;
						else _isHosulamNpcClick = true;

						_isMusuriNpcClick = _isJanggumiNpcClick = false;
						break;
					}
					else if (_currentPlaceTile[i].obj == OBJ_POTAL || _currentPlaceTile[i].obj == OBJ_POTAL_DUMMY)
					{
						mapChange();
					}
					else if (!_isMusuriNpcClick && !_isJanggumiNpcClick && !_isHosulamNpcClick)
					{
						//자연스레 이동 코드
						/*_angle =
							getAngle(_currentPlaceTile[_tileIndexX * ISOTILEX + _tileIndexY].getCenterPoint().x,
							_currentPlaceTile[_tileIndexX * ISOTILEX + _tileIndexY].getCenterPoint().y,
							_currentPlaceTile[i].getCenterPoint().x,
							_currentPlaceTile[i].getCenterPoint().y);*/

						_destTileIndexX = i / ISOTILEX;
						_destTileIndexY = i % ISOTILEX;


						//버그 수정부분 근데 부자연스러움
						if (_tileIndexX == _destTileIndexX && _tileIndexY == _destTileIndexY)
						{
							_characterAction = CHA_IDLE;
							_x = _currentPlaceTile[_destTileIndexX * ISOTILEX + _destTileIndexY].getCenterPoint().x;
							_y = _currentPlaceTile[_destTileIndexX * ISOTILEX + _destTileIndexY].getCenterPoint().y;
							_tempX = _x; _tempY = _y;
							_tileIndexX = _destTileIndexX;
							_tileIndexY = _destTileIndexY;

							DeleteObject(rgn);
							DeleteObject(tempPoint);
							break;
						}

						//_aStar->setTiles(_tileIndexX, _tileIndexY, _destTileIndexX, _destTileIndexY, _currentPlaceTile);
						//_aStar->getNextTile();

						//POINT tempPoint1 = _aStar->getTile();
					//	_aStar->removeFirstTile();
						//_destTempTileIndex = tempPoint1;

						//_characterAction = CHA_RIGHT;
						DeleteObject(rgn);
						DeleteObject(tempPoint);
						break;
						//makeRC();
					}
				}
				DeleteObject(rgn);
				DeleteObject(tempPoint);
			}
		}
	}
}
void character::mapChange()
{
	if (_place == PLACE_TOWN)
	{
		_place = PLACE_HUNTING;
		_clickPotal = true;
		_tileIndexX = _tileIndexY = _destTileIndexX = _destTileIndexY = 0;
		_x = _currentPlaceTile[_tileIndexX * ISOTILEX + _tileIndexY].getCenterPoint().x;
		_y = _currentPlaceTile[_tileIndexX * ISOTILEX + _tileIndexY].getCenterPoint().y;
		_tempX = _x; _tempY = _y;
		makeRC();
	}
	else
	{
		_place = PLACE_TOWN;
		_clickPotal = true;
		_tileIndexX = _tileIndexY = _destTileIndexX = _destTileIndexY = 0;
		_x = _currentPlaceTile[_tileIndexX * ISOTILEX + _tileIndexY].getCenterPoint().x;
		_y = _currentPlaceTile[_tileIndexX * ISOTILEX + _tileIndexY].getCenterPoint().y;
		_tempX = _x; _tempY = _y;
		makeRC();
	}

	/*if (KEYMANAGER->isOnceKeyDown('P'))
	{
		if (_place == PLACE_TOWN)
		{
			_place = PLACE_HUNTING;
			_clickPotal = true;
			_tileIndexX = _tileIndexY = 0;
			_x = _currentPlaceTile[_tileIndexX * ISOTILEX + _tileIndexY].getCenterPoint().x;
			_y = _currentPlaceTile[_tileIndexX * ISOTILEX + _tileIndexY].getCenterPoint().y;
			_tempX = _x; _tempY = _y;
		}
		else
		{
			_place = PLACE_TOWN;
			_clickPotal = true;
			_tileIndexX = _tileIndexY = 0;
			_x = _currentPlaceTile[_tileIndexX * ISOTILEX + _tileIndexY].getCenterPoint().x;
			_y = _currentPlaceTile[_tileIndexX * ISOTILEX + _tileIndexY].getCenterPoint().y;
			_tempX = _x; _tempY = _y;
		}
	}*/
}

void character::render()
{
	//자연스러움 그리기(1)
	//IMAGEMANAGER->frameRender("연이idle", getMemDC(),
	//	CAMERAMANAGER->CameraRelativePointX(_x),
	//	CAMERAMANAGER->CameraRelativePointY(_y),
	//	_frameX, 0);

	//자연스러움 그리기(2)
	_playImage->aniRender(getMemDC(),
		CAMERAMANAGER->CameraRelativePointX(_characterRC.left),
		CAMERAMANAGER->CameraRelativePointY(_characterRC.top), _animation);
	//IMAGEMANAGER->frameRender("연이기본", getMemDC(),
	//	CAMERAMANAGER->CameraRelativePointX(_characterRC.left),
	//	CAMERAMANAGER->CameraRelativePointY(_characterRC.top),
	//	_frameX, 0);


	//순간이동 그리기
	/*IMAGEMANAGER->frameRender("연이idle", getMemDC(), 
		CAMERAMANAGER->CameraRelativePointX(_currentPlaceTile[_tileIndexX * ISOTILEX + _tileIndexY].x - ISOTILESIZEX / 4),
		CAMERAMANAGER->CameraRelativePointY(_currentPlaceTile[_tileIndexX * ISOTILEX + _tileIndexY].y ),
		_frameX, 0);*/

	char test[30];
	sprintf(test, "%d, %d, %d, %d", _tileIndexX, _tileIndexY, _destTileIndexX, _destTileIndexY);
	//TextOut(getMemDC(), 500, 300, _tiletest, strlen(_tiletest));
	//TextOut(getMemDC(), 500, 400, _aStarTest, strlen(_aStarTest));
	

	if(_isStatusOpen)
		_status->statusOpen(_test);

	if (_isInvenOpen)
		_inven->inventoryOpen();

	if (_isEquipOpen)
		_equip->equipOpen();

	if (_isClickInvenItem)
		_inven->getInvenItem()->render(getMemDC(), _ptMouse.x-17, _ptMouse.y-17);

	if (_isClickEquip)
		_equip->getClickEquip()->render(getMemDC(), _ptMouse.x - 17, _ptMouse.y - 17);

	if (_isMagicOpen)
		_magic->openMagicUI();

	if (_isSkillOpen)
		_skill->openSkillUI();
	//_inven->render();

	if (_targetMonster != NULL)
	{
		IMAGEMANAGER->findImage("몬스터타겟")->render(getMemDC(),
			_targetMonster->getMonsterRC().left,
			_targetMonster->getMonsterRC().top - IMAGEMANAGER->findImage("몬스터타겟")->getHeight());

		_targetMonster->HPDraw();
	}



	char whatproblem[111];
	sprintf(whatproblem, "%d, %d", _characterAction, _attackDelay);

	EFFECTMANAGER->render();
	//TextOut(getMemDC(), 0, 100, whatproblem, strlen(whatproblem));
	//TextOut(getMemDC(), 100 * (i+1), 10, _test, strlen(_test));
}

void character::addImage()		//이미기 추가해주는 함수 이후 이미지는 여기서 add하는걸로
{
	IMAGEMANAGER->addFrameImage("알파벳", "./image/characterselect/alphabet.bmp", 208, 10, 26, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("연이생성선택", "./image/characterselect/연이생성선택.bmp", 179, 355, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("연이생성미선택", "./image/characterselect/연이생성미선택.bmp", 179, 355, true, RGB(255, 0, 255));

	/*
	CHA_IDLE, CHA_RIGHT, CHA_RIGHTDOWN, CHA_DOWN,
	CHA_LEFTDOWN, CHA_LEFT, CHA_LEFTUP, CHA_UP, CHA_RIGHTUP,
	*/
	//걷기
	_playImage = IMAGEMANAGER->addFrameImage("연이idle", "./image/character/연이/연이idle.bmp", 156, 57, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("연이오른쪽", "./image/character/연이/연이right.bmp", 210, 54, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("연이오른쪽아래", "./image/character/연이/연이rightdown.bmp", 220, 53, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("연이아래", "./image/character/연이/연이down.bmp", 270, 52, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("연이왼쪽아래", "./image/character/연이/연이leftdown.bmp", 220, 53, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("연이왼쪽", "./image/character/연이/연이left.bmp", 210, 54, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("연이왼쪽위", "./image/character/연이/연이leftup.bmp", 282, 61, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("연이위", "./image/character/연이/연이up.bmp", 225, 61, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("연이오른쪽위", "./image/character/연이/연이rightup.bmp", 282, 61, 6, 1, true, RGB(255, 0, 255));
	
	//공격
	//IMAGEMANAGER->addFrameImage("연이", "./image/character/연이/연이idle.bmp", 156, 57, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("연이오른쪽공격", "./image/character/연이/연이rightattack.bmp", 305, 55, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("연이오른쪽아래공격", "./image/character/연이/연이rightdownattack.bmp", 250, 58, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("연이아래공격", "./image/character/연이/연이downattack.bmp", 185, 60, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("연이왼쪽아래공격", "./image/character/연이/연이leftdownattack.bmp", 250, 58, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("연이왼쪽공격", "./image/character/연이/연이leftattack.bmp", 305, 55, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("연이왼쪽위공격", "./image/character/연이/연이leftupattack.bmp", 260, 54, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("연이위공격", "./image/character/연이/연이upattack.bmp", 205, 58, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("연이오른쪽위공격", "./image/character/연이/연이rightupattack.bmp", 260, 54, 5, 1, true, RGB(255, 0, 255));

	//죽음
	IMAGEMANAGER->addFrameImage("연이죽음", "./image/character/연이/연이death.bmp", 300, 59, 5, 1, true, RGB(255, 0, 255));



	IMAGEMANAGER->addImage("견이생성선택", "./image/characterselect/견이생성선택.bmp", 174, 351, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("견이생성미선택", "./image/characterselect/견이생성미선택.bmp", 179, 355, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("신이생성선택", "./image/characterselect/신이생성선택.bmp", 173, 351, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("신이생성미선택", "./image/characterselect/신이생성미선택.bmp", 179, 354, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("몬스터타겟", "./image/monster/타겟.bmp", 54, 56, true, RGB(255, 0, 255));

	//IMAGEMANAGER->addFrameImage("벼락", "./image/magic/magicUI/스킬이펙트.bmp", 300, 121, 5, 1, true, RGB(255, 0, 255));
	EFFECTMANAGER->addEffect("벼락", "./image/magic/magicUI/스킬이펙트.bmp", 300, 121, 60, 121, 1.0f, 0.1f, 10);
}

void character::initialization()	//변수들 new선언 및 init 해주는 함수 이후 new 및 init은 여기서 하는걸로
{

}

void character::singletonInit()	//init에서 싱글톤들 세팅해주는 함수 이후 세팅은 여기서 하는걸로
{

}

//셀렉트씬에서 그려주기 위한 렌더함수
void character::selectRender(int i, bool isSelect)
{
	//선택 되었으면
	if (isSelect)
	{
		strcpy(_characterImageName, _characterName);
		strcat(_characterImageName, "생성선택");
		_selectImage = IMAGEMANAGER->findImage(_characterImageName);
	}
	else
	{
		strcpy(_characterImageName, _characterName);
		strcat(_characterImageName, "생성미선택");
		_selectImage = IMAGEMANAGER->findImage(_characterImageName);
	}

	switch (i)
	{
	case 0:
		_selectImage->render(getMemDC(), 118, 54);		
		break;
	case 1:
		_selectImage->render(getMemDC(), 311, 54);
		break;
	case 2:
		_selectImage->render(getMemDC(), 504, 54);
		break;
	default:
		break;
	}
	selectAlphabetRender(i);
}
void character::selectAlphabetRender(int i)
{
	//97 67 504
	switch (i)
	{
	case 0:
		for (int i = 0; i < strlen(_test); ++i)
		{
			IMAGEMANAGER->findImage("알파벳")->frameRender(getMemDC(), 185 + 8* i, 60, (int)_test[i] - 97, 0);
		}
		//_selectImage->render(getMemDC(), 118, 54);
		break;
	case 1:
		for (int i = 0; i < strlen(_test); ++i)
		{
			IMAGEMANAGER->findImage("알파벳")->frameRender(getMemDC(), 378 + 8 * i, 60, (int)_test[i] - 97, 0);
		}
		//_selectImage->render(getMemDC(), 311, 54);
		break;
	case 2:
		for (int i = 0; i < strlen(_test); ++i)
		{
			IMAGEMANAGER->findImage("알파벳")->frameRender(getMemDC(), 571 + 8 * i, 60, (int)_test[i] - 97, 0);
		}
		//_selectImage->render(getMemDC(), 504, 54);
		break;
	default:
		break;
	}
}

void character::makeRC(){

	//순간이동 카메라
	/*_characterRC = RectMake(_currentPlaceTile[_tileIndexX * ISOTILEX + _tileIndexY].x - ISOTILESIZEX / 4,
		_currentPlaceTile[_tileIndexX * ISOTILEX + _tileIndexY].y,
		_playImage->getFrameWidth(),
		_playImage->getFrameHeight());*/

	//자연스러운 카메라
	_characterRC = RectMakeCenter(_x,	_y,
		_playImage->getFrameWidth(),
		_playImage->getFrameHeight());
}