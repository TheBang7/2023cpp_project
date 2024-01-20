#include <graphics.h>      
#include <conio.h>
#include<stdio.h>
#include<easyx.h>
#include <iostream>
#include "viewmenu.h"
#include <graphics.h>	
#include <chrono>
#include"myMap.h"
#include <conio.h>
#pragma comment( lib, "MSIMG32.LIB")
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg, UINT transparentcolor)
{
    HDC dstDC = GetImageHDC(dstimg);
    HDC srcDC = GetImageHDC(srcimg);
    int w = srcimg->getwidth();
    int h = srcimg->getheight();

    // ʹ�� Windows GDI ����ʵ��͸��λͼ
    TransparentBlt(dstDC, x, y, w, h, srcDC, 0, 0, w, h, transparentcolor);
}

void music(int a) {
    TCHAR cmd[256];
    wsprintf(cmd, _T("setaudio music volume to %d"), a*10);
    mciSendString(cmd, NULL, 0, NULL);

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

void choosesave(MyMap map,int& cen,int& room) {
    IMAGE background;
    loadimage(&background, _T("�������(1).jpg")); // ���ļ��м���ͼƬ
    putimage(0, 0, &background);
    int flag = 1;
    // ��Ӳ˵���ť
    int x = 550, y = 450; // �� y ��������
    int w = 200, h = 60; // ����ť�Ŀ�Ⱥ͸߶�
    TCHAR text[20] = "�浵һ";
    drawButton(x, y, w, h, text, WHITE);
    y += 70; // ���� y ����
    TCHAR textMenu[20] = "�浵��";
    drawButton(x, y, w, h, textMenu, WHITE);

    // ����˳���ť
    y += 70; // ���� y ����
    TCHAR textExit[20] = "�浵��";
    drawButton(x, y, w, h, textExit, WHITE);

    y += 70; // ���� y ����
    TCHAR textExit1[20] = "�浵��";
    drawButton(x, y, w, h, textExit, WHITE);

    MOUSEMSG m;
    while (flag) {
        if (_kbhit()) { // ����м�������
            int key = _getch(); // ��ȡ���µļ�
            if (key == 27) {
                break;
            }
        }
        m = GetMouseMsg(); // ��ȡһ�������Ϣ
        switch (m.uMsg) {
        case WM_MOUSEMOVE:
            if (m.x >= x && m.x <= x + w) {
                if (m.y >= y && m.y <= y + h) {
                    drawButton(x, y, w, h, textExit1, RED);
                }
                else {
                    drawButton(x, y, w, h, textExit1, WHITE);
                }
                if (m.y >= y - 70 && m.y <= y - 70 + h) { // ���� y �����ⷶΧ
                    drawButton(x, y - 70, w, h, textExit, RED);
                }
                else {
                    drawButton(x, y - 70, w, h, textExit, WHITE);
                }
                if (m.y >= y - 140 && m.y <= y - 140 + h) { // ���� y �����ⷶΧ
                    drawButton(x, y - 140, w, h, textMenu, RED);
                }
                else {
                    drawButton(x, y - 140, w, h, textMenu, WHITE);
                }
                if (m.y >= y - 210 && m.y <= y - 210 + h) { // ���� y �����ⷶΧ
                    drawButton(x, y - 210, w, h, text, RED);
                }
                else {
                    drawButton(x, y - 210, w, h, text, WHITE);
                }
            }
            break;
        case WM_LBUTTONDOWN: // ����������
            std::string ss;
            if (m.x >= x && m.x <= x + w && m.y >= y - 210 && m.y <= y - 210 + h) {
                // ����������λ���� "��ʼ��Ϸ" ��ť�ķ�Χ��
                
                ss = "�浵/" + std::to_string(cen) + "." + std::to_string(room) +"/1.txt";
                std::string filename = ss;
                map.saveMap(ss);
                flag = 0;
                break;

            }

            if (m.x >= x && m.x <= x + w && m.y >= y - 140 && m.y <= y - 140 + h) {
                // ����������λ���� "��ʼ��Ϸ" ��ť�ķ�Χ��
                ss = "�浵/" + std::to_string(cen) + "." + std::to_string(room) + "/2.txt";
                std::string filename = ss;
                map.saveMap(ss);
                flag = 0;
                break;

            }
            else if (m.x >= x && m.x <= x + w && m.y >= y - 70 && m.y <= y - 70 + h) {
                // ����������λ���� "��ʼ��Ϸ" ��ť�ķ�Χ��
                ss = "�浵/" + std::to_string(cen) + "." + std::to_string(room) + "/3.txt";
                std::string filename = ss;
                map.saveMap(ss);
                flag = 0;
                break;
            }
            else if (m.x >= x && m.x <= x + w && m.y >= y && m.y <= y + h) {
                // ����������λ���� "��ʼ��Ϸ" ��ť�ķ�Χ��
                ss = "�浵/" + std::to_string(cen) + "." + std::to_string(room) + "/3.txt";
                std::string filename = ss;
                map.saveMap(ss);
                flag = 0;
                break;
            }


            break;

        }
    }
}
void chooseload(MyMap map, int& cen, int& room) {
    IMAGE background;
    loadimage(&background, _T("�������(1).jpg")); // ���ļ��м���ͼƬ
    putimage(0, 0, &background);
    int flag = 1;
    // ��Ӳ˵���ť
    int x = 550, y = 450; // �� y ��������
    int w = 200, h = 60; // ����ť�Ŀ�Ⱥ͸߶�
    TCHAR text[20] = "�浵һ";
    drawButton(x, y, w, h, text, WHITE);
    y += 70; // ���� y ����
    TCHAR textMenu[20] = "�浵��";
    drawButton(x, y, w, h, textMenu, WHITE);

    // ����˳���ť
    y += 70; // ���� y ����
    TCHAR textExit[20] = "�浵��";
    drawButton(x, y, w, h, textExit, WHITE);

    y += 70; // ���� y ����
    TCHAR textExit1[20] = "�浵��";
    drawButton(x, y, w, h, textExit, WHITE);

    MOUSEMSG m;
    while (flag) {
        if (_kbhit()) { // ����м�������
            int key = _getch(); // ��ȡ���µļ�
            if (key == 27) {
                break;
            }
        }
        m = GetMouseMsg(); // ��ȡһ�������Ϣ
        switch (m.uMsg) {
        case WM_MOUSEMOVE:
            if (m.x >= x && m.x <= x + w) {
                if (m.y >= y && m.y <= y + h) {
                    drawButton(x, y, w, h, textExit1, RED);
                }
                else {
                    drawButton(x, y, w, h, textExit1, WHITE);
                }
                if (m.y >= y - 70 && m.y <= y - 70 + h) { // ���� y �����ⷶΧ
                    drawButton(x, y - 70, w, h, textExit, RED);
                }
                else {
                    drawButton(x, y - 70, w, h, textExit, WHITE);
                }
                if (m.y >= y - 140 && m.y <= y - 140 + h) { // ���� y �����ⷶΧ
                    drawButton(x, y - 140, w, h, textMenu, RED);
                }
                else {
                    drawButton(x, y - 140, w, h, textMenu, WHITE);
                }
                if (m.y >= y - 210 && m.y <= y - 210 + h) { // ���� y �����ⷶΧ
                    drawButton(x, y - 210, w, h, text, RED);
                }
                else {
                    drawButton(x, y - 210, w, h, text, WHITE);
                }
            }
            break;
        case WM_LBUTTONDOWN: // ����������
            std::string ss;
            if (m.x >= x && m.x <= x + w && m.y >= y - 210 && m.y <= y - 210 + h) {
                // ����������λ���� "��ʼ��Ϸ" ��ť�ķ�Χ��

                ss = "�浵/" + std::to_string(cen) + "." + std::to_string(room) + "/1.txt";
                std::string filename = ss;
                map.loadMap(ss);
                flag = 0;
                break;

            }

            if (m.x >= x && m.x <= x + w && m.y >= y - 140 && m.y <= y - 140 + h) {
                // ����������λ���� "��ʼ��Ϸ" ��ť�ķ�Χ��
                ss = "�浵/" + std::to_string(cen) + "." + std::to_string(room) + "/2.txt";
                std::string filename = ss;
                map.loadMap(ss);
                flag = 0;
                break;

            }
            else if (m.x >= x && m.x <= x + w && m.y >= y - 70 && m.y <= y - 70 + h) {
                // ����������λ���� "��ʼ��Ϸ" ��ť�ķ�Χ��
                ss = "�浵/" + std::to_string(cen) + "." + std::to_string(room) + "/3.txt";
                std::string filename = ss;
                map.loadMap(ss);
                flag = 0;
                break;
            }
            else if (m.x >= x && m.x <= x + w && m.y >= y && m.y <= y + h) {
                // ����������λ���� "��ʼ��Ϸ" ��ť�ķ�Χ��
                ss = "�浵/" + std::to_string(cen) + "." + std::to_string(room) + "/4.txt";
                std::string filename = ss;
                map.loadMap(ss);
                flag = 0;
                break;
            }


            break;

        }
    }
}

void chooseCeng(int& cen, int& room) {
    IMAGE background;
    loadimage(&background, _T("�������(1).jpg")); // ���ļ��м���ͼƬ
    putimage(0, 0, &background);
    // ��Ӳ˵���ť
    int x = 550, y = 450; // �� y ��������
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
    MOUSEMSG m;
    while (flag1 == 0) {
        if (_kbhit()) { // ����м�������
            int key = _getch(); // ��ȡ���µļ�
            if (key == 27) {
                menu1(cen, room);
                break;
            }
        }
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
                diyiceng(1, cen, room); // ���� startGame ��������ʾ��һ������

            }
            else if (m.x >= x && m.x <= x + w && m.y >= y - 70 && m.y <= y - 70 + h) {
                // ����������λ���� "��ʼ��Ϸ" ��ť�ķ�Χ��
                cleardevice();
                flag1 = 1;
                diyiceng(2, cen, room); // ���� startGame ��������ʾ��һ������
            }
            else if (m.x >= x && m.x <= x + w && m.y >= y && m.y <= y + h) {
                // ����������λ���� "��ʼ��Ϸ" ��ť�ķ�Χ��
                cleardevice();
                flag1 = 1;
                diyiceng(3, cen, room); // ���� startGame ��������ʾ��һ������
            }

            break;

        }
    }




}

void diyiceng(int n, int& cen, int& room) {
    cleardevice();
    IMAGE background; // ����һ�� IMAGE �������ڴ洢����ͼƬ
    loadimage(&background, _T("����.png")); // ���ļ��м���ͼƬ
    putimage(0, 0, &background); // ��ͼƬ���Ƶ������ϣ�ͼƬ���Ͻ�����Ϊ (0,0)
    while (true) {
        if (_kbhit()) { // ����м�������
            int key = _getch(); // ��ȡ���µļ�
            if (key == 27) {
                chooseCeng(cen, room);
                break;
            }
        }
        MOUSEMSG m;
        m = GetMouseMsg();
        if (m.uMsg == WM_LBUTTONDOWN) {
            if (m.x >= 0 && m.x <= 625 && m.y >= 0 && m.y <= 500) {
                // ����������λ���� "��һ��" ��Χ��
                cleardevice();
                cen = n;
                room = 1;
                break;
            }
            if (m.x >= 625 && m.x <= 1250 && m.y >= 0 && m.y <= 500) {
                // ����������λ���� "��һ��" ��Χ��
                cleardevice();
                cen = n;
                room = 2;
                break;
            }
            if (m.x >= 0 && m.x <= 625 && m.y >= 500 && m.y <= 1000) {
                // ����������λ���� "��һ��" ��Χ��
                cleardevice();
                cen = n;
                room = 3;
                break;
            }
            if (m.x >= 625 && m.x <= 1250 && m.y >= 500 && m.y <= 1000) {
                // ����������λ���� "��һ��" ��Χ��
                cleardevice();
                cen = n;
                room = 4;
                break;
            }
        }
    }
}

void startGame(int& cen, int& room) {
    cleardevice(); // ��յ�ǰ��ͼ���豸
    // �����������Ϸ��ʼ��Ľ������
    
    IMAGE background; // ����һ�� IMAGE �������ڴ洢����ͼƬ
    loadimage(&background, _T("�������(1).jpg")); // ���ļ��м���ͼƬ
    putimage(0, 0, &background); // ��ͼƬ���Ƶ������ϣ�ͼƬ���Ͻ�����Ϊ (0,0)
    IMAGE guard; // ����һ�� IMAGE �������ڴ洢����ͼƬ
    loadimage(&guard, _T("�ܼ�ͼƬ(1).png")); // ���ļ��м���ͼƬ
    transparentimage(NULL, 0, 750, &guard, BLACK); // ��ͼƬ���Ƶ������ϣ�ͼƬ���Ͻ�����Ϊ (1000,0)
    std::string ptext =
        "�𾴵����ߴ��ˣ����ڵȵ����ˣ������Ǳ��ĵ������ӡ��һֻ���������ڷ�ӡ���ɶ��ˡ����ߴ�����ֻҪ������ΰ�ʥ��Ż�ָ���ĵط�����վ�����۾Ϳ����������������㣬�ӵ�һ�㵽��������޸���ӡ���Ѷ�Խ��Խ�ߣ�ÿ�����ĸ���ӡ��Ҫ�޲���ף���ߴ��˿�����������";

    int currentChar = 0;
    int x = 250, y = 750;
    settextstyle(30, 0, _T("����")); // ���������СΪ 40
    settextcolor(WHITE); // ��������ɫ����Ϊ��ɫ
    MOUSEMSG m;
    bool flag2 = 0;
    while (true) {
        if (currentChar < ptext.length() && flag2 == 0) {
            setbkmode(TRANSPARENT); // ���ñ���ģʽΪ͸��
            outtextxy(x, y, ptext.substr(currentChar, 2).c_str());
            x = x + 40;
            if ((currentChar / 2 + 1) % 25 == 0) { // ÿ15���ֻ���
                x = 250;
                y = y + 40;
            }

            auto start = std::chrono::high_resolution_clock::now();
            while (true) {
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> elapsed = end - start;
                if (elapsed.count() > 100) {
                    break;
                }
                // �������������Ҫ��ѭ����ִ�еĴ���
                if (_kbhit()) { // ����м�������
                    int key = _getch(); // ��ȡ���µļ�
                    if (key == 32) {
                        flag2 = 1;
                    }
                }
            }

            currentChar += 2; // ÿ������2����Ϊһ�������������ַ����
        }
        else {
            break;
        }
    }
    chooseCeng(cen, room);
}

int volume = 5; // ��ʼ����



void shezhi(int& cen,int& room) {
    cleardevice(); // ��յ�ǰ��ͼ���豸
    
    IMAGE background; // ����һ�� IMAGE �������ڴ洢����ͼƬ
    loadimage(&background, _T("����ͼƬ.png")); // ���ļ��м���ͼƬ
    putimage(0, 0, &background); // ��ͼƬ���Ƶ������ϣ�ͼƬ���Ͻ�����Ϊ (0,0)

    // ��ʾ����������

    // ��ʾ�������ڰ�ť
    settextstyle(50, 0, _T("����")); // ���������С������
    settextcolor(WHITE); // ��������ɫ����Ϊ��ɫ

    setbkmode(TRANSPARENT); // ���ñ���ģʽΪ͸��
    rectangle(950, 230, 1025, 290); // ��������ť
    outtextxy(975, 235, _T("+"));
    rectangle(1050, 230, 1125, 290); // ��������ť
    outtextxy(1075, 235, _T("-"));
    TCHAR volumeText[20];
    _stprintf(volumeText, _T("����: %d"), volume);
    outtextxy(950, 150, volumeText);
    MOUSEMSG m; // ���������Ϣ
    while (true) {
        if (_kbhit()) { // ����м�������
             int key = _getch(); // ��ȡ���µļ�
             if (key == 27) {
                 menu1( cen, room);
                 break;
             }
        }
        
        m = GetMouseMsg(); // ��ȡһ�������Ϣ
        switch (m.uMsg) {
        case WM_LBUTTONDOWN: // ����������
            if (m.x >= 950 && m.x <= 1025 && m.y >= 230 && m.y <= 290) {
                // ����������λ���� "+" ��ť�ķ�Χ��
                if (volume < 10) {
                    volume++; // ��������
                    music(volume);
                }
                cleardevice(); // ��յ�ǰ��ͼ���豸
                putimage(0, 0, &background);
                settextstyle(50, 0, _T("����")); // ���������С������
                setbkmode(TRANSPARENT); // ���ñ���ģʽΪ͸��
                rectangle(950, 230, 1025, 290); // ��������ť
                outtextxy(975, 235, _T("+"));
                rectangle(1050, 230, 1125, 290); // ��������ť
                outtextxy(1075, 235, _T("-"));
                TCHAR volumeText[20];
                _stprintf(volumeText, _T("����: %d"), volume);
                outtextxy(950, 150, volumeText); // ��ͬһλ��д���µ�����
            }
            else if (m.x >= 1050 && m.x <= 1125 && m.y >= 230 && m.y <= 290) {
                // ����������λ���� "-" ��ť�ķ�Χ��
                if (volume >= 1) {
                    volume--; // ��������
                    music(volume);
                }
                cleardevice(); // ��յ�ǰ��ͼ���豸
                putimage(0, 0, &background);
                settextstyle(50, 0, _T("����")); // ���������С������
                setbkmode(TRANSPARENT); // ���ñ���ģʽΪ͸��
                rectangle(950, 230, 1025, 290); // ��������ť
                outtextxy(975, 235, _T("+"));
                rectangle(1050, 230, 1125, 290); // ��������ť
                outtextxy(1075, 235, _T("-"));
                TCHAR volumeText[20];
                _stprintf(volumeText, _T("����: %d"), volume);
                outtextxy(950, 150, volumeText); // ��ͬһλ��д���µ�����
            }
            break;

        }
    }
}



void menu1(int& cen,int& room) {

    mciSendString(_T("open Amphitrite.mp3 alias music"), NULL, 0, NULL);

    // ��������
    music(5);

    mciSendString(_T("play music repeat"), NULL, 0, NULL);

    
    
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
            else if (m.x >= x && m.x <= x + w && m.y >= y && m.y <= y + h) {
                // ����������λ���� "�˳�" ��ť�ķ�Χ��
                closegraph(); // �ر�ͼ�ν���
                exit(0); // ��������
            }
            else if (m.x >= x && m.x <= x + w && m.y >= y - 70 && m.y <= y + h-70) {
                shezhi(cen,room);
                flag1 = 1;
            }

            break;
        
        }
    }
}
