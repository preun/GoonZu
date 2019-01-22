#pragma once
#include "gameNode.h"
#include "itemParent.h"
#include "item.h"

#define MAXINVENTORY 20


class itemManager;
class equip;

class inventory :
	public gameNode
{
private:
	//�������з����� �����͹迭 20��
	itemParent* _inventory[MAXINVENTORY];
	//������ �ε��� ����ü �迭
	tagItemIndex _itemIndex[MAXINVENTORY];	
	//Ŭ��������� ������ ���� ������ ���� �׸�
	tagItemIndex _clickItemIndex;
	//ó�� Ŭ���Ҷ� � ĭ�� Ŭ���ߴ��� �˱����� �׸�
	int _clickIndex;
	//�κ��丮 �� ĭ�� RC
	RECT _inventoryRC[MAXINVENTORY];
	//������
	int _money;

	itemManager* _IM;
	equip* _equip;

public:
	inventory();
	~inventory();

	HRESULT init();
	void release();
	void update();
	void render();

	//�κ��丮 ����
	void inventoryOpen();

	//���� ���Ž� ����� �Լ�
	void buyItem(tagItemIndex tempItemIndex);

	//�κ��丮 �� ������ Ŭ��
	bool inventoryClick(int isClickInvenItem);
	//�κ��丮 �� ������ Ŭ��(���� �Լ�)
	bool inventoryClick(tagItemIndex tempItemIndex);
	//�κ��丮 ������ �ȱ����� Ŭ���̺�Ʈ
	bool inventoryClick();
	//���������� �κ��丮���� ������ ����� �Լ�
	void inventoryItemSell();
	
	//������
	int quickF1();
	int quickF2();
	int quickF3();
	int quickF4();
	int quickF5();

	//�κ��丮 �� ������ ������
	bool inventoryItemDrop();
	
	bool inventoryItemDrop(bool isEquipNull, tagItemIndex tempItemIndex );

	void setMoney(int money){ _money += money; }
	int getMoney(){ return _money; }
	//�κ��丮 ������ �̹��� ��������
	image* getInvenItem();

	tagItemIndex getClickItem(){ return _clickItemIndex; }
	itemParent* getClickItemParent(){ return _inventory[_clickIndex]; }

	void setIMMemoryAdressLink(itemManager* im) { _IM = im; }
	void setEquipMemoryAdressLink(equip* tempEquip){ _equip = tempEquip; }

	itemManager* getIM(){ return _IM; }
};

