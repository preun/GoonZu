#include "stdafx.h"
#include "pigMonster.h"
#include "character.h"

pigMonster::pigMonster()
{
}


pigMonster::~pigMonster()
{
	
}

HRESULT pigMonster::init()
{
	addImage();
	

	_monsterLevel = rndLevel(2);
	//_dropExp;	//�������ġ(������ �ɶ����� ��������)
	//_dropMoney;	//��� ��(������ �ɋ����� ��������)

	_maxHP = _monsterLevel * 6;		//���� �ִ� ��(������ �ɋ����� �������� 
	_currentHP = _maxHP;	//���� ���� ��

	_damage = _monsterLevel * 2;		//���� ��(������ �ɶ����� ��������)
	_def = _monsterLevel * 1;		//���� ����(������ �ɶ����� ��������)

	_isDead = false;	//���Ͱ� �׾���
	_respondCount = 0;	//���Ͱ� �װ� ������ �ð�

	_playPlayer = NULL;
	return S_OK;
}
HRESULT pigMonster::init(int respond)
{
	addImage();

	_monsterLevel = rndLevel(2);
	//_dropExp;	//�������ġ(������ �ɶ����� ��������)
	//_dropMoney;	//��� ��(������ �ɋ����� ��������)

	_maxHP = _monsterLevel * 6;		//���� �ִ� ��(������ �ɋ����� �������� 
	_currentHP = _maxHP;	//���� ���� ��

	_damage = _monsterLevel * 4;		//���� ��(������ �ɶ����� ��������)
	_def = _monsterLevel * 1;		//���� ����(������ �ɶ����� ��������)

	_isDead = false;	//���Ͱ� �׾���
	_respondCount = 0;	//���Ͱ� �װ� ������ �ð�

	_renderX = _HuntingPlaceTile[respond].getCenterPoint().x - _monsterImage->getFrameWidth() / 2 ;
	_renderY = _HuntingPlaceTile[respond].getCenterPoint().y - _monsterImage->getFrameHeight() / 2;

	_x = _HuntingPlaceTile[respond].getCenterPoint().x;
	_y = _HuntingPlaceTile[respond].getCenterPoint().y;

	_destTileIndexX = _tileIndexX = respond / 20;
	_destTileIndexY = _tileIndexY = respond % 20;

	_attackDelay = 0;
	_playPlayer = NULL;

	_monsterState = MON_IDLE;

	_moveCount = RND->getFromIntTo(100, 300);
	_count = 0;
	_angle = 0;
	
	_aStar = new aStar;
	_aStar->init();

	_idleEffectAnimation = new animation;
	_idleEffectAnimation -> init(IMAGEMANAGER->findImage("�����⺻ȿ��")->getWidth(), IMAGEMANAGER->findImage("�����⺻ȿ��")->getHeight(),
		IMAGEMANAGER->findImage("�����⺻ȿ��")->getFrameWidth(), IMAGEMANAGER->findImage("�����⺻ȿ��")->getFrameHeight());
	_idleEffectAnimation->setDefPlayFrame(true, true);
	_idleEffectAnimation->start();
	_idleEffectAnimation->setFPS(1);

	//�⺻
	_animationArray[MON_IDLE] = new animation;
	_animationArray[MON_IDLE]->init(IMAGEMANAGER->findImage("�����⺻")->getWidth(), IMAGEMANAGER->findImage("�����⺻")->getHeight(),
		IMAGEMANAGER->findImage("�����⺻")->getFrameWidth(), IMAGEMANAGER->findImage("�����⺻")->getFrameHeight());
	_animationArray[MON_IDLE]->setDefPlayFrame(false, true);
	_animationArray[MON_IDLE]->start();
	_animationArray[MON_IDLE]->setFPS(1);

	//������ �ȱ�
	_animationArray[MON_RIGHT] = new animation;
	_animationArray[MON_RIGHT]->init(IMAGEMANAGER->findImage("����������")->getWidth(), IMAGEMANAGER->findImage("����������")->getHeight(),
		IMAGEMANAGER->findImage("����������")->getFrameWidth(), IMAGEMANAGER->findImage("����������")->getFrameHeight());
	_animationArray[MON_RIGHT]->setDefPlayFrame(false, true);
	_animationArray[MON_RIGHT]->start();
	_animationArray[MON_RIGHT]->setFPS(1);

	//������ �Ʒ� �ȱ�
	_animationArray[MON_RIGHTDOWN] = new animation;
	_animationArray[MON_RIGHTDOWN]->init(IMAGEMANAGER->findImage("���������ʾƷ�")->getWidth(), IMAGEMANAGER->findImage("���������ʾƷ�")->getHeight(),
		IMAGEMANAGER->findImage("���������ʾƷ�")->getFrameWidth(), IMAGEMANAGER->findImage("���������ʾƷ�")->getFrameHeight());
	_animationArray[MON_RIGHTDOWN]->setDefPlayFrame(false, true);
	_animationArray[MON_RIGHTDOWN]->start();
	_animationArray[MON_RIGHTDOWN]->setFPS(1);

	//�Ʒ� �ȱ�
	_animationArray[MON_DOWN] = new animation;
	_animationArray[MON_DOWN]->init(IMAGEMANAGER->findImage("�����Ʒ�")->getWidth(), IMAGEMANAGER->findImage("�����Ʒ�")->getHeight(),
		IMAGEMANAGER->findImage("�����Ʒ�")->getFrameWidth(), IMAGEMANAGER->findImage("�����Ʒ�")->getFrameHeight());
	_animationArray[MON_DOWN]->setDefPlayFrame(false, true);
	_animationArray[MON_DOWN]->start();
	_animationArray[MON_DOWN]->setFPS(1);

	//���� �Ʒ� �ȱ�
	_animationArray[MON_LEFTDOWN] = new animation;
	_animationArray[MON_LEFTDOWN]->init(IMAGEMANAGER->findImage("�������ʾƷ�")->getWidth(), IMAGEMANAGER->findImage("�������ʾƷ�")->getHeight(),
		IMAGEMANAGER->findImage("�������ʾƷ�")->getFrameWidth(), IMAGEMANAGER->findImage("�������ʾƷ�")->getFrameHeight());
	_animationArray[MON_LEFTDOWN]->setDefPlayFrame(false, true);
	_animationArray[MON_LEFTDOWN]->start();
	_animationArray[MON_LEFTDOWN]->setFPS(1);

	//���� �ȱ�
	_animationArray[MON_LEFT] = new animation;
	_animationArray[MON_LEFT]->init(IMAGEMANAGER->findImage("��������")->getWidth(), IMAGEMANAGER->findImage("��������")->getHeight(),
		IMAGEMANAGER->findImage("��������")->getFrameWidth(), IMAGEMANAGER->findImage("��������")->getFrameHeight());
	_animationArray[MON_LEFT]->setDefPlayFrame(false, true);
	_animationArray[MON_LEFT]->start();
	_animationArray[MON_LEFT]->setFPS(1);

	//���� �� �ȱ�
	_animationArray[MON_LEFTUP] = new animation;
	_animationArray[MON_LEFTUP]->init(IMAGEMANAGER->findImage("����������")->getWidth(), IMAGEMANAGER->findImage("����������")->getHeight(),
		IMAGEMANAGER->findImage("����������")->getFrameWidth(), IMAGEMANAGER->findImage("����������")->getFrameHeight());
	_animationArray[MON_LEFTUP]->setDefPlayFrame(false, true);
	_animationArray[MON_LEFTUP]->start();
	_animationArray[MON_LEFTUP]->setFPS(1);

	//�� �ȱ�
	_animationArray[MON_UP] = new animation;
	_animationArray[MON_UP]->init(IMAGEMANAGER->findImage("������")->getWidth(), IMAGEMANAGER->findImage("������")->getHeight(),
		IMAGEMANAGER->findImage("������")->getFrameWidth(), IMAGEMANAGER->findImage("������")->getFrameHeight());
	_animationArray[MON_UP]->setDefPlayFrame(false, true);
	_animationArray[MON_UP]->start();
	_animationArray[MON_UP]->setFPS(1);

	//������ �� �ȱ�
	_animationArray[MON_RIGHTUP] = new animation;
	_animationArray[MON_RIGHTUP]->init(IMAGEMANAGER->findImage("������������")->getWidth(), IMAGEMANAGER->findImage("������������")->getHeight(),
		IMAGEMANAGER->findImage("������������")->getFrameWidth(), IMAGEMANAGER->findImage("������������")->getFrameHeight());
	_animationArray[MON_RIGHTUP]->setDefPlayFrame(false, true);
	_animationArray[MON_RIGHTUP]->start();
	_animationArray[MON_RIGHTUP]->setFPS(1);

	//������ ����
	_animationArray[MON_RIGHT_ATTACK] = new animation;
	_animationArray[MON_RIGHT_ATTACK]->init(IMAGEMANAGER->findImage("���������ʰ���")->getWidth(), IMAGEMANAGER->findImage("���������ʰ���")->getHeight(),
		IMAGEMANAGER->findImage("���������ʰ���")->getFrameWidth(), IMAGEMANAGER->findImage("���������ʰ���")->getFrameHeight());
	_animationArray[MON_RIGHT_ATTACK]->setDefPlayFrame(false, true);
	_animationArray[MON_RIGHT_ATTACK]->start();
	_animationArray[MON_RIGHT_ATTACK]->setFPS(1);
	
	//������ �Ʒ� ����
	_animationArray[MON_RIGHTDOWN_ATTACK] = new animation;
	_animationArray[MON_RIGHTDOWN_ATTACK]->init(IMAGEMANAGER->findImage("���������ʾƷ�����")->getWidth(), IMAGEMANAGER->findImage("���������ʾƷ�����")->getHeight(),
		IMAGEMANAGER->findImage("���������ʾƷ�����")->getFrameWidth(), IMAGEMANAGER->findImage("���������ʾƷ�����")->getFrameHeight());
	_animationArray[MON_RIGHTDOWN_ATTACK]->setDefPlayFrame(false, true);
	_animationArray[MON_RIGHTDOWN_ATTACK]->start();
	_animationArray[MON_RIGHTDOWN_ATTACK]->setFPS(1);
	
	//�Ʒ� ����
	_animationArray[MON_DOWN_ATTACK] = new animation;
	_animationArray[MON_DOWN_ATTACK]->init(IMAGEMANAGER->findImage("�����Ʒ�����")->getWidth(), IMAGEMANAGER->findImage("�����Ʒ�����")->getHeight(),
		IMAGEMANAGER->findImage("�����Ʒ�����")->getFrameWidth(), IMAGEMANAGER->findImage("�����Ʒ�����")->getFrameHeight());
	_animationArray[MON_DOWN_ATTACK]->setDefPlayFrame(false, true);
	_animationArray[MON_DOWN_ATTACK]->start();
	_animationArray[MON_DOWN_ATTACK]->setFPS(1);
	
	//���� �Ʒ� ����
	_animationArray[MON_LEFTDOWN_ATTACK] = new animation;
	_animationArray[MON_LEFTDOWN_ATTACK]->init(IMAGEMANAGER->findImage("�������ʾƷ�����")->getWidth(), IMAGEMANAGER->findImage("�������ʾƷ�����")->getHeight(),
		IMAGEMANAGER->findImage("�������ʾƷ�����")->getFrameWidth(), IMAGEMANAGER->findImage("�������ʾƷ�����")->getFrameHeight());
	_animationArray[MON_LEFTDOWN_ATTACK]->setDefPlayFrame(false, true);
	_animationArray[MON_LEFTDOWN_ATTACK]->start();
	_animationArray[MON_LEFTDOWN_ATTACK]->setFPS(1);
	
	//���� ����
	_animationArray[MON_LEFT_ATTACK] = new animation;
	_animationArray[MON_LEFT_ATTACK]->init(IMAGEMANAGER->findImage("�������ʰ���")->getWidth(), IMAGEMANAGER->findImage("�������ʰ���")->getHeight(),
		IMAGEMANAGER->findImage("�������ʰ���")->getFrameWidth(), IMAGEMANAGER->findImage("�������ʰ���")->getFrameHeight());
	_animationArray[MON_LEFT_ATTACK]->setDefPlayFrame(false, true);
	_animationArray[MON_LEFT_ATTACK]->start();
	_animationArray[MON_LEFT_ATTACK]->setFPS(1);
	
	//���� �� ����
	_animationArray[MON_LEFTUP_ATTACK] = new animation;
	_animationArray[MON_LEFTUP_ATTACK]->init(IMAGEMANAGER->findImage("��������������")->getWidth(), IMAGEMANAGER->findImage("��������������")->getHeight(),
		IMAGEMANAGER->findImage("��������������")->getFrameWidth(), IMAGEMANAGER->findImage("��������������")->getFrameHeight());
	_animationArray[MON_LEFTUP_ATTACK]->setDefPlayFrame(false, true);
	_animationArray[MON_LEFTUP_ATTACK]->start();
	_animationArray[MON_LEFTUP_ATTACK]->setFPS(1);
	
	//�� ����
	_animationArray[MON_UP_ATTACK] = new animation;
	_animationArray[MON_UP_ATTACK]->init(IMAGEMANAGER->findImage("����������")->getWidth(), IMAGEMANAGER->findImage("����������")->getHeight(),
		IMAGEMANAGER->findImage("����������")->getFrameWidth(), IMAGEMANAGER->findImage("����������")->getFrameHeight());
	_animationArray[MON_UP_ATTACK]->setDefPlayFrame(false, true);
	_animationArray[MON_UP_ATTACK]->start();
	_animationArray[MON_UP_ATTACK]->setFPS(1);
	
	//������ �� ����
	_animationArray[MON_RIGHTUP_ATTACK] = new animation;
	_animationArray[MON_RIGHTUP_ATTACK]->init(IMAGEMANAGER->findImage("����������������")->getWidth(), IMAGEMANAGER->findImage("����������������")->getHeight(),
		IMAGEMANAGER->findImage("����������������")->getFrameWidth(), IMAGEMANAGER->findImage("����������������")->getFrameHeight());
	_animationArray[MON_RIGHTUP_ATTACK]->setDefPlayFrame(false, true);
	_animationArray[MON_RIGHTUP_ATTACK]->start();
	_animationArray[MON_RIGHTUP_ATTACK]->setFPS(1);



	_animation = _animationArray[MON_IDLE]; //�ʱⰪ�� ���� �⺻

	return S_OK;
}
void pigMonster::addImage()
{
	_idleEffect = IMAGEMANAGER->addFrameImage("�����⺻ȿ��", "./image/monster/pig/����idle1.bmp", 114, 30, 3, 1, true, RGB(255, 0, 255));

	_monsterImage = IMAGEMANAGER->addFrameImage("�����⺻", "./image/monster/pig/����idle.bmp", 24, 38, 1, 1, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("����������", "./image/monster/pig/����right.bmp", 300, 41, 6, 1, true, RGB(255, 0, 255)); //���� �̹���
	IMAGEMANAGER->addFrameImage("���������ʾƷ�", "./image/monster/pig/����rightdown.bmp", 168, 39, 4, 1, true, RGB(255, 0, 255)); 
	IMAGEMANAGER->addFrameImage("�����Ʒ�", "./image/monster/pig/����down.bmp", 96, 39, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�������ʾƷ�", "./image/monster/pig/����leftdown.bmp", 168, 38, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��������", "./image/monster/pig/����left.bmp", 300, 41, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����������", "./image/monster/pig/����leftup.bmp", 168, 50, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������", "./image/monster/pig/����up.bmp", 96, 47, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������������", "./image/monster/pig/����rightup.bmp", 168, 50, 4, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("���������ʰ���", "./image/monster/pig/����rightattack.bmp", 345, 59, 5, 1, true, RGB(255, 0, 255)); //���� �̹���
	IMAGEMANAGER->addFrameImage("���������ʾƷ�����", "./image/monster/pig/����rightdownattack.bmp", 260, 45, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�����Ʒ�����", "./image/monster/pig/����downattack.bmp", 190, 45, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�������ʾƷ�����", "./image/monster/pig/����leftdownattack.bmp", 260, 45, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�������ʰ���", "./image/monster/pig/����leftattack.bmp", 345, 59, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��������������", "./image/monster/pig/����leftupattack.bmp", 260, 57, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����������", "./image/monster/pig/����upattack.bmp", 190, 65, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����������������", "./image/monster/pig/����rightupattack.bmp", 260, 57, 5, 1, true, RGB(255, 0, 255));

}
void pigMonster::drawIdleEffect()
{
	if (_monsterState == MON_IDLE)
	{
		_idleEffect->aniRender(getMemDC(), CAMERAMANAGER->CameraRelativePointX(_renderX), CAMERAMANAGER->CameraRelativePointY(_renderY) - 30, _idleEffectAnimation);
	}
}
void pigMonster::release()
{

}
void pigMonster::update()
{
	_animation->frameUpdate(TIMEMANAGER->getElapsedTime() * 5);
	_idleEffectAnimation->frameUpdate(TIMEMANAGER->getElapsedTime());
	//���� ���°� ������ �ִ� ���¸�
	if (_monsterState == MON_IDLE)
	{
		_count++;
	}
	if (_playPlayer != NULL)
	{
		if (_attackDelay < 250) _attackDelay++;
		playerAttack();
	}
	
	mosterActionDecide();
	animationChange();
	//�������� �̷��� �ϸ� �ɵ�
	//���Ͱ� �׾����� ������ ī��Ʈ�� �۵����Ѷ�
	//if (_isDead) _respondCount++;

	////���� �ൿ ����
	//else
	//{

	//}

	////1õ�� �Ѿ�� ���� ��Ȱ�Ѵ�.
	//if (_respondCount > 1000)
	//{
	//	init();
	//}
}
void pigMonster::animationChange()
{
	switch (_monsterState)
	{
	case MON_IDLE:
		_monsterImage = IMAGEMANAGER->findImage("�����⺻");
		_animation = _animationArray[MON_IDLE];
		break;
	case MON_RIGHT:
		_monsterImage = IMAGEMANAGER->findImage("����������");
		_animation = _animationArray[MON_RIGHT];
		break;
	case MON_RIGHTDOWN:
		_monsterImage = IMAGEMANAGER->findImage("���������ʾƷ�");
		_animation = _animationArray[MON_RIGHTDOWN];
		break;
	case MON_DOWN:
		_monsterImage = IMAGEMANAGER->findImage("�����Ʒ�");
		_animation = _animationArray[MON_DOWN];
		break;
	case MON_LEFTDOWN:
		_monsterImage = IMAGEMANAGER->findImage("�������ʾƷ�");
		_animation = _animationArray[MON_LEFTDOWN];
		break;
	case MON_LEFT:
		_monsterImage = IMAGEMANAGER->findImage("��������");
		_animation = _animationArray[MON_LEFT];
		break;
	case MON_LEFTUP:
		_monsterImage = IMAGEMANAGER->findImage("����������");
		_animation = _animationArray[MON_LEFTUP];
		break;
	case MON_UP:
		_monsterImage = IMAGEMANAGER->findImage("������");
		_animation = _animationArray[MON_UP];
		break;
	case MON_RIGHTUP:
		_monsterImage = IMAGEMANAGER->findImage("������������");
		_animation = _animationArray[MON_RIGHTUP];
		break;
		case MON_RIGHT_ATTACK:
			_monsterImage = IMAGEMANAGER->findImage("���������ʰ���");
			_animation = _animationArray[MON_RIGHT_ATTACK];
			break;
		case MON_RIGHTDOWN_ATTACK:
			_monsterImage = IMAGEMANAGER->findImage("���������ʾƷ�����");
			_animation = _animationArray[MON_RIGHTDOWN_ATTACK];
			break;
		case MON_DOWN_ATTACK:
			_monsterImage = IMAGEMANAGER->findImage("�����Ʒ�����");
			_animation = _animationArray[MON_DOWN_ATTACK];
			break;
		case MON_LEFTDOWN_ATTACK:
			_monsterImage = IMAGEMANAGER->findImage("�������ʾƷ�����");
			_animation = _animationArray[MON_LEFTDOWN_ATTACK];
			break;
		case MON_LEFT_ATTACK:
			_monsterImage = IMAGEMANAGER->findImage("�������ʰ���");
			_animation = _animationArray[MON_LEFT_ATTACK];
			break;
		case MON_LEFTUP_ATTACK:
			_monsterImage = IMAGEMANAGER->findImage("��������������");
			_animation = _animationArray[MON_LEFTUP_ATTACK];
			break;
		case MON_UP_ATTACK:
			_monsterImage = IMAGEMANAGER->findImage("����������");
			_animation = _animationArray[MON_UP_ATTACK];
			break;
		case MON_RIGHTUP_ATTACK:
			_monsterImage = IMAGEMANAGER->findImage("����������������");
			_animation = _animationArray[MON_RIGHTUP_ATTACK];
			break;
	case MON_DAMAGED:
		break;
	default:
		break;
	}
}
//void pigMonster::playerAttack()
//{
//
//}
void pigMonster::deadUpdate()
{
	//ī��Ʈ�� �������Ѷ�
	_respondCount++;
}
//void pigMonster::render()
//{
//
//}