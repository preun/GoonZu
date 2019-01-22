#include "stdafx.h"
#include "hosulam.h"
#include "itemManager.h"
#include "inventory.h"

hosulam::hosulam()
{
}


hosulam::~hosulam()
{
}

HRESULT hosulam::init(POINT pos)
{
	_npcImage = IMAGEMANAGER->addFrameImage("호설암", "./image/npc/호설암.bmp", 432, 59, 9, 1, true, RGB(255, 0, 255));
	_npcNameImage = IMAGEMANAGER->addImage("호설암위", "./image/npc/호설암위.bmp", 76, 17, true, RGB(255, 0, 255));
	_npcShopImage = IMAGEMANAGER->addImage("상점", "./image/shop/상점.bmp", 247, 281, true, RGB(255, 0, 255));

	_animation = new animation;
	_animation->init(_npcImage->getWidth(), _npcImage->getHeight(), _npcImage->getFrameWidth() , _npcImage->getHeight());
	_animation->setDefPlayFrame(false, true);
	
	_animation->start();
	_animation->setFPS(1);
	//포스 위치 조정
	_pos = pos;
	_npcRC = RectMakeCenter(_pos.x, _pos.y, _npcImage->getFrameWidth(), _npcImage->getFrameHeight());
	/*
	TYPE_WEAPON,	//무기
	TYPE_ARMOR,		//갑옷
	TYPE_HELMET,	//헬멧
	TYPE_RING,		//반지
	TYPE_NECK,		//목걸이
	TYPE_POTION		//포션
	*/
	//장비
	tagItemIndex tempIndex;
	tempIndex.itemtype = TYPE_WEAPON;
	tempIndex.index = 0;
	_sellItemIndex.push_back(tempIndex);

	tempIndex.itemtype = TYPE_WEAPON;
	tempIndex.index = 1;
	_sellItemIndex.push_back(tempIndex);

	tempIndex.itemtype = TYPE_ARMOR;
	tempIndex.index = 0;
	_sellItemIndex.push_back(tempIndex);

	tempIndex.itemtype = TYPE_ARMOR;
	tempIndex.index = 1;
	_sellItemIndex.push_back(tempIndex);

	tempIndex.itemtype = TYPE_HELMET;
	tempIndex.index = 0;
	_sellItemIndex.push_back(tempIndex);

	tempIndex.itemtype = TYPE_HELMET;
	tempIndex.index = 1;
	_sellItemIndex.push_back(tempIndex);

	tempIndex.itemtype = TYPE_NECK;
	tempIndex.index = 0;
	_sellItemIndex.push_back(tempIndex);

	tempIndex.itemtype = TYPE_RING;
	tempIndex.index = 0;
	_sellItemIndex.push_back(tempIndex);

	tempIndex.itemtype = TYPE_RING;
	tempIndex.index = 1;
	_sellItemIndex.push_back(tempIndex);

	for (int i = 0; i < _sellItemIndex.size(); ++i)
	{
		_sellItem.push_back( _IM->findItem(_sellItemIndex[i].itemtype, _sellItemIndex[i].index));
		_sellItemRC.push_back(RectMake(126 + 39 * (i % 3), 429 + 39 * (i / 3), 34, 34));
	}
	_buyRC = RectMake(113, 391, 40, 20);
	_sellRC = RectMake(170, 391, 40, 20);

	_clickIndex = -1;
	_invenClick = false;
	//113 91 40, 20
	//_sellItem[i]->getImage()->render(getMemDC(), 126 + 39*(i%3), 429 + 39*(i/3));
	return S_OK;
}
void hosulam::release()
{

}
void hosulam::update()
{
	_animation->frameUpdate(TIMEMANAGER->getElapsedTime() * 5);
}
void hosulam::render()
{
	_npcImage->aniRender(getMemDC(), CAMERAMANAGER->CameraRelativePointX(_npcRC.left),
		CAMERAMANAGER->CameraRelativePointY(_npcRC.top)-5, _animation);
	//_npcImage->aniRender(getMemDC(), _npcRC.left,_npcRC.top, _animation);
}

void hosulam::clickNpc()
{
	_npcShopImage->render(getMemDC(), 0, 300);
	char test[111];
	strcpy(test, "호설암");
	TextOut(getMemDC(), 0, 300, test, strlen(test));
	//126 129
	if (_sellItem.size() <= 0) return;
	for (int i = 0; i < _sellItem.size(); ++i)
	{
		_sellItem[i]->getImage()->render(getMemDC(), 126 + 39*(i%3), 429 + 39*(i/3));
	}
	_inven->inventoryOpen();
}

void hosulam::buyItem()
{
	for (int i = 0; i < _sellItemRC.size(); ++i)
	{
		if (PtInRect(&_sellItemRC[i], _ptMouse))
		{
			_clickIndex = i;
			break;
		}
	}

	if ( _clickIndex != -1 && PtInRect(&_buyRC, _ptMouse))
	{
		//소지금이 판매액보다 많으면 구매가능
		if (_inven->getMoney() >= _sellItem[_clickIndex]->getMoney())
		{
			_inven->setMoney(-_sellItem[_clickIndex]->getMoney());
			_inven->buyItem(_sellItemIndex[_clickIndex]);
		}
	}
}

void hosulam::sellItem()
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