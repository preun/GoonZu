#pragma once
#include "npcParent.h"
class musuri :
	public npcParent
{
public:
	musuri();
	~musuri();

	virtual HRESULT init(POINT pos);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void clickNpc();
	virtual void buyItem();
	virtual void sellItem();
};

