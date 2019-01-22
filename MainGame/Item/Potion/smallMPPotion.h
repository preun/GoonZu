#pragma once
#include "itemParent.h"
class smallMPPotion :
	public itemParent
{
public:
	smallMPPotion();
	~smallMPPotion();

	virtual HRESULT init();
	virtual void render();
};

