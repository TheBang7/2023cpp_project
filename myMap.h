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
	// 构造函数，接受地图的行数和列数
	MyMap(int rows, int cols);

	MyMap();

	// 析构函数，用于释放动态分配的内存
	~MyMap();

	// 示例方法，打印地图
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
	int** mapGrid; // 二维数组指针
	int numRows; // 地图行数
	int numCols; // 地图列数
	int size; //地图大小
	int manPositionRow; //小人在第几行
	int manPositionCol; //小人在第几列
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
