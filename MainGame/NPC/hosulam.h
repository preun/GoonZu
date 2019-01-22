#pragma once
#include "npcParent.h"
class hosulam :
	public npcParent
{
public:
	hosulam();
	~hosulam();

	virtual HRESULT init(POINT pos);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void clickNpc();
	virtual void buyItem();
	virtual void sellItem();
};

