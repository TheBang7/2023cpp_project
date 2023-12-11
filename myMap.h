#ifndef MY_MAP_H
#define MY_MAP_H
#include<stack>
#include<queue>

struct change
{
	int row, col;
	int init, final;
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

private:
	int** mapGrid; // ��ά����ָ��
	int numRows; // ��ͼ����
	int numCols; // ��ͼ����
	int size; //��ͼ��С
	int manPositionRow; //С���ڵڼ���
	int manPositionCol; //С���ڵڼ���
	std::stack<change> backStack;
	std::queue<change> changeQueue;
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
