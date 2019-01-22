#include "stdafx.h"
#include "gameScene.h"
#include "character.h"

gameScene::gameScene()
{
}


gameScene::~gameScene()
{

}

HRESULT gameScene::init()
{
	IMAGEMANAGER->addFrameImage("mapTiles", "./image/tile/Ÿ��.bmp", 210, 140, SAMPLETILEX, SAMPLETILEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("object", "./image/object/object.bmp", 142, 393, OBJTILEX, OBJTILEY, true, RGB(255, 0, 255));
	townLoad();
	huntingLoad();
	

	_playPlayer->setCurrentPlaceTile(_townTiles);
	_playPlayer->setCurrentPlaceAttribute(_townAttribute);

	_playPlayer->makeRC();

//	_cameraRC = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 100, 100);
	_cameraRC = RectMakeCenter(_playPlayer->getRC().left + (_playPlayer->getRC().right - _playPlayer->getRC().left) / 2,
		_playPlayer->getRC().top + (_playPlayer->getRC().bottom - _playPlayer->getRC().top) / 2,
		100, 100);


	CAMERAMANAGER->setCameraCondition(CAMERA_AIMING);
	//CAMERAMANAGER->setCameraAim(&_cameraRC);
	//_cameraRC = &_playPlayer->getRC();
	CAMERAMANAGER->setCameraAim(&_cameraRC);

	_itemManager = new itemManager;
	_itemManager->init();

	_playPlayer->getInven()->setIMMemoryAdressLink(_itemManager);

	_hosulam = new hosulam;
	_hosulam->setItemManagerAddressLink(_itemManager);
	_hosulam->setInventoryAddressLink(_playPlayer->getInven());
	_hosulam->init(PointMake(_townTiles[_posNPC[POS_HOSULAM]].getCenterPoint().x,_townTiles[_posNPC[POS_HOSULAM]].getCenterPoint().y));
	//_hosulam->init(PointMake(CAMERAMANAGER->CameraRelativePointX(_townTiles[_posNPC[POS_HOSULAM]].getCenterPoint().x),
	//	CAMERAMANAGER->CameraRelativePointY(_townTiles[_posNPC[POS_HOSULAM]].getCenterPoint().y)));

	_musuri = new musuri;
	_musuri->setItemManagerAddressLink(_itemManager);
	_musuri->setInventoryAddressLink(_playPlayer->getInven());
	_musuri->init(PointMake(_townTiles[_posNPC[POS_MUSURI]].getCenterPoint().x, _townTiles[_posNPC[POS_MUSURI]].getCenterPoint().y));
	//_musuri->init(PointMake(CAMERAMANAGER->CameraRelativePointX(_townTiles[_posNPC[POS_MUSURI]].getCenterPoint().x),
	//	CAMERAMANAGER->CameraRelativePointY(_townTiles[_posNPC[POS_MUSURI]].getCenterPoint().y)));

	_janggumi = new janggumi;
	_janggumi->setItemManagerAddressLink(_itemManager);
	_janggumi->setInventoryAddressLink(_playPlayer->getInven());
	_janggumi->init(PointMake(_townTiles[_posNPC[POS_JANGGUMI]].getCenterPoint().x, _townTiles[_posNPC[POS_JANGGUMI]].getCenterPoint().y));

	_monsterManager = new monsterManager;
	_monsterManager->init(_vHuntingRespond, _huntingTiles, _huntingAttribut);

	_UI = new UI;
	_UI->init(_playPlayer->getMaxHP(), _playPlayer->getCurrentHP(), _playPlayer->getMaxMP(), _playPlayer->getCurrentMP()
		, _playPlayer->getLevel(), _playPlayer->getExp());
	//_aStarTest = new aStar;
	//_aStarTest->init(_townTiles);
	

	//_janggumi->init(PointMake(CAMERAMANAGER->CameraRelativePointX(_townTiles[_posNPC[POS_JANGGUMI]].getCenterPoint().x),
	//	CAMERAMANAGER->CameraRelativePointY(_townTiles[_posNPC[POS_JANGGUMI]].getCenterPoint().y)));

	SOUNDMANAGER->stop("ĳ��");
	//���̸� �����
	if (_playPlayer->getPlayerPlace())
	{
		strcpy(_musicStr, "�����");
		
	}
	//�����̸� ����
	else
	{
		strcpy(_musicStr, "����");
		//SOUNDMANAGER->play("����");
	}
	SOUNDMANAGER->play(_musicStr);
	return S_OK;
	//huntingLoad();}
}
void gameScene::release()
{

}
void gameScene::update()
{
	//�÷��̾� �ǰ� 0�̸� ���
	if (*_playPlayer->getCurrentHP() <= 0)
	{
		//��������ε� �뷡���� ����� �ƴϸ� ��������� �ٲٰ�
		if (strcmp(_musicStr, "���"))
		{
			SOUNDMANAGER->stop(_musicStr);
			strcpy(_musicStr, "���");
			SOUNDMANAGER->play(_musicStr);
		}
		//������� ������ ��Ȱ
		if (!SOUNDMANAGER->isPlaySound(_musicStr))
		{
			//������Ұ� ����͸�
			if (_playPlayer->getPlayerPlace())
				strcpy(_musicStr, "�����");
			//�����̸�(��ǻ� �Ұ���)
			else strcpy(_musicStr, "����");
			//���ڸ� ��Ȱ
			_playPlayer->reborn();
			
		}
	}
	//���̸� �����
	else if (_playPlayer->getPlayerPlace())
	{
		if (!strcmp(_musicStr, "����") || !strcmp(_musicStr, "����1") || !strcmp(_musicStr, "����2"))
		{
			SOUNDMANAGER->stop(_musicStr);
			strcpy(_musicStr, "�����");
			SOUNDMANAGER->play(_musicStr);
		}
		if (!SOUNDMANAGER->isPlaySound(_musicStr))
		{
			//���������� �����̶� ���Ͽ� ���� ���ڿ��̸�
			if (!strcmp(_musicStr, "�����"))
			{
				//sprintf(test111, "%s �����", _musicStr);
				strcpy(_musicStr, "�����1");
			}
			else if (!strcmp(_musicStr, "�����1"))
			{
				//sprintf(test111, );
				strcpy(_musicStr, "�����");
			}
			SOUNDMANAGER->play(_musicStr);
		}
		////����� �뷡�� ������ �����1 �뷡
		//if (!SOUNDMANAGER->isPlaySound("�����")) SOUNDMANAGER->play("�����1");
		////�����1 �뷡 ������ ����� �뷡
		//else if (!SOUNDMANAGER->isPlaySound("�����1")) SOUNDMANAGER->play("�����");
	}
	//�����̸� ����
	else
	{
		if (!strcmp(_musicStr, "�����") || !strcmp(_musicStr, "�����1"))
		{
			SOUNDMANAGER->stop(_musicStr);
			strcpy(_musicStr, "����");
			SOUNDMANAGER->play(_musicStr);
		}
		//������� ������ �ʴ´ٸ� ������ Ʋ���
		if (!SOUNDMANAGER->isPlaySound(_musicStr))
		{
			//���������� �����̶� ���Ͽ� ���� ���ڿ��̸�
			if (!strcmp(_musicStr, "����"))
			{
				//sprintf(test111, "%s �����", _musicStr);
				strcpy(_musicStr, "����1");				
			}
			else if (!strcmp(_musicStr, "����1"))
			{
				//sprintf(test111, );
				strcpy(_musicStr, "����2");
			}
			else if (!strcmp(_musicStr, "����2"))
			{
				//sprintf(test111, );
				strcpy(_musicStr, "����");
			}
			SOUNDMANAGER->play(_musicStr);
		}
		//if (!SOUNDMANAGER->isPlaySound("����")) SOUNDMANAGER->play("����1");
		////�����1 �뷡 ������ ����� �뷡
		//else if (!SOUNDMANAGER->isPlaySound("����1")) SOUNDMANAGER->play("����");
	}
	//���̸� ����� �����̸� ����
	if (_playPlayer->getClickPotal() && _playPlayer->getPlayerPlace())
	{

	//	SOUNDMANAGER->stop(_musicStr);
		_playPlayer->setCurrentPlaceTile(_huntingTiles);
		_playPlayer->setCurrentPlaceAttribute(_huntingAttribut);
		_playPlayer->setClickPotal(false);
		_playPlayer->setMonsterManagerAddressLink(_monsterManager);


		//_playPlayer->getPlayerAStar()->setTiles(_huntingTiles);
		//_playPlayer->getPlayerAStar()->init();
		//_aStarTest->setTiles(_huntingTiles);
	}
	else if (_playPlayer->getClickPotal() && !_playPlayer->getPlayerPlace())
	{

	//	SOUNDMANAGER->stop(_musicStr);
		_playPlayer->setCurrentPlaceTile(_townTiles);
		_playPlayer->setCurrentPlaceAttribute(_townAttribute);
		_playPlayer->setClickPotal(false);
		_playPlayer->setMonsterManagerAddressLink(NULL);


		//_playPlayer->getPlayerAStar()->setTiles(_townTiles);
		//_playPlayer->getPlayerAStar()->init();

		//_aStarTest->setTiles(_townTiles);
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		move(0);
	}
	else if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		move(1);
	}
	else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		move(2);

	}
	else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		move(3);
	}
	_playPlayer->update();

	_cameraRC = RectMakeCenter(_playPlayer->getRC().left + (_playPlayer->getRC().right - _playPlayer->getRC().left) / 2,
		_playPlayer->getRC().top + (_playPlayer->getRC().bottom - _playPlayer->getRC().top) / 2,
		100, 100);
	_hosulam->update();
	_musuri->update();
	_janggumi->update();

	if (_playPlayer->getHosulamNpcClick()){
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_hosulam->buyItem();
			_hosulam->sellItem();
			//�ߺ� ����ȴ� ���⼭ �����Լ� ����ϸ� �ɵ�
			//sprintf(test111, "����");
		}
	//	_hosulam->clickNpc();
	}
	else if (_playPlayer->getMusuriNpcClick()){
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_musuri->buyItem();
			_musuri->sellItem();
			//�ߺ� ����ȴ� ���⼭ �����Լ� ����ϸ� �ɵ�
			//sprintf(test111, "����");
		}
	}
	else if (_playPlayer->getJanggumiNpcClick()){
		//_janggumi->clickNpc();
	}
	else
	{
		_hosulam->setClickIndex(-1); _musuri->setClickIndex(-1); _janggumi->setClickIndex(-1);
	}
	_monsterManager->update();
	//if (_playPlayer->getRC().top < 0)
		//		//��
		//	case 0:
		//	/*	if (_cameraRC.left > -(TILESIZEX / 2)){
		//			_cameraRC.right -= 3;
		//			_cameraRC.left = _cameraRC.right - TILEWINSIZEX;
		//		}
		//*/
		//		if (_cameraRC.left > -(TILESIZEX / 2) + 450)
		//		{
		//			_cameraRC.right -= 3;
		//			_cameraRC.left = _cameraRC.right - 100;
		//		}
		//		break;
		//
		//		//��
		//	case 1:
		//		/*if (_cameraRC.top > 0)
		//		{
		//			_cameraRC.top -= 3;
		//			_cameraRC.bottom = _cameraRC.top + TILEWINSIZEY;
		//		}*/
		//
		//		_cameraRC.top -= 3;
		//		_cameraRC.bottom = _cameraRC.top + 100;
		//
		//		break;
		//
		//		//��
		//	case 2:
		//	/*	if (_cameraRC.right < (TILESIZEX / 2 + TILESIZEX / 4))
		//		{
		//			_cameraRC.right += 3;
		//			_cameraRC.left = _cameraRC.right - TILEWINSIZEX;
		//		}*/
		//		if (_cameraRC.right < (TILESIZEX / 2))
		//		{
		//			_cameraRC.right += 3;
		//			_cameraRC.left = _cameraRC.right - 100;
		//		}
		//
		//		break;
		//
		//		//�Ʒ�
		//	case 3:
		//		/*if (_cameraRC.bottom < TILESIZEY)
		//		{
		//			_cameraRC.top += 3;
		//			_cameraRC.bottom = _cameraRC.top + TILEWINSIZEY;
		//		}*/
		//		if (_cameraRC.bottom < TILESIZEY-250)
		//		{
		//			_cameraRC.top += 3;
		//			_cameraRC.bottom = _cameraRC.top + 100;
		//		}
}
void gameScene::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	tileDraw();

	//

	//Rectangle(getMemDC(), _cameraRC.left, _cameraRC.top, _cameraRC.right, _cameraRC.bottom);
	//if (KEYMANAGER->isToggleKey(VK_F1))
	//{
	//	RectangleMake(getMemDC(),
	//		CAMERAMANAGER->CameraRelativePoint(_cameraRC).x,
	//		CAMERAMANAGER->CameraRelativePoint(_cameraRC).y,
	//		100, 100);
	//}

	

	char test[128];
	//POINT tempPoint = _aStarTest->getNextTile();
	//sprintf(test, "%d, %d, %d, %d", _cameraRC.right, _cameraRC.bottom, _playPlayer->getRC().left, _playPlayer->getRC().top );
	//TextOut(getMemDC(), 300, 300, test, strlen(test));

	

	_playPlayer->render();
	//TextOut(getMemDC(), 300, 100, test111, strlen(test111));
	if (_playPlayer->getHosulamNpcClick()){
		_hosulam->clickNpc();
	}
	else if (_playPlayer->getMusuriNpcClick()){
		_musuri->clickNpc();
	}
	else if (_playPlayer->getJanggumiNpcClick()){
		_janggumi->clickNpc();
	}

	if (_playPlayer->getPlayerPlace())
	_monsterManager->render();

	_UI->render();
}

void gameScene::tileDraw(){
	if (!_playPlayer->getPlayerPlace())
	{
		for (int i = 0; i < ISOTILEX * ISOTILEY; ++i)
		{
			RECT temp;

			RECT tempCameraRC =
				RectMakeCenter(
				CAMERAMANAGER->CameraRelativePointX(_cameraRC.left + (_cameraRC.right - _cameraRC.left) / 2),
				CAMERAMANAGER->CameraRelativePointY(_cameraRC.top + (_cameraRC.bottom - _cameraRC.top) / 2),
				WINSIZEX, WINSIZEY);

			RECT tempTileRC = RectMake(CAMERAMANAGER->CameraRelativePoint(_townTiles[i].renderPoint).x,
				CAMERAMANAGER->CameraRelativePoint(_townTiles[i].renderPoint).y,
				IMAGEMANAGER->findImage("mapTiles")->getFrameWidth(), IMAGEMANAGER->findImage("mapTiles")->getFrameHeight());

			if (!IntersectRect(&temp, &tempCameraRC, &tempTileRC)) continue;

			////test++;

			IMAGEMANAGER->frameRender("mapTiles", getMemDC(),
				CAMERAMANAGER->CameraRelativePoint(_townTiles[i].renderPoint).x,
				CAMERAMANAGER->CameraRelativePoint(_townTiles[i].renderPoint).y,
				_townTiles[i].terrainFrameX, _townTiles[i].terrainFrameY,
				&tempCameraRC
				/*&RectMakeCenter(CAMERAMANAGER->CameraRelativePoint(_cameraRC).x,
				CAMERAMANAGER->CameraRelativePoint(PointMake(0, 0)).y,
				WINSIZEX, WINSIZEY)*/
				);

			//IMAGEMANAGER->frameRender("mapTiles", getMemDC(),
			//	_townTiles[i].renderPoint.x,
			//	_townTiles[i].renderPoint.y,
			//	_townTiles[i].terrainFrameX, _townTiles[i].terrainFrameY/*,
			//	&RectMake(CAMERAMANAGER->CameraRelativePoint(_cameraRC).x,
			//	CAMERAMANAGER->CameraRelativePoint(_cameraRC).y,
			//	WINSIZEX, WINSIZEY)*/
			//	);

			/*switch (_tiles[i].obj)
			{
			case OBJ_MUSURI:case OBJ_HOSULAM: case OBJ_JANGGUMI:
			IMAGEMANAGER->frameRender("NPC", getMemDC(),
			CAMERAMANAGER->CameraRelativePoint(_tiles[i].renderPoint).x + TILESIZE / 4,
			CAMERAMANAGER->CameraRelativePoint(_tiles[i].renderPoint).y - 5,
			_tiles[i].objFrameX, _tiles[i].objFrameY,
			&RectMake(CAMERAMANAGER->CameraRelativePoint(_cameraRC).x,
			CAMERAMANAGER->CameraRelativePoint(_cameraRC).y,
			WINSIZEX, WINSIZEY));
			break;


			default:
			break;
			}*/
		}


		npcDraw();
		townObjectDraw();
	}
	else
	{
		for (int i = 0; i < ISOTILEX * ISOTILEY; ++i)
		{
			RECT temp;

			RECT tempCameraRC =
				RectMakeCenter(
				CAMERAMANAGER->CameraRelativePointX(_cameraRC.left + (_cameraRC.right - _cameraRC.left) / 2),
				CAMERAMANAGER->CameraRelativePointY(_cameraRC.top + (_cameraRC.bottom - _cameraRC.top) / 2),
				WINSIZEX, WINSIZEY);

			RECT tempTileRC = RectMake(CAMERAMANAGER->CameraRelativePoint(_huntingTiles[i].renderPoint).x,
				CAMERAMANAGER->CameraRelativePoint(_huntingTiles[i].renderPoint).y,
				IMAGEMANAGER->findImage("mapTiles")->getFrameWidth(), IMAGEMANAGER->findImage("mapTiles")->getFrameHeight());

			if (!IntersectRect(&temp, &tempCameraRC, &tempTileRC)) continue;

			////test++;

			IMAGEMANAGER->frameRender("mapTiles", getMemDC(),
				CAMERAMANAGER->CameraRelativePoint(_huntingTiles[i].renderPoint).x,
				CAMERAMANAGER->CameraRelativePoint(_huntingTiles[i].renderPoint).y,
				_huntingTiles[i].terrainFrameX, _huntingTiles[i].terrainFrameY,
				&tempCameraRC
				/*&RectMakeCenter(CAMERAMANAGER->CameraRelativePoint(_cameraRC).x,
				CAMERAMANAGER->CameraRelativePoint(PointMake(0, 0)).y,
				WINSIZEX, WINSIZEY)*/
				);

			//IMAGEMANAGER->frameRender("mapTiles", getMemDC(),
			//	_townTiles[i].renderPoint.x,
			//	_townTiles[i].renderPoint.y,
			//	_townTiles[i].terrainFrameX, _townTiles[i].terrainFrameY/*,
			//	&RectMake(CAMERAMANAGER->CameraRelativePoint(_cameraRC).x,
			//	CAMERAMANAGER->CameraRelativePoint(_cameraRC).y,
			//	WINSIZEX, WINSIZEY)*/
			//	);

			/*switch (_tiles[i].obj)
			{
			case OBJ_MUSURI:case OBJ_HOSULAM: case OBJ_JANGGUMI:
			IMAGEMANAGER->frameRender("NPC", getMemDC(),
			CAMERAMANAGER->CameraRelativePoint(_tiles[i].renderPoint).x + TILESIZE / 4,
			CAMERAMANAGER->CameraRelativePoint(_tiles[i].renderPoint).y - 5,
			_tiles[i].objFrameX, _tiles[i].objFrameY,
			&RectMake(CAMERAMANAGER->CameraRelativePoint(_cameraRC).x,
			CAMERAMANAGER->CameraRelativePoint(_cameraRC).y,
			WINSIZEX, WINSIZEY));
			break;


			default:
			break;
			}*/
		}
		huntingObjectDraw();
	}
}

void gameScene::npcDraw(){
	//TextOut(getMemDC(), CAMERAMANAGER->CameraRelativePointX(_townTiles[_posNPC[POS_MUSURI]].getCenterPoint().x),
	//	CAMERAMANAGER->CameraRelativePointY(_townTiles[_posNPC[POS_MUSURI]].getCenterPoint().y),
	//	"������", strlen("������"));

	//TextOut(getMemDC(), CAMERAMANAGER->CameraRelativePointX(_townTiles[_posNPC[POS_HOSULAM]].getCenterPoint().x),
	//	CAMERAMANAGER->CameraRelativePointY(_townTiles[_posNPC[POS_HOSULAM]].getCenterPoint().y),
	//	"ȣ����", strlen("ȣ����"));

	//TextOut(getMemDC(), CAMERAMANAGER->CameraRelativePointX(_townTiles[_posNPC[POS_JANGGUMI]].getCenterPoint().x),
	//	CAMERAMANAGER->CameraRelativePointY(_townTiles[_posNPC[POS_JANGGUMI]].getCenterPoint().y),
	//	"�����", strlen("�����"));


	_hosulam->render();
	_musuri->render();
	_janggumi->render();
}

void gameScene::townObjectDraw()
{
	RECT tempCameraRC =
		RectMakeCenter(
		CAMERAMANAGER->CameraRelativePointX(_cameraRC.left + (_cameraRC.right - _cameraRC.left) / 2),
		CAMERAMANAGER->CameraRelativePointY(_cameraRC.top + (_cameraRC.bottom - _cameraRC.top) / 2),
		WINSIZEX, WINSIZEY);

	for (int i = 0; i < ISOTILEX * ISOTILEY; ++i)
	{
		/*
		RECT temp;

			RECT tempCameraRC =
				RectMakeCenter(
				CAMERAMANAGER->CameraRelativePointX(_cameraRC.left + (_cameraRC.right - _cameraRC.left) / 2),
				CAMERAMANAGER->CameraRelativePointY(_cameraRC.top + (_cameraRC.bottom - _cameraRC.top) / 2),
				WINSIZEX, WINSIZEY);

			RECT tempTileRC = RectMake(CAMERAMANAGER->CameraRelativePoint(_huntingTiles[i].renderPoint).x,
				CAMERAMANAGER->CameraRelativePoint(_huntingTiles[i].renderPoint).y,
				IMAGEMANAGER->findImage("mapTiles")->getFrameWidth(), IMAGEMANAGER->findImage("mapTiles")->getFrameHeight());

			if (!IntersectRect(&temp, &tempCameraRC, &tempTileRC)) continue;

			////test++;

			IMAGEMANAGER->frameRender("mapTiles", getMemDC(),
				CAMERAMANAGER->CameraRelativePoint(_huntingTiles[i].renderPoint).x,
				CAMERAMANAGER->CameraRelativePoint(_huntingTiles[i].renderPoint).y,
				_huntingTiles[i].terrainFrameX, _huntingTiles[i].terrainFrameY,
				&tempCameraRC*/
		//NPC���� ������ �׷��ش�.

	

		if (_townTiles[i].obj != OBJ_TREE && _townTiles[i].obj != OBJ_GRASS && _townTiles[i].obj != OBJ_POTAL) continue;

		if (_townTiles[i].obj == OBJ_TREE)
			IMAGEMANAGER->frameRender("object", getMemDC(),
			CAMERAMANAGER->CameraRelativePoint(_townTiles[i].renderPoint).x - IMAGEMANAGER->findImage("object")->getFrameWidth() / 4,
			CAMERAMANAGER->CameraRelativePoint(_townTiles[i].renderPoint).y - (IMAGEMANAGER->findImage("object")->getFrameHeight() / 4) * 2.5,
			_townTiles[i].objFrameX, _townTiles[i].objFrameY,
			&tempCameraRC
			/*&RectMake(CAMERAMANAGER->CameraRelativePoint(_cameraRC).x,
			CAMERAMANAGER->CameraRelativePoint(_cameraRC).y,
			TILEWINSIZEX, TILEWINSIZEY)*/);

		else if (_townTiles[i].obj == OBJ_GRASS)
			IMAGEMANAGER->frameRender("object", getMemDC(),
			CAMERAMANAGER->CameraRelativePoint(_townTiles[i].renderPoint).x - IMAGEMANAGER->findImage("object")->getFrameWidth() / 6,
			CAMERAMANAGER->CameraRelativePoint(_townTiles[i].renderPoint).y - (IMAGEMANAGER->findImage("object")->getFrameHeight() / 6) /** 2.5*/,
			_townTiles[i].objFrameX, _townTiles[i].objFrameY,
			&tempCameraRC
			/*&RectMake(CAMERAMANAGER->CameraRelativePoint(_cameraRC).x,
			CAMERAMANAGER->CameraRelativePoint(_cameraRC).y,
			TILEWINSIZEX, TILEWINSIZEY)*/);

		else if (_townTiles[i].obj == OBJ_POTAL)
			IMAGEMANAGER->frameRender("object", getMemDC(),
			CAMERAMANAGER->CameraRelativePoint(_townTiles[i].renderPoint).x - TILESIZE / 2, //- IMAGEMANAGER->findImage("object")->getFrameWidth() / 6,
			CAMERAMANAGER->CameraRelativePoint(_townTiles[i].renderPoint).y,//+TILESIZE / 2,//- (IMAGEMANAGER->findImage("object")->getFrameHeight() / 6) /** 2.5*/,
			_townTiles[i].objFrameX, _townTiles[i].objFrameY,
			&tempCameraRC
			/*&RectMake(CAMERAMANAGER->CameraRelativePoint(_cameraRC).x,
			CAMERAMANAGER->CameraRelativePoint(_cameraRC).y,
			TILEWINSIZEX, TILEWINSIZEY)*/);
	}
}
void gameScene::huntingObjectDraw()
{
	RECT tempCameraRC =
		RectMakeCenter(
		CAMERAMANAGER->CameraRelativePointX(_cameraRC.left + (_cameraRC.right - _cameraRC.left) / 2),
		CAMERAMANAGER->CameraRelativePointY(_cameraRC.top + (_cameraRC.bottom - _cameraRC.top) / 2),
		WINSIZEX, WINSIZEY);

	for (int i = 0; i < ISOTILEX * ISOTILEY; ++i)
	{
		//NPC���� ������ �׷��ش�.
		if (_huntingTiles[i].obj != OBJ_TREE && _huntingTiles[i].obj != OBJ_GRASS && _huntingTiles[i].obj != OBJ_POTAL) continue;

		if (_huntingTiles[i].obj == OBJ_TREE)
			IMAGEMANAGER->frameRender("object", getMemDC(),
			CAMERAMANAGER->CameraRelativePoint(_huntingTiles[i].renderPoint).x - IMAGEMANAGER->findImage("object")->getFrameWidth() / 4,
			CAMERAMANAGER->CameraRelativePoint(_huntingTiles[i].renderPoint).y - (IMAGEMANAGER->findImage("object")->getFrameHeight() / 4) * 2.5,
			_huntingTiles[i].objFrameX, _huntingTiles[i].objFrameY,
			&tempCameraRC
			/*&RectMake(CAMERAMANAGER->CameraRelativePoint(_cameraRC).x,
			CAMERAMANAGER->CameraRelativePoint(_cameraRC).y,
			TILEWINSIZEX, TILEWINSIZEY)*/);

		else if (_huntingTiles[i].obj == OBJ_GRASS)
			IMAGEMANAGER->frameRender("object", getMemDC(),
			CAMERAMANAGER->CameraRelativePoint(_huntingTiles[i].renderPoint).x - IMAGEMANAGER->findImage("object")->getFrameWidth() / 6,
			CAMERAMANAGER->CameraRelativePoint(_huntingTiles[i].renderPoint).y - (IMAGEMANAGER->findImage("object")->getFrameHeight() / 6) /** 2.5*/,
			_huntingTiles[i].objFrameX, _huntingTiles[i].objFrameY,
			&tempCameraRC
			/*&RectMake(CAMERAMANAGER->CameraRelativePoint(_cameraRC).x,
			CAMERAMANAGER->CameraRelativePoint(_cameraRC).y,
			TILEWINSIZEX, TILEWINSIZEY)*/);

		else if (_huntingTiles[i].obj == OBJ_POTAL)
			IMAGEMANAGER->frameRender("object", getMemDC(),
			CAMERAMANAGER->CameraRelativePoint(_huntingTiles[i].renderPoint).x - TILESIZE / 2, //- IMAGEMANAGER->findImage("object")->getFrameWidth() / 6,
			CAMERAMANAGER->CameraRelativePoint(_huntingTiles[i].renderPoint).y,//+TILESIZE / 2,//- (IMAGEMANAGER->findImage("object")->getFrameHeight() / 6) /** 2.5*/,
			_huntingTiles[i].objFrameX, _huntingTiles[i].objFrameY,
			&tempCameraRC
			/*&RectMake(CAMERAMANAGER->CameraRelativePoint(_cameraRC).x,
			CAMERAMANAGER->CameraRelativePoint(_cameraRC).y,
			TILEWINSIZEX, TILEWINSIZEY)*/);
	}
}

void gameScene::townLoad()
{
	HANDLE file;
	DWORD read;

	file = CreateFile("./map/����.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _townTiles, sizeof(tagTile)* TILEX * TILEY, &read, NULL);

	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		//Ÿ���� POS�Ӽ� Ȯ���ؼ� Ÿ�� �ε����� ����
		if (_townTiles[i].pos == POS_MUSURI)	_posNPC[POS_MUSURI] = i;
		if (_townTiles[i].pos == POS_HOSULAM)	_posNPC[POS_HOSULAM] = i;
		if (_townTiles[i].pos == POS_JANGGUMI)	_posNPC[POS_JANGGUMI] = i;


		if (_townTiles[i].terrain == TR_WATER || _townTiles[i].obj != OBJ_NONE || _townTiles[i].obj != OBJ_POTAL || _townTiles[i].obj != OBJ_POTAL_DUMMY
			|| _townTiles[i].obj != OBJ_RESPOND)
		{
			_townAttribute[i] = ATTR_UNMOVE;
		}
	}

	CloseHandle(file);
}
void gameScene::huntingLoad()
{
	HANDLE file;
	DWORD read;

	file = CreateFile("./map/�����.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _huntingTiles, sizeof(tagTile)* TILEX * TILEY, &read, NULL);

	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (_huntingTiles[i].terrain == TR_WATER || _huntingTiles[i].obj != OBJ_NONE || _huntingTiles[i].obj != OBJ_POTAL || _huntingTiles[i].obj != OBJ_POTAL_DUMMY
			|| _huntingTiles[i].obj != OBJ_RESPOND)
		{
			_huntingAttribut[i] = ATTR_UNMOVE;
		}
		if (_huntingTiles[i].obj == OBJ_RESPOND)
			_vHuntingRespond.push_back(i);
	}

	CloseHandle(file);
}

void gameScene::move(int direction){
//	switch (direction)
//	{
//		//��
//	case 0:
//	/*	if (_cameraRC.left > -(TILESIZEX / 2)){
//			_cameraRC.right -= 3;
//			_cameraRC.left = _cameraRC.right - TILEWINSIZEX;
//		}
//*/
//		if (_cameraRC.left > -(TILESIZEX / 2) + 450)
//		{
//			_cameraRC.right -= 3;
//			_cameraRC.left = _cameraRC.right - 100;
//		}
//		break;
//
//		//��
//	case 1:
//		/*if (_cameraRC.top > 0)
//		{
//			_cameraRC.top -= 3;
//			_cameraRC.bottom = _cameraRC.top + TILEWINSIZEY;
//		}*/
//
//		_cameraRC.top -= 3;
//		_cameraRC.bottom = _cameraRC.top + 100;
//
//		break;
//
//		//��
//	case 2:
//	/*	if (_cameraRC.right < (TILESIZEX / 2 + TILESIZEX / 4))
//		{
//			_cameraRC.right += 3;
//			_cameraRC.left = _cameraRC.right - TILEWINSIZEX;
//		}*/
//		if (_cameraRC.right < (TILESIZEX / 2))
//		{
//			_cameraRC.right += 3;
//			_cameraRC.left = _cameraRC.right - 100;
//		}
//
//		break;
//
//		//�Ʒ�
//	case 3:
//		/*if (_cameraRC.bottom < TILESIZEY)
//		{
//			_cameraRC.top += 3;
//			_cameraRC.bottom = _cameraRC.top + TILEWINSIZEY;
//		}*/
//		if (_cameraRC.bottom < TILESIZEY-250)
//		{
//			_cameraRC.top += 3;
//			_cameraRC.bottom = _cameraRC.top + 100;
//		}
//
//		break;
//	default:
//		break;
//	}
}