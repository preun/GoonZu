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
	_level		=1;//레벨
	_exp		=0;//경험치
				  
	_maxHP		=50;//풀피
	_currentHP	=50;//피
				  
	_maxMP		=30;//풀 엠피
	_currentMP	=30;//엠피
				  
	_str		=5;//근력
	_dex		=5;//순발력
	_int		=5;//도력
	_life		=5;//생명력
	_luk		=5;//손재주
				  
	_statBonus	=20;//미분배 스탯치
				  
	_minAtt		=1 + (_str/2.5);//최소 공격력
	_maxAtt		=3 + (_str/2.5);//최대 공격력
	_def		=5;//방어력

	test1 = test2 = 0;

	IMAGEMANAGER->addImage("캐릭터스탯창", "./image/character/스탯/스탯창.bmp", 260, 448, true, RGB(255, 0, 255));
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
	IMAGEMANAGER->render("캐릭터스탯창", getMemDC(), 0, 100);
	HFONT hFont = CreateFont(10,5, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0,
		 VARIABLE_PITCH | FF_ROMAN, TEXT("돋움"));
	HFONT OldFont = (HFONT)SelectObject(getMemDC(), hFont);

	SetTextAlign(getMemDC(), TA_CENTER);

	//캐릭터 닉네임
	TextOut(getMemDC(), 33, 123, characterName, strlen(characterName));

	DeleteObject(OldFont);
	DeleteObject(hFont);

	SetTextAlign(getMemDC(), TA_TOP | TA_LEFT );
	char outPutStatus[16];
	//근력
	sprintf(outPutStatus, "%d", _str);
	TextOut(getMemDC(), 50, 245, outPutStatus, strlen(outPutStatus));
	//순발력
	sprintf(outPutStatus, "%d", _dex);
	TextOut(getMemDC(), 50, 261, outPutStatus, strlen(outPutStatus));
	//도력
	sprintf(outPutStatus, "%d", _int);
	TextOut(getMemDC(), 50, 278, outPutStatus, strlen(outPutStatus));
	//생명력
	sprintf(outPutStatus, "%d", _life);
	TextOut(getMemDC(), 50, 295, outPutStatus, strlen(outPutStatus));
	//손재주
	sprintf(outPutStatus, "%d", _luk);
	TextOut(getMemDC(), 50, 311, outPutStatus, strlen(outPutStatus));
	//보너스
	sprintf(outPutStatus, "%d", _statBonus);
	TextOut(getMemDC(), 50, 326, outPutStatus, strlen(outPutStatus));
	//레벨
	sprintf(outPutStatus, "%d", _level);
	TextOut(getMemDC(), 130, 143, outPutStatus, strlen(outPutStatus));
	//현재 경험치
	sprintf(outPutStatus, "%d", _exp);
	TextOut(getMemDC(), 140, 156, outPutStatus, strlen(outPutStatus));

	//만렙이 아니면 렙업에 필요한 경험치 보이기
	if (_level != MAXLEVEL)
	sprintf(outPutStatus, "%d", _needExp[_level-1]);
	//만렙이면 그 이상 안가도록
	else
		sprintf(outPutStatus, "%d", _needExp[MAXLEVEL - 2]);
	TextOut(getMemDC(), 185, 156, outPutStatus, strlen(outPutStatus));

	//현재 피
	sprintf(outPutStatus, "%d", _currentHP);
	TextOut(getMemDC(), 130, 170, outPutStatus, strlen(outPutStatus));
	//최대 피
	sprintf(outPutStatus, "%d", _maxHP);
	TextOut(getMemDC(), 170, 170, outPutStatus, strlen(outPutStatus));
	//현재 마나
	sprintf(outPutStatus, "%d", _currentMP);
	TextOut(getMemDC(), 136, 185, outPutStatus, strlen(outPutStatus));
	//최대 마나
	sprintf(outPutStatus, "%d", _maxMP);
	TextOut(getMemDC(), 170, 185, outPutStatus, strlen(outPutStatus));

	//공격력(60, 259)
	sprintf(outPutStatus, "%d - %d", _minAtt, _maxAtt);
	TextOut(getMemDC(), 60, 359, outPutStatus, strlen(outPutStatus));

	//방어력(60, 275)
	sprintf(outPutStatus, "%d", _def);
	TextOut(getMemDC(), 60, 375, outPutStatus, strlen(outPutStatus));


	//y축 + 100;
	//50, 145 힘
	//50, 161 순발력
	//50, 178 도력
	//50, 195 생명력
	//50, 211 손재주
	//50, 266 보너스
	//char testttt[100];
	//sprintf(testttt, "%d, %d", test1, test2);
	//TextOut(getMemDC(), 20, 200, testttt, strlen(testttt));
	
}

void status::setExp(int exp)
{
	
		//경험치 올리고
		_exp += exp;
		
		//만렙일경우 더이상의 렙업은 없다.
		if (_level == MAXLEVEL) return;

		//레벨업
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