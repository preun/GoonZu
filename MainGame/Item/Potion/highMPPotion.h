#pragma once
#include "itemParent.h"
class highMPPotion :
	public itemParent
{
public:
	highMPPotion();
	~highMPPotion();

	virtual HRESULT init();
	virtual void render();
};

