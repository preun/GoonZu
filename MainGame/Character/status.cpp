#include "stdafx.h"
#include "status.h"


status::status()
{
}


status::~status()
{

}

HRESULT status::init()
{
	_level		=1;//����
	_exp		=0;//����ġ
				  
	_maxHP		=50;//Ǯ��
	_currentHP	=50;//��
				  
	_maxMP		=30;//Ǯ ����
	_currentMP	=30;//����
				  
	_str		=5;//�ٷ�
	_dex		=5;//���߷�
	_int		=5;//����
	_life		=5;//�����
	_luk		=5;//������
				  
	_statBonus	=20;//�̺й� ����ġ
				  
	_minAtt		=1 + (_str/2.5);//�ּ� ���ݷ�
	_maxAtt		=3 + (_str/2.5);//�ִ� ���ݷ�
	_def		=5;//����

	test1 = test2 = 0;

	IMAGEMANAGER->addImage("ĳ���ͽ���â", "./image/character/����/����â.bmp", 260, 448, true, RGB(255, 0, 255));
	/*
	+100
	89, 142(158, 175, 191, 208)
110
	*/
	_statusButtonRC[STRPLUS-1] = RectMake(89, 242, 20, 14);
	_statusButtonRC[DEXPLUS - 1] = RectMake(89, 258, 20, 14);
	_statusButtonRC[INTPLUS - 1] = RectMake(89, 275, 20, 14);
	_statusButtonRC[LIFEPLUS - 1] = RectMake(89, 291, 20, 14);
	_statusButtonRC[LUKPLUS - 1] = RectMake(89, 308, 20, 14);

	_statusButtonRC[STRMINUS - 1] = RectMake(110, 242, 20, 14);
	_statusButtonRC[DEXMINUS - 1] = RectMake(110, 258, 20, 14);
	_statusButtonRC[INTMINUS - 1] = RectMake(110, 275, 20, 14);
	_statusButtonRC[LIFEMINUS - 1] = RectMake(110, 291, 20, 14);
	_statusButtonRC[LUKMINUS - 1] = RectMake(110, 308, 20, 14);

	return S_OK;
}
void status::release()
{

}
void status::update()
{
	if (KEYMANAGER->isOnceKeyDown('1')) _currentHP -= 10;
	if (KEYMANAGER->isOnceKeyDown('2')) init();
	//if (KEYMANAGER->isOnceKeyDown('1')) test1++;
	//if (KEYMANAGER->isOnceKeyDown('2')) test2++;
	if (KEYMANAGER->isOnceKeyDown('3')) setExp(10);

	/*if(KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < LUKMINUS; ++i)
		{
			if (_statBonus <= 0) break;
			if (PtInRect(&_statusButtonRC[i], _ptMouse))
			{
				switch (i+1)
				{
				case STRPLUS:
					setStr(1);
					setStatBonus(-1);
					break;

				case 	DEXPLUS:
					setDex(1);
					setStatBonus(-1);
					break;

				case 	INTPLUS:
					setInt(1);
					setStatBonus(-1);
					break;

				case 	LIFEPLUS:
					setLife(1);
					setStatBonus(-1);
					break;

				case 	LUKPLUS:
					setLuk(1);
					setStatBonus(-1);
					break;

				case STRMINUS:
					setStr(-1);
					setStatBonus(1);
					break;

				case 	DEXMINUS:
					setDex(-1);
					setStatBonus(1);
					break;
				case 	INTMINUS:
					setInt(-1);
					setStatBonus(1);
					break;

				case 	LIFEMINUS:
					setLife(-1);
					setStatBonus(1);
					break;

				case 	LUKMINUS:
					setLuk(-1);
					setStatBonus(1);
					break;
				default:
					break;
				}
			}
		}
	}*/
}
void status::render()
{

}

void status::statusOpen(char* characterName)
{
	IMAGEMANAGER->render("ĳ���ͽ���â", getMemDC(), 0, 100);
	HFONT hFont = CreateFont(10,5, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0,
		 VARIABLE_PITCH | FF_ROMAN, TEXT("����"));
	HFONT OldFont = (HFONT)SelectObject(getMemDC(), hFont);

	SetTextAlign(getMemDC(), TA_CENTER);

	//ĳ���� �г���
	TextOut(getMemDC(), 33, 123, characterName, strlen(characterName));

	DeleteObject(OldFont);
	DeleteObject(hFont);

	SetTextAlign(getMemDC(), TA_TOP | TA_LEFT );
	char outPutStatus[16];
	//�ٷ�
	sprintf(outPutStatus, "%d", _str);
	TextOut(getMemDC(), 50, 245, outPutStatus, strlen(outPutStatus));
	//���߷�
	sprintf(outPutStatus, "%d", _dex);
	TextOut(getMemDC(), 50, 261, outPutStatus, strlen(outPutStatus));
	//����
	sprintf(outPutStatus, "%d", _int);
	TextOut(getMemDC(), 50, 278, outPutStatus, strlen(outPutStatus));
	//�����
	sprintf(outPutStatus, "%d", _life);
	TextOut(getMemDC(), 50, 295, outPutStatus, strlen(outPutStatus));
	//������
	sprintf(outPutStatus, "%d", _luk);
	TextOut(getMemDC(), 50, 311, outPutStatus, strlen(outPutStatus));
	//���ʽ�
	sprintf(outPutStatus, "%d", _statBonus);
	TextOut(getMemDC(), 50, 326, outPutStatus, strlen(outPutStatus));
	//����
	sprintf(outPutStatus, "%d", _level);
	TextOut(getMemDC(), 130, 143, outPutStatus, strlen(outPutStatus));
	//���� ����ġ
	sprintf(outPutStatus, "%d", _exp);
	TextOut(getMemDC(), 140, 156, outPutStatus, strlen(outPutStatus));

	//������ �ƴϸ� ������ �ʿ��� ����ġ ���̱�
	if (_level != MAXLEVEL)
	sprintf(outPutStatus, "%d", _needExp[_level-1]);
	//�����̸� �� �̻� �Ȱ�����
	else
		sprintf(outPutStatus, "%d", _needExp[MAXLEVEL - 2]);
	TextOut(getMemDC(), 185, 156, outPutStatus, strlen(outPutStatus));

	//���� ��
	sprintf(outPutStatus, "%d", _currentHP);
	TextOut(getMemDC(), 130, 170, outPutStatus, strlen(outPutStatus));
	//�ִ� ��
	sprintf(outPutStatus, "%d", _maxHP);
	TextOut(getMemDC(), 170, 170, outPutStatus, strlen(outPutStatus));
	//���� ����
	sprintf(outPutStatus, "%d", _currentMP);
	TextOut(getMemDC(), 136, 185, outPutStatus, strlen(outPutStatus));
	//�ִ� ����
	sprintf(outPutStatus, "%d", _maxMP);
	TextOut(getMemDC(), 170, 185, outPutStatus, strlen(outPutStatus));

	//���ݷ�(60, 259)
	sprintf(outPutStatus, "%d - %d", _minAtt, _maxAtt);
	TextOut(getMemDC(), 60, 359, outPutStatus, strlen(outPutStatus));

	//����(60, 275)
	sprintf(outPutStatus, "%d", _def);
	TextOut(getMemDC(), 60, 375, outPutStatus, strlen(outPutStatus));


	//y�� + 100;
	//50, 145 ��
	//50, 161 ���߷�
	//50, 178 ����
	//50, 195 �����
	//50, 211 ������
	//50, 266 ���ʽ�
	//char testttt[100];
	//sprintf(testttt, "%d, %d", test1, test2);
	//TextOut(getMemDC(), 20, 200, testttt, strlen(testttt));
	
}

void status::setExp(int exp)
{
	
		//����ġ �ø���
		_exp += exp;
		
		//�����ϰ�� ���̻��� ������ ����.
		if (_level == MAXLEVEL) return;

		//������
		if (_exp >= _needExp[_level - 1])
		{
			_level += 1;
			setStatBonus(5);
		}
	

}
void status::statusDistribution(int weaponMinAtt, int weaponMaxAtt, int armorDef)
{
	for (int i = 0; i < LUKMINUS; ++i)
	{
		if (_statBonus <= 0) break;
		if (PtInRect(&_statusButtonRC[i], _ptMouse))
		{
			switch (i + 1)
			{
			case STRPLUS:
				setStr(1);
				setMinAtt(weaponMinAtt);
				setMaxAtt(weaponMaxAtt);
				setStatBonus(-1);
				break;

			case 	DEXPLUS:
				setDex(1);
				setStatBonus(-1);
				break;

			case 	INTPLUS:
				setInt(1);
				//setMaxMP(4);
				setStatBonus(-1);
				break;

			case 	LIFEPLUS:
				setLife(1);
				//setMaxHP(4);
				setStatBonus(-1);
				break;

			case 	LUKPLUS:
				setLuk(1);
				setStatBonus(-1);
				break;

			case STRMINUS:
				setStr(-1);
				setMinAtt(weaponMinAtt);
				setMaxAtt(weaponMaxAtt);
				setStatBonus(1);
				break;

			case 	DEXMINUS:
				setDex(-1);
				setStatBonus(1);
				break;
			case 	INTMINUS:
				setInt(-1);
				//setMaxMP(-4);
				setStatBonus(1);
				break;

			case 	LIFEMINUS:
				setLife(-1);
				//setMaxHP(-4);
				setStatBonus(1);
				break;

			case 	LUKMINUS:
				setLuk(-1);
				setStatBonus(1);
				break;
			default:
				break;
			}
		}
	}
}