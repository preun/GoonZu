#pragma once
#include "itemParent.h"
class strRing :
	public itemParent
{
public:
	strRing();
	~strRing();

	virtual HRESULT init();
	virtual void render();
};

