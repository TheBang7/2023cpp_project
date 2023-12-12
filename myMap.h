#ifndef MY_MAP_H
#define MY_MAP_H
#include<stack>
#define MAX_CHANGE_SIZE 4

struct Change
{
	int row[MAX_CHANGE_SIZE];
	int col[MAX_CHANGE_SIZE];
	int init[MAX_CHANGE_SIZE];
	int final[MAX_CHANGE_SIZE];
	int all = 0;
};

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
	int getElement(int x, int y);
	int getManPositionRow();
	int getManPositionCol();
	void dealChange(Change change);
	void backChange(Change change);
	bool isInMap(int row, int col);

private:
	int** mapGrid; // ��ά����ָ��
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
	HIT,
	ALL
};

#endif
