#include "stdafx.h"
#include "cowSkinHelmet.h"


cowSkinHelmet::cowSkinHelmet()
{
}


cowSkinHelmet::~cowSkinHelmet()
{
}
HRESULT cowSkinHelmet::init()
{
	/*
	itemType _itemType;				//아이템 종류가 뭐냐
	potionType _potionType;			//포션아이템일경우 뭐를 회복시켜주냐
	skillType _skillType;			//목걸이아이템일경우 무슨 기술을 올려주냐
	statType _stayType;				//반지 아이템일경우 무슨 스탯을 올려주냐
	statLimitType _statLimitType;	//무기 아이템일경우 어떤 종류의 스탯 제한이 걸려있냐

	tagItem _item;					//아이템 구조체
	image* itemImage;	//아이템이미지
	int limit[3];		//레벨, 스탯, 기술제한 순
	int effect[2];		//아이템 효과(무기는 최소, 최대 나머지는 0번쨰 인덱스만)
	int money;			//상점판매가격
	int invenNumber;	//인벤토리 몇번째 칸이냐
	int count;			//몇개들고있냐
	*/
	_itemType = TYPE_HELMET;
	_potionType = POTION_NONE;
	_skillType = SKILL_NONE;
	_statType = RING_NONE;
	_statLimitType = LIMIT_NONE;

	_item.itemImage = IMAGEMANAGER->addImage("쇠가죽투구", "./image/equip/helmet/Hmt01.bmp", 34, 34, true, RGB(255, 0, 255));

	_item.limit[LEVEL_INDEX] = 0;		//레벨제한
	_item.limit[STAT_INDEX] = 0;		//스탯제한
	_item.limit[SKILL_INDEX] = 0;		//기술제한

	_item.effect[EFFECT_DEF] = 3;		//방어구 방어력
	_item.effect[EFFECT_MAXATT] = 0;	//

	_item.money = 400;	//상점 500원판매
	_item.invenNumber = 0; //일단 인벤에 없음
	_item.count = 0;


	return S_OK;
}

void cowSkinHelmet::render()
{

}