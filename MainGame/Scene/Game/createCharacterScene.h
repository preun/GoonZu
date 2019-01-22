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
	//3개의 캐릭터 선택 RC
	RECT _characterSelectRC[3];

	//생성 버튼
	RECT _createRC;

	//어떤 캐릭터를 선택했는지
	characterSelect _characterSelect;

	//캐릭터 이름 입력관련 변수들
	RECT _nameRC;					//이름칸 RC
	bool _isNameInput;				//이름 입력중이냐
	vector<char*> _vCharacterName;	//입력된 값 담는 벡터
	char _name[10];

public:
	createCharacterScene();
	~createCharacterScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void addImage();		//이미기 추가해주는 함수 이후 이미지는 여기서 add하는걸로
	void initialization();	//변수들 new선언 및 init 해주는 함수 이후 new 및 init은 여기서 하는걸로
	void singletonInit();	//init에서 싱글톤들 세팅해주는 함수 이후 세팅은 여기서 하는걸로

	void characterDraw(characterSelect num); //선택에 따른 캐릭터들 그려주는 함수
	void inputName();
};

