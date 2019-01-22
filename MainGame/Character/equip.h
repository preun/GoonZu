#pragma once
#include "gameNode.h"
#include "item.h"
#include "itemParent.h"
#include "inventory.h"
#include "itemManager.h"

#define MAXEQUIPPLACE 6
//장착하는곳의 타입
enum equipType{
	EQUIP_WEAPON,	//무기
	EQUIP_ARMOR,		//갑옷
	EQUIP_HELMET,	//헬멧
	EQUIP_RING1,		//반지
	EQUIP_RING2,
	EQUIP_NECK		//목걸이
};

//장비장착하면 스탯 조절을 위한 전방선언
class status;
//class inventory;

class equip :
	public gameNode
{
	//장착 가능한곳은 6개
	itemParent* _equipItem[MAXEQUIPPLACE];
	//장착 가능한곳의 RC
	RECT	_equipPlaceRC[MAXEQUIPPLACE];

	//장착한곳의 아이템 정보 -->텍스트파일로 저장할떄 사용할듯
	tagItemIndex _equipItemIndex[MAXEQUIPPLACE];

	int _clickIndex;

	status* _status;
	inventory* _inven;
public:
	equip();
	~equip();

	HRESULT init();
	void release();
	void update();
	void render();

	//장비창 오픈
	void equipOpen();
	//장비 장착
	bool equipInstall(tagItemIndex equipItemIndex, itemParent* equipItem);
	//장비 해제
	bool equipUnInstall(bool isClickEquip);
	//장비 해제(인벤에서 쓸 함수)
	void equipUnInstall();

	image* getClickEquip(){
		return _inven->getIM()->findItem(_equipItemIndex[_clickIndex].itemtype, _equipItemIndex[_clickIndex].index)->getImage();
	}
	tagItemIndex getClickItem(){ return _equipItemIndex[_clickIndex]; }
	itemParent* getClickItemParent(){ return _equipItem[_clickIndex]; }
	
	//장비 장착시 스탯조절
	void equipStatus(itemParent* equipItem);
	//반지 장착시 스탯조절	장착장비			참이면 2번째 반지 장착, 거짓이면 1번쨰 반지 장착
	void equipStatus(itemParent* equipItem, bool isRing2Equip);

	POINT getWeponAtt(){ 
		if (_equipItem[EQUIP_WEAPON] == NULL) return{ 0, 0 };
		return{ _equipItem[EQUIP_WEAPON]->getEffect1(), _equipItem[EQUIP_WEAPON]->getEffect2() }; }

	void setStatusMemorryLink(status* tempStatus){ _status = tempStatus; }
	void setInventoryMemorryLink(inventory* inven){ _inven = inven; }
};

