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
	//0
	FLOOR,
	//1
	BOX_DEST,
	//2
	BOX,
	//3
	MAN,
	//4
	MAN_DEST,
	//5
	EXTRA,
	//6
	SUB_MAP,
	//7
	HIT,
	//8
	MAN_HIT,
	//9
	ALL
};

struct myPosition
{
	int row;
	int col;
};

struct moveInfo
{
	bool canMove = false;
	bool shouldInf = false;
};

class MyMap
{
public:
	MyMap(int rows, int cols);
	MyMap(bool isInf);
	MyMap();
	~MyMap();
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
	bool entrance[4]; //��������
	myPosition* entrancePosition; //��������
	MyMap* outsideMap;
	myPosition outsidePosition;
	bool getEntranceByMoveDirection_in(int rowChange, int colChange);
	bool getEntranceByMoveDirection_out(int rowChange, int colChange);
	myPosition getEntrancePositionByMoveDirection_in(int rowChange, int colChange);
	myPosition getEntrancePositionByMoveDirection_out(int rowChange, int colChange);
	moveInfo canMove(int const rowChange, int const colChange, int const initRow, int const initCol, bool loop,
	             int countInf);
	bool loopMove(int const rowChange, int const colChange, int const initRow, int const initCol, bool loop,
	              int countInf);
	bool printed = false;
	bool isInf = false;
	bool shouldCheck = false;
	bool checkMap();
	bool checked = false;

private:
	std::unordered_map<std::string, MyMap*> hashMap;
	std::vector<MyMap*> mapList;
	std::string mapName;
	bool hasMapGrid = false;
	void saveMap(std::ofstream& outFile, int countSub);
	MapGrid** mapGrid; // ��ά����ָ��
	MapGrid** mapGridRemains; // ��ά����ָ��
	int numRows; // ��ͼ����
	int numCols; // ��ͼ����
	int size; //��ͼ��С
	int manPositionRow; //С���ڵڼ���
	int manPositionCol; //С���ڵڼ���
	void generate();
	bool checkMap(std::vector<MyMap*>& list);

};


#endif
