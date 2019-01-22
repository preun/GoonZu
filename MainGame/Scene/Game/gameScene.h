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

//A스타 실험용
#include "aStar.h"

class character;

class gameScene :
	public gameNode
{
	//마을 타일 및 속성
	tagTile _townTiles[ISOTILEX * ISOTILEY];
	DWORD _townAttribute[ISOTILEX * ISOTILEY];

	//사냥터 타일 및 속성
	tagTile _huntingTiles[ISOTILEX * ISOTILEY];
	DWORD _huntingAttribut[ISOTILEX * ISOTILEY];
	//사냥터 리스폰 인덱스 벡터
	vector<int> _vHuntingRespond;
	vector<int>::iterator _vIHuntingRespond;

	//아이템매니저 초기화
	itemManager* _itemManager;

	//NPC 포스
	int _posNPC[3];

	//카메라 RC
	RECT _cameraRC;

	npcParent* _hosulam;
	npcParent* _musuri;
	npcParent* _janggumi;

	//노래변수
	char _musicStr[64];

	//a스타 실험용
	//aStar* _aStarTest;

	//UI
	UI* _UI;

	monsterManager* _monsterManager;

	//실험용 문자열
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

