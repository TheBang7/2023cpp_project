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

    // 使用 Windows GDI 函数实现透明位图
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
    IMAGE background; // 定义一个 IMAGE 对象用于存储背景图片
    loadimage(&background, _T("房间.png")); // 从文件中加载图片
    putimage(0, 0, &background); // 将图片绘制到窗口上，图片左上角坐标为 (0,0)
    MOUSEMSG m;
    m = GetMouseMsg();
    if (m.uMsg == WM_LBUTTONDOWN) {
        if (m.x >= 0 && m.x <= 625 && m.y >= 0 && m.y <= 500) {
            // 如果鼠标点击的位置在 "第一间" 范围内
            cleardevice();
            cen = n;
            room = 1;
        }
        if (m.x >= 625 && m.x <= 1250 && m.y >= 0 && m.y <= 500) {
            // 如果鼠标点击的位置在 "第一间" 范围内
            cleardevice();
            cen = n;
            room = 2;
        }
        if (m.x >= 0 && m.x <= 625 && m.y >= 500 && m.y <= 1000) {
            // 如果鼠标点击的位置在 "第一间" 范围内
            cleardevice();
            cen = n;
            room = 3;
        }
        if (m.x >= 625 && m.x <= 1250 && m.y >= 500 && m.y <= 1000) {
            // 如果鼠标点击的位置在 "第一间" 范围内
            cleardevice();
            cen = n;
            room = 4;
        }
    }
}



void startGame(int& cen, int& room) {
    cleardevice(); // 清空当前的图形设备
    // 在这里添加游戏开始后的界面代码
    initgraph(1250, 1000);
    IMAGE background; // 定义一个 IMAGE 对象用于存储背景图片
    loadimage(&background, _T("地牢入口(1).jpg")); // 从文件中加载图片
    putimage(0, 0, &background); // 将图片绘制到窗口上，图片左上角坐标为 (0,0)
    IMAGE guard; // 定义一个 IMAGE 对象用于存储背景图片
    loadimage(&guard, _T("管家图片(1).png")); // 从文件中加载图片
    transparentimage(NULL, 0, 750, &guard,BLACK); // 将图片绘制到窗口上，图片左上角坐标为 (1000,0)
    std::string ptext =
        "尊敬的勇者大人，终于等到您了！这座城堡的地牢里封印着一只恶龙，现在封印逐渐松动了。勇者大人您只要进入地牢把圣物放回指定的地方，并站入阵眼就可以啦！地牢有三层，从第一层到第三层的修复封印的难度越来越高，每层有四个封印需要修补。祝勇者大人凯旋！！！！";

    int currentChar = 0;
    int x = 250, y = 750;
    settextstyle(30, 0, _T("黑体")); // 设置字体大小为 40
    MOUSEMSG m;
    bool flag2 = 0;
    while (true) {
        if ( currentChar < ptext.length()&&flag2==0) {
            setbkmode(TRANSPARENT); // 设置背景模式为透明
            outtextxy(x, y, ptext.substr(currentChar, 2).c_str());
            x = x + 40;
            if ((currentChar / 2 + 1) % 25 == 0) { // 每15个字换行
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
                // 在这里添加你想要在循环中执行的代码
                m = GetMouseMsg();
                if (m.uMsg == WM_LBUTTONDOWN) {

                                flag2 = 1;
                                break;
                            }
            }
            
            currentChar += 2; // 每次增加2，因为一个汉字由两个字符组成
        }
        else {
            break;
        }
    }
    loadimage(&background, _T("地牢入口(1).jpg")); // 从文件中加载图片
    putimage(0, 0, &background);
    // 添加菜单按钮
    x = 550, y = 450; // 将 y 坐标上移
    int w = 200, h = 60; // 增大按钮的宽度和高度
    TCHAR text[20] = "第一层地牢";
    drawButton(x, y, w, h, text, WHITE);
    y += 70; // 更新 y 坐标
    TCHAR textMenu[20] = "第二层地牢";
    drawButton(x, y, w, h, textMenu, WHITE);

    // 添加退出按钮
    y += 70; // 更新 y 坐标
    TCHAR textExit[20] = "第三层地牢";
    drawButton(x, y, w, h, textExit, WHITE);

    
    bool flag1 = 0;
    while (flag1 == 0) {
        m = GetMouseMsg(); // 获取一条鼠标消息
        switch (m.uMsg) {
        case WM_MOUSEMOVE:
            if (m.x >= x && m.x <= x + w) {
                if (m.y >= y && m.y <= y + h) {
                    drawButton(x, y, w, h, textExit, RED);
                }
                else {
                    drawButton(x, y, w, h, textExit, WHITE);
                }
                if (m.y >= y - 70 && m.y <= y - 70 + h) { // 更新 y 坐标检测范围
                    drawButton(x, y - 70, w, h, textMenu, RED);
                }
                else {
                    drawButton(x, y - 70, w, h, textMenu, WHITE);
                }
                if (m.y >= y - 140 && m.y <= y - 140 + h) { // 更新 y 坐标检测范围
                    drawButton(x, y - 140, w, h, text, RED);
                }
                else {
                    drawButton(x, y - 140, w, h, text, WHITE);
                }
            }
            break;
        case WM_LBUTTONDOWN: // 鼠标左键按下
            if (m.x >= x && m.x <= x + w && m.y >= y - 140 && m.y <= y - 140 + h) {
                // 如果鼠标点击的位置在 "开始游戏" 按钮的范围内
                cleardevice();
                flag1 = 1;
                diyiceng(1,cen,room); // 调用 startGame 函数来显示下一个界面
                
            }
            else if (m.x >= x && m.x <= x + w && m.y >= y - 70 && m.y <= y - 70 + h) {
                // 如果鼠标点击的位置在 "开始游戏" 按钮的范围内
                cleardevice();
                flag1 = 1;
                diyiceng(2,cen,room); // 调用 startGame 函数来显示下一个界面
            }
            else if (m.x >= x && m.x <= x + w && m.y >= y  && m.y <= y + h) {
                // 如果鼠标点击的位置在 "开始游戏" 按钮的范围内
                cleardevice();
                flag1 = 1;
                diyiceng(3,cen,room); // 调用 startGame 函数来显示下一个界面
            }

            break;

        }
    }




}

void menu1(int argc, char** argv,int& cen,int& room) {

    initgraph(1250, 1000);
    IMAGE background; // 定义一个 IMAGE 对象用于存储背景图片
    loadimage(&background, _T("城堡背景(1).jpg")); // 从文件中加载图片
    putimage(0, 0, &background); // 将图片绘制到窗口上，图片左上角坐标为 (0,0)

    // 添加游戏名字
    TCHAR gameName[] = _T("封印恶龙");
    settextstyle(100, 0, _T("黑体")); // 设置字体大小和字体
    settextcolor(WHITE); // 设置字体颜色
    setbkmode(TRANSPARENT); // 设置背景模式为透明
    int tx = (getwidth() - textwidth(gameName)) / 2; // 计算文本的 x 坐标以使其居中
    outtextxy(tx, 50, gameName); // 在指定位置输出游戏名字

    int x = 550, y = 550; // 将 y 坐标上移
    int w = 200, h = 60; // 增大按钮的宽度和高度
    TCHAR text[20] = "开始游戏";
    drawButton(x, y, w, h, text, WHITE);

    // 添加菜单按钮
    y += 70; // 更新 y 坐标
    TCHAR textMenu[20] = "菜单";
    drawButton(x, y, w, h, textMenu, WHITE);

    // 添加退出按钮
    y += 70; // 更新 y 坐标
    TCHAR textExit[20] = "退出";
    drawButton(x, y, w, h, textExit, WHITE);

    MOUSEMSG m; // 定义鼠标消息
    bool flag1 = 0;
    while (flag1 == 0 ) {
        m = GetMouseMsg(); // 获取一条鼠标消息
        switch (m.uMsg) {
        case WM_MOUSEMOVE:
            if (m.x >= x && m.x <= x + w) {
                if (m.y >= y && m.y <= y + h) {
                    drawButton(x, y, w, h, textExit, RED);
                }
                else {
                    drawButton(x, y, w, h, textExit, WHITE);
                }
                if (m.y >= y - 70 && m.y <= y - 70 + h) { // 更新 y 坐标检测范围
                    drawButton(x, y - 70, w, h, textMenu, RED);
                }
                else {
                    drawButton(x, y - 70, w, h, textMenu, WHITE);
                }
                if (m.y >= y - 140 && m.y <= y - 140 + h) { // 更新 y 坐标检测范围
                    drawButton(x, y - 140, w, h, text, RED);
                }
                else {
                    drawButton(x, y - 140, w, h, text, WHITE);
                }
            }
            break;
        case WM_LBUTTONDOWN: // 鼠标左键按下
            if (m.x >= x && m.x <= x + w && m.y >= y - 140 && m.y <= y - 140 + h) {
                // 如果鼠标点击的位置在 "开始游戏" 按钮的范围内
                cleardevice();
                flag1 = 1;
                startGame(cen, room); // 调用 startGame 函数来显示下一个界面
            }

            break;
        
        }
    }
}
