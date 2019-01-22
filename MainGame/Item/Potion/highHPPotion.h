#pragma once
#include "itemParent.h"
class highHPPotion :
	public itemParent
{
public:
	highHPPotion();
	~highHPPotion();

	virtual HRESULT init();
	virtual void render();
};

