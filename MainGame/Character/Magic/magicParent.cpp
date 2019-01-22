#include "stdafx.h"
#include "magicParent.h"


magicParent::magicParent()
{
}


magicParent::~magicParent()
{

}

HRESULT magicParent::init()
{

	return S_OK;
}

void magicParent::release()
{

}

void magicParent::update()
{
	//스킬을 사용했으면
	if (_magicStat.isUsed)
	{
		//카운트 돌려라
		_count++;
		//그 카운트가 쿨타운을 넘겼다면
		if (_count >= _magicStat.cooldownTime)
		{
			//스킬은 사용가능하도록 바꾸고
			_magicStat.isUsed = false;
			//카운트 초기화
			_count = 0;
		}
	}
}

void magicParent::render()
{

}
