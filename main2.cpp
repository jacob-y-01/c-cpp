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


// �ж���û�и÷�Χ�ڵ���ɫ
int rmax=170,gmax=170, bmax=170;
int rmin=120,gmin=120, bmin=120;
int x2 = 1940, y = 1079, x = 1800,y2 = 1087;

// ��ȡĳ���ص��ɫ�ʣ�����ֵ��color
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
// ����
void warning()
{
    // �������ļ�
    mciSendString("open  warning.mp3 alias mymusic", NULL, 0, NULL);
    mciSendString("play mymusic", NULL, 0, NULL);
    Sleep(10000);
    mciSendString("stop mymusic", NULL, 0, NULL);
    mciSendString("close mymusic", NULL, 0, NULL);
}

// ����һ������ģ������ж��Ƿ�������
bool judge_name()
{
    // ��ɫ��Χֵ
    int r=120, g=120, b=120;
    int mr=150, mg=150, mb=150;

    // ���ֳ�������
    int x= 1715, y= 1075;
    int x1= 1750, y1=1080;
    for (int i = x; i < x1; i++)
    {
        for (int j = y; j < y1; j++)
        {
            color c1 = get_color(i, j);
            // ���ϰ�ɫ����������˵����������
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
                cout << "��ɫ" << endl;
                return false;
            }
            else if(c1.r<rmax&&c1.r>rmin)
            {
                cout << "��ɫ" << endl;
                return true;
            }
            else if(c1.b<bmax&& c1.b>bmin)
            {
                cout << "��ɫ" << endl;
                return false;
            }
            else
            {
                cout << "��ɫ" << endl;
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
        // ������           ���˷����棬û�˷��ؼ�
        if (judge_name())
        {
            cout << "��������" << endl;
            // �ж�����ɫ
            if (judge_color())
            {
                warning();
            }
        }
        else
        {
            cout << "����δ����������" << endl;
        }
    }
    return 0;
}