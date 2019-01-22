#pragma once
#include "itemParent.h"
class spearNeck :
	public itemParent
{
public:
	spearNeck();
	~spearNeck();

	virtual HRESULT init();
	virtual void render();
};

