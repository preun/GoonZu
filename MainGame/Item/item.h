#pragma once

//제한인덱스
enum limitIndex{
	LEVEL_INDEX,
	STAT_INDEX,
	SKILL_INDEX
};

enum effectIndex{
	EFFECT_MINATT,
	EFFECT_MAXATT,
	EFFECT_DEF = 0,
	EFFECT_POTION = 0,
	EFFECT_RING = 0,
	EFFECT_NECK = 0
};

//아이템 종류
enum itemType{
	TYPE_WEAPON,	//무기
	TYPE_ARMOR,		//갑옷
	TYPE_HELMET,	//헬멧
	TYPE_RING,		//반지
	TYPE_NECK,		//목걸이
	TYPE_POTION		//포션
};

//포션 회복 종류
enum potionType{
	POTION_HP,
	POTION_MP,
	POTION_NONE
};

//목걸이가 올려주는 기술 & 무기의 장착 제한 기술종류
enum skillType{
	SKILL_SWORD,
	SKILL_SPEAR,
	SKILL_AXE,
	SKILL_STAFF,
	SKILL_BOW,
	SKILL_GUN,
	SKILL_NONE
};
/*검 창 도끼 지팡이 활 총 */
//반지 스탯 종류
enum statType{
	RING_STR,
	RING_LIFE,
	RING_NONE
};

//무기 스탯제한 타입
enum statLimitType{
	LIMIT_STR,
	LIMIT_DEX,
	LIMIT_INT,
	LIMIT_LIFE,
	LIMIT_LUK,
	LIMIT_NONE
};
/* image _itemImage;	//인벤 및 장비창에 보일 이미지
	int _levelLimit;		//장착 레벨제한
	int _statLimit;			//장착 스탯제한
	int _minAtt;		//무기 최소공격력
	int _maxAtt;		//무기 최대공격력
	int _def;			//방어구 방어력*/
struct tagItem
{
	image* itemImage;	//아이템이미지
	int limit[3];		//레벨, 스탯, 기술제한 순
	int effect[2];		//아이템 효과(무기는 최소, 최대 나머지는 0번쨰 인덱스만)
	int money;			//상점판매가격
	int invenNumber;	//인벤토리 몇번째 칸이냐
	int count;			//몇개들고있냐
};

//아이템 매니저에서 검색하기 위한 인수들의 구조체
struct tagItemIndex{
	itemType itemtype;	//무슨타입이냐
	int index;			//해당 아이템의 벡터에서 위치하는 인덱스
};