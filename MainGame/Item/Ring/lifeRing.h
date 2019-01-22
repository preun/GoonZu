#pragma once
#include "itemParent.h"
class lifeRing :
	public itemParent
{
public:
	lifeRing();
	~lifeRing();

	virtual HRESULT init();
	virtual void render();
};

