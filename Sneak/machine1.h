#include "snake.h"
using namespace std;
const int obs = 10000;
const int unknow = 1000;
bool check1(point snake[5][100], int len[5], int t, GamePanel gp, int direction)
{
	//�����check��������ڴ˴�����ɾȥ����ʾ������
	//if (snake[t][1].y == gp.m && direction == 1) return false;
	//if (snake[t][1].y == 2 && direction == 2) return false;
	//if (snake[t][1].y == gp.m + 2 || snake[t][1].y == 0 || snake[t][1].x == 0 || snake[t][1].x == gp.n + 1)return false;
	if (snake[t][1].y == gp.m && (direction == 1 || direction == 4 || direction==5))return false;
	if (snake[t][1].y == 1 && (direction == 2 || direction == 6 || direction == 7))return false;
	if (snake[t][1].x == 1 && (direction == 3 || direction == 5 || direction == 6))return false;
	if (snake[t][1].x == gp.n && (direction == 0 || direction == 4 || direction == 7))return false;
	else {
		for (int i = 2; i <= len[t]; i++) {//�ж��Ƿ�ײ���Լ�
			if (snake[t][1].x == snake[t][i].x&&snake[t][1].y == snake[t][i].y)return false;
		}
		for (int i = 1; i <= len[1 - t]; i++) { //�ж��Ƿ�ײ����һ����
			if (snake[t][1].x == snake[1 - t][i].x&&snake[t][1].y == snake[1 - t][i].y)return false;
		}
		for (int i = 0; i < gp.wallnum; i++) {//�ж��Ƿ�ײ���ϰ���
			if (snake[t][1].x == gp.wall[i].x&&snake[t][1].y == gp.wall[i].y)return false;
		}
	}
	return true;
}
struct edge_node1       //�߽��
{
	int veradj;          //��һ������
	int cost;
	edge_node1* link;
	edge_node1(int a = 0, int b = 0, edge_node1* c = NULL) :veradj(a), cost(b), link(c) {};
};
struct ver_node1         //������
{
	int head_data;
	edge_node1* adjacent = NULL;      //���ȵıߵ�
};
struct graph1
{
	int numV;
	int numE;
	ver_node1* adjlist = NULL;
	graph1(int a = 0, int b = 0, ver_node1* c = NULL) :numV(a), numE(b), adjlist(c) {};
	void addedge_tolist(int from, int to, int cost);
	int DShortestPath(const int v, int fin[],int index);
};
void graph1::addedge_tolist(int from, int to, int cost)
{
	edge_node1* edge = new edge_node1(to, cost);
	if (adjlist[from].adjacent != NULL)
	{
		edge_node1 * temp = adjlist[from].adjacent;
		while (temp->link != NULL)
		{
			temp = temp->link;
		}
		temp->link = edge;
	}
	else
	{
		adjlist[from].adjacent = edge;
	}
}
int graph1::DShortestPath(const int v, int fin[],int index)
{
	int index_fin = v;
	int u, k;
	int max = 10000;          //���費ͨ����·������
	edge_node1* p;
	int n = numV;
	int *path = new int[n];
	int *dist = new int[n];
	int *s = new int[n];         //��¼�����Ƿ񱻷��ʹ�,0��ʾû�����ʣ�1��ʾ���ʹ�
	for (int i = 0; i < n; i++) {  //��ʼ��
		path[i] = -1; dist[i] = max; s[i] = 0;
	}
	dist[v] = 0; s[v] = 1;
	p = adjlist[v].adjacent;
	u = v;
	for (int j = 0; j < n; j++) {
		//ѭ��(2):�޸�u�ٽӶ����s����ֵ��path����ֵ��dist����ֵ
		while (p != NULL)
		{
			k = p->veradj;
			if (s[k] != 1 && dist[u] + p->cost < dist[k])
			{
				dist[k] = dist[u] + p->cost;
				path[k] = u;
			}
			p = p->link;
		}
		//ѭ��(3)��ȷ�����������ʵĶ���u
		int idist = max;
		for (int i = 0; i < n; i++)
		{
			if (dist[i] > 0 && dist[i] < idist&&s[i] == 0)
			{
				idist = dist[i];
				u = i;
			}
		}
		s[u] = 1;	//����u
		p = adjlist[u].adjacent;	//�޸�u�ı�����ͷָ��
	}
	//int p_fin = fin;
	int p_fin = fin[0];
	for (int i = 1; i < index; i++) {
		if (dist[fin[i]] < dist[p_fin])p_fin = fin[i];
	}
	if (path[p_fin] == -1)return -1;
	while (path[p_fin] != v) {
		p_fin = path[p_fin];
	}
	/*if (dist[index_fin] != 0)cout << dist[index_fin];
	else
		cout << "unreachable";*/
	//for (int i = 0; i < n; i++)cout << path[i] << " ";
	//cout << endl;
	/*for (int i = 1; i < n; i++)
	{
		if (dist[i] != max)cout << dist[i] << " ";
	}*/
	delete[] path;
	delete[] dist;
	//return 0;
	return p_fin;
}

int machine_move1(point snake[5][100], int len[5], int direct[5], int t, GamePanel gp)
{
	//�����check��������ڴ˴�����ɾȥ����ʾ������
	int start_i = snake[t][1].x - 1;
	int start_j = snake[t][1].y - 2;
	int** copyGamePanel = new int*[gp.n];  //��
	for (int i = 0; i < gp.n; i++) {
		copyGamePanel[i] = new int[gp.m];  //��
	}
	for (int i = 0; i < gp.n; i++) {
		for (int j = 0; j < gp.m ; j++) {
			copyGamePanel[i][j] = 1;  //��ʼ��
			if (gp.panel[i][j] == 2) {
				copyGamePanel[i-1][j-2] = obs; //�ϰ���
			}
			if (gp.panel[i][j] == 1) {
				copyGamePanel[i][j] = 0;  //ʳ���
			}
		}
	}
	for (int i = 2; i <= len[t]; i++) {//���Լ�����ϰ���
		copyGamePanel[snake[t][i].x-1][snake[t][i].y-2] = obs;
	}
	for (int i = 1; i <= len[1 - t]; i++) { //�������Ϊ�ϰ���
		copyGamePanel[snake[1 - t][i].x-1][snake[1 - t][i].y-2] = obs;
	}

	int** number = new int*[gp.n];
	for (int i = 0; i < gp.n; i++) {
		number[i] = new int[gp.m];
	}
	int a = 0;
	for (int i = 0; i < gp.n; i++) {
		for (int j = 0; j < gp.m; j += 2) {
			number[i][j] = a++;
		}
	}
	graph1 g;
	g.numV = gp.n * gp.m/2;
	g.adjlist = new ver_node1[gp.n*gp.m/2];
	for (int i = 0; i < gp.m*gp.n/2; i++)
	{
		g.adjlist[i].head_data = i;
	}
	for (int i = 0; i < gp.n; i++) {
		for (int j = 0; j < gp.m; j+=2) {
			if (copyGamePanel[i][j] != obs) {
				if (i + 1 <= gp.n - 1) {
					if (copyGamePanel[i+1][j] == 1) {
						g.addedge_tolist(number[i][j], number[i + 1][j], 1); g.numE++;
					}
				}
				if (i - 1 >= 0) {
					if (copyGamePanel[i - 1][j] == 1) {
						g.addedge_tolist(number[i][j], number[i - 1][j], 1); g.numE++;
					}
				}
				if (j + 2 <= gp.m - 2) {
					if (copyGamePanel[i][j + 2] == 1) {
						g.addedge_tolist(number[i][j], number[i][j + 2], 1); g.numE++;
					}
				}
				if (j - 2 >= 0) {
					if (copyGamePanel[i][j - 2] == 1) {
						g.addedge_tolist(number[i][j], number[i][j - 2], 1); g.numE++;
					}
				}
				if (gp.obliqueowner[t] == 1) { //���ӵ��б�ߵ���
					if (i + 1 <= gp.n - 1 && j + 2 <= gp.m - 2) {//����
						if (!((copyGamePanel[i + 1][j] == obs) && (copyGamePanel[i][j + 2] == obs))) {
							if (copyGamePanel[i + 1][j + 2] != obs) {
								g.addedge_tolist(number[i][j], number[i + 1][j + 2], 1); g.numE++;
								g.addedge_tolist(number[i + 1][j + 2], number[i][j], 1); g.numE++;
							}
						}
					}
					if (i + 1 <= gp.n - 1 && j - 2 >=0) {//����
						if (!((copyGamePanel[i + 1][j] == obs) && (copyGamePanel[i][j - 2] == obs))) {
							if (copyGamePanel[i + 1][j - 2] != obs) {
								g.addedge_tolist(number[i][j], number[i + 1][j - 2], 1); g.numE++;
								g.addedge_tolist(number[i + 1][j - 2], number[i][j], 1); g.numE++;
							}
						}
					}
				}

			}
		}
	}
	//�ҵ����������ʳ��
	int number_of_food[10]; //���ʳ��
	int number_of_techni[3]; //��ŵ���
	int index_food = 0;
	int index_techni = 0;
	//int food_i = 0;
	//int food_j = 0;
	int min = 1000;/*
	int if_have_obliqueprop = 0;
	int if_have_speed = 0;*/
	for (int i = 0; i < gp.n; i++) {
		for (int j = 0; j < gp.m; j += 2) {
			if (gp.panel[i][j] == 1) {
				number_of_food[index_food++] = number[i - 1][j - 2];
				/*if (min > (abs(i - 1 - start_i) + abs(j - 2 - start_j) / 2)) {
					min = (abs(i - 1 - start_i) + abs(j - 2 - start_j) / 2);
					food_i = i - 1; food_j = j - 2;
				}*/
			}
			if (gp.panel[i][j] == 3||gp.panel[i][j]==4) {
				number_of_techni[index_techni++] = number[i - 1][j - 2];
			}
		}
	}
	int fin_number = -1;
	if (index_techni > 0) {
		fin_number = g.DShortestPath(number[start_i][start_j], number_of_techni, index_techni);
	}
	else {
		fin_number = g.DShortestPath(number[start_i][start_j], number_of_food, index_food);
	}
//	int fin_number=g.DShortestPath(number[start_i][start_j], number[food_i][food_j]);
	int direct1 = 3;
	//����4������5������6������7
	if (start_j + 2 < gp.m ) {  //����
		if (number[start_i][start_j + 2] == fin_number) direct1 = 1;
	}
	if (start_j - 2 >= 0) {//����
		if (number[start_i][start_j - 2] == fin_number) direct1 = 2;
	}
	if (start_i - 1 >= 0) { //����
		if (number[start_i-1][start_j] == fin_number)direct1 = 3;
	}
	if (start_i + 1 < gp.n ) { //����
		if (number[start_i + 1][start_j] == fin_number) direct1 = 0;
	}
	if (start_i + 1 < gp.n&&start_j + 2 < gp.m) {//����
		if (number[start_i + 1][start_j + 2] == fin_number)direct1 = 4;
	}
	if (start_i - 1 >= 0 && start_j + 2 < gp.m) {//����
		if (number[start_i - 1][start_j + 2] == fin_number)direct1 = 5;
	}
	if (start_i - 1 >= 0 && start_j - 2 >= 0) {
		if (number[start_i - 1][start_j - 2] == fin_number)direct1 = 6;
	}
	if (start_i + 1 < gp.n&&start_j - 2 >= 0) {
		if (number[start_i + 1][start_j - 2] == fin_number)direct1 = 7;
	}


	if (fin_number == -1) {  //���û�����·�����Ҳ���ͨ��ʳ���·��
		if (gp.obliqueowner[t] == 1) {
			if (start_i + 1 < gp.n&&start_j + 2 < gp.m) {//����
				if (number[start_i + 1][start_j + 2] !=obs)direct1 = 4;
			}
			if (start_i - 1 >= 0 && start_j + 2 < gp.m) {//����
				if (number[start_i - 1][start_j + 2] != obs)direct1 = 5;
			}
			if (start_i - 1 >= 0 && start_j - 2 >= 0) {
				if (number[start_i - 1][start_j - 2] != obs)direct1 = 6;
			}
			if (start_i + 1 < gp.n&&start_j - 2 >= 0) {
				if (number[start_i + 1][start_j - 2] != obs)direct1 = 7;
			}
		}
		if (start_i + 1 < gp.n) {
			if (copyGamePanel[start_i + 1][start_j] != obs)direct1 = 0;
		}
		if (start_i - 1 >= 0) {
			if (copyGamePanel[start_i - 1][start_j] != obs)direct1 = 3;
		}
		if (start_j - 2 >= 0) {
			if (copyGamePanel[start_i][start_j - 2] != obs)direct1 = 2;
		}
		if (start_j + 2 < gp.m) {
			if (copyGamePanel[start_i][start_j + 2] != obs)direct1 = 1;
		}
	}
	for (int i = 0; i < gp.n ; i++){
		delete[] copyGamePanel[i];
	}
	delete[] copyGamePanel;
	//if (t == 0) return 2;
	//else return 1;
		return direct1;
}

