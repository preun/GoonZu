#pragma once
#include "gameNode.h"
#include "aStarTile.h"
#include "tileNode.h"

class aStar :
	public gameNode
{
	//��ü Ÿ��
	vector<aStarTile*> _vTotalList;
	vector<aStarTile*>::iterator _viTotalList;

	//���� �ִ� Ÿ�� ����
	vector<aStarTile*> _vOpenList;
	vector<aStarTile*>::iterator _viOpenList;

	//���������� ���� ����� ��� ��� ����
	vector<aStarTile*> _vCloseList;
	vector<aStarTile*>::iterator _viCloseList;

	aStarTile* _startTile;
	aStarTile* _endTile;
	aStarTile* _currentTile;

	tagTile* _currentGameTile;
	//���߿�
	int _count;
	bool _start;

public:
	aStar();
	~aStar();

	HRESULT init(tagTile* currentGameTile);
	HRESULT init();

	// Ÿ�� ���� �Լ�
	void setTiles(int playerX, int playerY, int enemyX, int enemyY, tagTile* currentGameTile);

	//�� �� �ִ� ���� �˻��ؼ� �߰��ϴ� �Լ�
	vector<aStarTile*> addOpenList(aStarTile* currentTile);

	//�� ã�� �Լ�
	void pathFinder(aStarTile* currentTile);



	POINT getNextTile();
	//POINT getTile();
	//void removeFirstTile(){ 
	//	if (_vCloseList.size() <= 0) return;
	//	_vCloseList.erase(_vCloseList.begin() + 0); }

	void release();
	void update();
	void render();
};

