#pragma once
#include "gameNode.h"
#include "monsterParent.h"
#include "pigMonster.h"
#include "tileNode.h"

class monsterManager :
	public gameNode
{
private:

	//사냥터 별로 몬스터 벡터 만드는걸로
	//기본 사냥터 몬스터 벡터
	vector<monsterParent*> _vHuntingMonster;
	vector<monsterParent*>::iterator _viHuntingMonster;

	int _respond[5];

public:
	monsterManager();
	~monsterManager();
	//tagTile
	//	DWORD
	virtual HRESULT init(vector<int> respond, tagTile* hungtingTile, DWORD* huntingTileAtt);
	virtual void release();
	virtual void update();
	virtual void render();

	//마우스 클릭시 클릭한 몬스터 찾아 주는 함수
	monsterParent* findClickMonster();
};

