#pragma once
#include "gameNode.h"
#include "aStarTile.h"
#include "tileNode.h"

class aStar :
	public gameNode
{
	//전체 타일
	vector<aStarTile*> _vTotalList;
	vector<aStarTile*>::iterator _viTotalList;

	//갈수 있는 타일 벡터
	vector<aStarTile*> _vOpenList;
	vector<aStarTile*>::iterator _viOpenList;

	//최종적으로 제일 가까운 경로 담는 벡터
	vector<aStarTile*> _vCloseList;
	vector<aStarTile*>::iterator _viCloseList;

	aStarTile* _startTile;
	aStarTile* _endTile;
	aStarTile* _currentTile;

	tagTile* _currentGameTile;
	//나중에
	int _count;
	bool _start;

public:
	aStar();
	~aStar();

	HRESULT init(tagTile* currentGameTile);
	HRESULT init();

	// 타일 셋팅 함수
	void setTiles(int playerX, int playerY, int enemyX, int enemyY, tagTile* currentGameTile);

	//갈 수 있는 길을 검색해서 추가하는 함수
	vector<aStarTile*> addOpenList(aStarTile* currentTile);

	//길 찾기 함수
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

