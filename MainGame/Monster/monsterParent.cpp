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
		//플레이어 공격
		_playPlayer->attacked(_damage);
		_attackDelay = 0;
	}

}
void monsterParent::mosterActionDecide()
{
	POINT tempPoint = { -1, -1 };
	//탐지된 플레이어가 있다.
	if (_playPlayer != NULL)
	{
		_aStar->setTiles(_tileIndexX, _tileIndexY, _playPlayer->getTileIndexX(), _playPlayer->getTileIndexY(), _HuntingPlaceTile);
		tempPoint = _aStar->getNextTile();
		
		//플레이어와 한칸차이이므로 움직일 필요 없이 바로 공격하면 된다.
		if (tempPoint.x == -1 && tempPoint.y == -1)
		{
			if (_playPlayer->getTileIndexX() == _tileIndexX && _playPlayer->getTileIndexY() > _tileIndexY)
			{
				_monsterState = MON_RIGHTDOWN_ATTACK;
			}
			//x축은 같고 y축이 갈 곳이 더 작으면 왼쪽 위로 가야한다.
			else if (_playPlayer->getTileIndexX() == _tileIndexX && _playPlayer->getTileIndexY() < _tileIndexY)
			{
				_monsterState = MON_LEFTUP_ATTACK;
			}
			//y축은 같고 x축이 갈 곳이 더 크면 왼쪽 아래로 가야한다.
			else if (_playPlayer->getTileIndexX() > _tileIndexX && _playPlayer->getTileIndexY() == _tileIndexY)
			{
				_monsterState = MON_LEFTDOWN_ATTACK;
			}
			//y축은 같고 x축이 갈 곳이 더 크면 오른쪽 위로 가야한다.
			else if (_playPlayer->getTileIndexX() < _tileIndexX && _playPlayer->getTileIndexY() == _tileIndexY)
			{
				_monsterState = MON_RIGHTUP_ATTACK;
			}
			//갈곳이 나랑 같은줄이면서 내가 왼쪽에 있으면 오른쪽으로 가야한다.
			else if (_playPlayer->getTileIndexX() < _tileIndexX && _playPlayer->getTileIndexY() > _tileIndexY)
			{
				_monsterState = MON_RIGHT_ATTACK;
			}
			//갈곳이 나랑 같은줄이면서 내가 오른쪽에 있으면 왼쪽으로 가야한다.
			else if (_playPlayer->getTileIndexX() > _tileIndexX && _playPlayer->getTileIndexY() < _tileIndexY)
			{
				_monsterState = MON_LEFT_ATTACK;
			}
			//갈곳이 나랑 같은줄이면서 내가 위쪽에 있으면 아래쪽으로 가야한다.
			else if (_playPlayer->getTileIndexX() > _tileIndexX && _playPlayer->getTileIndexY() > _tileIndexY)
			{
				_monsterState = MON_DOWN_ATTACK;
			}
			//갈곳이 나랑 같은줄이면서 내가 아래쪽에 있으면 위로 가야한다.
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

		//한칸 차이가 아니라서 이동해야한다.

		if (tempPoint.x == _tileIndexX && tempPoint.y > _tileIndexY)
		{
			_monsterState = MON_RIGHTDOWN;
		}
		//x축은 같고 y축이 갈 곳이 더 작으면 왼쪽 위로 가야한다.
		else if (tempPoint.x == _tileIndexX && tempPoint.y < _tileIndexY)
		{
			_monsterState = MON_LEFTUP;
		}
		//y축은 같고 x축이 갈 곳이 더 크면 왼쪽 아래로 가야한다.
		else if (tempPoint.x > _tileIndexX && tempPoint.y == _tileIndexY)
		{
			_monsterState = MON_LEFTDOWN;
		}
		//y축은 같고 x축이 갈 곳이 더 크면 오른쪽 위로 가야한다.
		else if (tempPoint.x < _tileIndexX && tempPoint.y > _tileIndexY)
		{
			_monsterState = MON_RIGHTUP;
		}
		//갈곳이 나랑 같은줄이면서 내가 왼쪽에 있으면 오른쪽으로 가야한다.
		else if (tempPoint.x < _tileIndexX && tempPoint.y > _tileIndexY)
		{
			_monsterState = MON_RIGHT;
		}
		//갈곳이 나랑 같은줄이면서 내가 오른쪽에 있으면 왼쪽으로 가야한다.
		else if (tempPoint.x > _tileIndexX && tempPoint.y < _tileIndexY)
		{
			_monsterState = MON_LEFT;
		}
		//갈곳이 나랑 같은줄이면서 내가 위쪽에 있으면 아래쪽으로 가야한다.
		else if (tempPoint.x > _tileIndexX && tempPoint.y > _tileIndexY)
		{
			_monsterState = MON_DOWN;
		}
		//갈곳이 나랑 같은줄이면서 내가 아래쪽에 있으면 위로 가야한다.
		else if (tempPoint.x < _tileIndexX && tempPoint.y < _tileIndexY)
		{
			_monsterState = MON_UP;
		}
		
		//}
	}
	//걸린 플레이어가 없으면 단순 이동
	else
	{

		//
		if (_monsterState == MON_IDLE)
		{
			//움직여라
			if (_count >= _moveCount)
			{
				//움직임에 관련된 변수 다시 설정하고
				_count = 0;
				_moveCount = RND->getFromIntTo(100, 300);

				//내가 움직일 타일은 내가 밟고 있는 타일에서 각각 -2~2만큼 타일중 하나이다.
				_destTileIndexX = _tileIndexX + RND->getFromIntTo(-2, 2);
				_destTileIndexY = _tileIndexY + RND->getFromIntTo(-2, 2);

				//예외처리
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

		//나의 현재타일이 목적지 타일이 아니라면
		//if (_destTileIndexX != _tileIndexX || _destTileIndexY != _tileIndexY)
		//{
			
			//A스타 돌려라
			_aStar->setTiles(_tileIndexX, _tileIndexY, _destTileIndexX, _destTileIndexY, _HuntingPlaceTile);
			tempPoint = _aStar->getNextTile();

			sprintf(plz, "x인덱스 %d, y인덱스 %d, 목 x인덱스 %d, 목 y인덱스 %d, temp x인덱스 %d, temp y인덱스 %d",
				_tileIndexX, _tileIndexY, _destTileIndexX, _destTileIndexY, tempPoint.x, tempPoint.y);
			//목적지 전 타일 도착했다는 의미같은데
			if (tempPoint.x == -1 && tempPoint.y == -1)
			{
				tempPoint = PointMake(_destTileIndexX, _destTileIndexY);
					//
			}
			if (KEYMANAGER->isToggleKey('M'))
			{
				sprintf(plz, "x인덱스 %d, y인덱스 %d, 목 x인덱스 %d, 목 y인덱스 %d, temp x인덱스 %d, temp y인덱스 %d",
					_tileIndexX, _tileIndexY, _destTileIndexX, _destTileIndexY, tempPoint.x, tempPoint.y);
			}
			if (tempPoint.x == _tileIndexX && tempPoint.y > _tileIndexY)
			{
				_monsterState = MON_RIGHTDOWN;
			}
			//x축은 같고 y축이 갈 곳이 더 작으면 왼쪽 위로 가야한다.
			else if (tempPoint.x == _tileIndexX && tempPoint.y < _tileIndexY)
			{
				_monsterState = MON_LEFTUP;
			}
			//y축은 같고 x축이 갈 곳이 더 크면 왼쪽 아래로 가야한다.
			else if (tempPoint.x > _tileIndexX && tempPoint.y == _tileIndexY)
			{
				_monsterState = MON_LEFTDOWN;
			}
			//y축은 같고 x축이 갈 곳이 더 크면 오른쪽 위로 가야한다.
			else if (tempPoint.x < _tileIndexX && tempPoint.y == _tileIndexY)
			{
				_monsterState = MON_RIGHTUP;
			}
			//갈곳이 나랑 같은줄이면서 내가 왼쪽에 있으면 오른쪽으로 가야한다.
			else if (tempPoint.x < _tileIndexX && tempPoint.y > _tileIndexY)
			{
				_monsterState = MON_RIGHT;
			}
			//갈곳이 나랑 같은줄이면서 내가 오른쪽에 있으면 왼쪽으로 가야한다.
			else if (tempPoint.x > _tileIndexX && tempPoint.y < _tileIndexY)
			{
				_monsterState = MON_LEFT;
			}
			//갈곳이 나랑 같은줄이면서 내가 위쪽에 있으면 아래쪽으로 가야한다.
			else if (tempPoint.x > _tileIndexX && tempPoint.y > _tileIndexY)
			{
				_monsterState = MON_DOWN;
			}
			//갈곳이 나랑 같은줄이면서 내가 아래쪽에 있으면 위로 가야한다.
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
			&& _y < _currentPlaceTile[_destTileIndexX * ISOTILEX + _destTileIndexY].getCent>	HexaWindowsAPI.exe!monsterParent::mosterActionDecide() 줄 272	C++
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
	IMAGEMANAGER->addImage("몹피뒤", "./image/UI/몹피뒤.bmp", 50, 9, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("몹피앞", "./image/UI/몹피앞.bmp", 50, 9, true, RGB(255, 0, 255));

	IMAGEMANAGER->render("몹피뒤", getMemDC(), CAMERAMANAGER->CameraRelativePointX(_x)-20, CAMERAMANAGER->CameraRelativePointY(_y) - 30);
	//IMAGEMANAGER->render("피바", getMemDC(), 44, 35, 0, 0, 211 * (float(*_currentHP) / (*_maxHP)), 9);
	IMAGEMANAGER->render("몹피앞", getMemDC(), CAMERAMANAGER->CameraRelativePointX(_x)-20, CAMERAMANAGER->CameraRelativePointY(_y) - 30,
		0, 0, 50 * (float(_currentHP) / (_maxHP)), 9);
}