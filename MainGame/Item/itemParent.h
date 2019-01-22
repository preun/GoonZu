#pragma once
#include "gameNode.h"
#include "item.h"

class itemParent :
	public gameNode
{
protected:

	itemType _itemType;				//아이템 종류가 뭐냐
	potionType _potionType;			//포션아이템일경우 뭐를 회복시켜주냐
	skillType _skillType;			//목걸이아이템일경우 무슨 기술을 올려주냐
	statType _statType;				//반지 아이템일경우 무슨 스탯을 올려주냐
	statLimitType _statLimitType;	//무기 아이템일경우 어떤 종류의 스탯 제한이 걸려있냐

	tagItem _item;					//아이템 구조체
	/*
	enum itemType{
	TYPE_WEAPON,	//무기
	TYPE_ARMOR,		//갑옷
	TYPE_HELMET,	//헬멧
	TYPE_RIGN,		//반지
	TYPE_NECK,		//목걸이
	TYPE_POTION		//포션
};

//포션 회복 종류
enum potionType{
	POTION_HP,
	POTION_MP
};

//목걸이 기술종류
enum skillType{
	SKILL_SPEAR
};

//반지 스탯 종류
enum statType{
	RIGN_STR,
	RIGN_LIFE
};
	*/
	

	/*

무기 : 석창 돌창
레벨, 스탯, 기술제한, 공격력
갑옷 : 쇠가죽 갑옷, 면피 갑옷
레벨 제한, 방어력
투구 : 쇠가죽 투구, 면피 투구
레벨제한, 방어력
목걸이 : 창술목걸이
레벨제한, 어떤 기술 상승
반지 : 생명의반지, 근력의반지
레벨제한, 오르는스탯 및 수치
포션 : 십전대보탕, 우황청심원
사군자탕, 독삼탕



	*/

public:
	itemParent();
	~itemParent();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	image* getImage(){ return _item.itemImage; }

	int getMoney(){ return _item.money; }
	itemType getItemType(){ return _itemType; }
	statType getStatType(){	return _statType; }				//반지 아이템일경우 무슨 스탯을 올려주냐
	//0이면 HP, 1이면 MP
	potionType getPotionType(){ return _potionType; }

	//무기의 최소공격력, 방어구들의 방어력, 포션의 회복량 등
	int getEffect1(){ return _item.effect[0]; }
	//무기의 최대공격력
	int getEffect2(){ return _item.effect[1]; }
	//장비의 레벨제한
	int getLimitLevel(){ return _item.limit[0]; }
	//무기의 스탯제한
	int getLimitStat(){ return _item.limit[1]; }
	//무기의 기술제한
	int getLimitSkill(){ return _item.limit[2]; }
	//포션의 갯수
	int getItemCount(){ return _item.count; }
	void setItemCount(int count){ _item.count += count; }
	/*
	itemType _itemType;				//아이템 종류가 뭐냐
	potionType _potionType;			//포션아이템일경우 뭐를 회복시켜주냐
	skillType _skillType;			//목걸이아이템일경우 무슨 기술을 올려주냐
	statType _statType;				//반지 아이템일경우 무슨 스탯을 올려주냐
	statLimitType _statLimitType;	//무기 아이템일경우 어떤 종류의 스탯 제한이 걸려있냐

	tagItem _item;					//아이템 구조체
	*/
};

