#ifndef MY_MAP_H
#define MY_MAP_H
#include<stack>
#include<string>
#include <unordered_map>

#include "MapGrid.h"
#include "myChange.h"
class MapGrid;
class MyChange;

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

struct myPosition
{
	int row;
	int col;
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
	int getElementType(int x, int y);
	MapGrid* getElement(int x, int y);
	int getElementRemainsType(int x, int y);
	int getManPositionRow();
	int getManPositionCol();
	void dealChange(MyChange* change);
	void backChange(MyChange* change);
	bool isInMap(int row, int col);
	MyMap* getSubMap(int row, int col);
	void saveMap(std::string address);
	void loadMap(std::string address);
	std::string getMapName();
	void setMapName(std::string name);
	void setSubMap(int row, int col, MyMap* subMap);
	std::string getSubMapNameToSet(int row, int col);
	void setGridType(int row, int col, int type);
	void setSubMapName(int row, int col, std::string);
	bool* entrance; //上下左右
	myPosition* entrancePosition; //上下左右
	bool getEntranceByMoveDirection(int rowChange, int colChange);
	myPosition getEntrancePositionByMoveDirection(int rowChange, int colChange);
	bool canMove(int const rowChange, int const colChange, int const initRow, int const initCol);


private:
	std::unordered_map<std::string, MyMap*> hashMap;
	std::vector<MyMap*> mapList;
	std::string mapName;
	bool hasMapGrid = false;
	void saveMap(std::ofstream& outFile, int countSub);
	MapGrid** mapGrid; // 二维数组指针
	MapGrid** mapGridRemains; // 二维数组指针
	int numRows; // 地图行数
	int numCols; // 地图列数
	int size; //地图大小
	int manPositionRow; //小人在第几行
	int manPositionCol; //小人在第几列
	void generate();
};


#endif
