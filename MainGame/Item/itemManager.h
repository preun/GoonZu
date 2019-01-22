#pragma once
#include "gameNode.h"
#include "simpleItem.h"

class itemManager :
	public gameNode
{
private:

	vector<itemParent*> _vArmor;
	vector<itemParent*>::iterator _viArmor;

	vector<itemParent*> _vWeapon;
	vector<itemParent*>::iterator _viWeapon;

	vector<itemParent*> _vNeck;
	vector<itemParent*>::iterator _viNeck;

	vector<itemParent*> _vRing;
	vector<itemParent*>::iterator _viRing;

	vector<itemParent*> _vPotion;
	vector<itemParent*>::iterator _viPotion;

	vector<itemParent*> _vHelmet;
	vector<itemParent*>::iterator _viHelmet;


public:
	itemManager();
	~itemManager();

	HRESULT init();
	void release();
	void update() ;
	void render() ;

	itemParent* findItem(itemType itemtype, int index);
};

