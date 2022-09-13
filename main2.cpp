#include<iostream>
#include<Windows.h>
#include <conio.h>
#include <vfw.h>
#include <MMSystem.h>
#include<string>
using namespace std;
#pragma comment(lib, "WINMM.LIB")
#pragma comment(lib,"vfw32.lib")

typedef struct {
    int r;
    int g;
    int b;

} color;


// 判断有没有该范围内的颜色
int rmax=170,gmax=170, bmax=170;
int rmin=120,gmin=120, bmin=120;
int x2 = 1940, y = 1079, x = 1800,y2 = 1087;

// 获取某像素点的色彩，并赋值给color
color get_color( int x, int y)
{
    color* RGB=(color*)malloc(sizeof(color));
    HWND hwnd;
    HDC hdc = GetDC(NULL);
    COLORREF clr = GetPixel(hdc, x, y);
    RGB->r = GetRValue(clr);
    RGB->g = GetGValue(clr);
    RGB->b = GetBValue(clr);
    return *RGB;
}
// 警报
void warning()
{
    // 打开音乐文件
    mciSendString("open  warning.mp3 alias mymusic", NULL, 0, NULL);
    mciSendString("play mymusic", NULL, 0, NULL);
    Sleep(10000);
    mciSendString("stop mymusic", NULL, 0, NULL);
    mciSendString("close mymusic", NULL, 0, NULL);
}

// 这是一个特殊的，用于判断是否有名字
bool judge_name()
{
    // 白色范围值
    int r=120, g=120, b=120;
    int mr=150, mg=150, mb=150;

    // 名字出现区域
    int x= 1715, y= 1075;
    int x1= 1750, y1=1080;
    for (int i = x; i < x1; i++)
    {
        for (int j = y; j < y1; j++)
        {
            color c1 = get_color(i, j);
            // 符合白色名字条件，说明本地有人
            if (c1.r>r&&c1.r<mr&& c1.g > g && c1.g < mg&& c1.b > b && c1.b < mb)
            {
                return true;
            }
        }
    }
    return false;
}

bool judge_color()
{
    for (int i = x; i < x2; i++)
    {
        for (int j = y; j < y2; j++)
        {
            color c1 = get_color(i, j);
            cout << c1.r<< " " << c1.g<<" " << c1.b << endl;
            if (c1.g<gmax&&c1.g>gmin)
            {
                cout << "绿色" << endl;
                return false;
            }
            else if(c1.r<rmax&&c1.r>rmin)
            {
                cout << "红色" << endl;
                return true;
            }
            else if(c1.b<bmax&& c1.b>bmin)
            {
                cout << "蓝色" << endl;
                return false;
            }
            else
            {
                cout << "白色" << endl;
                return true;
            }
        }
    }
    return false;
}


int main1()
{
    while (true)
    {
        Sleep(500);
        // 有人名           有人返回真，没人返回假
        if (judge_name())
        {
            cout << "发现名字" << endl;
            // 判断其颜色
            if (judge_color())
            {
                warning();
            }
        }
        else
        {
            cout << "本地未发现其他人" << endl;
        }
    }
    return 0;
}