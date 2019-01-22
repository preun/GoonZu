#include "stdafx.h"
#include "equip.h"
#include "status.h"
//#include "inventory.h"

equip::equip()
{
}


equip::~equip()
{

}

HRESULT equip::init()
{
	IMAGEMANAGER->addImage("장비창", "./image/character/장비창/장비창.bmp", 233, 254, true, RGB(255, 0, 255));

	for (int i = 0; i < MAXEQUIPPLACE; ++i)
	{
		_equipItem[i] = NULL;

	}
	_equipPlaceRC[EQUIP_WEAPON] = RectMake(270, 270, 34, 34);
	_equipPlaceRC[EQUIP_NECK] = RectMake(348, 176, 34, 34);
	_equipPlaceRC[EQUIP_ARMOR] = RectMake(407, 218, 34, 34);
	_equipPlaceRC[EQUIP_RING1] = RectMake(437, 266, 34, 34);
	_equipPlaceRC[EQUIP_RING2] = RectMake(437, 309, 34, 34);
	_equipPlaceRC[EQUIP_HELMET] = RectMake(407, 176, 34, 34);

	/*
	+ 260, 100
	무기 10, 170
	목걸이 88, 76
	갑옷 147 118
	반지1 177 166
	반지2 177 209
	헬멧	147 76
	*/
	return S_OK;
}

void equip::release()
{

}

void equip::update()
{

}

void equip::render()
{

}


void equip::equipOpen()
{
	IMAGEMANAGER->render("장비창", getMemDC(), 260, 100);
	for (int i = 0; i < MAXEQUIPPLACE; ++i)
	{
		//장착아이템이 없으면 컨티뉴
		if (_equipItem[i] == NULL) continue;

		_equipItem[i]->getImage()->render(getMemDC(), _equipPlaceRC[i].left, _equipPlaceRC[i].top);
	}
	//260, 100
}
bool equip::equipInstall(tagItemIndex equipItemIndex, itemParent* equipItem)
{
	//레벨조건보다 현재 레벨이 낮으면 리턴
	if (equipItem->getLimitLevel() > *_status->getLevel()) return false;
	
	/*
	TYPE_WEAPON,	//무기
	TYPE_ARMOR,		//갑옷
	TYPE_HELMET,	//헬멧
	TYPE_RING,		//반지
	TYPE_NECK,		//목걸이
	TYPE_POTION		//포션
	*/
	switch (equipItem->getItemType())
	{
	case TYPE_WEAPON:
		if (PtInRect(&_equipPlaceRC[EQUIP_WEAPON], _ptMouse))
		{
			if (equipItem->getLimitStat() > _status->getStr()) return false;
			//장착 조건식 확인하고 스탯조절하고 장착순서로 만들기
			equipStatus(equipItem);
			_equipItemIndex[EQUIP_WEAPON] = equipItemIndex;
			_equipItem[EQUIP_WEAPON] = equipItem;
		
		}
		break;
	case TYPE_ARMOR:
		if (PtInRect(&_equipPlaceRC[EQUIP_ARMOR], _ptMouse))
		{
			equipStatus(equipItem);
			_equipItemIndex[EQUIP_ARMOR] = equipItemIndex;
			_equipItem[EQUIP_ARMOR] = equipItem;
			//_inven->inventoryItemDrop();
		}
		break;
	case TYPE_HELMET:
		if (PtInRect(&_equipPlaceRC[EQUIP_HELMET], _ptMouse))
		{
			equipStatus(equipItem);
			_equipItemIndex[EQUIP_HELMET] = equipItemIndex;
			_equipItem[EQUIP_HELMET] = equipItem;
			//_inven->inventoryItemDrop();
		}
		break;
	case TYPE_RING:
		if (PtInRect(&_equipPlaceRC[EQUIP_RING1], _ptMouse))
		{
			equipStatus(equipItem, false);
			_equipItemIndex[EQUIP_RING1] = equipItemIndex;
			_equipItem[EQUIP_RING1] = equipItem;
			//_inven->inventoryItemDrop();
		}
		else if (PtInRect(&_equipPlaceRC[EQUIP_RING2], _ptMouse))
		{
			equipStatus(equipItem, true);
			_equipItemIndex[EQUIP_RING2] = equipItemIndex;
			_equipItem[EQUIP_RING2] = equipItem;
			//_inven->inventoryItemDrop();
		}
		break;
	case TYPE_NECK:
		if (PtInRect(&_equipPlaceRC[EQUIP_NECK], _ptMouse))
		{
			equipStatus(equipItem);
			_equipItemIndex[EQUIP_NECK] = equipItemIndex;
			_equipItem[EQUIP_NECK] = equipItem;
			//_inven->inventoryItemDrop();
		}
		break;
	default:
		break;
	}

	return false;
}
void equip::equipStatus(itemParent* equipItem){
	switch (equipItem->getItemType())
	{
	case TYPE_WEAPON:
		//장착한 아이템이 없다면 그냥 +
		if (_equipItem[EQUIP_WEAPON] == NULL)
		{
			_status->setMinAtt(equipItem->getEffect1());
			_status->setMaxAtt(equipItem->getEffect2());
			_inven->inventoryItemDrop(true, _equipItemIndex[EQUIP_WEAPON]);
		}
		//아이템을 장착하고 있다면
		else
		{
			_status->setMinAtt(-_equipItem[EQUIP_WEAPON]->getEffect1());
			_status->setMaxAtt(-_equipItem[EQUIP_WEAPON]->getEffect2());

			_status->setMinAtt(equipItem->getEffect1());
			_status->setMaxAtt(equipItem->getEffect2());
			_inven->inventoryItemDrop(false, _equipItemIndex[EQUIP_WEAPON]);
		}
		break;
	case TYPE_ARMOR:
		if (_equipItem[EQUIP_ARMOR] == NULL)
		{
			//헬멧 장착중이 아니면 갑옷 방어력만 조정
			if (_equipItem[EQUIP_HELMET] == NULL)_status->setDef(equipItem->getEffect1());
			//헬멧 장착중이면 헬멧 갑옷 방어력 조정
			else _status->setDef(equipItem->getEffect1(), _equipItem[EQUIP_HELMET]->getEffect1());

			_inven->inventoryItemDrop(true, _equipItemIndex[EQUIP_ARMOR]);
		}
		//아이템을 장착하고 있다면
		else
		{
			//헬멧 장착중이 아니면 갑옷 방어력만 조정
			if (_equipItem[EQUIP_HELMET] == NULL)
			{
				_status->setDef(-_equipItem[EQUIP_ARMOR]->getEffect1());
				_status->setDef(equipItem->getEffect1());
			}
			//헬멧 장착중이면 헬멧 갑옷 방어력 조정
			else
			{
				_status->setDef(-_equipItem[EQUIP_ARMOR]->getEffect1(), _equipItem[EQUIP_HELMET]->getEffect1());
				_status->setDef(equipItem->getEffect1(), _equipItem[EQUIP_HELMET]->getEffect1());
			}
			_inven->inventoryItemDrop(false, _equipItemIndex[EQUIP_ARMOR]);
		}
		break;
	case TYPE_HELMET:
		if (_equipItem[EQUIP_HELMET] == NULL)
		{
			//갑옷 장착중이 아니면 헬멧 방어력만 조정
			if (_equipItem[EQUIP_ARMOR] == NULL)_status->setDef(equipItem->getEffect1());
			//갑옷 장착중이면 헬멧 갑옷 방어력 조정
			else _status->setDef(equipItem->getEffect1(), _equipItem[EQUIP_ARMOR]->getEffect1());

			_inven->inventoryItemDrop(true, _equipItemIndex[EQUIP_HELMET]);
		}
		else
		{
			//헬멧 장착중이 아니면 갑옷 방어력만 조정
			if (_equipItem[EQUIP_ARMOR] == NULL)
			{
				_status->setDef(-_equipItem[EQUIP_HELMET]->getEffect1());
				_status->setDef(equipItem->getEffect1());
			}
			//헬멧 장착중이면 헬멧 갑옷 방어력 조정
			else
			{
				_status->setDef(-_equipItem[EQUIP_HELMET]->getEffect1(), _equipItem[EQUIP_ARMOR]->getEffect1());
				_status->setDef(equipItem->getEffect1(), _equipItem[EQUIP_ARMOR]->getEffect1());

			}
			_inven->inventoryItemDrop(false, _equipItemIndex[EQUIP_HELMET]);
		}
		break;
	
	case TYPE_NECK:
		if (_equipItem[EQUIP_NECK] == NULL)
		{
			//_status->setMinAtt(equipItem->getEffect1());
			//_status->setMaxAtt(equipItem->getEffect2());
		}
		break;
	default:
		break;
	}
}

void equip::equipStatus(itemParent* equipItem, bool isRing2Equip){
	//참 -> 2번째 반지를 장착한다.
	if (isRing2Equip)
	{
		//링2가 비었냐
		if (_equipItem[EQUIP_RING2] == NULL)
		{
			switch (equipItem->getStatType())
			{
				//생명력 스탯올려주면 생명력 스탯 증가
			case RING_LIFE:
				_status->setLife(equipItem->getEffect1());
				break;
			case RING_STR:
				//힘올려주면 힘스탯 증가와 최소 최대댐 갱신
				_status->setStr(equipItem->getEffect1());
				//무기가 없으면 무기데미지는 0이므로 
				if (_equipItem[EQUIP_WEAPON] == NULL)
				{					
					_status->setMinAtt(0);
					_status->setMaxAtt(0);
				}
				//무기장착하면 무기데미지로
				else
				{
					_status->setMinAtt(_equipItem[EQUIP_WEAPON]->getEffect1());
					_status->setMaxAtt(_equipItem[EQUIP_WEAPON]->getEffect2());
				}
				break;
			default:
				break;
			}
			_inven->inventoryItemDrop(true, _equipItemIndex[EQUIP_RING2]);
			//if (_equip)
		}
		//링2가 안비어있다
		else
		{
			//2링의 스탯을 확인해서 일단 기존 스탯을 까라
			switch (_equipItem[EQUIP_RING2]->getStatType())
			{
				//생명력 스탯올려주면 생명력 스탯 증가
			case RING_LIFE:
				_status->setLife(-_equipItem[EQUIP_RING2]->getEffect1());
				break;
			case RING_STR:
				//힘올려주면 힘스탯 증가와 최소 최대댐 갱신
				_status->setStr(-_equipItem[EQUIP_RING2]->getEffect1());
				//무기가 없으면 무기데미지는 0이므로 
				if (_equipItem[EQUIP_WEAPON] == NULL)
				{
					_status->setMinAtt(0);
					_status->setMaxAtt(0);
				}
				//무기장착하면 무기데미지로
				else
				{
					_status->setMinAtt(_equipItem[EQUIP_WEAPON]->getEffect1());
					_status->setMaxAtt(_equipItem[EQUIP_WEAPON]->getEffect2());
				}
				break;
			default:
				break;
			}

			switch (equipItem->getStatType())
			{
				//생명력 스탯올려주면 생명력 스탯 증가
			case RING_LIFE:
				_status->setLife(equipItem->getEffect1());
				break;
			case RING_STR:
				//힘올려주면 힘스탯 증가와 최소 최대댐 갱신
				_status->setStr(equipItem->getEffect1());
				//무기가 없으면 무기데미지는 0이므로 
				if (_equipItem[EQUIP_WEAPON] == NULL)
				{
					_status->setMinAtt(0);
					_status->setMaxAtt(0);
				}
				//무기장착하면 무기데미지로
				else
				{
					_status->setMinAtt(_equipItem[EQUIP_WEAPON]->getEffect1());
					_status->setMaxAtt(_equipItem[EQUIP_WEAPON]->getEffect2());
				}
				break;
			default:
				break;
			}
			_inven->inventoryItemDrop(false, _equipItemIndex[EQUIP_RING2]);
		}
	}
	//거짓 -> 1번쨰 반지를 장착한다.
	else
	{
		//링1이 비어있다
		if (_equipItem[EQUIP_RING1] == NULL)
		{
			switch (equipItem->getStatType())
			{
			case RING_LIFE:
				_status->setLife(equipItem->getEffect1());
				break;
			case RING_STR:
				//힘올려주면 힘스탯 증가와 최소 최대댐 갱신
				_status->setStr(equipItem->getEffect1());
				//무기가 없으면 무기데미지는 0이므로 
				if (_equipItem[EQUIP_WEAPON] == NULL)
				{
					_status->setMinAtt(0);
					_status->setMaxAtt(0);
				}
				//무기장착하면 무기데미지로
				else
				{
					_status->setMinAtt(_equipItem[EQUIP_WEAPON]->getEffect1());
					_status->setMaxAtt(_equipItem[EQUIP_WEAPON]->getEffect2());
				}
			default:
				break;
			}
			_inven->inventoryItemDrop(true, _equipItemIndex[EQUIP_RING1]);
			//if (_equip)
		}
		//링1이 안비었따.
		else
		{
			//1링의 스탯을 확인해서 일단 기존 스탯을 까라
			switch (_equipItem[EQUIP_RING1]->getStatType())
			{
				//생명력 스탯올려주면 생명력 스탯 증가
			case RING_LIFE:
				_status->setLife(-_equipItem[EQUIP_RING1]->getEffect1());
				break;
			case RING_STR:
				//힘올려주면 힘스탯 증가와 최소 최대댐 갱신
				_status->setStr(-_equipItem[EQUIP_RING1]->getEffect1());
				//무기가 없으면 무기데미지는 0이므로 
				if (_equipItem[EQUIP_WEAPON] == NULL)
				{
					_status->setMinAtt(0);
					_status->setMaxAtt(0);
				}
				//무기장착하면 무기데미지로
				else
				{
					_status->setMinAtt(_equipItem[EQUIP_WEAPON]->getEffect1());
					_status->setMaxAtt(_equipItem[EQUIP_WEAPON]->getEffect2());
				}
				break;
			default:
				break;
			}

			switch (equipItem->getStatType())
			{
				//생명력 스탯올려주면 생명력 스탯 증가
			case RING_LIFE:
				_status->setLife(equipItem->getEffect1());
				break;
			case RING_STR:
				//힘올려주면 힘스탯 증가와 최소 최대댐 갱신
				_status->setStr(equipItem->getEffect1());
				//무기가 없으면 무기데미지는 0이므로 
				if (_equipItem[EQUIP_WEAPON] == NULL)
				{
					_status->setMinAtt(0);
					_status->setMaxAtt(0);
				}
				//무기장착하면 무기데미지로
				else
				{
					_status->setMinAtt(_equipItem[EQUIP_WEAPON]->getEffect1());
					_status->setMaxAtt(_equipItem[EQUIP_WEAPON]->getEffect2());
				}
				break;
			default:
				break;
			}
			_inven->inventoryItemDrop(false, _equipItemIndex[EQUIP_RING1]);
		}
	}
}
bool equip::equipUnInstall(bool isClickEquip)
{
	//장비아이템 처음클릭함
	if (!isClickEquip)
	{
		for (int i = 0; i < MAXEQUIPPLACE; ++i)
		{
			//장비장의 특정칸을 눌렀다.
			if (PtInRect(&_equipPlaceRC[i], _ptMouse))
			{
				//근데 장착되어있는 아이템이 없다. --> 아무일도 하지마라
				if (_equipItem[i] == NULL) return false;

				//장착되어 있다면
				_clickIndex = i;
				return true;
			}
		}
	}
	else
	{
		/*
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
		*/
	}
	/*
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
	*/
	return false;
}
void equip::equipUnInstall()
{
	//아이템 해제시 스탯감소
	//switch (_equipItem[_clickIndex]->getItemType())
	switch (_clickIndex)
	{
	case EQUIP_WEAPON:
			_status->setMinAtt(0);
			_status->setMaxAtt(0);
	case EQUIP_ARMOR:
		//헬멧미장착중이면 갑옷방어력만 까면된다.
		if (_equipItem[EQUIP_HELMET] == NULL)
		{
			_status->setDef(0);
		}
		//헬멧 착용중이면 갑옷방어력 까고 헬멧아이템방어력은 더해준다
		else
		{
			_status->setDef(0, _equipItem[EQUIP_HELMET]->getEffect1());
		}
		break;
	case EQUIP_HELMET:
		//갑옷 미장착이면 헬멧 방어력만 까준다.
		if (_equipItem[EQUIP_ARMOR] == NULL)
		{
			_status->setDef(0);
		}
		//갑옷 착용중이면 헬멧 방어력 까고 갑옷 방어력은 더해준다.
		else
		{
			_status->setDef(0, _equipItem[EQUIP_ARMOR]->getEffect1());
		}
		break;

	case EQUIP_NECK:
		if (_equipItem[EQUIP_NECK] == NULL)
		{
			//_status->setMinAtt(equipItem->getEffect1());
			//_status->setMaxAtt(equipItem->getEffect2());
		}
		break;
	case EQUIP_RING1:
		if (_equipItem[EQUIP_RING1]->getStatType() == RING_LIFE)
		{
			_status->setLife(-_equipItem[EQUIP_RING1]->getEffect1());
		}
		else if (_equipItem[EQUIP_RING1]->getStatType() == RING_STR)
		{
			_status->setStr(-_equipItem[EQUIP_RING1]->getEffect1());
			//무기가 없으면 무기데미지는 0이므로 
			if (_equipItem[EQUIP_WEAPON] == NULL)
			{
				_status->setMinAtt(0);
				_status->setMaxAtt(0);
			}
			//무기장착하면 무기데미지로
			else
			{
				_status->setMinAtt(_equipItem[EQUIP_WEAPON]->getEffect1());
				_status->setMaxAtt(_equipItem[EQUIP_WEAPON]->getEffect2());
			}
		}
		break;
	case EQUIP_RING2:
		if (_equipItem[EQUIP_RING2]->getStatType() == RING_LIFE)
		{
			_status->setLife(-_equipItem[EQUIP_RING2]->getEffect1());
		}
		else if (_equipItem[EQUIP_RING2]->getStatType() == RING_STR)
		{
			_status->setStr(-_equipItem[EQUIP_RING2]->getEffect1());
			//무기가 없으면 무기데미지는 0이므로 
			if (_equipItem[EQUIP_WEAPON] == NULL)
			{
				_status->setMinAtt(0);
				_status->setMaxAtt(0);
			}
			//무기장착하면 무기데미지로
			else
			{
				_status->setMinAtt(_equipItem[EQUIP_WEAPON]->getEffect1());
				_status->setMaxAtt(_equipItem[EQUIP_WEAPON]->getEffect2());
			}
		}
		break;
	default:
		break;
	}

	_equipItem[_clickIndex] = NULL;
}