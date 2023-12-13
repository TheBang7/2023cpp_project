#ifndef MY_MAP_H
#define MY_MAP_H
#include<stack>

#include "MapGrid.h"
#include "myChange.h"
class MapGrid;


class MyMap
{
public:
	// ���캯�������ܵ�ͼ������������
	MyMap(int rows, int cols);

	MyMap();

	// ���������������ͷŶ�̬������ڴ�
	~MyMap();

	// ʾ����������ӡ��ͼ
	void printMap();
	int getNumCols();
	int getNumRows();
	int getElementType(int x, int y);
	int getManPositionRow();
	int getManPositionCol();
	void dealChange(MyChange* change);
	void backChange(MyChange* change);
	bool isInMap(int row, int col);
	MyMap* getSubMap(int row, int col);

private:
	MapGrid** mapGrid; // ��ά����ָ��
	int numRows; // ��ͼ����
	int numCols; // ��ͼ����
	int size; //��ͼ��С
	int manPositionRow; //С���ڵڼ���
	int manPositionCol; //С���ڵڼ���
	void generate();
};

enum Prop
{
	WALL,
	FLOOR,
	BOX_DEST,
	BOX,
	MAN,
	EXTRA,
	SUB_MAP,
	HIT,
	ALL
};

#endif
