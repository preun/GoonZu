#pragma once
#include "gameNode.h"
class UI :
	public gameNode
{
	int* _maxHP;
	int* _currentHP;
	int* _maxMP;
	int* _currentMP;
	int* _level;
	int* _exp;

public:
	UI();
	~UI();

	HRESULT init(int* maxHP, int* currentHP, int* maxMP, int* currentMP, int* level, int* exp);
	void release();
	void update() ;
	void render() ;
};				  

