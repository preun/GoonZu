#pragma once

//한 타일의 사이즈는 32X32
#define TILESIZE 70

//안씀
//타일 갯수(X 20개, Y 20개)
#define TILEX 20
#define TILEY 20

//iso타일 가로대각선 70, 세로대각선 70
#define ISOTILESIZEX 70
#define ISOTILESIZEY 70

//iso타일 10*10
#define ISOTILEX 20
#define ISOTILEY 20

//타일 총 사이즈 4500 * 4500
//#define TILESIZEX TILESIZE * TILEX
//#define TILESIZEY TILESIZE * TILEY
#define TILESIZEX ISOTILESIZEX * ISOTILEX
#define TILESIZEY ISOTILESIZEY * ISOTILEY

//맵툴
//맵툴에서 그려주는 화면 사이즈
#define TILEWINSIZEX 500
#define TILEWINSIZEY 550

//한 타일의 사이즈는 45X45
//#define TILESIZE 45

//타일셋(샘플타일) 의 갯수
#define SAMPLETILEX 3
#define SAMPLETILEY 2

//NPC사이즈
#define NPCSIZEX 32
#define NPCSIZEY 61

//NPC 타일셋의 갯수
#define NPCTILEX 3
#define NPCTILEY 1

//object 타일셋 사이즈
#define OBJSIZEX 142
#define OBJSIZEY 131

//object 타일셋의 갯수
#define OBJTILEX 1
#define OBJTILEY 3

//타일의 속성
//비트필드 느리긴 하나 메모리 관리 따봉
#define ATTR_UNMOVE 0x00000001
#define ATTR_SWAMP	0x00000002
#define ATTR_POISON 0x00000004
#define ATTR_ICE	0x00000008

//지형에 대한 정의
enum TERRAIN
{
	TR_CEMENT, TR_WATER, TR_END
};

//오브젝트 대한 정의
enum OBJECT
{
	//NPC
	OBJ_MUSURI, OBJ_HOSULAM, OBJ_JANGGUMI, 
	//오브젝트
	OBJ_TREE, OBJ_GRASS, OBJ_POTAL, OBJ_RESPOND,
	//오브젝트 더미
	OBJ_GRASS_DUMMY, OBJ_POTAL_DUMMY,
	OBJ_NONE
	/*OBJ_BLOCK1, OBJ_BLOCK3, OBJ_BLOCKS,
	OBJ_FLAG1, OBJ_FLAG2,
	OBJ_TANK1, OBJ_TANK2, OBJ_NONE*/
};

//포지션 (나중에 클래스와 연동키 위함)
enum POS
{
	POS_MUSURI, POS_HOSULAM, POS_JANGGUMI, POS_NONE,
	POS_RESPOND
	//POS_MUSURI, POS_HOSULAM
};

struct tagTile
{
	POINT point[4]; //피티인리젼을 쓰기 위한 포인트 배열
	int calibrateX, calibrateY; // iso 기준 좌표
	POINT renderPoint;
	float x, y; //그려주기 위한 X, Y좌표
	TERRAIN terrain;
	OBJECT	obj;
	POS		pos;
	//RECT	rc;
	int terrainFrameX;
	int terrainFrameY;
	int objFrameX;
	int objFrameY;

	POINT getCenterPoint()
	{
		return PointMake(point[0].x, point[1].y);
	}
};
//struct tagTile
//{
//	TERRAIN terrain;
//	OBJECT	obj;
//	RECT	rc;
//	int terrainFrameX;
//	int terrainFrameY;
//	int objFrameX;
//	int objFrameY;
//};

struct tagSampleTile
{
	RECT rcTile;
	int terrainFrameX;
	int terrainFrameY;
};

//struct tagNPCTile
//{
//	RECT rcTile;
//	int terrainFrameX;
//	int terrainFrameY;
//};

struct tagCurrentTile
{
	int x;
	int y;
};