#pragma once
#include "itemParent.h"
class smallHPPotion :
	public itemParent
{
public:
	smallHPPotion();
	~smallHPPotion();

	virtual HRESULT init();
	virtual void render();
};

