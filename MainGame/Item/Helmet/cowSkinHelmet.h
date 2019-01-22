#pragma once
#include "itemParent.h"
class cowSkinHelmet :
	public itemParent
{
public:
	cowSkinHelmet();
	~cowSkinHelmet();

	virtual HRESULT init();
	virtual void render();
};

