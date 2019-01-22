#pragma once
#include "itemParent.h"
class cottonSkinHelmet :
	public itemParent
{
public:
	cottonSkinHelmet();
	~cottonSkinHelmet();

	virtual HRESULT init();
	virtual void render();
};

