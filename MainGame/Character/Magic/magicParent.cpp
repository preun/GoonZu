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
	//��ų�� ���������
	if (_magicStat.isUsed)
	{
		//ī��Ʈ ������
		_count++;
		//�� ī��Ʈ�� ��Ÿ���� �Ѱ�ٸ�
		if (_count >= _magicStat.cooldownTime)
		{
			//��ų�� ��밡���ϵ��� �ٲٰ�
			_magicStat.isUsed = false;
			//ī��Ʈ �ʱ�ȭ
			_count = 0;
		}
	}
}

void magicParent::render()
{

}
