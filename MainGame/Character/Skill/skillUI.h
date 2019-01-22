#pragma once
#include "gameNode.h"
class skillUI :
	public gameNode
{
public:
	skillUI();
	~skillUI();

	HRESULT init();
	void release();
	void update();
	void render();

	void openSkillUI();
};

