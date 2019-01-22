#pragma once
#include "singletonBase.h"
#include "tileNode.h"
#include <map>

//stdafx.h��  BACKGROUNDSIZEX,Y DEFINE�߰� CAMERAMANAGER DEFINE �߰� GAMENODE�� CAMERAMANAGER INIT() UPDATE()


//ī�޶� ���°�
//#define MAPTOOL_CAMERA_FREE 0 //ī�޶� �����Ӱ� �̵��� �� ����
//#define MAPTOOL_CAMERA_AIMING 1 //ī�޶� aim ���� ������ rc�� ����
//#define MAPTOOL_CAMERA_EFFECT 2 //ī�޶� ��鸲, ȿ�� ó��
//#define MAPTOOL_CAMERA_MOVING 3 //ī�޶� �̵�ó��

//����Ʈ

//#define EFFECT_POWF 0
//#define MAPTOOL_EFFECT_SIN 1
//#define EFFECT_SINPOWF 2
//#define EFFECT_SINPOWF2 3



class mapToolCameraManager : public singletonBase<mapToolCameraManager>
{
private:


	RECT* _aim;

	POINT _camera;

	int _cameraCondition;
	int _prevCameraCondition;

	int _effectIndex;
	float originX, originY;
	float _strong;
	float _effectT, _maxEffectT;

public:
	mapToolCameraManager();
	~mapToolCameraManager();

	HRESULT init(void);
	void release(void);
	void update(void);



	// �ش��ϴ� rc�� ī�޶� �����մϴ�.
	void setCameraAim(RECT* rc);

	// object�� ī�޶� ȭ�� ���ʿ� �ִ��� �˾Ƴ��ϴ�.
	bool isInCamera(RECT rc);

	void cameraMove(bool isX, float speed);

	void cameraFollow();


	// CAMERA_FREE, CAMERA_AIMING, CAMERA_EFFEICTING, CAMERA_MOVING�� ī�޶� ���¸� �����մϴ�.
	void setCameraCondition(int cameraCondition) { _cameraCondition = cameraCondition; }

	//ī�޶� ȭ��� ��ǥ�� ��ȯ�մϴ�.(rc)
	POINT CameraRelativePoint(RECT rc) { return{ rc.left - _camera.x, rc.top - _camera.y }; }
	//ī�޶� ȭ��� ��ǥ�� ��ȯ�մϴ�.(point)
	POINT CameraRelativePoint(POINT point) { return{ point.x - _camera.x, point.y - _camera.y }; }

	int CameraRelativePointX(int x) { return{ x - _camera.x }; }
	int CameraRelativePointY(int y) { return{ y - _camera.y }; }


	//ī�޶� ��ġ�� ����� �����Ѵ�.
	void cameraRevision();

	//ī�޶� �ʳ� �����߳� �� ��ȯ�ϴ� �Լ�
	bool cameraRevisionLeft();
	bool cameraRevisionTop();
	bool cameraRevisionRight();
	bool cameraRevisionBottom();

	// ī�޶� ����Ʈ ���� EFFECT_SIN,..., ����, �ð�(��)
	void setEffect(int effectIndex, float strong, float time);

	//ī�޶� ������
	void cameraEffecting();

	int getCameraCondition() { return _cameraCondition; }

	POINT getCameraPoint() { return _camera; }
};

