#pragma once
#include "npcParent.h"
class janggumi :
	public npcParent
{
public:
	janggumi();
	~janggumi();

	virtual HRESULT init(POINT pos);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void clickNpc();
	virtual void buyItem();
	virtual void sellItem();
};

