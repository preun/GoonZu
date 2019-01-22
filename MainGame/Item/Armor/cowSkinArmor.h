#pragma once
#include "itemParent.h"
class cowSkinArmor :
	public itemParent
{
public:
	cowSkinArmor();
	~cowSkinArmor();

	virtual HRESULT init();
	virtual void render();

	//virtual void release();
	//virtual void update();
	
};

