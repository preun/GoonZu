#pragma once
#include "itemParent.h"
class cottonSkinArmor :
	public itemParent
{
public:
	cottonSkinArmor();
	~cottonSkinArmor();

	virtual HRESULT init();
	virtual void render();

};

