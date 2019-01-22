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
	IMAGEMANAGER->addImage("���â", "./image/character/���â/���â.bmp", 233, 254, true, RGB(255, 0, 255));

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
	���� 10, 170
	����� 88, 76
	���� 147 118
	����1 177 166
	����2 177 209
	���	147 76
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
	IMAGEMANAGER->render("���â", getMemDC(), 260, 100);
	for (int i = 0; i < MAXEQUIPPLACE; ++i)
	{
		//������������ ������ ��Ƽ��
		if (_equipItem[i] == NULL) continue;

		_equipItem[i]->getImage()->render(getMemDC(), _equipPlaceRC[i].left, _equipPlaceRC[i].top);
	}
	//260, 100
}
bool equip::equipInstall(tagItemIndex equipItemIndex, itemParent* equipItem)
{
	//�������Ǻ��� ���� ������ ������ ����
	if (equipItem->getLimitLevel() > *_status->getLevel()) return false;
	
	/*
	TYPE_WEAPON,	//����
	TYPE_ARMOR,		//����
	TYPE_HELMET,	//���
	TYPE_RING,		//����
	TYPE_NECK,		//�����
	TYPE_POTION		//����
	*/
	switch (equipItem->getItemType())
	{
	case TYPE_WEAPON:
		if (PtInRect(&_equipPlaceRC[EQUIP_WEAPON], _ptMouse))
		{
			if (equipItem->getLimitStat() > _status->getStr()) return false;
			//���� ���ǽ� Ȯ���ϰ� ���������ϰ� ���������� �����
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
		//������ �������� ���ٸ� �׳� +
		if (_equipItem[EQUIP_WEAPON] == NULL)
		{
			_status->setMinAtt(equipItem->getEffect1());
			_status->setMaxAtt(equipItem->getEffect2());
			_inven->inventoryItemDrop(true, _equipItemIndex[EQUIP_WEAPON]);
		}
		//�������� �����ϰ� �ִٸ�
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
			//��� �������� �ƴϸ� ���� ���¸� ����
			if (_equipItem[EQUIP_HELMET] == NULL)_status->setDef(equipItem->getEffect1());
			//��� �������̸� ��� ���� ���� ����
			else _status->setDef(equipItem->getEffect1(), _equipItem[EQUIP_HELMET]->getEffect1());

			_inven->inventoryItemDrop(true, _equipItemIndex[EQUIP_ARMOR]);
		}
		//�������� �����ϰ� �ִٸ�
		else
		{
			//��� �������� �ƴϸ� ���� ���¸� ����
			if (_equipItem[EQUIP_HELMET] == NULL)
			{
				_status->setDef(-_equipItem[EQUIP_ARMOR]->getEffect1());
				_status->setDef(equipItem->getEffect1());
			}
			//��� �������̸� ��� ���� ���� ����
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
			//���� �������� �ƴϸ� ��� ���¸� ����
			if (_equipItem[EQUIP_ARMOR] == NULL)_status->setDef(equipItem->getEffect1());
			//���� �������̸� ��� ���� ���� ����
			else _status->setDef(equipItem->getEffect1(), _equipItem[EQUIP_ARMOR]->getEffect1());

			_inven->inventoryItemDrop(true, _equipItemIndex[EQUIP_HELMET]);
		}
		else
		{
			//��� �������� �ƴϸ� ���� ���¸� ����
			if (_equipItem[EQUIP_ARMOR] == NULL)
			{
				_status->setDef(-_equipItem[EQUIP_HELMET]->getEffect1());
				_status->setDef(equipItem->getEffect1());
			}
			//��� �������̸� ��� ���� ���� ����
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
	//�� -> 2��° ������ �����Ѵ�.
	if (isRing2Equip)
	{
		//��2�� �����
		if (_equipItem[EQUIP_RING2] == NULL)
		{
			switch (equipItem->getStatType())
			{
				//����� ���ȿ÷��ָ� ����� ���� ����
			case RING_LIFE:
				_status->setLife(equipItem->getEffect1());
				break;
			case RING_STR:
				//���÷��ָ� ������ ������ �ּ� �ִ�� ����
				_status->setStr(equipItem->getEffect1());
				//���Ⱑ ������ ���ⵥ������ 0�̹Ƿ� 
				if (_equipItem[EQUIP_WEAPON] == NULL)
				{					
					_status->setMinAtt(0);
					_status->setMaxAtt(0);
				}
				//���������ϸ� ���ⵥ������
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
		//��2�� �Ⱥ���ִ�
		else
		{
			//2���� ������ Ȯ���ؼ� �ϴ� ���� ������ ���
			switch (_equipItem[EQUIP_RING2]->getStatType())
			{
				//����� ���ȿ÷��ָ� ����� ���� ����
			case RING_LIFE:
				_status->setLife(-_equipItem[EQUIP_RING2]->getEffect1());
				break;
			case RING_STR:
				//���÷��ָ� ������ ������ �ּ� �ִ�� ����
				_status->setStr(-_equipItem[EQUIP_RING2]->getEffect1());
				//���Ⱑ ������ ���ⵥ������ 0�̹Ƿ� 
				if (_equipItem[EQUIP_WEAPON] == NULL)
				{
					_status->setMinAtt(0);
					_status->setMaxAtt(0);
				}
				//���������ϸ� ���ⵥ������
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
				//����� ���ȿ÷��ָ� ����� ���� ����
			case RING_LIFE:
				_status->setLife(equipItem->getEffect1());
				break;
			case RING_STR:
				//���÷��ָ� ������ ������ �ּ� �ִ�� ����
				_status->setStr(equipItem->getEffect1());
				//���Ⱑ ������ ���ⵥ������ 0�̹Ƿ� 
				if (_equipItem[EQUIP_WEAPON] == NULL)
				{
					_status->setMinAtt(0);
					_status->setMaxAtt(0);
				}
				//���������ϸ� ���ⵥ������
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
	//���� -> 1���� ������ �����Ѵ�.
	else
	{
		//��1�� ����ִ�
		if (_equipItem[EQUIP_RING1] == NULL)
		{
			switch (equipItem->getStatType())
			{
			case RING_LIFE:
				_status->setLife(equipItem->getEffect1());
				break;
			case RING_STR:
				//���÷��ָ� ������ ������ �ּ� �ִ�� ����
				_status->setStr(equipItem->getEffect1());
				//���Ⱑ ������ ���ⵥ������ 0�̹Ƿ� 
				if (_equipItem[EQUIP_WEAPON] == NULL)
				{
					_status->setMinAtt(0);
					_status->setMaxAtt(0);
				}
				//���������ϸ� ���ⵥ������
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
		//��1�� �Ⱥ����.
		else
		{
			//1���� ������ Ȯ���ؼ� �ϴ� ���� ������ ���
			switch (_equipItem[EQUIP_RING1]->getStatType())
			{
				//����� ���ȿ÷��ָ� ����� ���� ����
			case RING_LIFE:
				_status->setLife(-_equipItem[EQUIP_RING1]->getEffect1());
				break;
			case RING_STR:
				//���÷��ָ� ������ ������ �ּ� �ִ�� ����
				_status->setStr(-_equipItem[EQUIP_RING1]->getEffect1());
				//���Ⱑ ������ ���ⵥ������ 0�̹Ƿ� 
				if (_equipItem[EQUIP_WEAPON] == NULL)
				{
					_status->setMinAtt(0);
					_status->setMaxAtt(0);
				}
				//���������ϸ� ���ⵥ������
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
				//����� ���ȿ÷��ָ� ����� ���� ����
			case RING_LIFE:
				_status->setLife(equipItem->getEffect1());
				break;
			case RING_STR:
				//���÷��ָ� ������ ������ �ּ� �ִ�� ����
				_status->setStr(equipItem->getEffect1());
				//���Ⱑ ������ ���ⵥ������ 0�̹Ƿ� 
				if (_equipItem[EQUIP_WEAPON] == NULL)
				{
					_status->setMinAtt(0);
					_status->setMaxAtt(0);
				}
				//���������ϸ� ���ⵥ������
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
	//�������� ó��Ŭ����
	if (!isClickEquip)
	{
		for (int i = 0; i < MAXEQUIPPLACE; ++i)
		{
			//������� Ư��ĭ�� ������.
			if (PtInRect(&_equipPlaceRC[i], _ptMouse))
			{
				//�ٵ� �����Ǿ��ִ� �������� ����. --> �ƹ��ϵ� ��������
				if (_equipItem[i] == NULL) return false;

				//�����Ǿ� �ִٸ�
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
			//�κ��丮�� Ư��ĭ�� ������.
			if (PtInRect(&_inventoryRC[i], _ptMouse))
			{
				//Ư��ĭ�� ����̴�.
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
				//������ ����
			}
		}
		*/
	}
	/*
	//�������� ó�� Ŭ����
	if (!isClickInvenItem)
	{
		for (int i = 0; i < MAXINVENTORY; ++i)
		{
			//�κ��丮�� Ư��ĭ�� ������.
			if (PtInRect(&_inventoryRC[i], _ptMouse))
			{
				//�ٵ� �� ĭ�� �������� ���� --> �ƹ��ϵ� ��������
				if (_inventory[i] == NULL) return false;

				_clickIndex = i;
				_clickItemIndex = _itemIndex[i];
				//�������� �ִٸ� �������� ������ Ư�� ������ ����
				return true;
			}
		}
	}
	//Ŭ���� �������� �ִٸ�
	else
	{
		for (int i = 0; i < MAXINVENTORY; ++i)
		{
			//�κ��丮�� Ư��ĭ�� ������.
			if (PtInRect(&_inventoryRC[i], _ptMouse))
			{
				//Ư��ĭ�� ����̴�.
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
				//������ ����
			}
		}
	}
	//�������� Ŭ���� �ȵǸ� false�� ��ȯ�ȴ�.
	return false;
	*/
	return false;
}
void equip::equipUnInstall()
{
	//������ ������ ���Ȱ���
	//switch (_equipItem[_clickIndex]->getItemType())
	switch (_clickIndex)
	{
	case EQUIP_WEAPON:
			_status->setMinAtt(0);
			_status->setMaxAtt(0);
	case EQUIP_ARMOR:
		//�����������̸� ���ʹ��¸� ���ȴ�.
		if (_equipItem[EQUIP_HELMET] == NULL)
		{
			_status->setDef(0);
		}
		//��� �������̸� ���ʹ��� ��� �������۹����� �����ش�
		else
		{
			_status->setDef(0, _equipItem[EQUIP_HELMET]->getEffect1());
		}
		break;
	case EQUIP_HELMET:
		//���� �������̸� ��� ���¸� ���ش�.
		if (_equipItem[EQUIP_ARMOR] == NULL)
		{
			_status->setDef(0);
		}
		//���� �������̸� ��� ���� ��� ���� ������ �����ش�.
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
			//���Ⱑ ������ ���ⵥ������ 0�̹Ƿ� 
			if (_equipItem[EQUIP_WEAPON] == NULL)
			{
				_status->setMinAtt(0);
				_status->setMaxAtt(0);
			}
			//���������ϸ� ���ⵥ������
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
			//���Ⱑ ������ ���ⵥ������ 0�̹Ƿ� 
			if (_equipItem[EQUIP_WEAPON] == NULL)
			{
				_status->setMinAtt(0);
				_status->setMaxAtt(0);
			}
			//���������ϸ� ���ⵥ������
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