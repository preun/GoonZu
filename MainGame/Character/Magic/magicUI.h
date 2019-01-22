#pragma once
#include "gameNode.h"
#include "magicParent.h"
#include "taesusingong.h"
#include "addMagicDamage.h"
#include "dropCri.h"
#include "waterDragonUP.h"


#define MAXSPEARMAGIC 4

class magicUI :
	public gameNode
{
private:

	//스킬 눌렀을때 이미지 갈아끼워주기 위한 이미지 변수
	image* _spearUI[MAXSPEARMAGIC];
	//창 기술 담을 배열
	magicParent* _spearMagic[MAXSPEARMAGIC];
	//내가 쓰기위한 기술
	magicParent* _useMagic;

	//4개 기술의 RC
	RECT _magicRC[MAXSPEARMAGIC];
	//기술 선택 인덱스
	int _clickIndex;

public:
	magicUI();
	~magicUI();

	HRESULT init();
	void release();
	void update();
	void render();

	//UI 오픈 함수
	void openMagicUI();
	//UI 클릭 함수(좌클릭으로 들어왔냐)
	void clickMagicUI(bool isLClick);

	//우클릭으로 설정한 마법 반환
	magicParent* getUseMagic(){ return _useMagic; }
};

