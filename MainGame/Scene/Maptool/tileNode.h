#pragma once

//�� Ÿ���� ������� 32X32
#define TILESIZE 70

//�Ⱦ�
//Ÿ�� ����(X 20��, Y 20��)
#define TILEX 20
#define TILEY 20

//isoŸ�� ���δ밢�� 70, ���δ밢�� 70
#define ISOTILESIZEX 70
#define ISOTILESIZEY 70

//isoŸ�� 10*10
#define ISOTILEX 20
#define ISOTILEY 20

//Ÿ�� �� ������ 4500 * 4500
//#define TILESIZEX TILESIZE * TILEX
//#define TILESIZEY TILESIZE * TILEY
#define TILESIZEX ISOTILESIZEX * ISOTILEX
#define TILESIZEY ISOTILESIZEY * ISOTILEY

//����
//�������� �׷��ִ� ȭ�� ������
#define TILEWINSIZEX 500
#define TILEWINSIZEY 550

//�� Ÿ���� ������� 45X45
//#define TILESIZE 45

//Ÿ�ϼ�(����Ÿ��) �� ����
#define SAMPLETILEX 3
#define SAMPLETILEY 2

//NPC������
#define NPCSIZEX 32
#define NPCSIZEY 61

//NPC Ÿ�ϼ��� ����
#define NPCTILEX 3
#define NPCTILEY 1

//object Ÿ�ϼ� ������
#define OBJSIZEX 142
#define OBJSIZEY 131

//object Ÿ�ϼ��� ����
#define OBJTILEX 1
#define OBJTILEY 3

//Ÿ���� �Ӽ�
//��Ʈ�ʵ� ������ �ϳ� �޸� ���� ����
#define ATTR_UNMOVE 0x00000001
#define ATTR_SWAMP	0x00000002
#define ATTR_POISON 0x00000004
#define ATTR_ICE	0x00000008

//������ ���� ����
enum TERRAIN
{
	TR_CEMENT, TR_WATER, TR_END
};

//������Ʈ ���� ����
enum OBJECT
{
	//NPC
	OBJ_MUSURI, OBJ_HOSULAM, OBJ_JANGGUMI, 
	//������Ʈ
	OBJ_TREE, OBJ_GRASS, OBJ_POTAL, OBJ_RESPOND,
	//������Ʈ ����
	OBJ_GRASS_DUMMY, OBJ_POTAL_DUMMY,
	OBJ_NONE
	/*OBJ_BLOCK1, OBJ_BLOCK3, OBJ_BLOCKS,
	OBJ_FLAG1, OBJ_FLAG2,
	OBJ_TANK1, OBJ_TANK2, OBJ_NONE*/
};

//������ (���߿� Ŭ������ ����Ű ����)
enum POS
{
	POS_MUSURI, POS_HOSULAM, POS_JANGGUMI, POS_NONE,
	POS_RESPOND
	//POS_MUSURI, POS_HOSULAM
};

struct tagTile
{
	POINT point[4]; //��Ƽ�θ����� ���� ���� ����Ʈ �迭
	int calibrateX, calibrateY; // iso ���� ��ǥ
	POINT renderPoint;
	float x, y; //�׷��ֱ� ���� X, Y��ǥ
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