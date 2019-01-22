#include "stdafx.h"
#include "aStar.h"


aStar::aStar()
{
}


aStar::~aStar()
{
}
HRESULT aStar::init(tagTile* currentGameTile)
{
	
	//_startTile = new aStarTile;
	//_endTile = new aStarTile;
	////타일 셋팅 해준다
	//setTiles(currentGameTile);

	//일단 메모리공간 할당해준다.
	

	_count = _start = 0;

	return S_OK;
}
HRESULT aStar::init()
{
	//for (int i = 0; i < _vTotalList.size(); ++i)
	//{
	//	SAFE_DELETE(_vTotalList[i]);
	//	//if (_vOpenList.size() > i)
	//	//{
	//	//	SAFE_DELETE(_vOpenList[i]);
	//	//}
	//	//if (_vCloseList.size() > i)
	//	//{
	//	//	SAFE_DELETE(_vCloseList[i]);
	//	//}
	//}
	//_vTotalList.clear();
	//_vOpenList.clear();
	//_vCloseList.clear();
	//
	//for (int i = 0; i < ISOTILEX; ++i)
	//{
	//	for (int j = 0; j < ISOTILEY; ++j)
	//	{			
	//		aStarTile* node = new aStarTile;
	//		node->init(i, j, _currentGameTile[i * ISOTILEX + j].getCenterPoint());
	//		if (_currentGameTile[i * ISOTILEX + j].terrain == TR_WATER ||
	//			!(_currentGameTile[i * ISOTILEX + j].obj == OBJ_NONE
	//			|| _currentGameTile[i * ISOTILEX + j].obj == OBJ_POTAL || _currentGameTile[i * ISOTILEX + j].obj == OBJ_POTAL_DUMMY
	//			|| _currentGameTile[i * ISOTILEX + j].obj == OBJ_RESPOND))
	//		{
	//			node->setIsOpen(false);
	//			node->setAttribute("wall");
	//		}
	//		_vTotalList[i*ISOTILEX + j] = node;
	//	}
	//}

	return S_OK;
}

// 타일 셋팅 함수
void aStar::setTiles(int playerX, int playerY, int enemyX, int enemyY, tagTile* currentGameTile)
{
	_vTotalList.clear();
	_vOpenList.clear();
	_vCloseList.clear();

	//시작타일
	_startTile = new aStarTile;
	_startTile->init(playerX, playerY, currentGameTile[playerX * 20 + playerY].getCenterPoint());
	_startTile->setAttribute("start");

	//끝 타일
	_endTile = new aStarTile;
	_endTile->init(enemyX, enemyY, currentGameTile[enemyX * 20 + enemyY].getCenterPoint());
	_endTile->setAttribute("end");

	//현재 타일은 처음에 시작타일로!
	_currentTile = _startTile;

	for (int i = 0; i < ISOTILEX; ++i)
	{
		for (int j = 0; j < ISOTILEY; ++j)
		{
			//해당 타일 찾았으면
			if (i == _startTile->getIdX() && j == _startTile->getIdY())
			{

				//_startTile->setColor(RGB(0, 255, 255));
				_vTotalList.push_back(_startTile);
				continue;
			}
			if (i == _endTile->getIdX() && j == _endTile->getIdY())
			{
				//_endTile->setColor(RGB(10, 120, 55));
				_vTotalList.push_back(_endTile);
				continue;
			}
			if (currentGameTile[i * ISOTILEX + j].terrain == TR_WATER ||
				!(currentGameTile[i * ISOTILEX + j].obj == OBJ_NONE
				|| currentGameTile[i * ISOTILEX + j].obj == OBJ_POTAL
				|| currentGameTile[i * ISOTILEX + j].obj == OBJ_POTAL_DUMMY
				|| currentGameTile[i * ISOTILEX + j].obj == OBJ_RESPOND))
			//if (attribute[i * ISOTILEX + j] == ATTR_UNMOVE)
			{
				aStarTile* node = new aStarTile;
				node->init(i, j, currentGameTile[i * 20 + j].getCenterPoint());
				//node->setColor(RGB(230, 140, 200));
				node->setIsOpen(false);
				node->setAttribute("wall");
				_vTotalList.push_back(node);
				continue;
			}
			//그 외 나머지 타일도 토탈벡터에 담아준다
			aStarTile* node = new aStarTile;
			node->init(i, j, currentGameTile[i*20 + j].getCenterPoint());
			_vTotalList.push_back(node);
		}
	}
	//
	//_vTotalList.clear();
	//_currentGameTile = currentGameTile;
	//
	//////시작타일
	////_startTile = new aStarTile;
	////_startTile->init(3, 3, currentGameTile[3 * 20 + 3].getCenterPoint());
	////_startTile->setAttribute("start");
	//
	////////끝 타일
	//////_endTile = new aStarTile;
	////_endTile->init(5, 5, currentGameTile[5*20 + 5].getCenterPoint());
	////_endTile->setAttribute("end");
	//
	////////현재 타일은 처음에 시작타일로!
	////_currentTile = _startTile;
	//
	////for (int i = 0; i < ISOTILEY; ++i)
	////{
	////	for (int j = 0; j < ISOTILEX; ++j)
	////	{
	////		//해당 타일 찾았으면
	////		if (j == _startTile->getIdX() && i == _startTile->getIdY())
	////		{
	////			//_startTile->setColor(RGB(0, 255, 255));
	////			_vTotalList.push_back(_startTile);
	////			continue;
	////		}
	////		if (j == _endTile->getIdX() && i == _endTile->getIdY())
	////		{
	////			//_endTile->setColor(RGB(10, 120, 55));
	////			_vTotalList.push_back(_endTile);
	////			continue;
	////		}
	//for (int i = 0; i < ISOTILEX; ++i)
	//{
	//	for (int j = 0; j < ISOTILEY; ++j)
	//	{
	//		/*if (j == _startTile->getIdX() && i == _startTile->getIdY())
	//		{
	//			_vTotalList.push_back(_startTile);
	//			continue;
	//		}
	//		if (j == _endTile->getIdX() && i == _endTile->getIdY())
	//		{
	//			_vTotalList.push_back(_endTile);
	//			continue;
	//		}*/
	//		aStarTile* node = new aStarTile;
	//		node->init(i, j, _currentGameTile[i * ISOTILEX + j].getCenterPoint());
	//		if (_currentGameTile[i * ISOTILEX + j].terrain == TR_WATER ||
	//			!(_currentGameTile[i * ISOTILEX + j].obj == OBJ_NONE
	//			|| _currentGameTile[i * ISOTILEX + j].obj == OBJ_POTAL || _currentGameTile[i * ISOTILEX + j].obj == OBJ_POTAL_DUMMY
	//			|| _currentGameTile[i * ISOTILEX + j].obj == OBJ_RESPOND))
	//		{
	//			node->setIsOpen(false);
	//			node->setAttribute("wall");
	//		}
	//		_vTotalList.push_back(node);
	//	}
	//}
	////		//그 외 나머지 타일도 토탈벡터에 담아준다
	////		aStarTile* node = new aStarTile;
	////		node->init(j, i);
	////		_vTotalList.push_back(node);
	////	}
	////}

}


//갈 수 있는 길을 검색해서 추가하는 함수
vector<aStarTile*> aStar::addOpenList(aStarTile* currentTile)
{
	int startX = currentTile->getIdX() - 1;
	int startY = currentTile->getIdY() - 1;

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if ((startX * ISOTILEX) + startY + j + (i * ISOTILEX) < 0) continue;
			if ((startX * ISOTILEX) + startY + j + (i * ISOTILEX) >= ISOTILEX*ISOTILEY) continue;

			aStarTile* node = _vTotalList[(startX * ISOTILEX) + startY + j + (i * ISOTILEX)];

			//갈수 없는 타일 및 시작 타일 그리고 벽은 제외한다
			if (!node->getIsOpen()) continue;
			if (node->getAttribute() == "start") continue;
			if (node->getAttribute() == "wall") continue;

			//최상위 노드는 현재 타일로 해준다
			node->setParentNode(_currentTile);

			//임의의 불 값을 하나 둔다(체크 용)
			bool addObj = true;

			for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
			{
				//한 번 체크 된 애는 중복 검출 하지 않는다
				if (*_viOpenList == node)
				{
					addObj = false;
					break;
				}
			}

			//도착타일이 아니면 (도달할때까지 계속)
			//if (node->getAttribute() != "end") node->setColor(RGB(128, 64, 28));

			if (!addObj) continue;

			//오픈리스트에 담아준다
			_vOpenList.push_back(node);
		}
	}
	//그렇게 (갈수있는 길이 담긴) 오픈리스트를 반환한다
	return _vOpenList;
}


//길 찾기 함수
void aStar::pathFinder(aStarTile* currentTile)
{
	float tempTotalCost = 5000;
	aStarTile* tempTile;

	for (int i = 0; i < addOpenList(currentTile).size(); ++i)
	{
		_vOpenList[i]->setCostToGoal(
			(abs(_endTile->getIdX() - _vOpenList[i]->getIdX()) +
			abs(_endTile->getIdY() - _vOpenList[i]->getIdY())) * 10);


		POINT center1 = _vOpenList[i]->getParentNode()->getCenter();
		POINT center2 = _vOpenList[i]->getCenter();

		_vOpenList[i]->setCostFromStart((getDistance(center1.x, center1.y, center2.x, center2.y) > ISOTILESIZEX) ? 10 : 14);

		_vOpenList[i]->setTotalCost(_vOpenList[i]->getCostToGoal() + _vOpenList[i]->getCostFromStart());

		if (tempTotalCost > _vOpenList[i]->getTotalCost())
		{
			tempTotalCost = _vOpenList[i]->getTotalCost();
			tempTile = _vOpenList[i];
		}

		bool addObj = true;
		for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
		{
			if (*_viOpenList == tempTile)
			{
				addObj = false;
				break;
			}
		}

		_vOpenList[i]->setIsOpen(false);
		if (!addObj) continue;

		_vOpenList.push_back(tempTile);
	}

	if (tempTile->getAttribute() == "end")
	{
		while (_currentTile->getParentNode() != NULL)
		{

			_currentTile = _currentTile->getParentNode();
		}
		return;
	}
	_vCloseList.push_back(tempTile);
	//_vDibugList.push_back(tempTile);

	for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
	{
		if (*_viOpenList == tempTile)
		{
			_viOpenList = _vOpenList.erase(_viOpenList);
			break;
		}
	}
	_currentTile = tempTile;
	pathFinder(_currentTile);
	//float tempTotalCost = 5000;
	//aStarTile* tempTile;			//가장 빠른 길을 색출하기 위한 템프타일
	//
	////갈 수 있는 길만 담긴 벡터 안에서~
	//for (int i = 0; i < addOpenList(currentTile).size(); ++i)
	//{
	//	//H 값 뽑는다
	//	//각 타일 이동에 대한 경로비용(타일과 거리)를 뽑아준다
	//
	//	//오픈 리스트의 x, y
	//	POINT tempOpenListIndex = { _vOpenList[i]->getIdX(), _vOpenList[i]->getIdY() };
	//	//엔드 타일의 x, y
	//	POINT tempEndTile = { _endTile->getIdX(), _endTile->getIdY() };
	//	//타일 인덱스 차이
	//	int tempInt = abs(tempOpenListIndex.x - tempEndTile.x) + abs(tempOpenListIndex.y - tempEndTile.y);
	//	//목적지까지의 거리가 한타일이 아니면 (4방향 기준)
	//	if (tempInt <= 1) _vOpenList[i]->setCostToGoal(tempInt * 10);
	//	//2타일 갈 거리는 한타일 갈수 있다면 (8방향 이동 가능하므로 2타일거리를 1타일로 줄일수 있따.
	//	else if (tempInt == 2)
	//	{
	//		//대각선으로 한칸 거리가 아닌 직선으로 2칸 거리일경우 예외처리
	//		if (tempEndTile.x == tempOpenListIndex.x || tempEndTile.y == tempOpenListIndex.y)
	//			_vOpenList[i]->setCostToGoal(tempInt * 10);
	//		else
	//		_vOpenList[i]->setCostToGoal((tempInt - 1) * 10);
	//	}
	//	//거리가 3칸이면 한번이상은 대각선으로 갈수 있다.
	//	else
	//	{
	//		//도착 타일 기준으로 아래 타일이면
	//		if (tempOpenListIndex.x > tempEndTile.x && tempOpenListIndex.y > tempEndTile.y)
	//		{
	//			//거리가 3 이상이냐
	//			int count = 0;
	//				//거리가 3 이상이냐
	//				while (1)
	//				{
	//					tempOpenListIndex.x--;
	//					tempOpenListIndex.y--;
	//					count++;
	//					//대각선 이동중 같은 선상이 되었으면 멈춰라
	//					if (tempOpenListIndex.x == tempEndTile.x || tempOpenListIndex.y == tempEndTile.y)
	//						break;
	//				}
	//				tempInt = abs(tempOpenListIndex.x - tempEndTile.x) + abs(tempOpenListIndex.y - tempEndTile.y);
	//
	//				_vOpenList[i]->setCostToGoal((count + tempInt) * 10);
	//			
	//		}
	//		////도착 타일 기준으로 왼쪽 타일이면
	//		else if (tempOpenListIndex.x > tempEndTile.x && tempOpenListIndex.y < tempEndTile.y)
	//		{
	//			int count = 0;
	//			//거리가 3 이상이냐
	//			while (1)
	//			{
	//				tempOpenListIndex.x--;
	//				tempOpenListIndex.y++;
	//				count++;
	//				//대각선 이동중 같은 선상이 되었으면 멈춰라
	//				if (tempOpenListIndex.x == tempEndTile.x || tempOpenListIndex.y == tempEndTile.y)
	//					break;
	//			}
	//			tempInt = abs(tempOpenListIndex.x - tempEndTile.x) + abs(tempOpenListIndex.y - tempEndTile.y);
	//
	//			_vOpenList[i]->setCostToGoal((count + tempInt) * 10);
	//		}
	//		//도착 타일 기준으로 위쪽 타일이면
	//		else if (tempOpenListIndex.x < tempEndTile.x && tempOpenListIndex.y < tempEndTile.y)
	//		{
	//			int count = 0;
	//			//거리가 3 이상이냐
	//			while (1)
	//			{
	//				tempOpenListIndex.x++;
	//				tempOpenListIndex.y++;
	//				count++;
	//				//대각선 이동중 같은 선상이 되었으면 멈춰라
	//				if (tempOpenListIndex.x == tempEndTile.x || tempOpenListIndex.y == tempEndTile.y)
	//					break;
	//			}
	//			tempInt = abs(tempOpenListIndex.x - tempEndTile.x) + abs(tempOpenListIndex.y - tempEndTile.y);
	//
	//			_vOpenList[i]->setCostToGoal((count + tempInt) * 10);
	//		}
	//		//도착 타일 기준으로 오른쪽 타일이면
	//		else if (tempOpenListIndex.x < tempEndTile.x && tempOpenListIndex.y > tempEndTile.y)
	//		{
	//			int count = 0;
	//			//거리가 3 이상이냐
	//			while (1)
	//			{
	//				tempOpenListIndex.x++;
	//				tempOpenListIndex.y--;
	//				count++;
	//				//대각선 이동중 같은 선상이 되었으면 멈춰라
	//				if (tempOpenListIndex.x == tempEndTile.x || tempOpenListIndex.y == tempEndTile.y)
	//					break;
	//			}
	//			tempInt = abs(tempOpenListIndex.x - tempEndTile.x) + abs(tempOpenListIndex.y - tempEndTile.y);
	//
	//			_vOpenList[i]->setCostToGoal((count + tempInt) * 10);
	//		}
	//		//대각선으로 갈필요가 없는 타일
	//		else
	//		{
	//			_vOpenList[i]->setCostToGoal(( tempInt) * 10);
	//		}
	//	}
	//		//break;
	//	//_vOpenList[i]->setCostToGoal(
	//	//	(abs(_endTile->getIdX() - _vOpenList[i]->getIdX()) +
	//	//	abs(_endTile->getIdY() - _vOpenList[i]->getIdY())) * 10);
	//
	//	//현재 타일의 중점
	//	POINT center1 = _vOpenList[i]->getParentNode()->getCenter();
	//	POINT center2 = _vOpenList[i]->getCenter();
	//
	//	//G 값 뽑는다
	//	_vOpenList[i]->setCostFromStart((getDistance(center1.x, center1.y, center2.x, center2.y) < ISOTILESIZEX-5) ? 14 : 10);
	//
	//	//총 경로 비용 == (갈수 있는 타일 들 중에서 총 경로비용)
	//	_vOpenList[i]->setTotalCost(_vOpenList[i]->getCostToGoal() +
	//		_vOpenList[i]->getCostFromStart());
	//
	//	//임의의 경로비용보다 뽑아낸 경로 비용이 작다면 == 빠른길 찾았다!
	//	if (tempTotalCost > _vOpenList[i]->getTotalCost())
	//	{
	//		tempTotalCost = _vOpenList[i]->getTotalCost();
	//		tempTile = _vOpenList[i];
	//	}
	//
	//	bool addObj = true;
	//	for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
	//	{
	//		//가장 저렴한 비용의 타일을 검출 한다
	//		if (*_viOpenList == tempTile)
	//		{
	//			addObj = false;
	//			break;
	//		}
	//	}
	//
	//	_vOpenList[i]->setIsOpen(false);
	//	if (!addObj) continue;
	//
	//	_vOpenList.push_back(tempTile);
	//}
	//
	//if (tempTile->getAttribute() == "end")
	//{
	//	while (_currentTile->getParentNode() != NULL)
	//	{
	//		//_currentTile->setColor(RGB(22, 14, 128));
	//		_currentTile = _currentTile->getParentNode();
	//	}
	//
	//	return;
	//}
	//
	//_vCloseList.push_back(tempTile);
	//
	////갈곳이 없는걸 아니까 지워주는 곳
	//for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
	//{
	//	if (*_viOpenList == tempTile)
	//	{
	//		_viOpenList = _vOpenList.erase(_viOpenList);
	//		break;
	//	}
	//}
	//
	//_currentTile = tempTile;
	//
	////함수 안에서 다시 함수를 호출 하는 방식이 재귀함수 방식
	////재귀함수는 사용해야할 때 주의 사항이 있다.
	////1. 코드가 짧아진다는 편리함이 있는대신 알아보기 힘들다
	////2. 한 번 호출할 때 마다 메모리 스택이 쌓인다
	////3. 이 스택 메모리가 1.2M 이상 쌓이면 터지는데 이 걸 스택오버플로우라 한다
	////4. 스택오버메모리 한계치는 코드로 정할 수 있지만, 실무에선 보통 그러지 않는다(앵간해선)
	//pathFinder(_currentTile);

}


void aStar::release()
{

}

void aStar::update()
{
	//if (KEYMANAGER->isOnceKeyDown('S')) /*_start = true;*/ pathFinder(_currentTile);

	//if (_start)
	//{
	//	_count++;
	//	if (_count % 10 == 0)
	//	{
	//		pathFinder(_currentTile);
	//		_count = 0;
	//	}
	//}

	//if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	//{
	//	for (int i = 0; i < _vTotalList.size(); ++i)
	//	{
	//		if (PtInRect(&_vTotalList[i]->getRect(), _ptMouse))
	//		{
	//			if (_vTotalList[i]->getAttribute() == "start") continue;
	//			if (_vTotalList[i]->getAttribute() == "end") continue;

	//			_vTotalList[i]->setIsOpen(false);
	//			_vTotalList[i]->setAttribute("wall");
	//			//_vTotalList[i]->setColor(RGB(230, 140, 200));
	//			break;
	//		}
	//	}
	//}

}

void aStar::render()
{
	/*for (int i = 0; i < _vTotalList.size(); ++i)
	{
		_vTotalList[i]->render();
	}*/
}
POINT aStar::getNextTile()
{
	//_startTile->init(startIdX, startIdY, _currentGameTile[startIdX * 20 + startIdY].getCenterPoint());
	//_startTile->setAttribute("start");
	//_vTotalList[startIdX * ISOTILEX + startIdY] = _startTile;
	//
	//_endTile->init(endIdX, endIdY, _currentGameTile[endIdX * 20 + endIdY].getCenterPoint());
	//_endTile->setAttribute("end");
	//_vTotalList[endIdX * ISOTILEX + endIdY] = _endTile;
	//
	//_currentTile = _startTile;
	//만약 시작타일과 끝타일이 같지 않으면 길을 찾아라
	if (_startTile->getIdX() != _endTile->getIdX() || _startTile->getIdY() != _endTile->getIdY())
	pathFinder(_currentTile);

	if (_vCloseList.size() <= 0)
	{
		return PointMake(-1, -1);
	}
	return{ _vCloseList[0]->getIdX(), _vCloseList[0]->getIdY() };
}
//POINT aStar::getTile()
//{
//	if (_vCloseList.size() <= 0) return{ -1, -1 };
//
//	return{ _vCloseList[0]->getIdX(), _vCloseList[0]->getIdY() };
//}