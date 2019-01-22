#pragma once
#include "gameNode.h"
#include "monsterParent.h"
#include "pigMonster.h"
#include "tileNode.h"

class monsterManager :
	public gameNode
{
private:

	//����� ���� ���� ���� ����°ɷ�
	//�⺻ ����� ���� ����
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

	//���콺 Ŭ���� Ŭ���� ���� ã�� �ִ� �Լ�
	monsterParent* findClickMonster();
};

