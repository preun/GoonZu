#pragma once
#include "itemParent.h"
class gravelSpear :
	public itemParent
{
public:
	gravelSpear();
	~gravelSpear();

	virtual HRESULT init();
	virtual void render();
};

