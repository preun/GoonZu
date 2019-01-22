#pragma once
#include "monsterParent.h"
class pigMonster :
	public monsterParent
{
private:
	image* _idleEffect;
	animation* _idleEffectAnimation;

public:
	pigMonster();
	~pigMonster();

	virtual HRESULT init();
	virtual HRESULT init(int respond);

	virtual void release();
	virtual void update();
	virtual void deadUpdate();

	virtual void addImage();
	virtual void drawIdleEffect();
	virtual void animationChange();
	//virtual void playerAttack();
	//virtual void render();

	
};

