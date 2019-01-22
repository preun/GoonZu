#include "stdafx.h"
#include "monsterManager.h"


monsterManager::monsterManager()
{
}


monsterManager::~monsterManager()
{

}

HRESULT monsterManager::init(vector<int> respond, tagTile* hungtingTile, DWORD* huntingTileAtt)
{
	//���������� 5�� �ʱ�ȭ
	for (int i = 0; i < 5; ++i)
	{
		_respond[i] = respond[i];
	}

	//3���� ����
	for (int i = 0; i < 1; ++i)
	{
		monsterParent* tempMonster;
		tempMonster = new pigMonster;
		tempMonster->setPlaceTileAndAtt(hungtingTile, huntingTileAtt);
		tempMonster->init(_respond[RND->getInt(5)]);

		_vHuntingMonster.push_back(tempMonster);
	}

	return S_OK;
}
void monsterManager::release()
{

}
void monsterManager::update()
{

	if (KEYMANAGER->isOnceKeyDown('1')) _vHuntingMonster[0]->setIsDead(true);
	//if (KEYMANAGER->isOnceKeyDown('2')) _vHuntingMonster[1]->setIsDead(true);
//	if (KEYMANAGER->isOnceKeyDown('3')) _vHuntingMonster[2]->setIsDead(true);
	/*if (KEYMANAGER->isOnceKeyDown('4')) _vHuntingMonster[3]->setIsDead(true);
	if (KEYMANAGER->isOnceKeyDown('5')) _vHuntingMonster[4]->setIsDead(true);
	if (KEYMANAGER->isOnceKeyDown('6')) _vHuntingMonster[5]->setIsDead(true);
	if (KEYMANAGER->isOnceKeyDown('7')) _vHuntingMonster[6]->setIsDead(true);
	if (KEYMANAGER->isOnceKeyDown('8')) _vHuntingMonster[7]->setIsDead(true);
	if (KEYMANAGER->isOnceKeyDown('9')) _vHuntingMonster[8]->setIsDead(true);
	if (KEYMANAGER->isOnceKeyDown('0')) _vHuntingMonster[9]->setIsDead(true);*/


	for (int i = 0; i < _vHuntingMonster.size(); ++i)
	{
		//���Ͱ� ���׾������� ������ ������Ʈ�� ������
		if (!_vHuntingMonster[i]->getIsDead())
		_vHuntingMonster[i]->update();
		//���� ���� Ư�� ������Ʈ�� ������
		else
		{
			_vHuntingMonster[i]->deadUpdate();
			//������ 10�� ������
			if (_vHuntingMonster[i]->getRespondCount() > 1000)
			{
				//������ Ÿ���� �����Ѱ����� ������Ƕ� 
				_vHuntingMonster[i]->init(_respond[RND->getInt(5)]);
			}
		}
		//_vHuntingMonster[i]->getLevel();
	}
}
void monsterManager::render()
{
	
	for (int i = 0; i < _vHuntingMonster.size(); ++i)
	{
		char ttt[111];
		sprintf(ttt, "%d, %d, %d, %d, %d, %d", _vHuntingMonster[i]->getLevel(),_vHuntingMonster[i]->getHP() , _vHuntingMonster[i]->getIsDead(),
			_vHuntingMonster[i]->getRespondCount()	,_vHuntingMonster[i]->getTileIndexX(), _vHuntingMonster[i]->getTileIndexY());
		//TextOut(getMemDC(), 0, 20 * i, ttt, strlen(ttt));

		_vHuntingMonster[i]->render();
		//_vHuntingMonster[i]->getLevel();
	}
}

monsterParent* monsterManager::findClickMonster()
{
	//�ݺ��� ������
	for (int i = 0; i < _vHuntingMonster.size(); ++i)
	{
		//�������� �������� ����
		if (_vHuntingMonster[i]->getIsDead()) continue;

		//���������߿� Ŭ���Ǿ����� �� Ÿ����ʹ� �׳��̴�.
		if (PtInRect(&_vHuntingMonster[i]->getMonsterRC(), _ptMouse))
			return _vHuntingMonster[i];
	}
	//�ɸ��� �����Ƿ� NULL ��ȯ
	return NULL;
}