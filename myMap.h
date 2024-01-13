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
	bool* entrance; //��������
	myPosition* entrancePosition; //��������
	bool getEntranceByMoveDirection(int rowChange, int colChange);
	myPosition getEntrancePositionByMoveDirection(int rowChange, int colChange);
	bool canMove(int const rowChange, int const colChange, int const initRow, int const initCol);


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
};


#endif
