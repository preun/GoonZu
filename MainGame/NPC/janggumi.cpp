#include "stdafx.h"
#include "janggumi.h"
#include "inventory.h"

janggumi::janggumi()
{
}


janggumi::~janggumi()
{
}

HRESULT janggumi::init(POINT pos)
{
	_npcImage = IMAGEMANAGER->addFrameImage("�����", "./image/npc/�����.bmp", 145, 56, 5, 1, true, RGB(255, 0, 255));
	_npcNameImage = IMAGEMANAGER->addImage("�������", "./image/npc/ȣ������.bmp", 74, 14, true, RGB(255, 0, 255));
	_npcShopImage = IMAGEMANAGER->addImage("����", "./image/shop/����.bmp", 247, 281, true, RGB(255, 0, 255));

	_animation = new animation;
	_animation->init(_npcImage->getWidth(), _npcImage->getHeight(), _npcImage->getFrameWidth(), _npcImage->getHeight());
	_animation->setDefPlayFrame(false, true);

	_animation->start();
	_animation->setFPS(1);

	//���� ��ġ ����
	_pos = pos;
	_npcRC = RectMakeCenter(_pos.x, _pos.y, _npcImage->getFrameWidth(), _npcImage->getFrameHeight());
	return S_OK;
}
void janggumi::release()
{

}
void janggumi::update()
{
	_animation->frameUpdate(TIMEMANAGER->getElapsedTime() * 5);
}
void janggumi::render()
{
	_npcImage->aniRender(getMemDC(), CAMERAMANAGER->CameraRelativePointX(_npcRC.left),
		CAMERAMANAGER->CameraRelativePointY(_npcRC.top), _animation);
	//_npcImage->aniRender(getMemDC(), _npcRC.left, _npcRC.top, _animation);
}
void janggumi::clickNpc()
{
	_npcShopImage->render(getMemDC(), 0, 300);

	char test[111];
	strcpy(test, "�����");
	TextOut(getMemDC(), 0, 300, test, strlen(test));
}

void janggumi::buyItem()
{

}

void janggumi::sellItem()
{

}