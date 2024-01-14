#include <graphics.h>      
#include <conio.h>
#include<stdio.h>
#include<easyx.h>
#include <iostream>
#include "viewmenu.h"
#include <graphics.h>	
#include <chrono>
#include <conio.h>
#pragma comment( lib, "MSIMG32.LIB")
void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg, UINT transparentcolor)
{
    HDC dstDC = GetImageHDC(dstimg);
    HDC srcDC = GetImageHDC(srcimg);
    int w = srcimg->getwidth();
    int h = srcimg->getheight();

    // ʹ�� Windows GDI ����ʵ��͸��λͼ
    TransparentBlt(dstDC, x, y, w, h, srcDC, 0, 0, w, h, transparentcolor);
}

void drawButton(int x, int y, int w, int h, TCHAR* text, COLORREF color) {
    setbkmode(TRANSPARENT);
    setfillcolor(color);
    fillroundrect(x, y, x + w, y + h, 10, 10);
    TCHAR s1[] = "Arial BLACK";
    settextstyle(30, 0, s1);
    settextcolor(BLACK);
    int tx = x + (w - textwidth(text)) / 2;
    int ty = y + (h - textheight(text)) / 2;
    outtextxy(tx, ty, text);
}

void diyiceng(int n, int& cen, int& room) {
    IMAGE background; // ����һ�� IMAGE �������ڴ洢����ͼƬ
    loadimage(&background, _T("����.png")); // ���ļ��м���ͼƬ
    putimage(0, 0, &background); // ��ͼƬ���Ƶ������ϣ�ͼƬ���Ͻ�����Ϊ (0,0)
    MOUSEMSG m;
    m = GetMouseMsg();
    if (m.uMsg == WM_LBUTTONDOWN) {
        if (m.x >= 0 && m.x <= 625 && m.y >= 0 && m.y <= 500) {
            // ����������λ���� "��һ��" ��Χ��
            cleardevice();
            cen = n;
            room = 1;
        }
        if (m.x >= 625 && m.x <= 1250 && m.y >= 0 && m.y <= 500) {
            // ����������λ���� "��һ��" ��Χ��
            cleardevice();
            cen = n;
            room = 2;
        }
        if (m.x >= 0 && m.x <= 625 && m.y >= 500 && m.y <= 1000) {
            // ����������λ���� "��һ��" ��Χ��
            cleardevice();
            cen = n;
            room = 3;
        }
        if (m.x >= 625 && m.x <= 1250 && m.y >= 500 && m.y <= 1000) {
            // ����������λ���� "��һ��" ��Χ��
            cleardevice();
            cen = n;
            room = 4;
        }
    }
}



void startGame(int& cen, int& room) {
    cleardevice(); // ��յ�ǰ��ͼ���豸
    // �����������Ϸ��ʼ��Ľ������
    initgraph(1250, 1000);
    IMAGE background; // ����һ�� IMAGE �������ڴ洢����ͼƬ
    loadimage(&background, _T("�������(1).jpg")); // ���ļ��м���ͼƬ
    putimage(0, 0, &background); // ��ͼƬ���Ƶ������ϣ�ͼƬ���Ͻ�����Ϊ (0,0)
    IMAGE guard; // ����һ�� IMAGE �������ڴ洢����ͼƬ
    loadimage(&guard, _T("�ܼ�ͼƬ(1).png")); // ���ļ��м���ͼƬ
    transparentimage(NULL, 0, 750, &guard,BLACK); // ��ͼƬ���Ƶ������ϣ�ͼƬ���Ͻ�����Ϊ (1000,0)
    std::string ptext =
        "�𾴵����ߴ��ˣ����ڵȵ����ˣ������Ǳ��ĵ������ӡ��һֻ���������ڷ�ӡ���ɶ��ˡ����ߴ�����ֻҪ������ΰ�ʥ��Ż�ָ���ĵط�����վ�����۾Ϳ����������������㣬�ӵ�һ�㵽��������޸���ӡ���Ѷ�Խ��Խ�ߣ�ÿ�����ĸ���ӡ��Ҫ�޲���ף���ߴ��˿�����������";

    int currentChar = 0;
    int x = 250, y = 750;
    settextstyle(30, 0, _T("����")); // ���������СΪ 40
    MOUSEMSG m;
    bool flag2 = 0;
    while (true) {
        if ( currentChar < ptext.length()&&flag2==0) {
            setbkmode(TRANSPARENT); // ���ñ���ģʽΪ͸��
            outtextxy(x, y, ptext.substr(currentChar, 2).c_str());
            x = x + 40;
            if ((currentChar / 2 + 1) % 25 == 0) { // ÿ15���ֻ���
                x = 250;
                y = y +40;
            }
            
            auto start = std::chrono::high_resolution_clock::now();
            while (true) {
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> elapsed = end - start;
                if (elapsed.count() > 100) {
                    break;
                }
                // �������������Ҫ��ѭ����ִ�еĴ���
                m = GetMouseMsg();
                if (m.uMsg == WM_LBUTTONDOWN) {

                                flag2 = 1;
                                break;
                            }
            }
            
            currentChar += 2; // ÿ������2����Ϊһ�������������ַ����
        }
        else {
            break;
        }
    }
    loadimage(&background, _T("�������(1).jpg")); // ���ļ��м���ͼƬ
    putimage(0, 0, &background);
    // ��Ӳ˵���ť
    x = 550, y = 450; // �� y ��������
    int w = 200, h = 60; // ����ť�Ŀ�Ⱥ͸߶�
    TCHAR text[20] = "��һ�����";
    drawButton(x, y, w, h, text, WHITE);
    y += 70; // ���� y ����
    TCHAR textMenu[20] = "�ڶ������";
    drawButton(x, y, w, h, textMenu, WHITE);

    // ����˳���ť
    y += 70; // ���� y ����
    TCHAR textExit[20] = "���������";
    drawButton(x, y, w, h, textExit, WHITE);

    
    bool flag1 = 0;
    while (flag1 == 0) {
        m = GetMouseMsg(); // ��ȡһ�������Ϣ
        switch (m.uMsg) {
        case WM_MOUSEMOVE:
            if (m.x >= x && m.x <= x + w) {
                if (m.y >= y && m.y <= y + h) {
                    drawButton(x, y, w, h, textExit, RED);
                }
                else {
                    drawButton(x, y, w, h, textExit, WHITE);
                }
                if (m.y >= y - 70 && m.y <= y - 70 + h) { // ���� y �����ⷶΧ
                    drawButton(x, y - 70, w, h, textMenu, RED);
                }
                else {
                    drawButton(x, y - 70, w, h, textMenu, WHITE);
                }
                if (m.y >= y - 140 && m.y <= y - 140 + h) { // ���� y �����ⷶΧ
                    drawButton(x, y - 140, w, h, text, RED);
                }
                else {
                    drawButton(x, y - 140, w, h, text, WHITE);
                }
            }
            break;
        case WM_LBUTTONDOWN: // ����������
            if (m.x >= x && m.x <= x + w && m.y >= y - 140 && m.y <= y - 140 + h) {
                // ����������λ���� "��ʼ��Ϸ" ��ť�ķ�Χ��
                cleardevice();
                flag1 = 1;
                diyiceng(1,cen,room); // ���� startGame ��������ʾ��һ������
                
            }
            else if (m.x >= x && m.x <= x + w && m.y >= y - 70 && m.y <= y - 70 + h) {
                // ����������λ���� "��ʼ��Ϸ" ��ť�ķ�Χ��
                cleardevice();
                flag1 = 1;
                diyiceng(2,cen,room); // ���� startGame ��������ʾ��һ������
            }
            else if (m.x >= x && m.x <= x + w && m.y >= y  && m.y <= y + h) {
                // ����������λ���� "��ʼ��Ϸ" ��ť�ķ�Χ��
                cleardevice();
                flag1 = 1;
                diyiceng(3,cen,room); // ���� startGame ��������ʾ��һ������
            }

            break;

        }
    }




}

void menu1(int argc, char** argv,int& cen,int& room) {

    initgraph(1250, 1000);
    IMAGE background; // ����һ�� IMAGE �������ڴ洢����ͼƬ
    loadimage(&background, _T("�Ǳ�����(1).jpg")); // ���ļ��м���ͼƬ
    putimage(0, 0, &background); // ��ͼƬ���Ƶ������ϣ�ͼƬ���Ͻ�����Ϊ (0,0)

    // �����Ϸ����
    TCHAR gameName[] = _T("��ӡ����");
    settextstyle(100, 0, _T("����")); // ���������С������
    settextcolor(WHITE); // ����������ɫ
    setbkmode(TRANSPARENT); // ���ñ���ģʽΪ͸��
    int tx = (getwidth() - textwidth(gameName)) / 2; // �����ı��� x ������ʹ�����
    outtextxy(tx, 50, gameName); // ��ָ��λ�������Ϸ����

    int x = 550, y = 550; // �� y ��������
    int w = 200, h = 60; // ����ť�Ŀ�Ⱥ͸߶�
    TCHAR text[20] = "��ʼ��Ϸ";
    drawButton(x, y, w, h, text, WHITE);

    // ��Ӳ˵���ť
    y += 70; // ���� y ����
    TCHAR textMenu[20] = "�˵�";
    drawButton(x, y, w, h, textMenu, WHITE);

    // ����˳���ť
    y += 70; // ���� y ����
    TCHAR textExit[20] = "�˳�";
    drawButton(x, y, w, h, textExit, WHITE);

    MOUSEMSG m; // ���������Ϣ
    bool flag1 = 0;
    while (flag1 == 0 ) {
        m = GetMouseMsg(); // ��ȡһ�������Ϣ
        switch (m.uMsg) {
        case WM_MOUSEMOVE:
            if (m.x >= x && m.x <= x + w) {
                if (m.y >= y && m.y <= y + h) {
                    drawButton(x, y, w, h, textExit, RED);
                }
                else {
                    drawButton(x, y, w, h, textExit, WHITE);
                }
                if (m.y >= y - 70 && m.y <= y - 70 + h) { // ���� y �����ⷶΧ
                    drawButton(x, y - 70, w, h, textMenu, RED);
                }
                else {
                    drawButton(x, y - 70, w, h, textMenu, WHITE);
                }
                if (m.y >= y - 140 && m.y <= y - 140 + h) { // ���� y �����ⷶΧ
                    drawButton(x, y - 140, w, h, text, RED);
                }
                else {
                    drawButton(x, y - 140, w, h, text, WHITE);
                }
            }
            break;
        case WM_LBUTTONDOWN: // ����������
            if (m.x >= x && m.x <= x + w && m.y >= y - 140 && m.y <= y - 140 + h) {
                // ����������λ���� "��ʼ��Ϸ" ��ť�ķ�Χ��
                cleardevice();
                flag1 = 1;
                startGame(cen, room); // ���� startGame ��������ʾ��һ������
            }

            break;
        
        }
    }
}
