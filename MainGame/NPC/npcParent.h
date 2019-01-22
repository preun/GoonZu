#pragma once
#include "gameNode.h"
#include "animation.h"
#include "item.h"
#include "itemParent.h"

class itemManager;
class inventory;

enum npcType{
	NPC_EQUIP,	//장비파는 NPC
	NPC_POTION,	//포션파는 NPC
	NPC_QUEST	//퀘스트 주는 NPC
};
class npcParent :
	public gameNode
{
protected:
	npcType _npcType;	//npc 종류

	image* _npcImage;	//npc 이미지
	animation* _animation;	//npc애니메이션

	image* _npcNameImage;	//npc 위 이름 이미지
	image* _npcShopImage;	//npc 상점 이미지

	vector<tagItemIndex> _sellItemIndex;	//판매할 아이템 인덱스 벡터
	vector<itemParent*> _sellItem;			//판매할 아이템 목록
	vector<RECT> _sellItemRC;				//판매할 아이템 렉트

	int _clickIndex;		//무슨 아이템 클릭했냐
	bool _invenClick;		//팔 아이템을 인벤토리에서 클릭했냐

	RECT _buyRC;	//구매버튼 
	RECT _sellRC;	//판매버튼
	//통신위한 변수
	itemManager* _IM;
	inventory* _inven;
	//113 91 40, 20

	POINT	_pos;		//npc 좌표
	RECT _npcRC;
public:
	npcParent();
	~npcParent();

	virtual HRESULT init(POINT pos);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void clickNpc();
	virtual void buyItem();
	virtual void sellItem();

	void setClickIndex(int index) { _clickIndex = index; }

	void setItemManagerAddressLink(itemManager* IM) { _IM = IM; }
	void setInventoryAddressLink(inventory* inven){ _inven = inven; }
	//npc 타입 (안쓸거같음)
	//npcType getNpcType(){ return _npcType; }

	//npc 클릭하면 발생하는 이벤트
	//void npcClick();
};

