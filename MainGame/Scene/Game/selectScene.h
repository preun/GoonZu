#pragma once
#include "gameNode.h"
//#include "character.h"
enum selectCharacterNumber
{	
	FIRSTRC,
	SECONDRC,
	THIRDRC,
	NONERC
};

class character;

class selectScene :
	public gameNode
{
	//3���� ĳ���� ĭ
	RECT _characterSelectRC[3];

	//��ŸƮ ��ư ĭ
	RECT _startRC;

	//ĳ���� ���� ĭ
	RECT _createCharacterRC;

	//ĳ���� ���� ĭ
	RECT _deleteCharacterRC;

	//����� ĭ�� �����Ͽ�����
	selectCharacterNumber _selectCharacterNumber;

	char test[128];

public:
	selectScene();
	~selectScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void addImage();		//�̹̱� �߰����ִ� �Լ� ���� �̹����� ���⼭ add�ϴ°ɷ�
	void initialization();	//������ new���� �� init ���ִ� �Լ� ���� new �� init�� ���⼭ �ϴ°ɷ�
	void singletonInit();	//init���� �̱���� �������ִ� �Լ� ���� ������ ���⼭ �ϴ°ɷ�
};

