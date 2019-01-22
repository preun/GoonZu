#include "stdafx.h"
#include "inventory.h"
#include "itemManager.h"
#include "equip.h"

inventory::inventory()
{
}


inventory::~inventory()
{

}

HRESULT inventory::init()
{
	IMAGEMANAGER->addImage("인벤토리창", "./image/character/인벤토리/인벤토리.bmp", 153, 331, true, RGB(255, 0, 255));

	for (int i = 0; i < MAXINVENTORY; ++i)
	{
		//포인터형이므로 초기화는 NULL으로
		_inventory[i] = NULL;
		_itemIndex[i].itemtype = TYPE_ARMOR;
		_itemIndex[i].index = 0;

		_inventoryRC[i] = RectMake(WINSIZEX - 153 + 5 + 36 * (i%4), 151 + 36 * (i/4), 34, 34);
		/*_inventoryRC[1] = RectMake(WINSIZEX - 153 + 41, 151, 34, 34);
		_inventoryRC[2] = RectMake(WINSIZEX - 153 + 78, 151, 34, 34);
		_inventoryRC[3] = RectMake(WINSIZEX - 153 + 115, 151, 34, 34);*/
		//51 3687 123
	}
	_itemIndex[1].index = 1;

	_itemIndex[2].itemtype = TYPE_HELMET;
	_itemIndex[2].index = 0;

	_itemIndex[3].itemtype = TYPE_HELMET;
	_itemIndex[3].index = 1;

	_itemIndex[4].itemtype = TYPE_NECK;
	_itemIndex[4].index = 0;

	_itemIndex[5].itemtype = TYPE_POTION;
	_itemIndex[5].index = 0;

	_itemIndex[6].itemtype = TYPE_POTION;
	_itemIndex[6].index = 1;

	_itemIndex[7].itemtype = TYPE_POTION;
	_itemIndex[7].index = 2;

	_itemIndex[8].itemtype = TYPE_POTION;
	_itemIndex[8].index = 3;

	_itemIndex[9].itemtype = TYPE_RING;
	_itemIndex[9].index = 0;

	_itemIndex[10].itemtype = TYPE_RING;
	_itemIndex[10].index = 1;

	_itemIndex[11].itemtype = TYPE_WEAPON;
	_itemIndex[11].index = 0;

	_itemIndex[12].itemtype = TYPE_WEAPON;
	_itemIndex[12].index = 1;

	_money = 100000;

	return S_OK;
}

void inventory::release()
{

}

void inventory::update()
{
	/*if (KEYMANAGER->isOnceKeyDown('4')) _inventory[0] = _IM->findItem(_itemIndex[0].itemtype, _itemIndex[0].index);
	if (KEYMANAGER->isOnceKeyDown('5')) _inventory[1] = _IM->findItem(_itemIndex[1].itemtype, _itemIndex[1].index);
	if (KEYMANAGER->isOnceKeyDown('6')) _inventory[2] = _IM->findItem(_itemIndex[2].itemtype, _itemIndex[2].index);
	if (KEYMANAGER->isOnceKeyDown('7')) _inventory[3] = _IM->findItem(_itemIndex[3].itemtype, _itemIndex[3].index);
	if (KEYMANAGER->isOnceKeyDown('8')) _inventory[4] = _IM->findItem(_itemIndex[4].itemtype, _itemIndex[4].index);
	if (KEYMANAGER->isOnceKeyDown('9')) _inventory[5] = _IM->findItem(_itemIndex[5].itemtype, _itemIndex[5].index);
	if (KEYMANAGER->isOnceKeyDown('0')) _inventory[6] = _IM->findItem(_itemIndex[6].itemtype, _itemIndex[6].index);
	if (KEYMANAGER->isOnceKeyDown('T')) _inventory[7] = _IM->findItem(_itemIndex[7].itemtype, _itemIndex[7].index);
	if (KEYMANAGER->isOnceKeyDown('Y')) _inventory[8] = _IM->findItem(_itemIndex[8].itemtype, _itemIndex[8].index);
	if (KEYMANAGER->isOnceKeyDown('Q')) _inventory[9] = _IM->findItem(_itemIndex[9].itemtype, _itemIndex[9].index);
	if (KEYMANAGER->isOnceKeyDown('W')) _inventory[10] = _IM->findItem(_itemIndex[10].itemtype, _itemIndex[10].index);
	if (KEYMANAGER->isOnceKeyDown('Y')) _inventory[11] = _IM->findItem(_itemIndex[11].itemtype, _itemIndex[11].index);
	if (KEYMANAGER->isOnceKeyDown('R')) _inventory[12] = _IM->findItem(_itemIndex[12].itemtype, _itemIndex[12].index);*/
}

void inventory::render()
{
	char money[111];
	sprintf(money, "%d", _money);
	//TextOut(getMemDC(), 400, 400, money, strlen(money));
}

void inventory::inventoryOpen()
{
	IMAGEMANAGER->render("인벤토리창", getMemDC(), WINSIZEX-153, 100);
	for (int i = 0; i < MAXINVENTORY; ++i)
	{
		if (_inventory[i] != NULL)
			_inventory[i]->getImage()->render(getMemDC(), _inventoryRC[i].left, _inventoryRC[i].top);
	}/*
	if (_inventory[0] != NULL)
	_inventory[0]->getImage()->render(getMemDC(), _inventoryRC[0].left, _inventoryRC[0].top);

	if (_inventory[1] != NULL)
		_inventory[1]->getImage()->render(getMemDC(), _inventoryRC[1].left, _inventoryRC[1].top);

	if (_inventory[2] != NULL)
		_inventory[2]->getImage()->render(getMemDC(), _inventoryRC[2].left, _inventoryRC[2].top);

	if (_inventory[3] != NULL)
		_inventory[3]->getImage()->render(getMemDC(), _inventoryRC[3].left, _inventoryRC[3].top);*/
}
bool inventory::inventoryClick(int isClickInvenItem){

	//아이템을 처음 클릭함
	if (!isClickInvenItem)
	{
		for (int i = 0; i < MAXINVENTORY; ++i)
		{
			//인벤토리의 특정칸을 눌렀다.
			if (PtInRect(&_inventoryRC[i], _ptMouse))
			{
				//근데 그 칸의 아이템이 없다 --> 아무일도 하지마라
				if (_inventory[i] == NULL) return false;

				_clickIndex = i;
				_clickItemIndex = _itemIndex[i];
				//아이템이 있다면 아이템의 정보를 특정 변수에 저장
				return true;
			}
		}
	}
	//클릭한 아이템이 있다면
	else
	{
		for (int i = 0; i < MAXINVENTORY; ++i)
		{
			//인벤토리의 특정칸을 눌렀다.
			if (PtInRect(&_inventoryRC[i], _ptMouse))
			{
				//특정칸이 빈곳이다.
				if (_inventory[i] == NULL)
				{
					_inventory[i] = _IM->findItem(_clickItemIndex.itemtype, _clickItemIndex.index);
					_itemIndex[i] = _clickItemIndex;

					_inventory[_clickIndex] = NULL;
					return false;
				}
				else
				{
					tagItemIndex tempIndex = _itemIndex[i];
					_inventory[i] = _IM->findItem(_clickItemIndex.itemtype, _clickItemIndex.index);
					_itemIndex[i] = _clickItemIndex;

					_inventory[_clickIndex] = _IM->findItem(tempIndex.itemtype, tempIndex.index);
					_itemIndex[_clickIndex] = tempIndex;
				}
				//아이템 스왑
			}
		}
	}
	//아이템이 클릭이 안되면 false가 반환된다.
	return false;
}
bool inventory::inventoryClick()
{
	for (int i = 0; i < MAXINVENTORY; ++i)
	{
		//인벤토리의 특정칸을 눌렀다.
		if (PtInRect(&_inventoryRC[i], _ptMouse))
		{
			//근데 그 칸의 아이템이 없다 --> 아무일도 하지마라
			if (_inventory[i] == NULL) return false;;

			_clickIndex = i;
			//아이템이 있다면 아이템의 정보를 특정 변수에 저장
			return true;
		}
	}
}

bool inventory::inventoryItemDrop()
{
	_inventory[_clickIndex] = NULL;

	return false;
}
bool inventory::inventoryItemDrop(bool isEquipNull, tagItemIndex tempItemIndex)
{
	//장비 장착할때 아무것도 장착안되있냐
	if (isEquipNull)
	{
		_inventory[_clickIndex] = NULL;
	}
	//장착 되있으면 장비아이템과 스왑
	else
	{
		_itemIndex[_clickIndex] = tempItemIndex;
		_inventory[_clickIndex] = _IM->findItem(_itemIndex[_clickIndex].itemtype, _itemIndex[_clickIndex].index);
	}

	return false;
}
image* inventory::getInvenItem(){

	return _IM->findItem(_itemIndex[_clickIndex].itemtype, _itemIndex[_clickIndex].index)->getImage();
}
bool inventory::inventoryClick(tagItemIndex tempItemIndex)
{
	for (int i = 0; i < MAXINVENTORY; ++i)
	{
		if (PtInRect(&_inventoryRC[i], _ptMouse))
		{
			//빈 공간이여야만 장비벗기 가능하도록
			if (_inventory[i] != NULL) return false;

			_itemIndex[i] = tempItemIndex;
			_inventory[i] = _IM->findItem(_itemIndex[i].itemtype, _itemIndex[i].index);
			_equip->equipUnInstall();

			return false;
		}
	}
	return false;
}
void inventory::buyItem(tagItemIndex tempItemIndex)
{
	if (tempItemIndex.itemtype == TYPE_POTION)
	{
		//포션은 겹쳐지므로 모든 인벤토리의 공간을 찾아야 한다.
		//인벤토리의 공간을 찾았는데 없다면 nullIndex위치에 포션을 저장한다.
		int nullIndex = MAXINVENTORY;
		for (int i = 0; i < MAXINVENTORY; ++i)
		{
			//i번째 공간의 인벤토리가 빈공간이다.
			if (_inventory[i] == NULL)
			{				
				i < nullIndex ? nullIndex = i : nullIndex = nullIndex;
				//continue;
			}
			//i번째 공간의 인벤토리가 해당 포션이면서 인덱스가 동일하다 --> 같은 아이템이다.
			else if (_inventory[i]->getItemType() == TYPE_POTION && _itemIndex[i].index == tempItemIndex.index)
			{
				//아이템 갯수를 증가시켜라
				_inventory[i]->setItemCount(1);
				return;
			}
		}
		//인벤토리를 다 뒤졌는데 해당 아이템이 없다.
		_itemIndex[nullIndex] = tempItemIndex;
		_inventory[nullIndex] = _IM->findItem(_itemIndex[nullIndex].itemtype, _itemIndex[nullIndex].index);
		_inventory[nullIndex]->setItemCount(1);
	}
	else
	{
		/*
		itemType itemtype;	//무슨타입이냐
		int index;			//해당 아이템의 벡터에서 위치하는 인덱스
		*/
		//0번칸부터 최대칸 까지 반복문 도는데
		for (int i = 0; i < MAXINVENTORY; ++i)
		{
			//빈공간 찾을때까지 돌아간다.
			if (_inventory[i] != NULL) continue;
			//빈공간을 찾았다면 해당칸에 구매아이템을 넣어준다.
			else
			{
				_itemIndex[i] = tempItemIndex;
				_inventory[i] = _IM->findItem(_itemIndex[i].itemtype, _itemIndex[i].index);
				break;
			}
		}
	}
}

void inventory::inventoryItemSell()
{
	//소지금 증가
	setMoney(_inventory[_clickIndex]->getMoney() * 0.8);
	_inventory[_clickIndex] = NULL;
}

int inventory::quickF1()
{
	if (_inventory[0] == NULL) return 0;
	//인벤토리 아이템 타입이 포션이면
	if (_inventory[0]->getItemType() == TYPE_POTION)
	{

		int tempPotionEffect = _inventory[0]->getEffect1();
		

		//if (_inventory[0]->getItemCount <= 0) return;
		//1이면 MP
		if (_inventory[0]->getPotionType())
		{
			_inventory[0]->setItemCount(-1);
			if (_inventory[0]->getItemCount() <= 0) _inventory[0] = NULL;
			return -tempPotionEffect;
		}
		//0이면 HP
		else
		{
			_inventory[0]->setItemCount(-1);
			if (_inventory[0]->getItemCount() <= 0) _inventory[0] = NULL;
			return tempPotionEffect;
		}
	}

		return 0;

}

int inventory::quickF2()
{

	return 0;
}

int inventory::quickF3()
{

	return 0;
}

int inventory::quickF4()
{

	return 0;
}

int inventory::quickF5()
{

	return 0;
}
