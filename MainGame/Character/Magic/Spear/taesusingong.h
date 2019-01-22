#pragma once
#include "magicParent.h"
class taesusingong :
	public magicParent
{
public:
	taesusingong();
	~taesusingong();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};

