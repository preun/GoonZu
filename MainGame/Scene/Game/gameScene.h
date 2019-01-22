#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "itemManager.h"
#include "npcParent.h"
#include "hosulam.h"
#include "musuri.h"
#include "janggumi.h"
#include "monsterManager.h"
#include "UI.h"

//A��Ÿ �����
#include "aStar.h"

class character;

class gameScene :
	public gameNode
{
	//���� Ÿ�� �� �Ӽ�
	tagTile _townTiles[ISOTILEX * ISOTILEY];
	DWORD _townAttribute[ISOTILEX * ISOTILEY];

	//����� Ÿ�� �� �Ӽ�
	tagTile _huntingTiles[ISOTILEX * ISOTILEY];
	DWORD _huntingAttribut[ISOTILEX * ISOTILEY];
	//����� ������ �ε��� ����
	vector<int> _vHuntingRespond;
	vector<int>::iterator _vIHuntingRespond;

	//�����۸Ŵ��� �ʱ�ȭ
	itemManager* _itemManager;

	//NPC ����
	int _posNPC[3];

	//ī�޶� RC
	RECT _cameraRC;

	npcParent* _hosulam;
	npcParent* _musuri;
	npcParent* _janggumi;

	//�뷡����
	char _musicStr[64];

	//a��Ÿ �����
	//aStar* _aStarTest;

	//UI
	UI* _UI;

	monsterManager* _monsterManager;

	//����� ���ڿ�
	//char test111[111];
public:
	gameScene();
	~gameScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void townLoad();
	void huntingLoad();

	void move(int direction);

	void tileDraw();
	void npcDraw();
	void townObjectDraw();
	void huntingObjectDraw();
};

