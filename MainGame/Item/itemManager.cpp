#include "stdafx.h"
#include "itemManager.h"


itemManager::itemManager()
{
}


itemManager::~itemManager()
{

}

HRESULT itemManager::init()
{
	//갑옷
	itemParent* tempArmor1 = new cowSkinArmor;
	tempArmor1->init();

	itemParent* tempArmor2 = new cottonSkinArmor;
	tempArmor2->init();

	_vArmor.push_back(tempArmor1);
	_vArmor.push_back(tempArmor2);

	//투구
	itemParent* tempHelmet1 = new cowSkinHelmet;
	tempHelmet1->init();

	itemParent* tempHelmet2 = new cottonSkinHelmet;
	tempHelmet2->init();

	_vHelmet.push_back(tempHelmet1);
	_vHelmet.push_back(tempHelmet2);

	//목걸이
	itemParent* tempNeck1 = new spearNeck;
	tempNeck1->init();

	_vNeck.push_back(tempNeck1);

	//포션
	itemParent* tempPotion1 = new smallHPPotion;
	tempPotion1->init();

	itemParent* tempPotion2 = new highHPPotion;
	tempPotion2->init();

	itemParent* tempPotion3 = new smallMPPotion;
	tempPotion3->init();

	itemParent* tempPotion4 = new highMPPotion;
	tempPotion4->init();

	_vPotion.push_back(tempPotion1);
	_vPotion.push_back(tempPotion2);
	_vPotion.push_back(tempPotion3);
	_vPotion.push_back(tempPotion4);

	//반지
	itemParent* tempRing1 = new lifeRing;
	tempRing1->init();

	itemParent* tempRing2 = new strRing;
	tempRing2->init();

	_vRing.push_back(tempRing1);
	_vRing.push_back(tempRing2);

	//무기
	itemParent* tempWeapon1 = new gravelSpear;
	tempWeapon1->init();

	itemParent* tempWeapon2 = new stoneSpear;
	tempWeapon2->init();

	_vWeapon.push_back(tempWeapon1);
	_vWeapon.push_back(tempWeapon2);

	return S_OK;
}

void itemManager::release()
{

}

void itemManager::update()
{

}

void itemManager::render()
{

}
itemParent* itemManager::findItem(itemType itemtype, int index)
{
	switch (itemtype)
	{
	case TYPE_WEAPON:
		return _vWeapon[index];
		break;
	case TYPE_ARMOR:
		return _vArmor[index];
		break;
	case TYPE_HELMET:
		return _vHelmet[index];
		break;
	case TYPE_RING:
		return _vRing[index];
		break;
	case TYPE_NECK:
		return _vNeck[index];
		break;
	case TYPE_POTION:
		return _vPotion[index];
		break;
	default:
		break;
	}
}