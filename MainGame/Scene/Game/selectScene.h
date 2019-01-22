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
	//3개의 캐릭터 칸
	RECT _characterSelectRC[3];

	//스타트 버튼 칸
	RECT _startRC;

	//캐릭터 생성 칸
	RECT _createCharacterRC;

	//캐릭터 삭제 칸
	RECT _deleteCharacterRC;

	//몇번쨰 칸을 선택하였는지
	selectCharacterNumber _selectCharacterNumber;

	char test[128];

public:
	selectScene();
	~selectScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void addImage();		//이미기 추가해주는 함수 이후 이미지는 여기서 add하는걸로
	void initialization();	//변수들 new선언 및 init 해주는 함수 이후 new 및 init은 여기서 하는걸로
	void singletonInit();	//init에서 싱글톤들 세팅해주는 함수 이후 세팅은 여기서 하는걸로
};

