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

	//��ų �������� �̹��� ���Ƴ����ֱ� ���� �̹��� ����
	image* _spearUI[MAXSPEARMAGIC];
	//â ��� ���� �迭
	magicParent* _spearMagic[MAXSPEARMAGIC];
	//���� �������� ���
	magicParent* _useMagic;

	//4�� ����� RC
	RECT _magicRC[MAXSPEARMAGIC];
	//��� ���� �ε���
	int _clickIndex;

public:
	magicUI();
	~magicUI();

	HRESULT init();
	void release();
	void update();
	void render();

	//UI ���� �Լ�
	void openMagicUI();
	//UI Ŭ�� �Լ�(��Ŭ������ ���Գ�)
	void clickMagicUI(bool isLClick);

	//��Ŭ������ ������ ���� ��ȯ
	magicParent* getUseMagic(){ return _useMagic; }
};

