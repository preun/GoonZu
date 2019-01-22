#pragma once
#include "gameNode.h"
class aStarTile :
	public gameNode
{
private:
	int _idX;	//타일 인덱스X
	int _idY;	//타일 인덱스Y

	POINT _center; //타일 중점 좌표(거리계산)
	//RECT _rc;		//타일 렉트

	float _totalCost;
	float _costFromStart;
	float _costToGoal;

	bool _isOpen;

	aStarTile* _parentNode;

	string _attribute;
public:
	aStarTile();
	~aStarTile();

	HRESULT init(int idX, int idY, POINT centerPoint);
	void release(void);
	void update(void);
	void render(void);

	void setIdX(int idx) { _idX = idx; }
	int getIdX() { return _idX; }

	void setIdY(int idY) { _idY = idY; }
	int getIdY() { return _idY; }

	//RECT getRect() { return _rc; }

	void setCenter(POINT center) { _center = center; }
	POINT getCenter() { return _center; }

	//속성 설정자
	void setAttribute(string str) { _attribute = str; }
	string getAttribute() { return _attribute; }

	void setTotalCost(float totalCost) { _totalCost = totalCost; }
	float getTotalCost() { return _totalCost; }

	void setCostFromStart(float costFromStart) { _costFromStart = costFromStart; }
	float getCostFromStart() { return _costFromStart; }

	void setCostToGoal(float costToGoal) { _costToGoal = costToGoal; }
	float getCostToGoal() { return _costToGoal; }

	void setParentNode(aStarTile* t) { _parentNode = t; }
	aStarTile* getParentNode() { return _parentNode; }

	void setIsOpen(bool isOpen) { _isOpen = isOpen; }
	bool getIsOpen() { return _isOpen; }
};

