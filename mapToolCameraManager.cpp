#include "stdafx.h"
#include "mapToolCameraManager.h"


mapToolCameraManager::mapToolCameraManager()
{
}


mapToolCameraManager::~mapToolCameraManager()
{

}


//카메라 초기 설정
HRESULT mapToolCameraManager::init(void)
{
	//초기 카메라 위치 배경 크기의 중앙으로 설정
	_camera.x = TILESIZEX / 2 - TILEWINSIZEX / 2;
	_camera.y = TILESIZEY / 2 - TILEWINSIZEY / 2;
	//_cameraCondition = MAPTOOL_CAMERA_FREE;
	//_aim = NULL;
	return S_OK;
}
void mapToolCameraManager::release(void)
{

}

//카메라 UPDATE() gameNode의 update()에서 실행된다.
void mapToolCameraManager::update(void)
{
	//switch (_cameraCondition)
	//{
	//case MAPTOOL_CAMERA_AIMING:
		cameraFollow();
	//	break;
	//case MAPTOOL_CAMERA_EFFECT:
	//	cameraEffecting();
	//	break;
	//}


}

//매개변수로 받는 RECT를 중심으로 카메라를 이동시키는 함수
void mapToolCameraManager::setCameraAim(RECT * rc)
{
	_aim = rc;

	int centerX, centerY;
	centerX = (rc->left + rc->right) / 2;
	centerY = (rc->top + rc->bottom) / 2;

	_camera.x = centerX - TILEWINSIZEX / 2;
	_camera.y = centerY - TILEWINSIZEY / 2;

	cameraRevision();
}


//매개변수로 받은 RC가 현재 카메라범위 안쪽에 있는지 판단하여 TRUE나 FALSE를 반환하는 함수
bool mapToolCameraManager::isInCamera(RECT rc)
{
	if (rc.right > _camera.x && rc.left<_camera.x - TILEWINSIZEX
		&& rc.bottom > _camera.y && rc.top < _camera.y - TILEWINSIZEY) return true;
	else return false;
}

//카메라가 화면 밖으로 나갈 시 보정해주는 함수
void mapToolCameraManager::cameraRevision()
{
	if (_camera.x < -(TILESIZEX - TILEWINSIZEX))
	{
		_camera.x = -(TILESIZEX - TILEWINSIZEX);
	}
	else if (_camera.x > TILESIZEX - TILEWINSIZEX)
	{
		_camera.x = TILESIZEX - TILEWINSIZEX;
	}

	if (_camera.y < 0)
	{
		_camera.y = 0;
	}
	else if (_camera.y > TILESIZEY - TILEWINSIZEY)
	{
		_camera.y = TILESIZEY - TILEWINSIZEY;
	}
}

//이펙트를 주고싶을때 쓰는함수 EFFECT 종류, 세기, 시간(초)
void mapToolCameraManager::setEffect(int effectIndex, float strong, float time)
{
	//if (_cameraCondition != MAPTOOL_CAMERA_EFFECT)
	//	_prevCameraCondition = _cameraCondition;
	//_cameraCondition = MAPTOOL_CAMERA_EFFECT;
	//_effectIndex = effectIndex;
	//_maxEffectT = time * 60;
	//_strong = strong;
	//_effectT = 0;
	//originX = _camera.x;
	//originY = _camera.y;
}

//이펙트 함수 _cameraCondition 이 CAMERA_EFFECT일때 실행된다.
void mapToolCameraManager::cameraEffecting()
{


	//switch (_effectIndex)
	//{
	//case MAPTOOL_EFFECT_SIN:
	//	_camera.x = originX + _strong * sinf(_effectT);
	//	_camera.y = originY + _strong * sinf(_effectT);
	//	break;
	//}
	////cameraRevision();
	//_effectT++;
	//
	//cameraRevision();
	//
	//if (_effectT > _maxEffectT)
	//{
	//	_cameraCondition = _prevCameraCondition;
	//}

}

void mapToolCameraManager::cameraMove(bool isX, float speed)
{
	//if (_cameraCondition == MAPTOOL_CAMERA_FREE)
	//{
	//	if (isX) _camera.x += speed;
	//	else _camera.y += speed;
	//
	//	cameraRevision();
	//}
}

void mapToolCameraManager::cameraFollow()
{
	int centerX, centerY;
	centerX = (_aim->left + _aim->right) / 2;
	centerY = (_aim->top + _aim->bottom) / 2;

	_camera.x = centerX - TILEWINSIZEX / 2;
	_camera.y = centerY - TILEWINSIZEY / 2;

	cameraRevision();
}


bool mapToolCameraManager::cameraRevisionLeft()
{
	if (_camera.x <-(TILESIZEX - TILEWINSIZEX))
	{
		return false;
	}
	
	return true;	
}
bool mapToolCameraManager::cameraRevisionTop()
{
	if (_camera.y < 0)
	{
		return false;
	}
	return true;
}
bool mapToolCameraManager::cameraRevisionRight()
{
if (_camera.x > TILESIZEX - TILEWINSIZEX)
	{
	return false;
	}
return true;
}
bool mapToolCameraManager::cameraRevisionBottom()
{
	if (_camera.y > TILESIZEY - TILEWINSIZEY)
	{
		return false;
	}
	return true;
}