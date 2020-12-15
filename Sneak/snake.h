#include <cstdio>
#include <conio.h>
#include <cstdlib>
#include <math.h>
#include <fstream>
#include <iostream>
#include <windows.h>
#include <time.h>
using namespace std;
#define MEM(a,b) memset(a,(b),sizeof(a))
#define setcolor(x) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x)//������ɫ


const int maxiterationtime = 200;
struct point
{
	int x;
	int y;
};
struct GamePanel
{
	int n;		//��ͼ��ģ
	int m;		//��ͼ��ģ
	int totalfoodnum;		//��ǰ��ͼ�е�ʳ������
	int wallnum;			//�ϰ�������
	int success_num;		//��ʤ����Ե�ʳ����
	int speednum;			//��ǰ��ͼ�б��ٵ�����
	int step_speed;			//��ҳԱ��ٵ��ߺ��ߵĲ������˱���ֵ������50
	int obliquenum;			//��ǰ��ͼ��б�ߵ�����
	int speedowner;			//���ٵ��ߵ�ӵ���ߣ�ֵΪ0��1
	int obliqueowner[5];	//б�ߵ��ߵ�ӵ���ߣ�obliqueowner[t]==1��ʾ��tӵ��б�ߵ��ߣ�obliqueowner[t]==0��ʾ��tû��б�ߵ���
	int currentfoodnum;		//��ǰ��ͼ����ʣʳ����
	point food[20];			//��ǰ��ͼ������ʳ�������
	point wall[20];			//��ǰ��ͼ�������ϰ��������
	point speedprops;		//��ǰ��ͼ�б��ٵ��ߵ�����
	point obliqueprops[2];	//��ǰ��ͼ�б���б�ߵ�����
	int panel[50][100];		//��Ϸ����,panel[i][j]��ֵΪ0,1,2,3,4���ֱ��ʾ��ͼ�е�i,jΪ��λ�ã�ʳ��ϰ�����ٵ��ߣ�б�ߵ���
	int stage;
};

int brand()
{
	return (rand() << 16) | (rand() << 1) | (rand() & 1);
}
void bsrand()
{
	srand(GetTickCount());
}
void cls()
{
	system("cls");
}
void retr()	//�˳����� 
{
	HWND hWnd = GetForegroundWindow();
	ShowWindow(hWnd, SW_HIDE);
	exit(0);
}
void GOTO(int x, int y)	//������ƶ�����Ļ�е�λ��
{
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	HANDLE hConsoleOut;
	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);
	csbiInfo.dwCursorPosition.Y = x;
	csbiInfo.dwCursorPosition.X = y;
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
}
void HideCursor()//���ؿ���̨�Ĺ�� 
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

