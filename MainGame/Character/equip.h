#pragma once
#include "gameNode.h"
#include "item.h"
#include "itemParent.h"
#include "inventory.h"
#include "itemManager.h"

#define MAXEQUIPPLACE 6
//�����ϴ°��� Ÿ��
enum equipType{
	EQUIP_WEAPON,	//����
	EQUIP_ARMOR,		//����
	EQUIP_HELMET,	//���
	EQUIP_RING1,		//����
	EQUIP_RING2,
	EQUIP_NECK		//�����
};

//��������ϸ� ���� ������ ���� ���漱��
class status;
//class inventory;

class equip :
	public gameNode
{
	//���� �����Ѱ��� 6��
	itemParent* _equipItem[MAXEQUIPPLACE];
	//���� �����Ѱ��� RC
	RECT	_equipPlaceRC[MAXEQUIPPLACE];

	//�����Ѱ��� ������ ���� -->�ؽ�Ʈ���Ϸ� �����ҋ� ����ҵ�
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

	//���â ����
	void equipOpen();
	//��� ����
	bool equipInstall(tagItemIndex equipItemIndex, itemParent* equipItem);
	//��� ����
	bool equipUnInstall(bool isClickEquip);
	//��� ����(�κ����� �� �Լ�)
	void equipUnInstall();

	image* getClickEquip(){
		return _inven->getIM()->findItem(_equipItemIndex[_clickIndex].itemtype, _equipItemIndex[_clickIndex].index)->getImage();
	}
	tagItemIndex getClickItem(){ return _equipItemIndex[_clickIndex]; }
	itemParent* getClickItemParent(){ return _equipItem[_clickIndex]; }
	
	//��� ������ ��������
	void equipStatus(itemParent* equipItem);
	//���� ������ ��������	�������			���̸� 2��° ���� ����, �����̸� 1���� ���� ����
	void equipStatus(itemParent* equipItem, bool isRing2Equip);

	POINT getWeponAtt(){ 
		if (_equipItem[EQUIP_WEAPON] == NULL) return{ 0, 0 };
		return{ _equipItem[EQUIP_WEAPON]->getEffect1(), _equipItem[EQUIP_WEAPON]->getEffect2() }; }

	void setStatusMemorryLink(status* tempStatus){ _status = tempStatus; }
	void setInventoryMemorryLink(inventory* inven){ _inven = inven; }
};

