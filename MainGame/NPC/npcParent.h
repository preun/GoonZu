#pragma once
#include "gameNode.h"
#include "animation.h"
#include "item.h"
#include "itemParent.h"

class itemManager;
class inventory;

enum npcType{
	NPC_EQUIP,	//����Ĵ� NPC
	NPC_POTION,	//�����Ĵ� NPC
	NPC_QUEST	//����Ʈ �ִ� NPC
};
class npcParent :
	public gameNode
{
protected:
	npcType _npcType;	//npc ����

	image* _npcImage;	//npc �̹���
	animation* _animation;	//npc�ִϸ��̼�

	image* _npcNameImage;	//npc �� �̸� �̹���
	image* _npcShopImage;	//npc ���� �̹���

	vector<tagItemIndex> _sellItemIndex;	//�Ǹ��� ������ �ε��� ����
	vector<itemParent*> _sellItem;			//�Ǹ��� ������ ���
	vector<RECT> _sellItemRC;				//�Ǹ��� ������ ��Ʈ

	int _clickIndex;		//���� ������ Ŭ���߳�
	bool _invenClick;		//�� �������� �κ��丮���� Ŭ���߳�

	RECT _buyRC;	//���Ź�ư 
	RECT _sellRC;	//�ǸŹ�ư
	//������� ����
	itemManager* _IM;
	inventory* _inven;
	//113 91 40, 20

	POINT	_pos;		//npc ��ǥ
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
	//npc Ÿ�� (�Ⱦ��Ű���)
	//npcType getNpcType(){ return _npcType; }

	//npc Ŭ���ϸ� �߻��ϴ� �̺�Ʈ
	//void npcClick();
};

