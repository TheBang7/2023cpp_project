#pragma once
#include <graphics.h>      
#include <conio.h>
#include<stdio.h>
#include<easyx.h>
#include <iostream>
#include"myMap.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void menu1(int& cen,int& room);
void diyiceng(int n, int& cen, int& room);
void drawButton(int x, int y, int w, int h, TCHAR* text, COLORREF color);
void choosesave(MyMap* map,int& cen, int& room);
void chooseload(MyMap* map, int& cen, int& room);