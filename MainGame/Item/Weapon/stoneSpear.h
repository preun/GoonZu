#pragma once
#include "itemParent.h"
class stoneSpear :
	public itemParent
{
public:
	stoneSpear();
	~stoneSpear();

	virtual HRESULT init();
	virtual void render();
};

