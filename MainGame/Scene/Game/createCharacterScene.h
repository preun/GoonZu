#pragma once
#include "gameNode.h"
#include <string>
#include <vector>
enum characterSelect{
	FIRSTCHAR,
	SECONDCHAR,
	THIRDCHAR,
	NONECHAR
};

class character;

class createCharacterScene :
	public gameNode
{
private:
	//3���� ĳ���� ���� RC
	RECT _characterSelectRC[3];

	//���� ��ư
	RECT _createRC;

	//� ĳ���͸� �����ߴ���
	characterSelect _characterSelect;

	//ĳ���� �̸� �Է°��� ������
	RECT _nameRC;					//�̸�ĭ RC
	bool _isNameInput;				//�̸� �Է����̳�
	vector<char*> _vCharacterName;	//�Էµ� �� ��� ����
	char _name[10];

public:
	createCharacterScene();
	~createCharacterScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void addImage();		//�̹̱� �߰����ִ� �Լ� ���� �̹����� ���⼭ add�ϴ°ɷ�
	void initialization();	//������ new���� �� init ���ִ� �Լ� ���� new �� init�� ���⼭ �ϴ°ɷ�
	void singletonInit();	//init���� �̱���� �������ִ� �Լ� ���� ������ ���⼭ �ϴ°ɷ�

	void characterDraw(characterSelect num); //���ÿ� ���� ĳ���͵� �׷��ִ� �Լ�
	void inputName();
};

