#include "stdafx.h"
#include "monsterParent.h"
#include "character.h"

monsterParent::monsterParent()
{
}


monsterParent::~monsterParent()
{

}

HRESULT monsterParent::init()
{

	return S_OK;
}
HRESULT monsterParent::init(int respond)
{

	return S_OK;
}

void monsterParent::release()
{

}
void monsterParent::update()
{

}
void monsterParent::deadUpdate()
{

}
void monsterParent::render()
{
	if (!_isDead)
	{
		_monsterImage->aniRender(getMemDC(), CAMERAMANAGER->CameraRelativePointX(_renderX), CAMERAMANAGER->CameraRelativePointY(_renderY), _animation);
		drawIdleEffect();
		//_monsterImage->frameRender(getMemDC(), CAMERAMANAGER->CameraRelativePointX(_renderX), CAMERAMANAGER->CameraRelativePointY(_renderY), 0, 0);
		//TextOut(getMemDC(), 0, 300, plz, strlen(plz));
	}
}

int monsterParent::rndLevel(int level)
{
	return RND->getFromIntTo(level - 1, level + 1);
}
//int monsterParent::rndExp()
//{
//	//27200
//	return RND->getFromIntTo(_monsterLevel )
//}
//int monsterParent::rndMoney()
//{
//
//}
int monsterParent::rndHP()
{

	return 0;
}
int monsterParent::rndDamage()
{

	return 0;
}
int monsterParent::rndDef()
{

	return 0;
}
void monsterParent::playerAttack()
{
	if (_isDead) return;

	if (_attackDelay >= 250)
	{
		//�÷��̾� ����
		_playPlayer->attacked(_damage);
		_attackDelay = 0;
	}

}
void monsterParent::mosterActionDecide()
{
	POINT tempPoint = { -1, -1 };
	//Ž���� �÷��̾ �ִ�.
	if (_playPlayer != NULL)
	{
		_aStar->setTiles(_tileIndexX, _tileIndexY, _playPlayer->getTileIndexX(), _playPlayer->getTileIndexY(), _HuntingPlaceTile);
		tempPoint = _aStar->getNextTile();
		
		//�÷��̾�� ��ĭ�����̹Ƿ� ������ �ʿ� ���� �ٷ� �����ϸ� �ȴ�.
		if (tempPoint.x == -1 && tempPoint.y == -1)
		{
			if (_playPlayer->getTileIndexX() == _tileIndexX && _playPlayer->getTileIndexY() > _tileIndexY)
			{
				_monsterState = MON_RIGHTDOWN_ATTACK;
			}
			//x���� ���� y���� �� ���� �� ������ ���� ���� �����Ѵ�.
			else if (_playPlayer->getTileIndexX() == _tileIndexX && _playPlayer->getTileIndexY() < _tileIndexY)
			{
				_monsterState = MON_LEFTUP_ATTACK;
			}
			//y���� ���� x���� �� ���� �� ũ�� ���� �Ʒ��� �����Ѵ�.
			else if (_playPlayer->getTileIndexX() > _tileIndexX && _playPlayer->getTileIndexY() == _tileIndexY)
			{
				_monsterState = MON_LEFTDOWN_ATTACK;
			}
			//y���� ���� x���� �� ���� �� ũ�� ������ ���� �����Ѵ�.
			else if (_playPlayer->getTileIndexX() < _tileIndexX && _playPlayer->getTileIndexY() == _tileIndexY)
			{
				_monsterState = MON_RIGHTUP_ATTACK;
			}
			//������ ���� �������̸鼭 ���� ���ʿ� ������ ���������� �����Ѵ�.
			else if (_playPlayer->getTileIndexX() < _tileIndexX && _playPlayer->getTileIndexY() > _tileIndexY)
			{
				_monsterState = MON_RIGHT_ATTACK;
			}
			//������ ���� �������̸鼭 ���� �����ʿ� ������ �������� �����Ѵ�.
			else if (_playPlayer->getTileIndexX() > _tileIndexX && _playPlayer->getTileIndexY() < _tileIndexY)
			{
				_monsterState = MON_LEFT_ATTACK;
			}
			//������ ���� �������̸鼭 ���� ���ʿ� ������ �Ʒ������� �����Ѵ�.
			else if (_playPlayer->getTileIndexX() > _tileIndexX && _playPlayer->getTileIndexY() > _tileIndexY)
			{
				_monsterState = MON_DOWN_ATTACK;
			}
			//������ ���� �������̸鼭 ���� �Ʒ��ʿ� ������ ���� �����Ѵ�.
			else if (_playPlayer->getTileIndexX() < _tileIndexX && _playPlayer->getTileIndexY() < _tileIndexY)
			{
				_monsterState = MON_UP_ATTACK;
			}

			//switch (_monsterState)
			//{
			//case MON_IDLE:
			//	break;
			//case MON_RIGHT:
			//	_monsterState = MON_RIGHT_ATTACK;
			//	break;
			//case MON_RIGHTDOWN:
			//	_monsterState = MON_RIGHTDOWN_ATTACK;
			//	break;
			//case MON_DOWN:
			//	_monsterState = MON_DOWN_ATTACK;
			//	break;
			//case MON_LEFTDOWN:
			//	_monsterState = MON_LEFTDOWN_ATTACK;
			//	break;
			//case MON_LEFT:
			//	_monsterState = MON_LEFT_ATTACK;
			//	break;
			//case MON_LEFTUP:
			//	_monsterState = MON_LEFTUP_ATTACK;
			//	break;
			//case MON_UP:
			//	_monsterState = MON_UP_ATTACK;
			//	break;
			//case MON_RIGHTUP:
			//	_monsterState = MON_RIGHTUP_ATTACK;
			//	break;
			//default:
			//	break;
			//}
			return;
		}

		//��ĭ ���̰� �ƴ϶� �̵��ؾ��Ѵ�.

		if (tempPoint.x == _tileIndexX && tempPoint.y > _tileIndexY)
		{
			_monsterState = MON_RIGHTDOWN;
		}
		//x���� ���� y���� �� ���� �� ������ ���� ���� �����Ѵ�.
		else if (tempPoint.x == _tileIndexX && tempPoint.y < _tileIndexY)
		{
			_monsterState = MON_LEFTUP;
		}
		//y���� ���� x���� �� ���� �� ũ�� ���� �Ʒ��� �����Ѵ�.
		else if (tempPoint.x > _tileIndexX && tempPoint.y == _tileIndexY)
		{
			_monsterState = MON_LEFTDOWN;
		}
		//y���� ���� x���� �� ���� �� ũ�� ������ ���� �����Ѵ�.
		else if (tempPoint.x < _tileIndexX && tempPoint.y > _tileIndexY)
		{
			_monsterState = MON_RIGHTUP;
		}
		//������ ���� �������̸鼭 ���� ���ʿ� ������ ���������� �����Ѵ�.
		else if (tempPoint.x < _tileIndexX && tempPoint.y > _tileIndexY)
		{
			_monsterState = MON_RIGHT;
		}
		//������ ���� �������̸鼭 ���� �����ʿ� ������ �������� �����Ѵ�.
		else if (tempPoint.x > _tileIndexX && tempPoint.y < _tileIndexY)
		{
			_monsterState = MON_LEFT;
		}
		//������ ���� �������̸鼭 ���� ���ʿ� ������ �Ʒ������� �����Ѵ�.
		else if (tempPoint.x > _tileIndexX && tempPoint.y > _tileIndexY)
		{
			_monsterState = MON_DOWN;
		}
		//������ ���� �������̸鼭 ���� �Ʒ��ʿ� ������ ���� �����Ѵ�.
		else if (tempPoint.x < _tileIndexX && tempPoint.y < _tileIndexY)
		{
			_monsterState = MON_UP;
		}
		
		//}
	}
	//�ɸ� �÷��̾ ������ �ܼ� �̵�
	else
	{

		//
		if (_monsterState == MON_IDLE)
		{
			//��������
			if (_count >= _moveCount)
			{
				//�����ӿ� ���õ� ���� �ٽ� �����ϰ�
				_count = 0;
				_moveCount = RND->getFromIntTo(100, 300);

				//���� ������ Ÿ���� ���� ��� �ִ� Ÿ�Ͽ��� ���� -2~2��ŭ Ÿ���� �ϳ��̴�.
				_destTileIndexX = _tileIndexX + RND->getFromIntTo(-2, 2);
				_destTileIndexY = _tileIndexY + RND->getFromIntTo(-2, 2);

				//����ó��
				if (_destTileIndexX < 0) _destTileIndexX = 0;
				if (_destTileIndexX > ISOTILEX - 1) _destTileIndexX = ISOTILEX - 1;
				if (_destTileIndexY < 0) _destTileIndexY = 0;
				if (_destTileIndexY > ISOTILEY - 1) _destTileIndexY = ISOTILEY - 1;
			}
			//if (_tileIndexX == _destTileIndexX && _tileIndexY == _destTileIndexY)
			//{
			//	//_monsterState = MON_IDLE;
			//	return;
			//}
		}

		if (_tileIndexX == _destTileIndexX && _tileIndexY == _destTileIndexY)
		{
			_monsterState = MON_IDLE;
			return;
		}

		//���� ����Ÿ���� ������ Ÿ���� �ƴ϶��
		//if (_destTileIndexX != _tileIndexX || _destTileIndexY != _tileIndexY)
		//{
			
			//A��Ÿ ������
			_aStar->setTiles(_tileIndexX, _tileIndexY, _destTileIndexX, _destTileIndexY, _HuntingPlaceTile);
			tempPoint = _aStar->getNextTile();

			sprintf(plz, "x�ε��� %d, y�ε��� %d, �� x�ε��� %d, �� y�ε��� %d, temp x�ε��� %d, temp y�ε��� %d",
				_tileIndexX, _tileIndexY, _destTileIndexX, _destTileIndexY, tempPoint.x, tempPoint.y);
			//������ �� Ÿ�� �����ߴٴ� �ǹ̰�����
			if (tempPoint.x == -1 && tempPoint.y == -1)
			{
				tempPoint = PointMake(_destTileIndexX, _destTileIndexY);
					//
			}
			if (KEYMANAGER->isToggleKey('M'))
			{
				sprintf(plz, "x�ε��� %d, y�ε��� %d, �� x�ε��� %d, �� y�ε��� %d, temp x�ε��� %d, temp y�ε��� %d",
					_tileIndexX, _tileIndexY, _destTileIndexX, _destTileIndexY, tempPoint.x, tempPoint.y);
			}
			if (tempPoint.x == _tileIndexX && tempPoint.y > _tileIndexY)
			{
				_monsterState = MON_RIGHTDOWN;
			}
			//x���� ���� y���� �� ���� �� ������ ���� ���� �����Ѵ�.
			else if (tempPoint.x == _tileIndexX && tempPoint.y < _tileIndexY)
			{
				_monsterState = MON_LEFTUP;
			}
			//y���� ���� x���� �� ���� �� ũ�� ���� �Ʒ��� �����Ѵ�.
			else if (tempPoint.x > _tileIndexX && tempPoint.y == _tileIndexY)
			{
				_monsterState = MON_LEFTDOWN;
			}
			//y���� ���� x���� �� ���� �� ũ�� ������ ���� �����Ѵ�.
			else if (tempPoint.x < _tileIndexX && tempPoint.y == _tileIndexY)
			{
				_monsterState = MON_RIGHTUP;
			}
			//������ ���� �������̸鼭 ���� ���ʿ� ������ ���������� �����Ѵ�.
			else if (tempPoint.x < _tileIndexX && tempPoint.y > _tileIndexY)
			{
				_monsterState = MON_RIGHT;
			}
			//������ ���� �������̸鼭 ���� �����ʿ� ������ �������� �����Ѵ�.
			else if (tempPoint.x > _tileIndexX && tempPoint.y < _tileIndexY)
			{
				_monsterState = MON_LEFT;
			}
			//������ ���� �������̸鼭 ���� ���ʿ� ������ �Ʒ������� �����Ѵ�.
			else if (tempPoint.x > _tileIndexX && tempPoint.y > _tileIndexY)
			{
				_monsterState = MON_DOWN;
			}
			//������ ���� �������̸鼭 ���� �Ʒ��ʿ� ������ ���� �����Ѵ�.
			else if (tempPoint.x < _tileIndexX && tempPoint.y < _tileIndexY)
			{
				_monsterState = MON_UP;
			}
		//}
	}
	_angle = getAngle(_HuntingPlaceTile[_tileIndexX * ISOTILEX + _tileIndexY].getCenterPoint().x,
		_HuntingPlaceTile[_tileIndexX * ISOTILEX + _tileIndexY].getCenterPoint().y,
		_HuntingPlaceTile[tempPoint.x * ISOTILEX + tempPoint.y].getCenterPoint().x,
		_HuntingPlaceTile[tempPoint.x * ISOTILEX + tempPoint.y].getCenterPoint().y);
	move(tempPoint);
}
void monsterParent::move(POINT tempPoint)
{
	if (MON_IDLE < _monsterState && _monsterState < MON_RIGHT_ATTACK)
	{
		if (PtInRect(&RectMakeCenter(_HuntingPlaceTile[tempPoint.x * ISOTILEX + tempPoint.y].getCenterPoint().x,
			_HuntingPlaceTile[tempPoint.x * ISOTILEX + tempPoint.y].getCenterPoint().y,
			10, 10), 
			PointMake(_x, _y)))
			/*_currentPlaceTile[_destTileIndexX * ISOTILEX + _destTileIndexY].getCenterPoint().x - 1 < _x
			&& _x < _currentPlaceTile[_destTileIndexX * ISOTILEX + _destTileIndexY].getCenterPoint().x + 1
			&& _currentPlaceTile[_destTileIndexX * ISOTILEX + _destTileIndexY].getCenterPoint().y - 1 < _y
			&& _y < _currentPlaceTile[_destTileIndexX * ISOTILEX + _destTileIndexY].getCent>	HexaWindowsAPI.exe!monsterParent::mosterActionDecide() �� 272	C++
erPoint().y + 1)*/
		{
			//_monsterImage->getFrameWidth() / 2
			//_monsterImage->getFrameHeight() / 2
			//_monsterState = CHA_IDLE;
			_x = _HuntingPlaceTile[tempPoint.x * ISOTILEX + tempPoint.y].getCenterPoint().x ;
			_y = _HuntingPlaceTile[tempPoint.x * ISOTILEX + tempPoint.y].getCenterPoint().y ;

			_renderX = _x - _monsterImage->getFrameWidth() / 2;
			_renderY = _y - _monsterImage->getFrameHeight() / 2;

			//_tempX = _x; _tempY = _y;
			_tileIndexX = tempPoint.x;
			_tileIndexY = tempPoint.y;
		}
		else
		{
			_x += cos(_angle) * 1;
			_y += -sin(_angle) * 1;
			_renderX = _x - _monsterImage->getFrameWidth() / 2;
			_renderY = _y - _monsterImage->getFrameHeight() / 2;
		}
	}
}
void monsterParent::addImage()
{

}
void monsterParent::drawIdleEffect()
{

}
void monsterParent::animationChange()
{

}
void monsterParent::HPDraw()
{
	IMAGEMANAGER->addImage("���ǵ�", "./image/UI/���ǵ�.bmp", 50, 9, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���Ǿ�", "./image/UI/���Ǿ�.bmp", 50, 9, true, RGB(255, 0, 255));

	IMAGEMANAGER->render("���ǵ�", getMemDC(), CAMERAMANAGER->CameraRelativePointX(_x)-20, CAMERAMANAGER->CameraRelativePointY(_y) - 30);
	//IMAGEMANAGER->render("�ǹ�", getMemDC(), 44, 35, 0, 0, 211 * (float(*_currentHP) / (*_maxHP)), 9);
	IMAGEMANAGER->render("���Ǿ�", getMemDC(), CAMERAMANAGER->CameraRelativePointX(_x)-20, CAMERAMANAGER->CameraRelativePointY(_y) - 30,
		0, 0, 50 * (float(_currentHP) / (_maxHP)), 9);
}