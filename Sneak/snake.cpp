#include "machine1.h"
using namespace std;

int main();

int CreateSnake(int m, int n, point snake[5][100], int len[5], int direct[5])	//���ɳ�ʼ��
{
	int i;

	setcolor(15);	//��0���߰�ɫ
	snake[0][1].x = n; snake[0][1].y = m - 6;//��0����panel[n][m-6]+panel[n][m-4]+panel[n][m-2], ��ɫ
	snake[0][2].x = n; snake[0][2].y = m - 4;
	len[0] = 3;
	snake[0][3].x = n; snake[0][3].y = m - 2;
	direct[0] = 2;
	for (i = 1; i <= len[0]; i++) GOTO(snake[0][i].x, snake[0][i].y), printf("�~");

	setcolor(13);	//��1���߷�ɫ
	snake[1][1].x = 1; snake[1][1].y = 6;  //��1����panel[1][6]+panel[1][4]+panel[1][2]
	snake[1][2].x = 1; snake[1][2].y = 4;
	len[1] = 3;
	snake[1][3].x = 1; snake[1][3].y = 2;
	direct[1] = 1;
	for (i = 1; i <= len[1]; i++) GOTO(snake[1][i].x, snake[1][i].y), printf("�~");

	return 0;
}

void draw(int m, int n)//���߽�
{
	int i;
	setcolor(6);
	for (i = 0; i <= n + 1; i++) GOTO(i, m + 2), printf("�~"), GOTO(i, 0), printf("�~");
	for (i = 1; i <= m / 2 + 1; i++) GOTO(n + 1, i * 2), printf("�~"), GOTO(0, i * 2), printf("�~");
}

void stop(int n)
{
	setcolor(7);
	GOTO(n + 1, 30);
	printf("���س��ָ�");
	char ch = _getch();
	while (ch != 13) ch = _getch();
}

void Ending(int n) {
	GOTO(n + 1, 30);
	printf("���س�����\n");
	char ch = _getch();
	while (ch != 13) ch = _getch();
	main(); exit(0);
}

bool check_food_wall_props(int m, int n, int x, int y, point snake[5][100], int len[5])
{
	int i;
	if (x<2 || x>n - 1 || y<4 || y>m - 2) return false;

	for (i = 1; i <= len[0]; i++)
		if (x == snake[0][i].x && y == snake[0][i].y) return false;

	for (i = 1; i <= len[1]; i++)
		if (x == snake[1][i].x && y == snake[1][i].y) return false;

	return true;
}

void rand_food(point snake[5][100], int len[5], GamePanel &gp)
{
	int x, y, i, m, n;
	if (gp.currentfoodnum > 0) return;
	m = gp.m;
	n = gp.n;

	setcolor(10);
	for (i = 0; i < gp.totalfoodnum; i++)
	{
		x = brand() % (n + 1);
		y = (brand() % m / 2) * 2;
		while (gp.panel[x][y] != 0 || !check_food_wall_props(m, n, x, y, snake, len))
		{
			x = brand() % (n + 1);
			y = (brand() % m / 2) * 2;
		}
		gp.currentfoodnum++;
		gp.panel[x][y] = 1;
		gp.food[i].x = x;
		gp.food[i].y = y;
		GOTO(x, y);
		printf("��");
	}

}

void rand_wall(point snake[5][100], int len[5], GamePanel &gp)
{
	int x, y, i, m, n;
	m = gp.m;
	n = gp.n;

	setcolor(6);
	for (i = 0; i < 20; i++)
	{
		x = brand() % (n + 1);
		y = (brand() % m / 2) * 2;
		while (gp.panel[x][y] != 0 || !check_food_wall_props(m, n, x, y, snake, len))
		{
			x = brand() % (n + 1);
			y = (brand() % m / 2) * 2;
		}
		gp.panel[x][y] = 2;
		gp.wall[i].x = x;
		gp.wall[i].y = y;
		GOTO(x, y);
		printf("�~");
	}
	gp.wallnum = 20;

}
void rand_props(point snake[5][100], int len[5], GamePanel &gp)
{
	int x, y, m, n;
	m = gp.m;
	n = gp.n;

	setcolor(9);
	x = brand() % (n + 1);
	y = (brand() % m / 2) * 2;
	while (gp.panel[x][y] != 0 || !check_food_wall_props(m, n, x, y, snake, len))
	{
		x = brand() % (n + 1);
		y = (brand() % m / 2) * 2;
	}
	gp.panel[x][y] = 3;
	gp.speedprops.x = x;
	gp.speedprops.y = y;

	GOTO(x, y);
	printf("��");

	setcolor(12);
	x = brand() % (n + 1);
	y = (brand() % m / 2) * 2;
	while (gp.panel[x][y] != 0 || !check_food_wall_props(m, n, x, y, snake, len))
	{
		x = brand() % (n + 1);
		y = (brand() % m / 2) * 2;
	}
	gp.panel[x][y] = 4;
	gp.obliqueprops[0].x = x;
	gp.obliqueprops[0].y = y;
	GOTO(x, y);
	printf("��");

	x = brand() % (n + 1);
	y = (brand() % m / 2) * 2;
	while (gp.panel[x][y] != 0 || !check_food_wall_props(m, n, x, y, snake, len))
	{
		x = brand() % (n + 1);
		y = (brand() % m / 2) * 2;
	}
	gp.panel[x][y] = 4;
	gp.obliqueprops[1].x = x;
	gp.obliqueprops[1].y = y;

	GOTO(x, y);
	printf("��");

	gp.speednum = 1;
	gp.obliquenum = 2;
}


int move(int t, point snake[5][100], int len[5], int direct[5], GamePanel &gp, int &iterationtime)
{
	if (t == 0) setcolor(15);
	else if (t == 1) setcolor(13);
	int m = gp.m;
	int n = gp.n;

	int x, y;


	x = snake[t][1].x; y = snake[t][1].y;
	/****************************************************************/
	int nextdirection = machine_move1(snake, len, direct, t, gp);
	/****************************************************************/

	if (gp.obliqueowner[t] != 1) //�����t�� ӵ��б�ߵ��ߣ�����б��ָ��ת��Ϊ����
	{
		if (nextdirection == 4) nextdirection = 1;
		else if (nextdirection == 5) nextdirection = 1;
		else if (nextdirection == 6) nextdirection = 2;
		else if (nextdirection == 7) nextdirection = 2;
	}

	int temp = -1;	//Ӯ�ұ��,temp=0��ʾ0Ӯ��temp=1��ʾ1Ӯ��temp=111��ʾƽ�֣�temp=-1��ʾûӮû�����ڽ���
	int op = 1 - t;	//t�Ķ��ֱ��
	bool enough = false;
	bool timelimit = false;
	bool selfkill = false;
	if (check1(snake, len, t, gp, nextdirection) == false) { selfkill = true; temp = op; }//lose
	else
	{

		direct[t] = nextdirection;
		int flg[8][2] = { { 1,0 },{ 0,2 },{ 0,-2 },{ -1,0 },{ 1,2 },{ -1,2 },{ -1,-2 },{ 1,-2 } };
		x += flg[direct[t]][0]; y += flg[direct[t]][1];

		if (gp.panel[x][y] == 1)			//�Ե�ʳ��
		{
			gp.currentfoodnum--;
			len[t]++;
			iterationtime = 0;
			setcolor(15);//cls();
			if (t == 0)
			{
				GOTO(n + 1, 77);
				printf("%d", len[t] - 3);
			}
			else
			{
				GOTO(0, 9);
				printf("%d", len[t] - 3);
				setcolor(13);
			}
		}
		else if (gp.panel[x][y] == 3)		//�Ե����ٵ���
		{
			gp.speedowner = t;
			gp.speednum = 0;
			gp.step_speed = 0;
		}
		else if (gp.panel[x][y] == 4)		//�Ե�б�ߵ���
		{
			gp.obliqueowner[t] = 1;
			gp.obliquenum--;
		}
		if (gp.panel[x][y] == 0 || gp.panel[x][y] == 3 || gp.panel[x][y] == 4)
		{
			GOTO(snake[t][len[t]].x, snake[t][len[t]].y);
			printf("  ");
		}
		gp.panel[x][y] = 0;
		for (int i = len[t]; i > 1; i--) snake[t][i] = snake[t][i - 1];
		snake[t][1].x = x;
		snake[t][1].y = y;
		GOTO(snake[t][1].x, snake[t][1].y);
		printf("�~");

		if (len[t] - 3 >= gp.success_num) { enough = true; temp = t; }		//��tӮ�ˣ�����t
		else if (iterationtime >= maxiterationtime)	//�ﵽ������������δ�ֳ�ʤ��
		{
			timelimit = true;
			if (len[0] > len[1]) temp = 0;
			else if (len[1] > len[0]) temp = 1;
			else temp = 111;			//ƽ��
		}
	}

	if (temp != -1)
	{
		setcolor(15);//cls();
		GOTO(n + 1, 0);

		if (temp == 0)
		{
			if (enough == true) printf("�׷��Թ�ʳ���ʤ��");
			else if (selfkill == true) printf("�׷���Է���ɱ��ʤ��");
			else if (timelimit == true) printf("�׷���ʱ��ʤ��");
			else printf("�׷���ʤ��");
		}
		else if (temp == 1)
		{
			if (enough == true) printf("�۷��Թ�ʳ���ʤ��");
			else if (selfkill == true) printf("�۷���Է���ɱ��ʤ��");
			else if (timelimit == true) printf("�۷���ʱ��ʤ��");
			else printf("�۷���ʤ��");
		}
		else { printf("˫����ƽ��"); }
		Ending(n);
	}
	else
	{
		if (gp.currentfoodnum == 0)
		{
			rand_food(snake, len, gp);
			gp.stage++;
		}
	}
	return 0;
}

int main()
{
	HideCursor();
	bsrand();

	GamePanel gp;
	gp.m = 76;
	gp.n = 28;
	gp.stage = 1;
	gp.totalfoodnum = 10;
	gp.wallnum = 0;
	gp.success_num = 35;
	gp.currentfoodnum = 0;
	MEM(gp.panel, 0);
	MEM(gp.obliqueowner, 0);


	int score = 0;

	int iterationtime = 0;
	int m, n;
	m = gp.m, n = gp.n;
	point snake[5][100];//1ͷ totβ 
	int len[5], direct[8];

	system("title ̰���ߴ���ս");
	system("mode con cols=80 lines=31");
	SetWindowLongPtrA(
		GetForegroundWindow(),
		GWL_STYLE,
		GetWindowLongPtrA(GetForegroundWindow(), GWL_STYLE)
		& ~WS_SIZEBOX & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX
	);
	cls();
	int tim = 50;		//ֵԽС����ʾ�ٶ�Խ��
	MEM(snake, 0);
	gp.speedowner = -1;
	gp.speednum = 0;
	gp.obliquenum = 0;
	cls();
	draw(m, n);	//���߽�
	CreateSnake(m, n, snake, len, direct); //���ɳ�ʼ��

	gp.step_speed = 0; //���ٵ���ʹ�õĲ�����

	setcolor(15);
	GOTO(n + 1, 68);
	printf("�׷�ʳ�� ");
	GOTO(n + 1, 77);
	printf("%d", len[0] - 3);
	GOTO(0, 0);
	printf("�۷�ʳ�� ");
	GOTO(0, 9);
	printf("%d", len[1] - 3);
	int t = 0;		//�����������
	while (1)
	{
		GOTO(n + 1, 30);
		printf("���س���ͣ");
		while (!_kbhit())
		{
			if (gp.speedowner != -1) gp.step_speed++;
			iterationtime++;
			if (gp.step_speed > 50) gp.speedowner = -1;	//���ٵ������ֻ��ʹ��50��
			Sleep(tim);
			rand_food(snake, len, gp);
			if (gp.speedowner == -1)
			{
				move(t, snake, len, direct, gp, iterationtime);
				move(1-t, snake, len, direct, gp, iterationtime);
			}
			else if (gp.speedowner == t)
			{
				move(t, snake, len, direct, gp, iterationtime);
				move(t, snake, len, direct, gp, iterationtime);
				move(1-t, snake, len, direct, gp, iterationtime);
			}
			else if(gp.speedowner == 1-t){
				move(1 - t, snake, len, direct, gp, iterationtime);
				move(1 - t, snake, len, direct, gp, iterationtime);
				move(t, snake, len, direct, gp, iterationtime);
			}
			if (gp.stage == 2 && gp.wallnum == 0)	//�ڶ��濪���ϰ���
			{
				rand_wall(snake, len, gp);
				rand_props(snake, len, gp);


			}
		}
		char ch = _getch();
		if (ch == 13) stop(n);

	}
	return 0;
}
