#include "stdafx.h"
#include "aStarTile.h"


aStarTile::aStarTile()
: _totalCost(0), _costFromStart(0),
_costToGoal(0), _parentNode(NULL), _idX(0), _idY(0), _isOpen(true)
{
}


aStarTile::~aStarTile()
{
}
HRESULT aStarTile::init(int idX, int idY, POINT centerPoint)
{/*
 _color = RGB(250, 150, 0);
 _brush = Brush(_color);
 _pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
 */
	_center = centerPoint;

	_idX = idX;
	_idY = idY;

	//_rc = RectMakeCenter(_center.x, _center.y, TILESIZE, TILESIZE);

	return S_OK;
}
void aStarTile::release()
{


}
void aStarTile::update()
{

}
void aStarTile::render()
{
}