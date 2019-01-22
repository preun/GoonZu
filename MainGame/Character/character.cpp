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
		strcpy(_characterName, "����");
		break;
	case YOUN:
		strcpy(_characterName, "����");
		break;
	case SIN:
		strcpy(_characterName, "����");
		break;
	case NONEKIND:
		break;
	default:
		break;
	}
	//�⺻���� **�������� �ʱ�ȭ��
	strcpy(_characterImageName, _characterName);
	strcat(_characterImageName, "��������");

	addImage();
	
	strcpy(_test, test);

	//�ʱ� �ε��� ��ǥ�� 10, 10
	_tileIndexX = _tileIndexY = _destTileIndexX = _destTileIndexY =0;
	//�ʱ� ��Ҵ� ����
	_place = PLACE_TOWN;
	_clickPotal = false;

	//�ʱ���´� ���̵�
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

	//�⺻
	_animationArray[CHA_IDLE] = new animation;
	_animationArray[CHA_IDLE]->init(IMAGEMANAGER->findImage("����idle")->getWidth(), IMAGEMANAGER->findImage("����idle")->getHeight(),
		IMAGEMANAGER->findImage("����idle")->getFrameWidth(), IMAGEMANAGER->findImage("����idle")->getFrameHeight());
	_animationArray[CHA_IDLE]->setDefPlayFrame(false, true);
	_animationArray[CHA_IDLE]->start();
	_animationArray[CHA_IDLE]->setFPS(1);

	//������ �ȱ�
	_animationArray[CHA_RIGHT] = new animation;
	_animationArray[CHA_RIGHT]->init(IMAGEMANAGER->findImage("���̿�����")->getWidth(), IMAGEMANAGER->findImage("���̿�����")->getHeight(),
		IMAGEMANAGER->findImage("���̿�����")->getFrameWidth(), IMAGEMANAGER->findImage("���̿�����")->getFrameHeight());
	_animationArray[CHA_RIGHT]->setDefPlayFrame(false, true);
	_animationArray[CHA_RIGHT]->start();
	_animationArray[CHA_RIGHT]->setFPS(1);
	
	//������ �Ʒ� �ȱ�
	_animationArray[CHA_RIGHTDOWN] = new animation;
	_animationArray[CHA_RIGHTDOWN]->init(IMAGEMANAGER->findImage("���̿����ʾƷ�")->getWidth(), IMAGEMANAGER->findImage("���̿����ʾƷ�")->getHeight(),
		IMAGEMANAGER->findImage("���̿����ʾƷ�")->getFrameWidth(), IMAGEMANAGER->findImage("���̿����ʾƷ�")->getFrameHeight());
	_animationArray[CHA_RIGHTDOWN]->setDefPlayFrame(false, true);
	_animationArray[CHA_RIGHTDOWN]->start();
	_animationArray[CHA_RIGHTDOWN]->setFPS(1);
	
	//�Ʒ� �ȱ�
	_animationArray[CHA_DOWN] = new animation;
	_animationArray[CHA_DOWN]->init(IMAGEMANAGER->findImage("���̾Ʒ�")->getWidth(), IMAGEMANAGER->findImage("���̾Ʒ�")->getHeight(),
		IMAGEMANAGER->findImage("���̾Ʒ�")->getFrameWidth(), IMAGEMANAGER->findImage("���̾Ʒ�")->getFrameHeight());
	_animationArray[CHA_DOWN]->setDefPlayFrame(false, true);
	_animationArray[CHA_DOWN]->start();
	_animationArray[CHA_DOWN]->setFPS(1);
	
	//���� �Ʒ� �ȱ�
	_animationArray[CHA_LEFTDOWN] = new animation;
	_animationArray[CHA_LEFTDOWN]->init(IMAGEMANAGER->findImage("���̿��ʾƷ�")->getWidth(), IMAGEMANAGER->findImage("���̿��ʾƷ�")->getHeight(),
		IMAGEMANAGER->findImage("���̿��ʾƷ�")->getFrameWidth(), IMAGEMANAGER->findImage("���̿��ʾƷ�")->getFrameHeight());
	_animationArray[CHA_LEFTDOWN]->setDefPlayFrame(false, true);
	_animationArray[CHA_LEFTDOWN]->start();
	_animationArray[CHA_LEFTDOWN]->setFPS(1);
	
	//���� �ȱ�
	_animationArray[CHA_LEFT] = new animation;
	_animationArray[CHA_LEFT]->init(IMAGEMANAGER->findImage("���̿���")->getWidth(), IMAGEMANAGER->findImage("���̿���")->getHeight(),
		IMAGEMANAGER->findImage("���̿���")->getFrameWidth(), IMAGEMANAGER->findImage("���̿���")->getFrameHeight());
	_animationArray[CHA_LEFT]->setDefPlayFrame(false, true);
	_animationArray[CHA_LEFT]->start();
	_animationArray[CHA_LEFT]->setFPS(1);
	
	//���� �� �ȱ�
	_animationArray[CHA_LEFTUP] = new animation;
	_animationArray[CHA_LEFTUP]->init(IMAGEMANAGER->findImage("���̿�����")->getWidth(), IMAGEMANAGER->findImage("���̿�����")->getHeight(),
		IMAGEMANAGER->findImage("���̿�����")->getFrameWidth(), IMAGEMANAGER->findImage("���̿�����")->getFrameHeight());
	_animationArray[CHA_LEFTUP]->setDefPlayFrame(false, true);
	_animationArray[CHA_LEFTUP]->start();
	_animationArray[CHA_LEFTUP]->setFPS(1);
	
	//�� �ȱ�
	_animationArray[CHA_UP] = new animation;
	_animationArray[CHA_UP]->init(IMAGEMANAGER->findImage("������")->getWidth(), IMAGEMANAGER->findImage("������")->getHeight(),
		IMAGEMANAGER->findImage("������")->getFrameWidth(), IMAGEMANAGER->findImage("������")->getFrameHeight());
	_animationArray[CHA_UP]->setDefPlayFrame(false, true);
	_animationArray[CHA_UP]->start();
	_animationArray[CHA_UP]->setFPS(1);
	
	//������ �� �ȱ�
	_animationArray[CHA_RIGHTUP] = new animation;
	_animationArray[CHA_RIGHTUP]->init(IMAGEMANAGER->findImage("���̿�������")->getWidth(), IMAGEMANAGER->findImage("���̿�������")->getHeight(),
		IMAGEMANAGER->findImage("���̿�������")->getFrameWidth(), IMAGEMANAGER->findImage("���̿�������")->getFrameHeight());
	_animationArray[CHA_RIGHTUP]->setDefPlayFrame(false, true);
	_animationArray[CHA_RIGHTUP]->start();
	_animationArray[CHA_RIGHTUP]->setFPS(1);

	//������ ����
	_animationArray[CHA_RIGHT_ATTACK] = new animation;
	_animationArray[CHA_RIGHT_ATTACK]->init(IMAGEMANAGER->findImage("���̿����ʰ���")->getWidth(), IMAGEMANAGER->findImage("���̿����ʰ���")->getHeight(),
		IMAGEMANAGER->findImage("���̿����ʰ���")->getFrameWidth(), IMAGEMANAGER->findImage("���̿����ʰ���")->getFrameHeight());
	_animationArray[CHA_RIGHT_ATTACK]->setDefPlayFrame(false, true);
	_animationArray[CHA_RIGHT_ATTACK]->start();
	_animationArray[CHA_RIGHT_ATTACK]->setFPS(1);

	//������ �Ʒ� ����
	_animationArray[CHA_RIGHTDOWN_ATTACK] = new animation;
	_animationArray[CHA_RIGHTDOWN_ATTACK]->init(IMAGEMANAGER->findImage("���̿����ʾƷ�����")->getWidth(), IMAGEMANAGER->findImage("���̿����ʾƷ�����")->getHeight(),
		IMAGEMANAGER->findImage("���̿����ʾƷ�����")->getFrameWidth(), IMAGEMANAGER->findImage("���̿����ʾƷ�����")->getFrameHeight());
	_animationArray[CHA_RIGHTDOWN_ATTACK]->setDefPlayFrame(false, true);
	_animationArray[CHA_RIGHTDOWN_ATTACK]->start();
	_animationArray[CHA_RIGHTDOWN_ATTACK]->setFPS(1);

	//�Ʒ� ����
	_animationArray[CHA_DOWN_ATTACK] = new animation;
	_animationArray[CHA_DOWN_ATTACK]->init(IMAGEMANAGER->findImage("���̾Ʒ�����")->getWidth(), IMAGEMANAGER->findImage("���̾Ʒ�����")->getHeight(),
		IMAGEMANAGER->findImage("���̾Ʒ�����")->getFrameWidth(), IMAGEMANAGER->findImage("���̾Ʒ�����")->getFrameHeight());
	_animationArray[CHA_DOWN_ATTACK]->setDefPlayFrame(false, true);
	_animationArray[CHA_DOWN_ATTACK]->start();
	_animationArray[CHA_DOWN_ATTACK]->setFPS(1);

	//���� �Ʒ� ����
	_animationArray[CHA_LEFTDOWN_ATTACK] = new animation;
	_animationArray[CHA_LEFTDOWN_ATTACK]->init(IMAGEMANAGER->findImage("���̿��ʾƷ�����")->getWidth(), IMAGEMANAGER->findImage("���̿��ʾƷ�����")->getHeight(),
		IMAGEMANAGER->findImage("���̿��ʾƷ�����")->getFrameWidth(), IMAGEMANAGER->findImage("���̿��ʾƷ�����")->getFrameHeight());
	_animationArray[CHA_LEFTDOWN_ATTACK]->setDefPlayFrame(false, true);
	_animationArray[CHA_LEFTDOWN_ATTACK]->start();
	_animationArray[CHA_LEFTDOWN_ATTACK]->setFPS(1);

	//���� ����
	_animationArray[CHA_LEFT_ATTACK] = new animation;
	_animationArray[CHA_LEFT_ATTACK]->init(IMAGEMANAGER->findImage("���̿��ʰ���")->getWidth(), IMAGEMANAGER->findImage("���̿��ʰ���")->getHeight(),
		IMAGEMANAGER->findImage("���̿��ʰ���")->getFrameWidth(), IMAGEMANAGER->findImage("���̿��ʰ���")->getFrameHeight());
	_animationArray[CHA_LEFT_ATTACK]->setDefPlayFrame(false, true);
	_animationArray[CHA_LEFT_ATTACK]->start();
	_animationArray[CHA_LEFT_ATTACK]->setFPS(1);

	//���� �� ����
	_animationArray[CHA_LEFTUP_ATTACK] = new animation;
	_animationArray[CHA_LEFTUP_ATTACK]->init(IMAGEMANAGER->findImage("���̿���������")->getWidth(), IMAGEMANAGER->findImage("���̿���������")->getHeight(),
		IMAGEMANAGER->findImage("���̿���������")->getFrameWidth(), IMAGEMANAGER->findImage("���̿���������")->getFrameHeight());
	_animationArray[CHA_LEFTUP_ATTACK]->setDefPlayFrame(false, true);
	_animationArray[CHA_LEFTUP_ATTACK]->start();
	_animationArray[CHA_LEFTUP_ATTACK]->setFPS(1);

	//�� ����
	_animationArray[CHA_UP_ATTACK] = new animation;
	_animationArray[CHA_UP_ATTACK]->init(IMAGEMANAGER->findImage("����������")->getWidth(), IMAGEMANAGER->findImage("����������")->getHeight(),
		IMAGEMANAGER->findImage("����������")->getFrameWidth(), IMAGEMANAGER->findImage("����������")->getFrameHeight());
	_animationArray[CHA_UP_ATTACK]->setDefPlayFrame(false, true);
	_animationArray[CHA_UP_ATTACK]->start();
	_animationArray[CHA_UP_ATTACK]->setFPS(1);

	//������ �� ����
	_animationArray[CHA_RIGHTUP_ATTACK] = new animation;
	_animationArray[CHA_RIGHTUP_ATTACK]->init(IMAGEMANAGER->findImage("���̿�����������")->getWidth(), IMAGEMANAGER->findImage("���̿�����������")->getHeight(),
		IMAGEMANAGER->findImage("���̿�����������")->getFrameWidth(), IMAGEMANAGER->findImage("���̿�����������")->getFrameHeight());
	_animationArray[CHA_RIGHTUP_ATTACK]->setDefPlayFrame(false, true);
	_animationArray[CHA_RIGHTUP_ATTACK]->start();
	_animationArray[CHA_RIGHTUP_ATTACK]->setFPS(1);

	_animationArray[CHA_DEATH] = new animation;
	_animationArray[CHA_DEATH]->init(IMAGEMANAGER->findImage("��������")->getWidth(), IMAGEMANAGER->findImage("��������")->getHeight(),
		IMAGEMANAGER->findImage("��������")->getFrameWidth(), IMAGEMANAGER->findImage("��������")->getFrameHeight());
	_animationArray[CHA_DEATH]->setDefPlayFrame(false, false);
	_animationArray[CHA_DEATH]->start();
	_animationArray[CHA_DEATH]->setFPS(1);

	_animation = _animationArray[CHA_IDLE]; //�ʱⰪ�� ���� �⺻

	//_skillRC = RectMake();

	return S_OK;
}

void character::release()
{

}

void character::update()
{
	//�׾��ٸ� ������Ʈ ��������
	if (*_status->getCurrentHP() <= 0)
	{
		_characterAction = CHA_DEATH;
		_playImage = IMAGEMANAGER->findImage("��������");
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
	//F1������
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
	//F2������
	else if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{

	}
	//F3������
	else if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{

	}
	//F4������
	else if (KEYMANAGER->isOnceKeyDown(VK_F4))
	{

	}
	//F5������
	else if (KEYMANAGER->isOnceKeyDown(VK_F5))
	{

	}

	//���������� 3 ������ ����ġ ��� 
	if (_isStatusOpen) _status->update();
	//�����
	if (_isInvenOpen) _inven->update();

	//if (_isMagicOpen) _magic->update();

	//������(Ű�ִϸŴ���ȭ)?
	//_count++;
	//if (_count % 10 == 0)
	//{
	//	_frameX++;
	//	if (_frameX >= IMAGEMANAGER->findImage("����idle")->getMaxFrameX()) _frameX = 0;
	//	_count = 0;
	//}

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		if (_isClickEquip) _isClickEquip = false;
		else if (_isClickInvenItem) _isClickInvenItem = false;
		else if (_isMagicOpen && PtInRect(&_magicRC, _ptMouse)) _magic->clickMagicUI(false);
		//��ų���
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
						EFFECTMANAGER->play("����", tempTargetMonsterPoint.x,
							tempTargetMonsterPoint.y - 121 / 2);//- IMAGEMANAGER->findImage();
					}
				
			}
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		lbuttonEvent();
	}
	//ĳ���� �ൿ ���� ���ϱ�
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
		//Ÿ�ٸ��Ͱ� ������ aStar�� �� Ÿ�� ã�� 
		//if (tempPoint.x != _tileIndexX && tempPoint.y != _tileIndexY)
		//{
		_aStar->setTiles(_tileIndexX, _tileIndexY, _targetMonster->getTileIndexX(), _targetMonster->getTileIndexY(), _currentPlaceTile);
		tempPoint = _aStar->getNextTile();
		//}
		//���Ϳ� ��ĭ���̸� �ű���� ����!
		if (tempPoint.x == -1 && tempPoint.y == -1 )
		{
			if (_targetMonster->getTileIndexX() == _tileIndexX && _targetMonster->getTileIndexY() > _tileIndexY)
			{
				_characterAction = CHA_RIGHTDOWN_ATTACK;
			}
			//x���� ���� y���� �� ���� �� ������ ���� ���� �����Ѵ�.
			else if (_targetMonster->getTileIndexX() == _tileIndexX && _targetMonster->getTileIndexY() < _tileIndexY)
			{
				_characterAction = CHA_LEFTUP_ATTACK;
			}
			//y���� ���� x���� �� ���� �� ũ�� ���� �Ʒ��� �����Ѵ�.
			else if (_targetMonster->getTileIndexX() > _tileIndexX && _targetMonster->getTileIndexY() == _tileIndexY)
			{
				_characterAction = CHA_LEFTDOWN_ATTACK;
			}
			//y���� ���� x���� �� ���� �� ũ�� ������ ���� �����Ѵ�.
			else if (_targetMonster->getTileIndexX() < _tileIndexX && _targetMonster->getTileIndexY() == _tileIndexY)
			{
				_characterAction = CHA_RIGHTUP_ATTACK;
			}
			//������ ���� �������̸鼭 ���� ���ʿ� ������ ���������� �����Ѵ�.
			else if (_targetMonster->getTileIndexX() < _tileIndexX && _targetMonster->getTileIndexY() > _tileIndexY)
			{
				_characterAction = CHA_RIGHT_ATTACK;
			}
			//������ ���� �������̸鼭 ���� �����ʿ� ������ �������� �����Ѵ�.
			else if (_targetMonster->getTileIndexX() > _tileIndexX && _targetMonster->getTileIndexY() < _tileIndexY)
			{
				_characterAction = CHA_LEFT_ATTACK;
			}
			//������ ���� �������̸鼭 ���� ���ʿ� ������ �Ʒ������� �����Ѵ�.
			else if (_targetMonster->getTileIndexX() > _tileIndexX && _targetMonster->getTileIndexY() > _tileIndexY)
			{
				_characterAction = CHA_DOWN_ATTACK;
			}
			//������ ���� �������̸鼭 ���� �Ʒ��ʿ� ������ ���� �����Ѵ�.
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

		//x���� ���� y���� �� ���� �� ũ�� ������ �Ʒ��� �����Ѵ�.
		//if (tempPoint.x != _tileIndexX && tempPoint.y != _tileIndexY)
		//{
			if (tempPoint.x == _tileIndexX && tempPoint.y > _tileIndexY)
			{
				_characterAction = CHA_RIGHTDOWN;
			}
			//x���� ���� y���� �� ���� �� ������ ���� ���� �����Ѵ�.
			else if (tempPoint.x == _tileIndexX && tempPoint.y < _tileIndexY)
			{
				_characterAction = CHA_LEFTUP;
			}
			//y���� ���� x���� �� ���� �� ũ�� ���� �Ʒ��� �����Ѵ�.
			else if (tempPoint.x > _tileIndexX && tempPoint.y == _tileIndexY)
			{
				_characterAction = CHA_LEFTDOWN;
			}
			//y���� ���� x���� �� ���� �� ũ�� ������ ���� �����Ѵ�.
			else if (tempPoint.x < _tileIndexX && tempPoint.y == _tileIndexY)
			{
				_characterAction = CHA_RIGHTUP;
			}
			//������ ���� �������̸鼭 ���� ���ʿ� ������ ���������� �����Ѵ�.
			else if (tempPoint.x < _tileIndexX && tempPoint.y > _tileIndexY)
			{
				_characterAction = CHA_RIGHT;
			}
			//������ ���� �������̸鼭 ���� �����ʿ� ������ �������� �����Ѵ�.
			else if (tempPoint.x > _tileIndexX && tempPoint.y < _tileIndexY)
			{
				_characterAction = CHA_LEFT;
			}
			//������ ���� �������̸鼭 ���� ���ʿ� ������ �Ʒ������� �����Ѵ�.
			else if (tempPoint.x > _tileIndexX && tempPoint.y > _tileIndexY)
			{
				_characterAction = CHA_DOWN;
			}
			//������ ���� �������̸鼭 ���� �Ʒ��ʿ� ������ ���� �����Ѵ�.
			else if (tempPoint.x < _tileIndexX && tempPoint.y < _tileIndexY)
			{
				_characterAction = CHA_UP;
			}
		//}
	}
	//Ÿ�ٸ��Ͱ� ������ �׳� �̵��̴�.
	else
	{
		//���� ���ִ°��� �������� ������ ������ �ʿ䰡 ����.
		if (_tileIndexX == _destTileIndexX && _tileIndexY == _destTileIndexY)
		{
			_characterAction = CHA_IDLE;
			return;
		}

		//�ٸ��ٸ� �̵��� �ؾ��ϴ� A��Ÿ ȣ���� �Ѵ�.

		_aStar->setTiles(_tileIndexX, _tileIndexY, _destTileIndexX, _destTileIndexY, _currentPlaceTile);
		tempPoint = _aStar->getNextTile();

		//�ٷ� ��ĭ���̴�. 
		if (tempPoint.x == -1 && tempPoint.y == -1) tempPoint = PointMake(_destTileIndexX, _destTileIndexY);
		if (tempPoint.x == _tileIndexX && tempPoint.y > _tileIndexY)
		{
			_characterAction = CHA_RIGHTDOWN;
		}
		//x���� ���� y���� �� ���� �� ������ ���� ���� �����Ѵ�.
		else if (tempPoint.x == _tileIndexX && tempPoint.y < _tileIndexY)
		{
			_characterAction = CHA_LEFTUP;
		}
		//y���� ���� x���� �� ���� �� ũ�� ���� �Ʒ��� �����Ѵ�.
		else if (tempPoint.x > _tileIndexX && tempPoint.y == _tileIndexY)
		{
			_characterAction = CHA_LEFTDOWN;
		}
		//y���� ���� x���� �� ���� �� ũ�� ������ ���� �����Ѵ�.
		else if (tempPoint.x < _tileIndexX && tempPoint.y == _tileIndexY)
		{
			_characterAction = CHA_RIGHTUP;
		}
		//������ ���� �������̸鼭 ���� ���ʿ� ������ ���������� �����Ѵ�.
		else if (tempPoint.x < _tileIndexX && tempPoint.y > _tileIndexY)
		{
			_characterAction = CHA_RIGHT;
		}
		//������ ���� �������̸鼭 ���� �����ʿ� ������ �������� �����Ѵ�.
		else if (tempPoint.x > _tileIndexX && tempPoint.y < _tileIndexY)
		{
			_characterAction = CHA_LEFT;
		}
		//������ ���� �������̸鼭 ���� ���ʿ� ������ �Ʒ������� �����Ѵ�.
		else if (tempPoint.x > _tileIndexX && tempPoint.y > _tileIndexY)
		{
			_characterAction = CHA_DOWN;
		}
		//������ ���� �������̸鼭 ���� �Ʒ��ʿ� ������ ���� �����Ѵ�.
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
		_playImage = IMAGEMANAGER->findImage("����idle");
		_animation = _animationArray[CHA_IDLE];
		break;
	case CHA_RIGHT:
		_playImage = IMAGEMANAGER->findImage("���̿�����");
		_animation = _animationArray[CHA_RIGHT];
		break;
	case CHA_RIGHTDOWN:
		_playImage = IMAGEMANAGER->findImage("���̿����ʾƷ�");
		_animation = _animationArray[CHA_RIGHTDOWN];
		break;
	case CHA_DOWN:
		_playImage = IMAGEMANAGER->findImage("���̾Ʒ�");
		_animation = _animationArray[CHA_DOWN];
		break;
	case CHA_LEFTDOWN:
		_playImage = IMAGEMANAGER->findImage("���̿��ʾƷ�");
		_animation = _animationArray[CHA_LEFTDOWN];
		break;
	case CHA_LEFT:
		_playImage = IMAGEMANAGER->findImage("���̿���");
		_animation = _animationArray[CHA_LEFT];
		break;
	case CHA_LEFTUP:
		_playImage = IMAGEMANAGER->findImage("���̿�����");
		_animation = _animationArray[CHA_LEFTUP];
		break;
	case CHA_UP:
		_playImage = IMAGEMANAGER->findImage("������");
		_animation = _animationArray[CHA_UP];
		break;
	case CHA_RIGHTUP:
		_playImage = IMAGEMANAGER->findImage("���̿�������");
		_animation = _animationArray[CHA_RIGHTUP];
		break;
	case CHA_RIGHT_ATTACK:
		_playImage = IMAGEMANAGER->findImage("���̿����ʰ���");
		_animation = _animationArray[CHA_RIGHT_ATTACK];
		break;
	case CHA_RIGHTDOWN_ATTACK:
		_playImage = IMAGEMANAGER->findImage("���̿����ʾƷ�����");
		_animation = _animationArray[CHA_RIGHTDOWN_ATTACK];
		break;
	case CHA_DOWN_ATTACK:
		_playImage = IMAGEMANAGER->findImage("���̾Ʒ�����");
		_animation = _animationArray[CHA_DOWN_ATTACK];
		break;
	case CHA_LEFTDOWN_ATTACK:
		_playImage = IMAGEMANAGER->findImage("���̿��ʾƷ�����");
		_animation = _animationArray[CHA_LEFTDOWN_ATTACK];
		break;
	case CHA_LEFT_ATTACK:
		_playImage = IMAGEMANAGER->findImage("���̿��ʰ���");
		_animation = _animationArray[CHA_LEFT_ATTACK];
		break;
	case CHA_LEFTUP_ATTACK:
		_playImage = IMAGEMANAGER->findImage("���̿���������");
		_animation = _animationArray[CHA_LEFTUP_ATTACK];
		break;
	case CHA_UP_ATTACK:
		_playImage = IMAGEMANAGER->findImage("����������");
		_animation = _animationArray[CHA_UP_ATTACK];
		break;
	case CHA_RIGHTUP_ATTACK:
		_playImage = IMAGEMANAGER->findImage("���̿�����������");
		_animation = _animationArray[CHA_RIGHTUP_ATTACK];
		break;
	case CHA_DEATH:
		_playImage = IMAGEMANAGER->findImage("��������");
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

			////���� ����ִ� Ÿ�� �ε����� ������ �ε����� ��������
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
			//				//Ÿ�ϰ�� �̵��� ����
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
	//ĳ������ �ൿ�� �����ϴ� ��Ȳ�̵� ���� �����̰� 50�� �Ѱ����� ���� �� �ִ�.
	if (CHA_RIGHT_ATTACK <= _characterAction && _characterAction <= CHA_RIGHTUP_ATTACK && _attackDelay >= ATTACKDELAY)
	{
		//�����̴� �ٽ� 0���� �����ְ�
		_attackDelay = 0;
		//�÷��̾ �����¼��� ���ʹ� �÷��̾����� �ݰ��Ѵ�.
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
	//��Ŭ�� �ߴµ� �װ��� ����UI�� -> ���Ⱥй�
	//������ ������ �����ϸ� �������� ����⤺
	if (_ptMouse.x > WINSIZEX || _ptMouse.y > WINSIZEY) return;
	//�κ��丮�� ���������� Ŭ���� ���ϸ鼭 ����â ���������
	if (!_isClickInvenItem && !_isClickEquip && _isStatusOpen && PtInRect(&_statusRC, _ptMouse))
	{
		//���Ⱥй�����
		_status->statusDistribution(
			_equip->getWeponAtt().x, _equip->getWeponAtt().y, 5);
	}

	//�κ��丮 ���»��¿��� �κ��丮�� Ŭ�������� �ش� ó�����ִ� �Լ�ȣ��
	else if (!_isClickEquip && _isInvenOpen && PtInRect(&_invenRC, _ptMouse))
	{
		/*������ ��� �ִ»��¿��� Ŭ���� ��ġ �ٲٱ�(false��ȯ)
		  ������ ��� ���� ������ ������ ���(true��ȯ)*/
		_isClickInvenItem = _inven->inventoryClick(_isClickInvenItem);
	}

	//�κ����� ������ Ŭ���ϰ� ������� �����ִ»��¿��� ����� �����ٸ�
	else if (_isClickInvenItem && _isEquipOpen && PtInRect(&_equipRC, _ptMouse))
	{
		//������ ����(���� ������ fasle ��ȯ)
		_isClickInvenItem = _equip->equipInstall(_inven->getClickItem(), _inven->getClickItemParent());
	}

	//�κ��丮���� �������� Ŭ���� ���¿��� ����ǰ� �κ��丮 �ܸ̿� Ŭ���ߴٸ� ������ ������
	else if (_isClickInvenItem &&( (!_isInvenOpen ||  !PtInRect(&_invenRC, _ptMouse) )|| (!_isEquipOpen || !PtInRect(&_equipRC, _ptMouse)) ))
	{
		//������
		_isClickInvenItem = _inven->inventoryItemDrop();
	}

	//�κ����� Ŭ������ ���� ���¿��� ������������ Ŭ���������
	else if (!_isClickInvenItem && _isEquipOpen && PtInRect(&_equipRC, _ptMouse))
	{
		_isClickEquip = _equip->equipUnInstall(_isClickEquip);
	}

	//���â ���� Ŭ���ѻ��¿��� �κ� Ŭ���ϸ� �κ��丮�� �ٽ� ���ƿ´�.
	//equip = treu, invenitem = false, open �Ѵ� true
	else if (_isClickEquip && _isInvenOpen && PtInRect(&_invenRC, _ptMouse))
	{
		_isClickEquip = _inven->inventoryClick(_equip->getClickItem());
	}
	
	//���â �����ְ� �������� Ŭ������ ���� ���¿��� ���â ���ý� 
	else if (_isMagicOpen && !_isClickInvenItem && !_isClickEquip && PtInRect(&_magicRC, _ptMouse))
	{
		_magic->clickMagicUI(true);
	}
	//�� ���� Ŭ��ó���� �̵��̶� �Ǵ�(���� ���� �߰��� ����)
	else 
	{
		//���� Ŭ��
		//MM�� ���� ����ִٸ� ������̴�. 
		if (_MM != NULL)
		{
			//���� Ŭ���ϸ� Ÿ�� ���Ͱ� �Ϸ� ����.
			_targetMonster = _MM->findClickMonster();
			//�̰����� ����
			//1. Ÿ�ٰ��� ��ġ �Ǵ��Ͽ� �� ��ġ�� ���� ��ĭ���̱��� �̵�(A* �����Ű��)
			/*while (1)
			{
			
			}*/
			

					//POINT tempPoint =
				//		_aStar->getNextTile(_tileIndexX, _tileIndexY, _targetMonster->getTileIndexX(), _targetMonster->getTileIndexY());
					//sprintf(_aStarTest, "aaa", tempPoint.x, tempPoint.y);
				
			
				//Ÿ�ٸ����� ��ǥ�� �ӽ÷� �����ϰ�
				//int tempX = _targetMonster->getTileIndexX();
				//int tempY = _targetMonster->getTileIndexY();

				////Ÿ�� ���� ���� �� ���� ��ǥ���� �����߿� �÷��̾ �ִٸ� �÷��̾�� ���������� �̵��ؾ��Ѵ�.
				//while (tempX != ISOTILEX - 1 && tempY !=0 && _characterAction==CHA_IDLE)
				//{
				//	tempX++;
				//	tempY--;
				//	if (tempX == _tileIndexX && tempY == _tileIndexY)
				//	{
				//		//ĳ���� �ൿ�� ���������� �ɾ
				//		_characterAction = CHA_RIGHT;
				//		//ĳ���� �������� Ÿ�� ������ �ٷ� ����ĭ
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
				////Ÿ�� ���� ���� �� ������ ��ǥ���� �����߿� �÷��̾ �ִٸ� �÷��̾�� �������� �̵��ؾ��Ѵ�.
				//while (tempX != 0 && tempY != ISOTILEY - 1 && _characterAction == CHA_IDLE)
				//{
				//	tempX--;
				//	tempY++;
				//	if (tempX == _tileIndexX && tempY == _tileIndexY)
				//	{
				//		//ĳ���� �ൿ�� �������� �ɾ
				//		_characterAction = CHA_LEFT;
				//		//ĳ���� �������� Ÿ�� ������ �ٷ� ������ĭ
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
				////Ÿ�� ���� ���� �� �� ��ǥ���� �����߿� �÷��̾ �ִٸ� �÷��̾�� �Ʒ����� �̵��ؾ��Ѵ�.
				//while (tempX != 0 && tempY != 0 && _characterAction == CHA_IDLE)
				//{
				//	tempX--;
				//	tempY--;
				//	if (tempX == _tileIndexX && tempY == _tileIndexY)
				//	{
				//		//ĳ���� �ൿ�� �Ʒ��η� �ɾ
				//		_characterAction = CHA_DOWN;
				//		//ĳ���� �������� Ÿ�� ������ �ٷ� ��ĭ
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
				////Ÿ�� ���� ���� �� �Ʒ� ��ǥ���� �����߿� �÷��̾ �ִٸ� �÷��̾�� ���� �̵��ؾ��Ѵ�.
				//while (tempX != ISOTILEY - 1 && tempY != ISOTILEY - 1 && _characterAction == CHA_IDLE)
				//{
				//	tempX++;
				//	tempY++;
				//	if (tempX == _tileIndexX && tempY == _tileIndexY)
				//	{
				//		//ĳ���� �ൿ�� ���� �ɾ
				//		_characterAction = CHA_UP;
				//		//ĳ���� �������� Ÿ�� ������ �ٷ� ��ĭ
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
				//�� 
				//for (;tempX == _targetMonster->getTileIndexX() && _targetMonster->getTileIndexY(); )
				//{
				//	//�� ��������
				//	if ()
				//	tempX--; tempY++;
				//}
			
			//2. ��������
			//2-1. ���� ������ �� ��ų �� �̰�����

		}

		//Ÿ�ٵ� ���Ͱ� ���ٸ� �ܼ� Ÿ�� �̵��̹Ƿ�
		if (_targetMonster == NULL)
		{
			//Ÿ�� ���� �� �̵�
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
					//���콺 Ŭ���� �����̵� �ڵ�
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
						//�ڿ����� �̵� �ڵ�
						/*_angle =
							getAngle(_currentPlaceTile[_tileIndexX * ISOTILEX + _tileIndexY].getCenterPoint().x,
							_currentPlaceTile[_tileIndexX * ISOTILEX + _tileIndexY].getCenterPoint().y,
							_currentPlaceTile[i].getCenterPoint().x,
							_currentPlaceTile[i].getCenterPoint().y);*/

						_destTileIndexX = i / ISOTILEX;
						_destTileIndexY = i % ISOTILEX;


						//���� �����κ� �ٵ� ���ڿ�������
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
	//�ڿ������� �׸���(1)
	//IMAGEMANAGER->frameRender("����idle", getMemDC(),
	//	CAMERAMANAGER->CameraRelativePointX(_x),
	//	CAMERAMANAGER->CameraRelativePointY(_y),
	//	_frameX, 0);

	//�ڿ������� �׸���(2)
	_playImage->aniRender(getMemDC(),
		CAMERAMANAGER->CameraRelativePointX(_characterRC.left),
		CAMERAMANAGER->CameraRelativePointY(_characterRC.top), _animation);
	//IMAGEMANAGER->frameRender("���̱⺻", getMemDC(),
	//	CAMERAMANAGER->CameraRelativePointX(_characterRC.left),
	//	CAMERAMANAGER->CameraRelativePointY(_characterRC.top),
	//	_frameX, 0);


	//�����̵� �׸���
	/*IMAGEMANAGER->frameRender("����idle", getMemDC(), 
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
		IMAGEMANAGER->findImage("����Ÿ��")->render(getMemDC(),
			_targetMonster->getMonsterRC().left,
			_targetMonster->getMonsterRC().top - IMAGEMANAGER->findImage("����Ÿ��")->getHeight());

		_targetMonster->HPDraw();
	}



	char whatproblem[111];
	sprintf(whatproblem, "%d, %d", _characterAction, _attackDelay);

	EFFECTMANAGER->render();
	//TextOut(getMemDC(), 0, 100, whatproblem, strlen(whatproblem));
	//TextOut(getMemDC(), 100 * (i+1), 10, _test, strlen(_test));
}

void character::addImage()		//�̹̱� �߰����ִ� �Լ� ���� �̹����� ���⼭ add�ϴ°ɷ�
{
	IMAGEMANAGER->addFrameImage("���ĺ�", "./image/characterselect/alphabet.bmp", 208, 10, 26, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("���̻�������", "./image/characterselect/���̻�������.bmp", 179, 355, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���̻����̼���", "./image/characterselect/���̻����̼���.bmp", 179, 355, true, RGB(255, 0, 255));

	/*
	CHA_IDLE, CHA_RIGHT, CHA_RIGHTDOWN, CHA_DOWN,
	CHA_LEFTDOWN, CHA_LEFT, CHA_LEFTUP, CHA_UP, CHA_RIGHTUP,
	*/
	//�ȱ�
	_playImage = IMAGEMANAGER->addFrameImage("����idle", "./image/character/����/����idle.bmp", 156, 57, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���̿�����", "./image/character/����/����right.bmp", 210, 54, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���̿����ʾƷ�", "./image/character/����/����rightdown.bmp", 220, 53, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���̾Ʒ�", "./image/character/����/����down.bmp", 270, 52, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���̿��ʾƷ�", "./image/character/����/����leftdown.bmp", 220, 53, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���̿���", "./image/character/����/����left.bmp", 210, 54, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���̿�����", "./image/character/����/����leftup.bmp", 282, 61, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������", "./image/character/����/����up.bmp", 225, 61, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���̿�������", "./image/character/����/����rightup.bmp", 282, 61, 6, 1, true, RGB(255, 0, 255));
	
	//����
	//IMAGEMANAGER->addFrameImage("����", "./image/character/����/����idle.bmp", 156, 57, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���̿����ʰ���", "./image/character/����/����rightattack.bmp", 305, 55, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���̿����ʾƷ�����", "./image/character/����/����rightdownattack.bmp", 250, 58, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���̾Ʒ�����", "./image/character/����/����downattack.bmp", 185, 60, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���̿��ʾƷ�����", "./image/character/����/����leftdownattack.bmp", 250, 58, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���̿��ʰ���", "./image/character/����/����leftattack.bmp", 305, 55, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���̿���������", "./image/character/����/����leftupattack.bmp", 260, 54, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����������", "./image/character/����/����upattack.bmp", 205, 58, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���̿�����������", "./image/character/����/����rightupattack.bmp", 260, 54, 5, 1, true, RGB(255, 0, 255));

	//����
	IMAGEMANAGER->addFrameImage("��������", "./image/character/����/����death.bmp", 300, 59, 5, 1, true, RGB(255, 0, 255));



	IMAGEMANAGER->addImage("���̻�������", "./image/characterselect/���̻�������.bmp", 174, 351, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���̻����̼���", "./image/characterselect/���̻����̼���.bmp", 179, 355, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("���̻�������", "./image/characterselect/���̻�������.bmp", 173, 351, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���̻����̼���", "./image/characterselect/���̻����̼���.bmp", 179, 354, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("����Ÿ��", "./image/monster/Ÿ��.bmp", 54, 56, true, RGB(255, 0, 255));

	//IMAGEMANAGER->addFrameImage("����", "./image/magic/magicUI/��ų����Ʈ.bmp", 300, 121, 5, 1, true, RGB(255, 0, 255));
	EFFECTMANAGER->addEffect("����", "./image/magic/magicUI/��ų����Ʈ.bmp", 300, 121, 60, 121, 1.0f, 0.1f, 10);
}

void character::initialization()	//������ new���� �� init ���ִ� �Լ� ���� new �� init�� ���⼭ �ϴ°ɷ�
{

}

void character::singletonInit()	//init���� �̱���� �������ִ� �Լ� ���� ������ ���⼭ �ϴ°ɷ�
{

}

//����Ʈ������ �׷��ֱ� ���� �����Լ�
void character::selectRender(int i, bool isSelect)
{
	//���� �Ǿ�����
	if (isSelect)
	{
		strcpy(_characterImageName, _characterName);
		strcat(_characterImageName, "��������");
		_selectImage = IMAGEMANAGER->findImage(_characterImageName);
	}
	else
	{
		strcpy(_characterImageName, _characterName);
		strcat(_characterImageName, "�����̼���");
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
			IMAGEMANAGER->findImage("���ĺ�")->frameRender(getMemDC(), 185 + 8* i, 60, (int)_test[i] - 97, 0);
		}
		//_selectImage->render(getMemDC(), 118, 54);
		break;
	case 1:
		for (int i = 0; i < strlen(_test); ++i)
		{
			IMAGEMANAGER->findImage("���ĺ�")->frameRender(getMemDC(), 378 + 8 * i, 60, (int)_test[i] - 97, 0);
		}
		//_selectImage->render(getMemDC(), 311, 54);
		break;
	case 2:
		for (int i = 0; i < strlen(_test); ++i)
		{
			IMAGEMANAGER->findImage("���ĺ�")->frameRender(getMemDC(), 571 + 8 * i, 60, (int)_test[i] - 97, 0);
		}
		//_selectImage->render(getMemDC(), 504, 54);
		break;
	default:
		break;
	}
}

void character::makeRC(){

	//�����̵� ī�޶�
	/*_characterRC = RectMake(_currentPlaceTile[_tileIndexX * ISOTILEX + _tileIndexY].x - ISOTILESIZEX / 4,
		_currentPlaceTile[_tileIndexX * ISOTILEX + _tileIndexY].y,
		_playImage->getFrameWidth(),
		_playImage->getFrameHeight());*/

	//�ڿ������� ī�޶�
	_characterRC = RectMakeCenter(_x,	_y,
		_playImage->getFrameWidth(),
		_playImage->getFrameHeight());
}