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
	////Ÿ�� ���� ���ش�
	//setTiles(currentGameTile);

	//�ϴ� �޸𸮰��� �Ҵ����ش�.
	

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

// Ÿ�� ���� �Լ�
void aStar::setTiles(int playerX, int playerY, int enemyX, int enemyY, tagTile* currentGameTile)
{
	_vTotalList.clear();
	_vOpenList.clear();
	_vCloseList.clear();

	//����Ÿ��
	_startTile = new aStarTile;
	_startTile->init(playerX, playerY, currentGameTile[playerX * 20 + playerY].getCenterPoint());
	_startTile->setAttribute("start");

	//�� Ÿ��
	_endTile = new aStarTile;
	_endTile->init(enemyX, enemyY, currentGameTile[enemyX * 20 + enemyY].getCenterPoint());
	_endTile->setAttribute("end");

	//���� Ÿ���� ó���� ����Ÿ�Ϸ�!
	_currentTile = _startTile;

	for (int i = 0; i < ISOTILEX; ++i)
	{
		for (int j = 0; j < ISOTILEY; ++j)
		{
			//�ش� Ÿ�� ã������
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
			//�� �� ������ Ÿ�ϵ� ��Ż���Ϳ� ����ش�
			aStarTile* node = new aStarTile;
			node->init(i, j, currentGameTile[i*20 + j].getCenterPoint());
			_vTotalList.push_back(node);
		}
	}
	//
	//_vTotalList.clear();
	//_currentGameTile = currentGameTile;
	//
	//////����Ÿ��
	////_startTile = new aStarTile;
	////_startTile->init(3, 3, currentGameTile[3 * 20 + 3].getCenterPoint());
	////_startTile->setAttribute("start");
	//
	////////�� Ÿ��
	//////_endTile = new aStarTile;
	////_endTile->init(5, 5, currentGameTile[5*20 + 5].getCenterPoint());
	////_endTile->setAttribute("end");
	//
	////////���� Ÿ���� ó���� ����Ÿ�Ϸ�!
	////_currentTile = _startTile;
	//
	////for (int i = 0; i < ISOTILEY; ++i)
	////{
	////	for (int j = 0; j < ISOTILEX; ++j)
	////	{
	////		//�ش� Ÿ�� ã������
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
	////		//�� �� ������ Ÿ�ϵ� ��Ż���Ϳ� ����ش�
	////		aStarTile* node = new aStarTile;
	////		node->init(j, i);
	////		_vTotalList.push_back(node);
	////	}
	////}

}


//�� �� �ִ� ���� �˻��ؼ� �߰��ϴ� �Լ�
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

			//���� ���� Ÿ�� �� ���� Ÿ�� �׸��� ���� �����Ѵ�
			if (!node->getIsOpen()) continue;
			if (node->getAttribute() == "start") continue;
			if (node->getAttribute() == "wall") continue;

			//�ֻ��� ���� ���� Ÿ�Ϸ� ���ش�
			node->setParentNode(_currentTile);

			//������ �� ���� �ϳ� �д�(üũ ��)
			bool addObj = true;

			for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
			{
				//�� �� üũ �� �ִ� �ߺ� ���� ���� �ʴ´�
				if (*_viOpenList == node)
				{
					addObj = false;
					break;
				}
			}

			//����Ÿ���� �ƴϸ� (�����Ҷ����� ���)
			//if (node->getAttribute() != "end") node->setColor(RGB(128, 64, 28));

			if (!addObj) continue;

			//���¸���Ʈ�� ����ش�
			_vOpenList.push_back(node);
		}
	}
	//�׷��� (�����ִ� ���� ���) ���¸���Ʈ�� ��ȯ�Ѵ�
	return _vOpenList;
}


//�� ã�� �Լ�
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
	//aStarTile* tempTile;			//���� ���� ���� �����ϱ� ���� ����Ÿ��
	//
	////�� �� �ִ� �游 ��� ���� �ȿ���~
	//for (int i = 0; i < addOpenList(currentTile).size(); ++i)
	//{
	//	//H �� �̴´�
	//	//�� Ÿ�� �̵��� ���� ��κ��(Ÿ�ϰ� �Ÿ�)�� �̾��ش�
	//
	//	//���� ����Ʈ�� x, y
	//	POINT tempOpenListIndex = { _vOpenList[i]->getIdX(), _vOpenList[i]->getIdY() };
	//	//���� Ÿ���� x, y
	//	POINT tempEndTile = { _endTile->getIdX(), _endTile->getIdY() };
	//	//Ÿ�� �ε��� ����
	//	int tempInt = abs(tempOpenListIndex.x - tempEndTile.x) + abs(tempOpenListIndex.y - tempEndTile.y);
	//	//������������ �Ÿ��� ��Ÿ���� �ƴϸ� (4���� ����)
	//	if (tempInt <= 1) _vOpenList[i]->setCostToGoal(tempInt * 10);
	//	//2Ÿ�� �� �Ÿ��� ��Ÿ�� ���� �ִٸ� (8���� �̵� �����ϹǷ� 2Ÿ�ϰŸ��� 1Ÿ�Ϸ� ���ϼ� �ֵ�.
	//	else if (tempInt == 2)
	//	{
	//		//�밢������ ��ĭ �Ÿ��� �ƴ� �������� 2ĭ �Ÿ��ϰ�� ����ó��
	//		if (tempEndTile.x == tempOpenListIndex.x || tempEndTile.y == tempOpenListIndex.y)
	//			_vOpenList[i]->setCostToGoal(tempInt * 10);
	//		else
	//		_vOpenList[i]->setCostToGoal((tempInt - 1) * 10);
	//	}
	//	//�Ÿ��� 3ĭ�̸� �ѹ��̻��� �밢������ ���� �ִ�.
	//	else
	//	{
	//		//���� Ÿ�� �������� �Ʒ� Ÿ���̸�
	//		if (tempOpenListIndex.x > tempEndTile.x && tempOpenListIndex.y > tempEndTile.y)
	//		{
	//			//�Ÿ��� 3 �̻��̳�
	//			int count = 0;
	//				//�Ÿ��� 3 �̻��̳�
	//				while (1)
	//				{
	//					tempOpenListIndex.x--;
	//					tempOpenListIndex.y--;
	//					count++;
	//					//�밢�� �̵��� ���� ������ �Ǿ����� �����
	//					if (tempOpenListIndex.x == tempEndTile.x || tempOpenListIndex.y == tempEndTile.y)
	//						break;
	//				}
	//				tempInt = abs(tempOpenListIndex.x - tempEndTile.x) + abs(tempOpenListIndex.y - tempEndTile.y);
	//
	//				_vOpenList[i]->setCostToGoal((count + tempInt) * 10);
	//			
	//		}
	//		////���� Ÿ�� �������� ���� Ÿ���̸�
	//		else if (tempOpenListIndex.x > tempEndTile.x && tempOpenListIndex.y < tempEndTile.y)
	//		{
	//			int count = 0;
	//			//�Ÿ��� 3 �̻��̳�
	//			while (1)
	//			{
	//				tempOpenListIndex.x--;
	//				tempOpenListIndex.y++;
	//				count++;
	//				//�밢�� �̵��� ���� ������ �Ǿ����� �����
	//				if (tempOpenListIndex.x == tempEndTile.x || tempOpenListIndex.y == tempEndTile.y)
	//					break;
	//			}
	//			tempInt = abs(tempOpenListIndex.x - tempEndTile.x) + abs(tempOpenListIndex.y - tempEndTile.y);
	//
	//			_vOpenList[i]->setCostToGoal((count + tempInt) * 10);
	//		}
	//		//���� Ÿ�� �������� ���� Ÿ���̸�
	//		else if (tempOpenListIndex.x < tempEndTile.x && tempOpenListIndex.y < tempEndTile.y)
	//		{
	//			int count = 0;
	//			//�Ÿ��� 3 �̻��̳�
	//			while (1)
	//			{
	//				tempOpenListIndex.x++;
	//				tempOpenListIndex.y++;
	//				count++;
	//				//�밢�� �̵��� ���� ������ �Ǿ����� �����
	//				if (tempOpenListIndex.x == tempEndTile.x || tempOpenListIndex.y == tempEndTile.y)
	//					break;
	//			}
	//			tempInt = abs(tempOpenListIndex.x - tempEndTile.x) + abs(tempOpenListIndex.y - tempEndTile.y);
	//
	//			_vOpenList[i]->setCostToGoal((count + tempInt) * 10);
	//		}
	//		//���� Ÿ�� �������� ������ Ÿ���̸�
	//		else if (tempOpenListIndex.x < tempEndTile.x && tempOpenListIndex.y > tempEndTile.y)
	//		{
	//			int count = 0;
	//			//�Ÿ��� 3 �̻��̳�
	//			while (1)
	//			{
	//				tempOpenListIndex.x++;
	//				tempOpenListIndex.y--;
	//				count++;
	//				//�밢�� �̵��� ���� ������ �Ǿ����� �����
	//				if (tempOpenListIndex.x == tempEndTile.x || tempOpenListIndex.y == tempEndTile.y)
	//					break;
	//			}
	//			tempInt = abs(tempOpenListIndex.x - tempEndTile.x) + abs(tempOpenListIndex.y - tempEndTile.y);
	//
	//			_vOpenList[i]->setCostToGoal((count + tempInt) * 10);
	//		}
	//		//�밢������ ���ʿ䰡 ���� Ÿ��
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
	//	//���� Ÿ���� ����
	//	POINT center1 = _vOpenList[i]->getParentNode()->getCenter();
	//	POINT center2 = _vOpenList[i]->getCenter();
	//
	//	//G �� �̴´�
	//	_vOpenList[i]->setCostFromStart((getDistance(center1.x, center1.y, center2.x, center2.y) < ISOTILESIZEX-5) ? 14 : 10);
	//
	//	//�� ��� ��� == (���� �ִ� Ÿ�� �� �߿��� �� ��κ��)
	//	_vOpenList[i]->setTotalCost(_vOpenList[i]->getCostToGoal() +
	//		_vOpenList[i]->getCostFromStart());
	//
	//	//������ ��κ�뺸�� �̾Ƴ� ��� ����� �۴ٸ� == ������ ã�Ҵ�!
	//	if (tempTotalCost > _vOpenList[i]->getTotalCost())
	//	{
	//		tempTotalCost = _vOpenList[i]->getTotalCost();
	//		tempTile = _vOpenList[i];
	//	}
	//
	//	bool addObj = true;
	//	for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
	//	{
	//		//���� ������ ����� Ÿ���� ���� �Ѵ�
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
	////������ ���°� �ƴϱ� �����ִ� ��
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
	////�Լ� �ȿ��� �ٽ� �Լ��� ȣ�� �ϴ� ����� ����Լ� ���
	////����Լ��� ����ؾ��� �� ���� ������ �ִ�.
	////1. �ڵ尡 ª�����ٴ� ������ �ִ´�� �˾ƺ��� �����
	////2. �� �� ȣ���� �� ���� �޸� ������ ���δ�
	////3. �� ���� �޸𸮰� 1.2M �̻� ���̸� �����µ� �� �� ���ÿ����÷ο�� �Ѵ�
	////4. ���ÿ����޸� �Ѱ�ġ�� �ڵ�� ���� �� ������, �ǹ����� ���� �׷��� �ʴ´�(�ް��ؼ�)
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
	//���� ����Ÿ�ϰ� ��Ÿ���� ���� ������ ���� ã�ƶ�
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