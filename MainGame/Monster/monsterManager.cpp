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
	//리스폰지역 5개 초기화
	for (int i = 0; i < 5; ++i)
	{
		_respond[i] = respond[i];
	}

	//3마리 생성
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
		//몬스터가 안죽어있으면 몬스터의 업데이트를 돌리고
		if (!_vHuntingMonster[i]->getIsDead())
		_vHuntingMonster[i]->update();
		//죽은 몹은 특별 업데이트를 돌려라
		else
		{
			_vHuntingMonster[i]->deadUpdate();
			//죽은지 10초 지나면
			if (_vHuntingMonster[i]->getRespondCount() > 1000)
			{
				//리스폰 타일의 랜덤한곳에서 재생성되라 
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
	//반복문 돌리기
	for (int i = 0; i < _vHuntingMonster.size(); ++i)
	{
		//죽은놈은 검출하지 마라
		if (_vHuntingMonster[i]->getIsDead()) continue;

		//안죽은놈중에 클릭되었으면 내 타깃몬스터는 네놈이다.
		if (PtInRect(&_vHuntingMonster[i]->getMonsterRC(), _ptMouse))
			return _vHuntingMonster[i];
	}
	//걸린게 없으므로 NULL 반환
	return NULL;
}