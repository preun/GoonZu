#include "stdafx.h"
#include "musuri.h"
#include "itemManager.h"
#include "inventory.h"

musuri::musuri()
{
}


musuri::~musuri()
{
}

HRESULT musuri::init(POINT pos)
{
	_npcImage = IMAGEMANAGER->addFrameImage("무수리", "./image/npc/무수리.bmp", 450, 61, 10, 1, true, RGB(255, 0, 255));
	_npcNameImage = IMAGEMANAGER->addImage("무수리위", "./image/npc/무수리.bmp", 77, 18, true, RGB(255, 0, 255));
	_npcShopImage = IMAGEMANAGER->addImage("상점", "./image/shop/상점.bmp", 247, 281, true, RGB(255, 0, 255));

	_animation = new animation;
	_animation->init(_npcImage->getWidth(), _npcImage->getHeight(), _npcImage->getFrameWidth(), _npcImage->getHeight());
	_animation->setDefPlayFrame(false, true);

	_animation->start();
	_animation->setFPS(1);

	//포스 위치 조정
	_pos = pos;
	_npcRC = RectMakeCenter(_pos.x, _pos.y, _npcImage->getFrameWidth(), _npcImage->getFrameHeight());

	tagItemIndex tempIndex;
	tempIndex.itemtype = TYPE_POTION;
	tempIndex.index = 0;
	_sellItemIndex.push_back(tempIndex);

	tempIndex.itemtype = TYPE_POTION;
	tempIndex.index = 1;
	_sellItemIndex.push_back(tempIndex);

	tempIndex.itemtype = TYPE_POTION;
	tempIndex.index = 2;
	_sellItemIndex.push_back(tempIndex);

	tempIndex.itemtype = TYPE_POTION;
	tempIndex.index = 3;
	_sellItemIndex.push_back(tempIndex);

	for (int i = 0; i < _sellItemIndex.size(); ++i)
	{
		_sellItem.push_back(_IM->findItem(_sellItemIndex[i].itemtype, _sellItemIndex[i].index));
		_sellItemRC.push_back(RectMake(126 + 39 * (i % 3), 429 + 39 * (i / 3), 34, 34));
	}
	_buyRC = RectMake(113, 391, 40, 20);
	_sellRC = RectMake(170, 391, 40, 20);

	_clickIndex = -1;
	_invenClick = false;
	return S_OK;
}
void musuri::release()
{

}
void musuri::update()
{
	_animation->frameUpdate(TIMEMANAGER->getElapsedTime() * 5);
}
void musuri::render()
{
	_npcImage->aniRender(getMemDC(), CAMERAMANAGER->CameraRelativePointX(_npcRC.left), 
		CAMERAMANAGER->CameraRelativePointY(_npcRC.top)-5, _animation);
}
void musuri::clickNpc()
{
	_npcShopImage->render(getMemDC(), 0, 300);

	char test[111];
	strcpy(test, "무수리");
	TextOut(getMemDC(), 0, 300, test, strlen(test));

	if (_sellItem.size() <= 0) return;
	for (int i = 0; i < _sellItem.size(); ++i)
	{
		_sellItem[i]->getImage()->render(getMemDC(), 126 + 39 * (i % 3), 429 + 39 * (i / 3));
		//_sellItemRC.push_back(RectMake(126 + 39 * (i % 3), 429 + 39 * (i / 3), 34, 34));
	}
	_inven->inventoryOpen();
}

void musuri::buyItem()
{
	for (int i = 0; i < _sellItemRC.size(); ++i)
	{
		if (PtInRect(&_sellItemRC[i], _ptMouse))
		{
			_clickIndex = i;
			break;
		}
	}

	if (_clickIndex != -1 && PtInRect(&_buyRC, _ptMouse))
	{
		_inven->buyItem(_sellItemIndex[_clickIndex]);
	}
}

void musuri::sellItem()
{
	//인벤에서 클릭했으면 true반환
	_invenClick = _inven->inventoryClick();

	//인벤에서 무언가를 클릭하고 판매버튼을 눌렀다면
	if (_invenClick  && PtInRect(&_sellRC, _ptMouse))
	{
		//팔아라
		_inven->inventoryItemSell();
		_invenClick = false;
	}
}