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
	//아이템패런츠형 포인터배열 20개
	itemParent* _inventory[MAXINVENTORY];
	//아이템 인덱스 구조체 배열
	tagItemIndex _itemIndex[MAXINVENTORY];	
	//클릭했을경우 아이템 정보 저장을 위한 그릇
	tagItemIndex _clickItemIndex;
	//처음 클릭할때 어떤 칸을 클릭했는지 알기위한 그릇
	int _clickIndex;
	//인벤토리 각 칸의 RC
	RECT _inventoryRC[MAXINVENTORY];
	//소지금
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

	//인벤토리 오픈
	void inventoryOpen();

	//상점 구매시 생기는 함수
	void buyItem(tagItemIndex tempItemIndex);

	//인벤토리 내 아이템 클릭
	bool inventoryClick(int isClickInvenItem);
	//인벤토리 내 아이템 클릭(장비용 함수)
	bool inventoryClick(tagItemIndex tempItemIndex);
	//인벤토리 아이템 팔기위한 클릭이벤트
	bool inventoryClick();
	//실질적으로 인벤토리에서 아이템 지우는 함수
	void inventoryItemSell();
	
	//퀵슬롯
	int quickF1();
	int quickF2();
	int quickF3();
	int quickF4();
	int quickF5();

	//인벤토리 내 아이템 버리기
	bool inventoryItemDrop();
	
	bool inventoryItemDrop(bool isEquipNull, tagItemIndex tempItemIndex );

	void setMoney(int money){ _money += money; }
	int getMoney(){ return _money; }
	//인벤토리 아이템 이미지 가져오기
	image* getInvenItem();

	tagItemIndex getClickItem(){ return _clickItemIndex; }
	itemParent* getClickItemParent(){ return _inventory[_clickIndex]; }

	void setIMMemoryAdressLink(itemManager* im) { _IM = im; }
	void setEquipMemoryAdressLink(equip* tempEquip){ _equip = tempEquip; }

	itemManager* getIM(){ return _IM; }
};

