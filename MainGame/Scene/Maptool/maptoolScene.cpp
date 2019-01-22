#include "stdafx.h"
#include "maptoolScene.h"


maptoolScene::maptoolScene()
{
}


maptoolScene::~maptoolScene()
{

}

HRESULT maptoolScene::init()
{
	addImage();
	variableInit();		

	strcpy(_basePath, "./map/");
	strcpy(_townPath, "마을.map");
	strcpy(_huntingPath, "사냥터.map");
	strcpy(_savePath, _basePath);

	setup();	

	//MAPTOOLCAMERAMANAGER->setCameraCondition(MAPTOOL_CAMERA_AIMING);
	MAPTOOLCAMERAMANAGER->setCameraAim(&_cameraRC);	

	return S_OK;
}

void maptoolScene::addImage(){
	IMAGEMANAGER->addFrameImage("mapTiles", "./image/tile/타일.bmp", 210, 140, SAMPLETILEX, SAMPLETILEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("NPC", "./image/npc/npc.bmp", 96, 61, NPCTILEX, NPCTILEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("object", "./image/object/object.bmp", 142, 393, OBJTILEX, OBJTILEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("respond", "./image/object/리스폰.bmp", 45, 40,1,1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("saveButton", "./image/tile/저장버튼.bmp", 50, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("loadButton", "./image/tile/불러오기버튼.bmp", 50, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("terrainButton", "./image/tile/타일버튼.bmp", 50, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("objectButton", "./image/tile/오브젝트버튼.bmp", 50, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("NPCButton", "./image/tile/NPC버튼.bmp", 50, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("eraserButton", "./image/tile/지우기버튼.bmp", 50, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("town", "./image/tile/마을버튼.bmp", 50, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("hunting", "./image/tile/사냥터버튼.bmp", 50, 30, true, RGB(255, 0, 255));
}

void maptoolScene::variableInit(){
	/*
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
	*/
	_button[BTN_SAVE] = RectMake(550, 520, BUTTONSIZEX, BUTTONSIZEY);
	_button[BTN_LOAD] = RectMake(550, 570, BUTTONSIZEX, BUTTONSIZEY);
	_button[BTN_TERRAIN] = RectMake(650, 520, BUTTONSIZEX, BUTTONSIZEY);
	_button[BTN_OBJECT] = RectMake(650, 570, BUTTONSIZEX, BUTTONSIZEY);
	_button[BTN_NPC] = RectMake(750, 520, BUTTONSIZEX, BUTTONSIZEY);	
	_button[BTN_TOWN] = RectMake(550, 470, BUTTONSIZEX, BUTTONSIZEY);
	_button[BTN_HUNTING] = RectMake(650, 470, BUTTONSIZEX, BUTTONSIZEY);
	_button[BTN_ERASER_TERRAIN] = RectMake(750, 570, BUTTONSIZEX, BUTTONSIZEY);

	_buttonType = BTN_TERRAIN;

	_cameraRC = RectMake(0, 0, TILEWINSIZEX, TILEWINSIZEY);

	_currentTile.x = TILEDEFAULTX;
	_currentTile.y = TILEDEFAULTY;

	test = 0;
}

void maptoolScene::release()
{

}

void maptoolScene::update()
{
	
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		buttonChange();

		//_leftMouseButton = true;
		
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		mouseMove(0);
	}
	else if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		mouseMove(1);
	}
	else if(KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		mouseMove(2);

	}
	else if(KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		mouseMove(3);
	}
}

void maptoolScene::buttonChange(){

	for (int i = 0; i<MAXBUTTON; ++i)
	{
		if (PtInRect(&_button[i], _ptMouse))
		{
			if (i == 7)
			{
				switch (_buttonType)
				{
				case BTN_TERRAIN:case BTN_OBJECT:case BTN_NPC:
					_buttonType = (tagButtonType)(5 + (int)_buttonType);
					break;
				default:
					break;
				}
			}
			else
			{
				_buttonType = (tagButtonType)i;
			}
			break;
		}

	}
	if (_buttonType == BTN_SAVE)
	{
		save();
	}
	else if (_buttonType == BTN_LOAD)
	{
		load();
	}
	else if (_buttonType == BTN_TOWN)
	{
		strcpy(_savePath, _basePath);

		strcat(_savePath, _townPath);
	}
	else if (_buttonType == BTN_HUNTING)
	{
		strcpy(_savePath, _basePath);
		strcat(_savePath, _huntingPath);
	}
	else if (_buttonType == BTN_TERRAIN || _buttonType == BTN_ERASER_TERRAIN)
	{
		setMap();
	}
	else if (_buttonType == BTN_NPC || _buttonType == BTN_ERASER_NPC)
	{
		setNPC();
	}
	else if (_buttonType == BTN_OBJECT || _buttonType == BTN_ERASER_OBJECT)
	{
		setOBJ();
	}
}

void maptoolScene::render()
{
	sampleTileDraw();
	
	test = 0;

	//지형
	baseTileDraw();


	//오브젝트
	objectTileDraw();

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		RectangleMake(getMemDC(),
			MAPTOOLCAMERAMANAGER->CameraRelativePoint(_cameraRC).x,
			MAPTOOLCAMERAMANAGER->CameraRelativePoint(_cameraRC).y,
			TILEWINSIZEX, TILEWINSIZEY);
	}

	sprintf(testChar, "%d, %d, %d, %d, %d", MAPTOOLCAMERAMANAGER->CameraRelativePointX(_ptMouse.x), MAPTOOLCAMERAMANAGER->CameraRelativePointY(_ptMouse.y)
		, _currentTile.x, _currentTile.y, _buttonType);
	//TextOut(getMemDC(), 300, 10, testChar, strlen(testChar));

	buttonDraw();

	/*for (int i = 0; i < 2; ++i)
	{
		Rectangle(getMemDC(), _OBJTile[i].rcTile.left, _OBJTile[i].rcTile.top, _OBJTile[i].rcTile.right, _OBJTile[i].rcTile.bottom);
	}*/
	//Rectangle(getMemDC(), _cameraRC.left, _cameraRC.top, _cameraRC.right, _cameraRC.bottom);
}

void maptoolScene::sampleTileDraw(){

	if (_buttonType == BTN_TERRAIN)
		IMAGEMANAGER->render("mapTiles", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("mapTiles")->getWidth(), 0);
	else if (_buttonType == BTN_NPC)
		IMAGEMANAGER->render("NPC", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("NPC")->getWidth(), 0);
	else if (_buttonType == BTN_OBJECT)
	{
		IMAGEMANAGER->render("object", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("object")->getWidth(), 0);
		IMAGEMANAGER->render("respond", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("object")->getWidth() - IMAGEMANAGER->findImage("respond")->getWidth(), 0);
	}


}

void maptoolScene::buttonDraw(){

	IMAGEMANAGER->findImage("saveButton")->render(getMemDC(), _button[BTN_SAVE].left, _button[BTN_SAVE].top);
	IMAGEMANAGER->findImage("loadButton")->render(getMemDC(), _button[BTN_LOAD].left, _button[BTN_LOAD].top);
	IMAGEMANAGER->findImage("terrainButton")->render(getMemDC(), _button[BTN_TERRAIN].left, _button[BTN_TERRAIN].top);
	IMAGEMANAGER->findImage("objectButton")->render(getMemDC(), _button[BTN_OBJECT].left, _button[BTN_OBJECT].top);
	IMAGEMANAGER->findImage("NPCButton")->render(getMemDC(), _button[BTN_NPC].left, _button[BTN_NPC].top);
	IMAGEMANAGER->findImage("eraserButton")->render(getMemDC(), _button[BTN_ERASER_TERRAIN].left, _button[BTN_ERASER_TERRAIN].top);
	IMAGEMANAGER->findImage("town")->render(getMemDC(), _button[BTN_TOWN ].left, _button[BTN_TOWN].top);
	IMAGEMANAGER->findImage("hunting")->render(getMemDC(), _button[BTN_HUNTING ].left, _button[BTN_HUNTING].top);

}

void maptoolScene::baseTileDraw()
{
	for (int i = 0; i < ISOTILEX * ISOTILEY; ++i)
	{
		RECT temp;

		RECT tempCameraRC = RectMake(MAPTOOLCAMERAMANAGER->CameraRelativePoint(_cameraRC).x,
			MAPTOOLCAMERAMANAGER->CameraRelativePoint(_cameraRC).y,
			TILEWINSIZEX, TILEWINSIZEY);

		RECT tempTileRC = RectMake(MAPTOOLCAMERAMANAGER->CameraRelativePoint(_tiles[i].renderPoint).x,
			MAPTOOLCAMERAMANAGER->CameraRelativePoint(_tiles[i].renderPoint).y,
			IMAGEMANAGER->findImage("mapTiles")->getFrameWidth(), IMAGEMANAGER->findImage("mapTiles")->getFrameHeight());

		if (!IntersectRect(&temp, &tempCameraRC, &tempTileRC)) continue;

		test++;

		IMAGEMANAGER->frameRender("mapTiles", getMemDC(),
			MAPTOOLCAMERAMANAGER->CameraRelativePoint(_tiles[i].renderPoint).x,
			MAPTOOLCAMERAMANAGER->CameraRelativePoint(_tiles[i].renderPoint).y,
			_tiles[i].terrainFrameX, _tiles[i].terrainFrameY,
			&RectMake(MAPTOOLCAMERAMANAGER->CameraRelativePoint(_cameraRC).x,
			MAPTOOLCAMERAMANAGER->CameraRelativePoint(_cameraRC).y,
			TILEWINSIZEX, TILEWINSIZEY)
			);

		switch (_tiles[i].obj)
		{
		case OBJ_MUSURI:case OBJ_HOSULAM: case OBJ_JANGGUMI:
			IMAGEMANAGER->frameRender("NPC", getMemDC(),
				MAPTOOLCAMERAMANAGER->CameraRelativePoint(_tiles[i].renderPoint).x + TILESIZE / 4,
				MAPTOOLCAMERAMANAGER->CameraRelativePoint(_tiles[i].renderPoint).y - 5,
				_tiles[i].objFrameX, _tiles[i].objFrameY,
				&RectMake(MAPTOOLCAMERAMANAGER->CameraRelativePoint(_cameraRC).x,
				MAPTOOLCAMERAMANAGER->CameraRelativePoint(_cameraRC).y,
				TILEWINSIZEX, TILEWINSIZEY));
			break;


		default:
			break;
		}
		//sprintf(testChar, "%d", test);
		//TextOut(getMemDC(), MAPTOOLCAMERAMANAGER->CameraRelativePoint(_tiles[i].renderPoint).x + 22,
		//	MAPTOOLCAMERAMANAGER->CameraRelativePoint(_tiles[i].renderPoint).y + 22, testChar, strlen(testChar));

		//	IMAGEMANAGER->frameRender("mapTiles", getMemDC(),
		//		MAPTOOLCAMERAMANAGER->CameraRelativePoint(PointMake(_tiles[i].renderX, _tiles[i].renderY)).x,
		//		MAPTOOLCAMERAMANAGER->CameraRelativePoint(PointMake(_tiles[i].renderX, _tiles[i].renderY)).y,
		//		//_tiles[i].rc.left, _tiles[i].rc.top,
		//		_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
	}
}

void maptoolScene::objectTileDraw()
{
	for (int i = 0; i < ISOTILEX * ISOTILEY; ++i)
	{
		//NPC들은 위에서 그려준다.
		if (_tiles[i].obj != OBJ_TREE && _tiles[i].obj != OBJ_GRASS && _tiles[i].obj != OBJ_POTAL && _tiles[i].obj != OBJ_RESPOND) continue;

		if (_tiles[i].obj == OBJ_TREE)
		IMAGEMANAGER->frameRender("object", getMemDC(),
			MAPTOOLCAMERAMANAGER->CameraRelativePoint(_tiles[i].renderPoint).x - IMAGEMANAGER->findImage("object")->getFrameWidth()/4 ,
			MAPTOOLCAMERAMANAGER->CameraRelativePoint(_tiles[i].renderPoint).y - (IMAGEMANAGER->findImage("object")->getFrameHeight()/4 ) * 2.5,
			_tiles[i].objFrameX, _tiles[i].objFrameY,
			&RectMake(MAPTOOLCAMERAMANAGER->CameraRelativePoint(_cameraRC).x,
			MAPTOOLCAMERAMANAGER->CameraRelativePoint(_cameraRC).y,
			TILEWINSIZEX, TILEWINSIZEY));

		else if (_tiles[i].obj == OBJ_GRASS)
			IMAGEMANAGER->frameRender("object", getMemDC(),
			MAPTOOLCAMERAMANAGER->CameraRelativePoint(_tiles[i].renderPoint).x - IMAGEMANAGER->findImage("object")->getFrameWidth() / 6,
			MAPTOOLCAMERAMANAGER->CameraRelativePoint(_tiles[i].renderPoint).y - (IMAGEMANAGER->findImage("object")->getFrameHeight() / 6) /** 2.5*/,
			_tiles[i].objFrameX, _tiles[i].objFrameY,
			&RectMake(MAPTOOLCAMERAMANAGER->CameraRelativePoint(_cameraRC).x,
			MAPTOOLCAMERAMANAGER->CameraRelativePoint(_cameraRC).y,
			TILEWINSIZEX, TILEWINSIZEY));

		else if (_tiles[i].obj == OBJ_POTAL)
			IMAGEMANAGER->frameRender("object", getMemDC(),
			MAPTOOLCAMERAMANAGER->CameraRelativePoint(_tiles[i].renderPoint).x - TILESIZE/2, //- IMAGEMANAGER->findImage("object")->getFrameWidth() / 6,
			MAPTOOLCAMERAMANAGER->CameraRelativePoint(_tiles[i].renderPoint).y ,//+TILESIZE / 2,//- (IMAGEMANAGER->findImage("object")->getFrameHeight() / 6) /** 2.5*/,
			_tiles[i].objFrameX, _tiles[i].objFrameY,
			&RectMake(MAPTOOLCAMERAMANAGER->CameraRelativePoint(_cameraRC).x,
			MAPTOOLCAMERAMANAGER->CameraRelativePoint(_cameraRC).y,
			TILEWINSIZEX, TILEWINSIZEY));

		else if (_tiles[i].obj == OBJ_RESPOND)
			IMAGEMANAGER->frameRender("respond", getMemDC(),
			MAPTOOLCAMERAMANAGER->CameraRelativePoint(_tiles[i].renderPoint).x +TILESIZE/4, //- IMAGEMANAGER->findImage("object")->getFrameWidth() / 6,
			MAPTOOLCAMERAMANAGER->CameraRelativePoint(_tiles[i].renderPoint).y + TILESIZE / 4,//+TILESIZE / 2,//- (IMAGEMANAGER->findImage("object")->getFrameHeight() / 6) /** 2.5*/,
			0, 0,
			&RectMake(MAPTOOLCAMERAMANAGER->CameraRelativePoint(_cameraRC).x,
			MAPTOOLCAMERAMANAGER->CameraRelativePoint(_cameraRC).y,
			TILEWINSIZEX, TILEWINSIZEY));

		/*switch (_tiles[i].obj)
		{
		case OBJ_MUSURI:case OBJ_HOSULAM:
		IMAGEMANAGER->frameRender("NPC", getMemDC(),
		MAPTOOLCAMERAMANAGER->CameraRelativePoint(_tiles[i].renderPoint).x, MAPTOOLCAMERAMANAGER->CameraRelativePoint(_tiles[i].renderPoint).y,
		_tiles[i].objFrameX, _tiles[i].objFrameY, &_cameraRC);
		break;


		default:
		break;
		}*/

		//if (_tiles[i].obj == OBJ_MUSURI)
		//IMAGEMANAGER->frameRender("mapTiles", getMemDC(),
		//	MAPTOOLCAMERAMANAGER->CameraRelativePoint(_tiles[i].rc).x, MAPTOOLCAMERAMANAGER->CameraRelativePoint(_tiles[i].rc).y,
		//	_tiles[i].objFrameX, _tiles[i].objFrameY, &_cameraRC
		//	);

		//if (_tiles[i].obj == OBJ_NONE) continue;
		//IMAGEMANAGER->frameRender("mapTiles", getMemDC(),
		//	MAPTOOLCAMERAMANAGER->CameraRelativePoint(_tiles[i].rc).x, MAPTOOLCAMERAMANAGER->CameraRelativePoint(_tiles[i].rc).y,
		//	//_tiles[i].rc.left, _tiles[i].rc.top,
		//	_tiles[i].objFrameX, _tiles[i].objFrameY);
	}
}

void maptoolScene::setup()
{
	/*_btnSave = CreateWindow("button", "Save", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 550, 520,
		BUTTONSIZEX, BUTTONSIZEY, _hWnd, HMENU(0), _hInstance, NULL);

	_btnLoad = CreateWindow("button", "Load", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 550, 570,
		BUTTONSIZEX, BUTTONSIZEY, _hWnd, HMENU(1), _hInstance, NULL);

	_btnTerrainDraw = CreateWindow("button", "지형", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 650, 470, BUTTONSIZEX, BUTTONSIZEY, _hWnd, HMENU(2), _hInstance, NULL);

	_btnObjectDraw = CreateWindow("button", "오브젝", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 650, 520, BUTTONSIZEX, BUTTONSIZEY, _hWnd, HMENU(3), _hInstance, NULL);

	_btnEraser = CreateWindow("button", "Eraser", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 650, 570, BUTTONSIZEX, BUTTONSIZEY, _hWnd, HMENU(4), _hInstance, NULL);

	_btnSlot1 = CreateWindow("button", "슬롯1", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 750, 470, BUTTONSIZEX, BUTTONSIZEY, _hWnd, HMENU(5), _hInstance, NULL);
	_btnSlot2 = CreateWindow("button", "슬롯2", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 750, 520, BUTTONSIZEX, BUTTONSIZEY, _hWnd, HMENU(6), _hInstance, NULL);
	_btnSlot3 = CreateWindow("button", "슬롯3", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 750, 570, BUTTONSIZEX, BUTTONSIZEY, _hWnd, HMENU(7), _hInstance, NULL);*/


	//_ctrSelect = CTRL_TERRAINDRAW;

	//타일셋 (샘플타일) 셋팅
	for (int i = 0; i < SAMPLETILEY; ++i)
	{
		for (int j = 0; j < SAMPLETILEX; ++j)
		{
			_sampleTile[i * SAMPLETILEX + j].terrainFrameX = j;
			_sampleTile[i * SAMPLETILEX + j].terrainFrameY = i;

			//렉트 셋팅함수(셋팅될 렉트, left, top, right, bottom)
			SetRect(&_sampleTile[i * SAMPLETILEX + j].rcTile,
				(WINSIZEX - IMAGEMANAGER->findImage("mapTiles")->getWidth()) + j * TILESIZE,
				i * TILESIZE,
				(WINSIZEX - IMAGEMANAGER->findImage("mapTiles")->getWidth()) + j * TILESIZE + TILESIZE,
				i * TILESIZE + TILESIZE);
		}
	}

	//오른쪽 NPC셋업
	for (int i = 0; i < NPCTILEY; ++i)
	{
		for (int j = 0; j < NPCTILEX; ++j)
		{
			_NPCTile[i * NPCTILEX + j].terrainFrameX = j;
			_NPCTile[i * NPCTILEX + j].terrainFrameY = i;

			//렉트 셋팅함수(셋팅될 렉트, left, top, right, bottom)
			SetRect(&_NPCTile[i * NPCTILEX + j].rcTile,
				(WINSIZEX - IMAGEMANAGER->findImage("NPC")->getWidth()) + j * NPCSIZEX,
				i * NPCSIZEY,
				(WINSIZEX - IMAGEMANAGER->findImage("NPC")->getWidth()) + j * NPCSIZEX + NPCSIZEX,
				i * NPCSIZEY + NPCSIZEY);
		}
	}

	//오른쪽 오브젝트 장애물 및 포탈 셋업
	for (int i = 0; i < OBJTILEY; ++i)
	{
		for (int j = 0; j < OBJTILEX; ++j)
		{
			_OBJTile[i*OBJTILEX + j].terrainFrameX = j;
			_OBJTile[i*OBJTILEX + j].terrainFrameY = i;

			SetRect(&_OBJTile[i * OBJTILEX + j].rcTile,
				(WINSIZEX - IMAGEMANAGER->findImage("object")->getWidth()) + j * OBJSIZEX,
				i * OBJSIZEY,
				(WINSIZEX - IMAGEMANAGER->findImage("object")->getWidth()) + j * OBJSIZEX + OBJSIZEX,
				i * OBJSIZEY + OBJSIZEY);
		}
	}

	//오른쪽 오브젝트 몬스터 리스폰 구역 셋업
	_respondTile.terrainFrameX = _respondTile.terrainFrameY = 3;
	SetRect(&_respondTile.rcTile,
		(WINSIZEX - IMAGEMANAGER->findImage("object")->getWidth()) - IMAGEMANAGER->findImage("respond")->getWidth(),
		0, WINSIZEX - IMAGEMANAGER->findImage("object")->getWidth(), IMAGEMANAGER->findImage("respond")->getHeight());

	/*
	struct tagTile
	{
	POINT point[4]; //피티인리젼을 쓰기 위한 포인트 배열
	int calibrateX, calibrateY; // iso 기준 좌표
	float renderX, renderY; //그려주기 위한 X, Y좌표
	TERRAIN terrain;
	OBJECT	obj;
	//RECT	rc;
	int terrainFrameX;
	int terrainFrameY;
	int objFrameX;
	int objFrameY;
	};
	*/
	//왼쪽 타일영역
	for (int i = 0; i < ISOTILEY; ++i)
	{
		for (int j = 0; j < ISOTILEX; ++j)
		{
			_tiles[i*ISOTILEX + j].calibrateX = -(ISOTILESIZEX / 2) * i + (ISOTILESIZEX / 2) * j;
			_tiles[i*ISOTILEX + j].calibrateY = (ISOTILESIZEY / 2) * i + (ISOTILESIZEY / 2) * j;
			//_tiles[i*ISOTILEX + j].renderX = WINSIZEX / 2 + _tiles[i*ISOTILEX + j].calibrateX;
			_tiles[i*ISOTILEX + j].x = TILEWINSIZEX / 2 + _tiles[i*ISOTILEX + j].calibrateX;
			_tiles[i*ISOTILEX + j].y = _tiles[i*ISOTILEX + j].calibrateY;
			_tiles[i*ISOTILEX + j].renderPoint = PointMake(_tiles[i*ISOTILEX + j].x - ISOTILESIZEX / 2,
				_tiles[i*ISOTILEX + j].y);

			//ptInRgn
			_tiles[i*ISOTILEX + j].point[0] = PointMake(_tiles[i*ISOTILEX + j].x, _tiles[i*ISOTILEX + j].y);
			_tiles[i*ISOTILEX + j].point[1] = PointMake(_tiles[i*ISOTILEX + j].x - ISOTILESIZEX / 2, _tiles[i*ISOTILEX + j].y + ISOTILESIZEY / 2);
			_tiles[i*ISOTILEX + j].point[3] = PointMake(_tiles[i*ISOTILEX + j].x + ISOTILESIZEX / 2, _tiles[i*ISOTILEX + j].y + ISOTILESIZEY / 2);
			_tiles[i*ISOTILEX + j].point[2] = PointMake(_tiles[i*ISOTILEX + j].x, _tiles[i*ISOTILEX + j].y + ISOTILESIZEY);

			_tiles[i*ISOTILEX + j].terrainFrameX = TILEDEFAULTX;
			_tiles[i*ISOTILEX + j].terrainFrameY = TILEDEFAULTY;
			_tiles[i*ISOTILEX + j].objFrameX = 0;
			_tiles[i*ISOTILEX + j].objFrameY = 0;
			_tiles[i*ISOTILEX + j].terrain = terrainSelect(_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
			_tiles[i*ISOTILEX + j].obj = OBJ_NONE;
			_tiles[i*ISOTILEX + j].pos = POS_NONE;
		}
	}


	////타일 영역
	//for ( int i = 0; i < TILEY; ++i )
	//{
	//	for ( int j = 0; j < TILEX; ++j )
	//	{
	//		SetRect(&_tiles[i * TILEX + j].rc,
	//			j * TILESIZE,
	//			i * TILESIZE,
	//			j * TILESIZE + TILESIZE,
	//			i * TILESIZE + TILESIZE);
	//	}
	//}

	//기본적으로 셋팅해놓을 타일은 잔디 타일이다
	/*for ( int i = 0; i < TILEX * TILEY; ++i )
	{
	_tiles[i].terrainFrameX = TILEDEFAULTX;
	_tiles[i].terrainFrameY = TILEDEFAULTY;
	_tiles[i].objFrameX = 0;
	_tiles[i].objFrameY = 0;
	_tiles[i].terrain = terrainSelect(_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
	_tiles[i].obj = OBJ_NONE;
	}*/
}

void maptoolScene::setMap()
{
	for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; ++i)
	{
		if (PtInRect(&_sampleTile[i].rcTile, _ptMouse))
		{
			_currentTile.x = _sampleTile[i].terrainFrameX;
			_currentTile.y = _sampleTile[i].terrainFrameY;
			break;
		}
	}
	//for ( int i = 0; i < TILEX * TILEY; ++i )
	if (0 < _ptMouse.x && _ptMouse.x < TILEWINSIZEX && 0 < _ptMouse.y &&  _ptMouse.y <TILEWINSIZEY)
	{
		for (int i = 0; i < ISOTILEX * ISOTILEY; ++i)
		{
			RECT temp;

			RECT tempCameraRC = RectMake(MAPTOOLCAMERAMANAGER->CameraRelativePoint(_cameraRC).x,
				MAPTOOLCAMERAMANAGER->CameraRelativePoint(_cameraRC).y,
				TILEWINSIZEX, TILEWINSIZEY);

			RECT tempTileRC = RectMake(MAPTOOLCAMERAMANAGER->CameraRelativePoint(_tiles[i].renderPoint).x,
				MAPTOOLCAMERAMANAGER->CameraRelativePoint(_tiles[i].renderPoint).y,
				IMAGEMANAGER->findImage("mapTiles")->getFrameWidth(), IMAGEMANAGER->findImage("mapTiles")->getFrameHeight());

			if (!IntersectRect(&temp, &tempCameraRC, &tempTileRC)) continue;
			POINT tempPoint[4];
			//if ( PtInRect(&_tiles[i].rc, _ptMouse) )
			for (int j = 0; j < 4; ++j)
			{
				tempPoint[j] = MAPTOOLCAMERAMANAGER->CameraRelativePoint(_tiles[i].point[j]);
			}
			HRGN rgn = CreatePolygonRgn(tempPoint, 4, 1);
			//HRGN rgn = CreatePolygonRgn(_tiles[i].point, 4, 1);
			if (PtInRegion(rgn, _ptMouse.x, _ptMouse.y))
				//if (PtInRegion(rgn, MAPTOOLCAMERAMANAGER->CameraRelativePointX(_ptMouse.x), MAPTOOLCAMERAMANAGER->CameraRelativePointY(_ptMouse.y)))
			{
				if (_buttonType == BTN_TERRAIN)
				{
					_tiles[i].terrainFrameX = _currentTile.x;
					_tiles[i].terrainFrameY = _currentTile.y;

					_tiles[i].terrain = terrainSelect(_currentTile.x, _currentTile.y);
				}/*
				else if (_ctrSelect == CTRL_OBJDRAW)
				{
					_tiles[i].objFrameX = _currentTile.x;
					_tiles[i].objFrameY = _currentTile.y;

					_tiles[i].obj = objSelect(_currentTile.x, _currentTile.y);
				}*/
				else if (_buttonType == BTN_ERASER_TERRAIN)
				{
					//타일의 기본 속성(기본속성이 바뀌면 이분도 바뀌어야함
					_tiles[i].terrainFrameX = TILEDEFAULTX;
					_tiles[i].terrainFrameY = TILEDEFAULTY;

					//오브젝트의 기본 속성
					/*_tiles[i].objFrameX = NULL;
					_tiles[i].objFrameY = NULL;

					_tiles[i].obj = OBJ_NONE;*/
					_tiles[i].terrain = TILEDEFAULTTERRAIN;
				}

				InvalidateRect(_hWnd, NULL, false);
				break;
			}

			DeleteObject(rgn);
		}
	}

	/*else{
	for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; ++i)
	{
	if (PtInRect(&_sampleTile[i].rcTile, _ptMouse))
	{
	_currentTile.x = _sampleTile[i].terrainFrameX;
	_currentTile.y = _sampleTile[i].terrainFrameY;
	break;
	}
	}
	}*/

}

void maptoolScene::setNPC()
{
	for (int i = 0; i < NPCTILEX * NPCTILEY; ++i)
	{
		if (PtInRect(&_NPCTile[i].rcTile, _ptMouse))
		{
			_currentTile.x = _NPCTile[i].terrainFrameX;
			_currentTile.y = _NPCTile[i].terrainFrameY;
			break;
		}
	}
	//for ( int i = 0; i < TILEX * TILEY; ++i )
	if (0 < _ptMouse.x && _ptMouse.x < TILEWINSIZEX && 0 < _ptMouse.y &&  _ptMouse.y <TILEWINSIZEY)
	{
		for (int i = 0; i < ISOTILEX * ISOTILEY; ++i)
		{
			RECT temp;

			RECT tempCameraRC = RectMake(MAPTOOLCAMERAMANAGER->CameraRelativePoint(_cameraRC).x,
				MAPTOOLCAMERAMANAGER->CameraRelativePoint(_cameraRC).y,
				TILEWINSIZEX, TILEWINSIZEY);

			RECT tempTileRC = RectMake(MAPTOOLCAMERAMANAGER->CameraRelativePoint(_tiles[i].renderPoint).x,
				MAPTOOLCAMERAMANAGER->CameraRelativePoint(_tiles[i].renderPoint).y,
				IMAGEMANAGER->findImage("NPC")->getFrameWidth(), IMAGEMANAGER->findImage("NPC")->getFrameHeight());

			if (!IntersectRect(&temp, &tempCameraRC, &tempTileRC)) continue;
			POINT tempPoint[4];
			//if ( PtInRect(&_tiles[i].rc, _ptMouse) )
			for (int j = 0; j < 4; ++j)
			{
				tempPoint[j] = MAPTOOLCAMERAMANAGER->CameraRelativePoint(_tiles[i].point[j]);
			}
			HRGN rgn = CreatePolygonRgn(tempPoint, 4, 1);
			//HRGN rgn = CreatePolygonRgn(_tiles[i].point, 4, 1);
			if (PtInRegion(rgn, _ptMouse.x, _ptMouse.y))
				//if (PtInRegion(rgn, MAPTOOLCAMERAMANAGER->CameraRelativePointX(_ptMouse.x), MAPTOOLCAMERAMANAGER->CameraRelativePointY(_ptMouse.y)))
			{
				if (_buttonType == BTN_NPC)
				{
					_tiles[i].objFrameX = _currentTile.x;
					_tiles[i].objFrameY = _currentTile.y;

					_tiles[i].obj = objSelect(_currentTile.x, _currentTile.y);
					_tiles[i].pos = posSelect(_currentTile.x, _currentTile.y);
				}
				else if (_buttonType == BTN_ERASER_NPC)
				{
					//타일의 기본 속성(기본속성이 바뀌면 이분도 바뀌어야함
					/*_tiles[i].terrainFrameX = TILEDEFAULTX;
					_tiles[i].terrainFrameY = TILEDEFAULTY;*/

					//오브젝트의 기본 속성
					_tiles[i].objFrameX = NULL;
					_tiles[i].objFrameY = NULL;

					_tiles[i].obj = OBJ_NONE;
					//_tiles[i].terrain = TILEDEFAULTTERRAIN;
				}

				InvalidateRect(_hWnd, NULL, false);
				break;
			}

			DeleteObject(rgn);
		}
	}
}

void maptoolScene::setOBJ(){
	for (int i = 0; i < OBJTILEX * OBJTILEY; ++i)
	{
		if (PtInRect(&_OBJTile[i].rcTile, _ptMouse))
		{
			_currentTile.x = _OBJTile[i].terrainFrameX;
			_currentTile.y = _OBJTile[i].terrainFrameY;
			break;
		}
	}
	if (PtInRect(&_respondTile.rcTile, _ptMouse))
	{
		_currentTile.x = _respondTile.terrainFrameX;
		_currentTile.y = _respondTile.terrainFrameY;
	}
	//for ( int i = 0; i < TILEX * TILEY; ++i )
	if (0 < _ptMouse.x && _ptMouse.x < TILEWINSIZEX && 0 < _ptMouse.y &&  _ptMouse.y <TILEWINSIZEY)
	{
		//if (_currentTile.x == 3 && _currentTile.y == 3)
		//{
		//	for (int i = 0; i < ISOTILEX * ISOTILEY; ++i)
		//	{
		//		RECT temp;

		//		RECT tempCameraRC = RectMake(MAPTOOLCAMERAMANAGER->CameraRelativePoint(_cameraRC).x,
		//			MAPTOOLCAMERAMANAGER->CameraRelativePoint(_cameraRC).y,
		//			TILEWINSIZEX, TILEWINSIZEY);

		//		RECT tempTileRC = RectMake(MAPTOOLCAMERAMANAGER->CameraRelativePoint(_tiles[i].renderPoint).x,
		//			MAPTOOLCAMERAMANAGER->CameraRelativePoint(_tiles[i].renderPoint).y,
		//			IMAGEMANAGER->findImage("respond")->getFrameWidth(), IMAGEMANAGER->findImage("respond")->getFrameHeight());

		//		if (!IntersectRect(&temp, &tempCameraRC, &tempTileRC)) continue;
		//		POINT tempPoint[4];

		//		for (int j = 0; j < 4; ++j)
		//		{
		//			tempPoint[j] = MAPTOOLCAMERAMANAGER->CameraRelativePoint(_tiles[i].point[j]);
		//		}
		//		HRGN rgn = CreatePolygonRgn(tempPoint, 4, 1);
		//		//HRGN rgn = CreatePolygonRgn(_tiles[i].point, 4, 1);
		//		if (PtInRegion(rgn, _ptMouse.x, _ptMouse.y))
		//			//if (PtInRegion(rgn, MAPTOOLCAMERAMANAGER->CameraRelativePointX(_ptMouse.x), MAPTOOLCAMERAMANAGER->CameraRelativePointY(_ptMouse.y)))
		//		{
		//			if (_buttonType == BTN_OBJECT)
		//			{
		//				//풀은 2칸을 차지하므로 더비상태면 앞타일이 풀이므로 그려지면 안됨
		//				if (_tiles[i].obj == OBJ_GRASS_DUMMY) return;
		//				//풀과 마찬가지로 포탈 더비면 ㄴㄴ
		//				if (_tiles[i].obj == OBJ_POTAL_DUMMY) return;
		//				//풀은 2칸인데 x축(iso기준) 끝이면 풀 그리지 마라
		//				if ((i % ISOTILEX) == 19 && objSelect(_currentTile.x, _currentTile.y) == OBJ_GRASS) return;
		//				//포탈도 같은 예외처리
		//				if (((i % ISOTILEX) == 19 || (i / ISOTILEX) == 19) && objSelect(_currentTile.x, _currentTile.y) == OBJ_POTAL) return;

		//				//현제 오브젝트가 풀인데 거기에 풀 외에 다른걸로 덮는다면
		//				if (_tiles[i].obj == OBJ_GRASS && objSelect(_currentTile.x, _currentTile.y) != OBJ_GRASS) _tiles[i + 1].obj = OBJ_NONE;
		//				//포탈 또한 동일하게
		//				if (_tiles[i].obj == OBJ_POTAL && objSelect(_currentTile.x, _currentTile.y) != OBJ_POTAL)
		//				{
		//					_tiles[i + 1].obj = _tiles[i + ISOTILEX].obj = _tiles[i + ISOTILEX + 1].obj = OBJ_NONE;
		//				}

		//				_tiles[i].objFrameX = _currentTile.x;
		//				_tiles[i].objFrameY = _currentTile.y;

		//				_tiles[i].obj = objSelect(_currentTile.x, _currentTile.y);

		//				if (objSelect(_currentTile.x, _currentTile.y) == OBJ_GRASS)
		//					_tiles[i + 1].obj = OBJ_GRASS_DUMMY;

		//				if (objSelect(_currentTile.x, _currentTile.y) == OBJ_POTAL)
		//				{
		//					_tiles[i + 1].obj = OBJ_POTAL_DUMMY;
		//					_tiles[i + ISOTILEX].obj = OBJ_POTAL_DUMMY;
		//					_tiles[i + ISOTILEX + 1].obj = OBJ_POTAL_DUMMY;
		//				}
		//			}
		//			else if (_buttonType == BTN_ERASER_OBJECT)
		//			{
		//				//타일의 기본 속성(기본속성이 바뀌면 이분도 바뀌어야함
		//				/*_tiles[i].terrainFrameX = TILEDEFAULTX;
		//				_tiles[i].terrainFrameY = TILEDEFAULTY;*/

		//				//더비타일을 지울려고 하면 불가능하다.
		//				if (_tiles[i].obj == OBJ_GRASS_DUMMY
		//					|| _tiles[i].obj == OBJ_POTAL_DUMMY) return;

		//				//오브젝트의 기본 속성
		//				_tiles[i].objFrameX = NULL;
		//				_tiles[i].objFrameY = NULL;

		//				//지울 타일이 풀이면 그 다음 타일의 속성도 논속성으로
		//				if (_tiles[i].obj == OBJ_GRASS) _tiles[i + 1].obj = OBJ_NONE;
		//				//포탈 또한 동일하게 지우기
		//				if (_tiles[i].obj == OBJ_POTAL)
		//				{
		//					_tiles[i + 1].obj = _tiles[i + ISOTILEX].obj = _tiles[i + ISOTILEX + 1].obj = OBJ_NONE;
		//				}

		//				_tiles[i].obj = OBJ_NONE;
		//				//_tiles[i].terrain = TILEDEFAULTTERRAIN;
		//			}

		//			InvalidateRect(_hWnd, NULL, false);
		//			break;
		//		}

		//		DeleteObject(rgn);
		//	}
		//	
		//}
		//else
		//{
			for (int i = 0; i < ISOTILEX * ISOTILEY; ++i)
			{
				RECT temp;

				RECT tempCameraRC = RectMake(MAPTOOLCAMERAMANAGER->CameraRelativePoint(_cameraRC).x,
					MAPTOOLCAMERAMANAGER->CameraRelativePoint(_cameraRC).y,
					TILEWINSIZEX, TILEWINSIZEY);

				RECT tempTileRC = RectMake(MAPTOOLCAMERAMANAGER->CameraRelativePoint(_tiles[i].renderPoint).x,
					MAPTOOLCAMERAMANAGER->CameraRelativePoint(_tiles[i].renderPoint).y,
					IMAGEMANAGER->findImage("object")->getFrameWidth(), IMAGEMANAGER->findImage("object")->getFrameHeight());

				if (!IntersectRect(&temp, &tempCameraRC, &tempTileRC)) continue;
				POINT tempPoint[4];
				//if ( PtInRect(&_tiles[i].rc, _ptMouse) )
				for (int j = 0; j < 4; ++j)
				{
					tempPoint[j] = MAPTOOLCAMERAMANAGER->CameraRelativePoint(_tiles[i].point[j]);
				}
				HRGN rgn = CreatePolygonRgn(tempPoint, 4, 1);
				//HRGN rgn = CreatePolygonRgn(_tiles[i].point, 4, 1);
				if (PtInRegion(rgn, _ptMouse.x, _ptMouse.y))
					//if (PtInRegion(rgn, MAPTOOLCAMERAMANAGER->CameraRelativePointX(_ptMouse.x), MAPTOOLCAMERAMANAGER->CameraRelativePointY(_ptMouse.y)))
				{
					if (_buttonType == BTN_OBJECT)
					{
						//풀은 2칸을 차지하므로 더비상태면 앞타일이 풀이므로 그려지면 안됨
						if (_tiles[i].obj == OBJ_GRASS_DUMMY) return;
						//풀과 마찬가지로 포탈 더비면 ㄴㄴ
						if (_tiles[i].obj == OBJ_POTAL_DUMMY) return;
						//풀은 2칸인데 x축(iso기준) 끝이면 풀 그리지 마라
						if ((i % ISOTILEX) == 19 && objSelect(_currentTile.x, _currentTile.y) == OBJ_GRASS) return;
						//포탈도 같은 예외처리
						if (((i % ISOTILEX) == 19 || (i / ISOTILEX) == 19) && objSelect(_currentTile.x, _currentTile.y) == OBJ_POTAL) return;

						//현제 오브젝트가 풀인데 거기에 풀 외에 다른걸로 덮는다면
						if (_tiles[i].obj == OBJ_GRASS && objSelect(_currentTile.x, _currentTile.y) != OBJ_GRASS) _tiles[i + 1].obj = OBJ_NONE;
						//포탈 또한 동일하게
						if (_tiles[i].obj == OBJ_POTAL && objSelect(_currentTile.x, _currentTile.y) != OBJ_POTAL)
						{
							_tiles[i + 1].obj = _tiles[i + ISOTILEX].obj = _tiles[i + ISOTILEX + 1].obj = OBJ_NONE;
						}

						_tiles[i].objFrameX = _currentTile.x;
						_tiles[i].objFrameY = _currentTile.y;

						_tiles[i].obj = objSelect(_currentTile.x, _currentTile.y);

						if (objSelect(_currentTile.x, _currentTile.y) == OBJ_GRASS)
							_tiles[i + 1].obj = OBJ_GRASS_DUMMY;

						if (objSelect(_currentTile.x, _currentTile.y) == OBJ_POTAL)
						{
							_tiles[i + 1].obj = OBJ_POTAL_DUMMY;
							_tiles[i + ISOTILEX].obj = OBJ_POTAL_DUMMY;
							_tiles[i + ISOTILEX + 1].obj = OBJ_POTAL_DUMMY;
						}
					}
					else if (_buttonType == BTN_ERASER_OBJECT)
					{
						//타일의 기본 속성(기본속성이 바뀌면 이분도 바뀌어야함
						/*_tiles[i].terrainFrameX = TILEDEFAULTX;
						_tiles[i].terrainFrameY = TILEDEFAULTY;*/

						//더비타일을 지울려고 하면 불가능하다.
						if (_tiles[i].obj == OBJ_GRASS_DUMMY
							|| _tiles[i].obj == OBJ_POTAL_DUMMY) return;

						//오브젝트의 기본 속성
						_tiles[i].objFrameX = NULL;
						_tiles[i].objFrameY = NULL;

						//지울 타일이 풀이면 그 다음 타일의 속성도 논속성으로
						if (_tiles[i].obj == OBJ_GRASS) _tiles[i + 1].obj = OBJ_NONE;
						//포탈 또한 동일하게 지우기
						if (_tiles[i].obj == OBJ_POTAL)
						{
							_tiles[i + 1].obj = _tiles[i + ISOTILEX].obj = _tiles[i + ISOTILEX + 1].obj = OBJ_NONE;
						}

						_tiles[i].obj = OBJ_NONE;
						//_tiles[i].terrain = TILEDEFAULTTERRAIN;
					}

					InvalidateRect(_hWnd, NULL, false);
					break;
				}

				DeleteObject(rgn);
			}
		
	}
}

void maptoolScene::save()
{
	if (!strcmp(_savePath, _basePath)) return;
	//if (_savePath == NULL) return;

	HANDLE file;
	DWORD write;

	//char* str = getMemDC();

	file = CreateFile(_savePath, GENERIC_WRITE, FALSE, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, _tiles, sizeof(_tiles), &write, NULL);

	CloseHandle(file);
}

void maptoolScene::load()
{
	if (!strcmp(_savePath, _basePath)) return;

	HANDLE file;
	DWORD read;



	file = CreateFile(_savePath, GENERIC_READ, FALSE, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(_tiles), &read, NULL);

	CloseHandle(file);
}


//0 : 왼, 1 : 위, 2 : 오, 3 : 아
void maptoolScene::mouseMove(int direction)
{
	switch (direction)
	{
		//왼
	case 0:
		if (_cameraRC.left > -(TILESIZEX / 2)){
			_cameraRC.right -= 3;
			_cameraRC.left = _cameraRC.right - TILEWINSIZEX;
		}
		break;

		//위
	case 1:
		if (_cameraRC.top > 0)
		{
			_cameraRC.top -= 3;
			_cameraRC.bottom = _cameraRC.top + TILEWINSIZEY;
		}
		break;

		//오
	case 2:
		if (_cameraRC.right < (TILESIZEX / 2 + TILESIZEX / 4))
		{
			_cameraRC.right += 3;
			_cameraRC.left = _cameraRC.right - TILEWINSIZEX;
		}
		break;

		//아래
	case 3:
		if (_cameraRC.bottom < TILESIZEY)
		{
			_cameraRC.top += 3;
			_cameraRC.bottom = _cameraRC.top + TILEWINSIZEY;
		}
		break;
	default:
		break;
	}
}


TERRAIN maptoolScene::terrainSelect(int frameX, int frameY)
{
	//물 뺴고 다 갈수 있으므로 솔직히 두개만 있어도 충분함
	//타일에 따른 함정같은게 없으므로 
	if (frameX == 2 && frameY == 1)
		return TR_WATER;

	return TR_CEMENT;
}

OBJECT maptoolScene::objSelect(int frameX, int frameY)
{
	/*
	//NPC
	OBJ_MUSURI, OBJ_HOSULAM, OBJ_JANGGUMI, 
	//오브젝트
	OBJ_TREE, OBJ_GRASS, OBJ_GRASS_DUMMY,
	OBJ_NONE
	/*OBJ_BLOCK1, OBJ_BLOCK3, OBJ_BLOCKS,
	OBJ_FLAG1, OBJ_FLAG2,
	OBJ_TANK1, OBJ_TANK2, OBJ_NONE*/
	if (_buttonType == BTN_NPC)
	{
		if (frameX == 0 && frameY == 0)
			return OBJ_MUSURI;

		else if (frameX == 1 && frameY == 0)
			return OBJ_HOSULAM;

		else if (frameX == 2 && frameY == 0)
			return OBJ_JANGGUMI;
	}
	else if (_buttonType == BTN_OBJECT)
	{
		if (frameX == 0 && frameY == 0)
			return OBJ_TREE;
		else if (frameX == 0 && frameY == 1)
			return OBJ_GRASS;
		else if (frameX == 0 && frameY == 2)
			return OBJ_POTAL;
		else if (frameX == 3 && frameY == 3)
			return OBJ_RESPOND;
	}
	return OBJ_NONE;
	//if (frameX == 0 && frameY == 0)
	//{
	//	return OBJ_TANK1;
	//}
	//else if (frameX == 0 && frameY == 8)
	//{
	//	return OBJ_TANK2;
	//}
	//else if (frameX == 0 && frameY == 1)
	//{
	//	return OBJ_BLOCK1;
	//}
	//else if (frameX == 0 && frameY == 2)
	//{
	//	return OBJ_BLOCK3;
	//}
	//else if (frameX == 15 && frameY == 3)
	//{
	//	return OBJ_BLOCKS;
	//}

	//return OBJ_BLOCK1;
}

POS	maptoolScene::posSelect(int frameX, int frameY){
	if (frameX == 0 && frameY == 0)
		return POS_MUSURI;

	else if (frameX == 1 && frameY == 0)
		return POS_HOSULAM;

	else if (frameX == 2 && frameY == 0)
		return POS_JANGGUMI;

	return POS_NONE;
	/*
	POS_MUSURI, POS_HOSULAM, POS_JANGGUMI, POS_NONE
	//POS_MUSURI, POS_HOSULAM
	*/
}