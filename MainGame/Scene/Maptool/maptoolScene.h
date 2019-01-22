#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include <commdlg.h>

//버튼갯수
#define MAXBUTTON 8

//지형버튼눌렀냐, 오브젝트냐, NPC냐 등등
enum tagButtonType{
	BTN_SAVE,			//0
	BTN_LOAD,			//1
	BTN_TERRAIN,		//2
	BTN_OBJECT,			//3
	BTN_NPC,			//4
	BTN_TOWN,			//5
	BTN_HUNTING,		//6
	BTN_ERASER_TERRAIN,	//7
	BTN_ERASER_OBJECT,	//8
	BTN_ERASER_NPC		//9
};
class maptoolScene :
	public gameNode
{
private : 
	typedef tagSampleTile tagNPCTile;
	typedef tagSampleTile tagOBJTile;
	typedef tagSampleTile tagRespondTile;

private:
	RECT _button[MAXBUTTON];
	tagButtonType _buttonType;
	//RECT _saveButtonRC;
	//RECT _loadButtonRC;
	//RECT _terrainButtonRC;
	//RECT _objectButtonRC;
	//RECT _NPCButtonRC;
	//RECT _eraserButtonRC;

	//HWND _btnSave;
	//HWND _btnLoad;
	//HWND _btnTerrainDraw;
	//HWND _btnObjectDraw;
	//HWND _btnEraser;

	////슬롯핸들
	//HWND _btnSlot1;
	//HWND _btnSlot2;
	//HWND _btnSlot3;

	tagCurrentTile _currentTile;
	tagSampleTile _sampleTile[SAMPLETILEX * SAMPLETILEY];
	tagNPCTile		_NPCTile[NPCTILEX * NPCTILEY];
	tagOBJTile		_OBJTile[OBJTILEX * OBJTILEY];
	tagRespondTile _respondTile;
	tagTile _tiles[ISOTILEX * ISOTILEY];

	int _pos[2];

	//맵툴 카메라 RC
	RECT _cameraRC;

	timer* _timer;

	char _savePath[80];
	char _basePath[80];
	char _townPath[10];
	char _huntingPath[20];

	char testChar[128];
	int test;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void setup();
	virtual void setMap();
	void setNPC();
	void setOBJ();

	virtual void save();
	virtual void load();

	//init에서 쓰기 위한 초기화 함수들
	void addImage();
	void variableInit();

	//render에서 쓰기 위한 드로우 함수들
	void sampleTileDraw();
	void baseTileDraw();
	void objectTileDraw();
	void buttonDraw();

	//update에서 쓰기 위한 함수들
	void buttonChange();

	//0 : 왼, 1 : 위, 2 : 오, 3 : 아
	virtual void mouseMove(int direction);

	TERRAIN terrainSelect(int frameX, int frameY);
	OBJECT objSelect(int frameX, int frameY);
	POS	posSelect(int frameX, int frameY);

	maptoolScene();
	~maptoolScene();
};

