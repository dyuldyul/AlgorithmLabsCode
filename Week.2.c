#pragma warning (disable:4996)

#if 0
#include <stdio.h>
int main(void)
{
	return 0;
}
#endif

//DFS: �⺻: ���ϱ�(basic), å����, ���� Ż��
//����: �⺻: �ǹ������(basic), �ֻ���1, ���ʽ�
//�Һ�, ����: �������(basic)

/*
[��������]
FF:
�ѷ�(
������ȣ ���̱� (��ǥ)
���̷��� (����)

BFS
����
�ڿܼ� ���ذ���


DFS
����
- ��� ���
- R�� �̱� (�ߺ�����)
����
- ��� ��� (��ġ��ȯ ǥ��)
- R���̱�
����/�Һ� (ũ��������Ʈ��)
- �� ����
- �� �������� �ʴ´�
�׿�
- ��������
- ���ڸ��

*�ܹ���/����� �׷����� �������
*���� �ɰ��� / ���� reverse
*���ϰ��� ���� (���ʽ�, �ع���, �ǹ������)
������� - ����ǥ�� ��� - ���ʽ�, �׷���, �ǹ������
������� - ����Ȱ� ���󰡱� �뵵 - �ع���, FF
*debugging: printList Ȱ���ϱ�

DFS������ ��������:
- �ߺ� ���� ���
- int�� �����ϱ� ��� if(DFS() == 1) return 1;
- ����ġ�� (�ּҰ�, �ִ밪, �Ȱ��� ��)

�迭 �̿��� ��:
- ����ġ��
- �ߺ�����
- Lookup Table
- ����
*/


//////////////////////////////������������////////////////////////////////////////////

//�丶��
#if 0

#include <stdio.h>
#define MAX (100+10)
int a[MAX][MAX][MAX];
int tcnt; //�丶�䰡 �� �� �ִ� ĭ�� ��
int M, N, H;

struct st {
	int x, y, z;
};
struct st Queue[MAX*MAX*MAX];
int wp, rp;
void In_Queue(int z, int y, int x)
{
	Queue[wp].z = z;
	Queue[wp].y = y;
	Queue[wp].x = x;
	wp++;
}
struct st Out_Queue(void)
{
	return Queue[rp++];
}



void printAry(void)
{
	int i, j, k;
	for (k = 1; k <= H; k++)
	{
		for (i = 1; i <= N; i++)
		{
			for (j = 1; j <= M; j++)
			{
				printf("%d", a[k][i][j]);
			}
			printf("\n");
		}
	}
	printf("\n");
}
void input(void)
{
	int i, j, k;
	scanf("%d %d %d", &M, &N, &H);

	for (k = 1; k <= H; k++)
	{
		for (i = 1; i <= N; i++)
		{
			for (j = 1; j <= M; j++)
			{
				scanf("%d", &a[k][i][j]);
				if (a[k][i][j] == 0) tcnt++;
			}
		}
	}

}

int dx[] = { 0, 0, 0, 0, -1, 1 };
int dy[] = { 0, 0, -1, 1, 0, 0 };
int dz[] = { -1, 1, 0, 0, 0, 0 };

int BFS(int sz, int sy, int sx)
{
	int i, j, k, ny, nx, nz;
	struct st out = { 0 };

	wp = rp = 0;

	for (k = 1; k <= H; k++)
	{
		for (i = 1; i <= N; i++)
		{
			for (j = 1; j <= M; j++)
			{
				if (a[k][i][j] == 1)
				{
					In_Queue(k, i, j);
				}
			}
		}
	}

	//printf("wp=%d, rp = %d\n", wp, rp);

	while (wp > rp)
	{
		out = Out_Queue();

		for (i = 0; i < 6; i++)
		{
			nz = out.z + dz[i];
			ny = out.y + dy[i];
			nx = out.x + dx[i];

			if (nz < 1 || ny < 1 || nx < 1 || nz > H || ny > N || nx > M) continue;
			//printf("nz, ny, nx = %d %d %d", nz, ny, nx);
			if (a[nz][ny][nx] == 0)
			{

				a[nz][ny][nx] = a[out.z][out.y][out.x] + 1;
				tcnt--;
				In_Queue(nz, ny, nx);
			}
		}
	}

	//printf("out = %d", a[out.z][out.y][out.x]);

	return (tcnt > 0) ? (-1) : (a[out.z][out.y][out.x] - 1);

}
int main(void)
{
	int ret, i, j, k;
	input();

	if (tcnt == 0)
	{
		printf("0");
		return 0;
	}

	ret = BFS(1, 1, 1);

	if (ret == -1) printf("-1");
	else printf("%d", ret);
	return 0;
}
#endif

//�ܲ���
#if 0
#include <stdio.h>
#define MAX (100+10)
char a[MAX][MAX]; //����
int C[MAX][MAX]; //int�� ���� ���� - �Ϲݲܲ���
int N;
int W[MAX][MAX]; //�����ܲ���

void printAry(void)
{
	int i, j;
	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			printf("%d", C[i][j]);
		}
		printf("\n");
	}
}
//
//void copyAry(void)
//{
//	int i, j;
//	for (i = 1; i <= N; i++)
//	{
//		for (j = 1; j <= N; j++)
//		{
//			C[i][j] = A[i][j];
//		}
//	}
//}

void input(void)
{
	int i, j;
	scanf("%d", &N);

	for (i = 1; i <= N; i++)
	{
		scanf("%s", &a[i][1]);
	}

	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			if (a[i][j] == 'R')
			{
				C[i][j] = 1;
				W[i][j] = 1;
			}
			else if (a[i][j] == 'G')
			{
				C[i][j] = 2;
				W[i][j] = 1;
			}
			else if (a[i][j] == 'B')
			{
				C[i][j] = 3;
				W[i][j] = 3;
			}
		}
	}

	//printAry();
}

struct st {
	int x, y;
};
struct st Queue[MAX*MAX];
int wp, rp;
void In_Queue(int y, int x)
{
	Queue[wp].y = y;
	Queue[wp].x = x;
	wp++;
}
struct st Out_Queue(void)
{
	return Queue[rp++];
}

int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };

int cnt = 0;
int BFS(int sy, int sx, int color, int status)
{//���� ã�� �� ���� 0: ã�� ����, 1: ���� ã�� ����
	int i, ny, nx;
	struct st out = { 0 };
	int found = 0;


	if (status == 0)
	{
		//printf("sy, sx = %d, %d\n", sy, sx);
		wp = rp = 0;
		In_Queue(sy, sx);
		C[sy][sx] = 0;
		found++;

		while (wp > rp)
		{
			out = Out_Queue();

			for (i = 0; i < 4; i++)
			{
				ny = out.y + dy[i];
				nx = out.x + dx[i];

				if (ny < 1 || nx < 1 || ny > N || nx > N) continue;

				if (C[ny][nx] == color)
				{
					C[ny][nx] = 0;//�湮ǥ��
					In_Queue(ny, nx);
					found++;
				}
			}
		}
	}

	else if (status == 1)
	{
		wp = rp = 0;
		In_Queue(sy, sx);
		W[sy][sx] = 0;
		found++;
		while (wp > rp)
		{
			out = Out_Queue();
			for (i = 0; i < 4; i++)
			{
				ny = out.y + dy[i];
				nx = out.x + dx[i];

				if (ny < 1 || nx < 1 || ny > N || nx > N) continue;

				if (W[ny][nx] == color)
				{
					W[ny][nx] = 0;//�湮ǥ��
					In_Queue(ny, nx);
					found++;
				}
			}
		}

	}

	/*if (status == 0)
	{
	printf("%d: found = %d, (x,y)=(%d,%d), color=%d\n", ++cnt, found, sx, sy, color);
	printAry();
	}*/

	return (found > 0) ? (1) : (0);
}

/*printf("ret=%d, cb=%d\n", ret, cb);
printf("R: %d, G: %d, B: %d\n", visit[0], visit[1], visit[2]);*/
int main(void)
{
	int i, j, cb = 0, nor = 0; //cb: ���ϻ��� �ܲ�, cn: �Ϲ� �ܲ�
	input();
	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			if (C[i][j] == 1)
			{//R
				nor += BFS(i, j, 1, 0);
			}
			else if (C[i][j] == 2)
			{//G
				nor += BFS(i, j, 2, 0);
			}
			else if (C[i][j] == 3)
			{//B
				nor += BFS(i, j, 3, 0);
			}
		}
	}


	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			if (W[i][j] == 1)
			{
				cb += BFS(i, j, 1, 1);
			}
			else if (W[i][j] == 3)
			{
				cb += BFS(i, j, 3, 1);
			}
		}
	}

	printf("%d %d\n", nor, cb);
	return 0;
}
#endif


////////////////////////////////Day 10////////////////////////////////////////////

//[] �м�����
#if 0
#include <stdio.h>
#define MAX (160*100000+5)
int a[MAX][2];
int N;

void getAry(void)
{
	int pos = 0;
	int i, j;

	for (i = 2; i <= N; i++)
	{
		for (j = i + 1; j <= N - 1; j++)
		{
			pos = (j * 100000) / i;

			if (a[pos][0] == 0 && a[pos][1] == 0)
			{
				a[pos][0] = i;
				a[pos][1] = j;
			}
		}
	}
}

void print(void)
{
	int i, j;
	printf("0/1\n");
	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N - 1; j++)
		{
			printf("%d/%d\n", a[])
		}
	}
	printf("1/1\n");
}

int main(void)
{
	scanf("%d", &N);
	getAry();
	print();
	return 0;
}
#endif


////////////////////////////////Day 9////////////////////////////////////////////

//[] �ʺ�켱Ž��
#if 0
#include <stdio.h>
#define MAX (200+10)
//#define MAXV (100+10)
//#define MAXE (200+10)
int V, E;
int Queue[MAX];
int visit[MAX];
int s[MAX];
int e[MAX];
int wp, rp;

void input(void)
{
	//int i, a, b;
	int i;
	scanf("%d %d", &V, &E);
	for (i = 1; i <= E; i++)
	{
		/*scanf("%d %d", &a, &b);
		s[i] = a;
		e[i] = b;*/
		scanf("%d %d", &s[i], &e[i]);
	}
}

void In_Queue(int data)
{
	Queue[wp++] = data;
}

int Out_Queue(void)
{
	return Queue[rp++];
}

void printQueue(void)
{
	int i;
	for (i = 0; i < V; i++)
	{
		printf("%d ", Queue[i]);
	}
	printf("\n");
}

void BFS(int start)
{
	int i, out = 0;

	wp = rp = 0;
	In_Queue(start);
	visit[start] = 1;

	while (wp > rp)
	{
		out = Out_Queue();
		//printQueue();
		//printf("out = %d\n", out);
		for (i = 1; i <= E; i++)
		{
			//out�Ѱſ� �����鼭 edge�� �ѹ��� �湮���� �ʾ����� 
			if (s[i] == out && visit[e[i]] == 0)
			{
				visit[e[i]] = 1;
				In_Queue(e[i]);

			}
			if (e[i] == out && visit[s[i]] == 0)
			{
				visit[s[i]] = 1;
				In_Queue(s[i]);
			}
		}
	}
}

void output(void)
{
	int i;
	for (i = 0; i < V; i++)
	{
		printf("%d ", Queue[i]);
	}
	/*for (i = 0; i < wp; i++)
	{
	printf("%d ", Queue[i]);
	}*/
}
int main(void)
{
	input();
	BFS(1);
	output();
	return 0;
}
#endif

//[j] [sol] ��������ȯ
#if 0
#include <stdio.h>
#define MAX (500+10)
int N; //������ ���� 
int V; //������ ������ ��ȣ vertex
int a[MAX][MAX];

int visit[MAX]; //����� ������ ���� (���� ����)
int Queue[MAX];
int wp, rp;

void In_Queue(int data)
{
	Queue[wp++] = data;
}
int Out_Queue(void)
{
	return Queue[rp++];
}

void printAry(void)
{
	int i, j;

	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			printf("%2d ", a[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void printVisit(void)
{
	int i;

	for (i = 1; i <= V; i++)
	{
		printf("%2d ", visit[i]);
	}
	printf("\n");
}
void input(void)
{
	int i, y, x;
	scanf("%d", &N);
	V = 0;
	for (i = 1; i <= N; i++)
	{
		scanf("%d %d", &y, &x);
		a[y][x] = 1;
		if (V < y) V = y;
		if (V < x) V = x;
	}
	//printAry();
}

void initVisit(void)
{
	int i;

	for (i = 1; i <= V; i++)
	{
		visit[i] = 0;
	}
}

int BFS(int start)
{
	int i, out;
	int sum = 0;
	wp = rp = 0;
	In_Queue(start);
	visit[start] = 1;

	while (wp > rp)
	{
		out = Out_Queue();
		for (i = 1; i <= V; i++)
		{//������ĸ�ŭ ����
			//����� �����ε� ���� �湮���� ���� 
			if (a[out][i] == 1 && visit[i] == 0)
			{
				visit[i] = visit[out] + 1;
				In_Queue(i);
			}

		}
	}

	for (i = 1; i <= V; i++)
	{
		sum += visit[i];
	}
	return (sum - V);
}
int main(void)
{
	int i;
	int tot = 0;

	input();

	for (i = 1; i <= V; i++)
	{
		tot += BFS(i);
		printVisit();
		initVisit();
	}
	printf("%.3f", (double)tot / (V*(V - 1)));
	return 0;
}
#endif

//[re]
#if 0
#include <stdio.h>
#define MAX (500+10)
int a[MAX][MAX];
int V;
int N;
int visit[MAX];
int Queue[MAX];
int wp, rp;
//���ӵ� �������� �ƴҶ� ����
int use[MAX];
int U;

void In_Queue(int data)
{
	Queue[wp++] = data;
}
int Out_Queue(void)
{
	return Queue[rp++];
}

void input(void)
{
	int i, x, y;
	scanf("%d", &N);
	for (i = 1; i <= N; i++)
	{
		scanf("%d %d", &y, &x);
		a[y][x] = 1;

		use[y] = 1; use[x] = 1;
		if (y > V) V = y;
		if (x > V) V = x;

		//U = 0;
		//for (i = 1; i <= V; i++)
		//{
		//	if (use[i] = 1)
		//	{

		//	}
		//}

	}
}

void printVisit(void)
{
	int i;

	for (i = 1; i <= V; i++)
	{
		printf("%2d ", visit[i]);
	}
	printf("\n");
}

int BFS(int start)
{
	int i, out = 0;
	int sum = 0;
	wp = rp = 0;
	visit[start] = 1;
	In_Queue(start);

	while (wp > rp)
	{
		out = Out_Queue();
		for (i = 1; i <= V; i++)
		{
			if (a[out][i] == 1 && visit[i] == 0)
			{//�����̸鼭 �ѹ��� �湮���� ������ 
				visit[i] = visit[out] + 1;
				In_Queue(i);
			}
		}
	}

	for (i = 1; i <= V; i++)
	{
		sum += visit[i];
	}

	return (sum - V); //������ ������ŭ �ߺ� �������ϱ� ����

}

void init_visit(void)
{
	int i;
	for (i = 1; i <= V; i++)
	{
		visit[i] = 0;
	}
}
int main(void)
{
	int i, tot = 0;
	input();
	for (i = 1; i <= V; i++)
	{
		//if(use[i] == 1)

		tot += BFS(i);
		printVisit();
		init_visit();
	}

	//printf("%2d\n", tot);

	//U*(U-1)
	//printf("%.3f", (double)tot / (V*(V - 1)));
	return 0;
}
#endif

//[j] [my] ��������ȯ
#if 0
#include <stdio.h>
#define MAX (500+5)
#define IMSIMAX (499)
int a[MAX][MAX];
int N, ARYN; //n: ���� ã��� for loop��
int list[MAX]; //�� depth���� �̵��ϴ� Ƚ�� list[1]���� ���, 
float sol; // ��ü ������ �̵� ��� Ƚ�� (�Ҽ� 3�ڸ�)
int lnum;
void input(void)
{
	int i, j, start, end, t;
	scanf("%d", &N);
	for (i = 1; i <= N; i++)
	{
		scanf("%d %d", &start, &end);
		a[start][end] = 1; //�������� �̾��ش�.
		t = (start < end) ? (end) : (start);
		ARYN = (t > ARYN) ? t : ARYN;
	}

	//�������� �� �̾��� ���� �ִ밪�� �ʱ�ȭ�Ѵ�
	for (i = 1; i <= ARYN; i++)
	{
		for (j = 1; j <= ARYN; j++)
		{
			if (!a[i][j])a[i][j] = IMSIMAX;
		}
	}
}

void find(void)
{//�÷��̵� �˰���
	int i, j, k;
	for (k = 1; k <= ARYN; k++)
	{
		for (i = 1; i <= ARYN; i++)
		{
			for (j = 1; j <= ARYN; j++)
			{
				if (a[i][j] > a[i][k] + a[k][j]) a[i][j] = a[i][k] + a[k][j];
			}
		}
	}

	for (i = 1; i <= ARYN; i++)
	{
		for (j = 1; j <= ARYN; j++)
		{
			if (i != j) sol += a[i][j];
		}
	}
}

int main(void)
{
	input();
	find();
	sol /= (float)(ARYN * (ARYN - 1));
	printf("%.3f\n", sol);
	return 0;
}
#endif

//[] [sol]�������� ����
#if 0
#include <stdio.h>
#define MAX (5+1)

int a[MAX][MAX];
int K; //������ ����
int N; //
int sol;
int cnt;

void input(void)
{
	int i;
	int x, y;
	scanf("%d", &K);
	for (i = 1; i <= K; i++)
	{
		scanf("%d %d", &y, &x);
		a[y][x] = 99; // ���� ��ġ ǥ��
	}
	N = 25 - K;
}

void printAry(void)
{
	int i, j;
	printf("============%d\n", ++cnt);

	for (i = 1; i < MAX; i++)
	{
		for (j = 1; j < MAX; j++)
		{
			printf("%2d ", a[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };

void DFS(int L, int sy, int sx)
{
	int i, ny, nx;

	if (L > N)
	{
		if (sy == 5 && sx == 5) sol++;
		printAry();
		return;
	}
	//if (sy == 5 && sx == 5)
	//{//������ �� �� �ɾ��µ� �������� �� ���
	//	return;
	//}

	for (i = 0; i < 4; i++)
	{
		ny = sy + dy[i];
		nx = sx + dx[i];

		if (ny < 1 || nx < 1 || ny > 5 || nx > 5) continue;

		if (a[ny][nx] == 0)
		{
			a[ny][nx] = L+1; //�湮�ߴٴ� ǥ�ð� �ƴ϶�, depth ǥ��
			DFS(L + 1, ny, nx);
			a[ny][nx] = 0;
		}
	}
}

int main(void)
{
	input();
	//������ �ɰ� �����Ѵ�. 
	a[1][1] = 1; //�������� ������ �ɴ´�. 
	DFS(2, 1, 1);//DFS(1, 1, 1); 
	printf("%d", sol);
	return 0;
}
#endif

//[] [my] ��� ������(BASIC)
#if 0
#include <stdio.h>
#define MAX (50+5)
int stair[MAX];
int sum[MAX][2];
int N;
int sol;

void input(void)
{
	int i;
	scanf("%d", &N);
	for (i = 1; i <= N; i++) scanf("%d", &stair[i]);
}

int max(int a, int b)
{
	return (a>b) ? (a) : (b);
}
void DP(void)
{
	int i;
	sum[1][0] = sum[1][1] = stair[1];

	for (i = 2; i <= N; i++)
	{
		sum[i][0] = sum[i - 1][1] + stair[i];
		sum[i][1] = max(sum[i - 2][0], sum[i - 2][1]) + stair[i];
	}

	//for (int i = 1; i <= N; i++)
	//{
	//	for (int j = 1; j <= N; j++)
	//	{
	//		printf("%2d ", sum[i][j]);
	//	}
	//	printf("\n");
	//}
	sol = max(sum[N][0], sum[N][1]);
}
int main(void)
{
	input();
	sol = 0;
	DP();
	printf("%d", sol);
	return 0;
}
#endif

////////////////////////////////Day 8////////////////////////////////////////////

//�׷���ĥ�ϱ�, �ְ��Ǽ����� ã�ƶ�
//��������, �ʺ�켱Ž��
//��������, ���幮, �������� ����, ��ܿ����� - DFS

//��ܿ�����
//����: http://blog.naver.com/PostView.nhn?blogId=occidere&logNo=220788947949

#if 0
#include <stdio.h>
#define MAX (50+5)
int stair[MAX];
int sum[MAX][2];
int N; 
int sol;

void input(void)
{
	int i;
	scanf("%d", &N);
	for (i = 1; i <= N; i++)
	{
		scanf("%d", &stair[i]);
	}
}

int max(int a, int b)
{
	return (a>b) ? (a): (b);
}
void DP(void)
{
	int i;
	sum[1][0] = sum[1][1] = stair[1];
	
	for (i = 2; i <= N; i++)
	{
		sum[i][0] = sum[i - 1][1] + stair[i];
		sum[i][1] = max(sum[i-2][0], sum[i-2][1]) + stair[i]; 
	}

	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= 2; j++)
		{
			printf("%2d ", sum[i][j]);
		}
		printf("\n");
	}
	sol = max(sum[N][0],sum[N][1]);
}
int main(void)
{
	input();
	sol = 0;
	DP();
	printf("%d", sol);
	return 0;
}
#endif

//[j] [my] ��������ȯ
#if 0
#include <stdio.h>
#define MAX (500+5)
#define IMSIMAX (499)
int a[MAX][MAX];
int N, ARYN; //n: ���� ã��� for loop��
int list[MAX]; //�� depth���� �̵��ϴ� Ƚ�� list[1]���� ���, 
float sol; // ��ü ������ �̵� ��� Ƚ�� (�Ҽ� 3�ڸ�)
int lnum;
void input(void)
{
	int i, j, start, end, t;
	scanf("%d", &N);
	for (i = 1; i <= N; i++)
	{
		scanf("%d %d", &start, &end);
		a[start][end] = 1; //�������� �̾��ش�.
		t = (start < end) ? (end) : (start);
		ARYN = (t > ARYN) ? t : ARYN;
	}

	//�������� �� �̾��� ���� �ִ밪�� �ʱ�ȭ�Ѵ�
	for (i = 1; i <= ARYN; i++)
	{
		for (j = 1; j <= ARYN; j++)
		{
			if (!a[i][j])a[i][j] = IMSIMAX;
		}
	}
}

void find(void)
{//�÷��̵� �˰���
	int i, j, k;
	for (k = 1; k <= ARYN; k++)
	{
		for (i = 1; i <= ARYN; i++)
		{
			for (j = 1; j <= ARYN; j++)
			{
				if (a[i][j] > a[i][k] + a[k][j]) a[i][j] = a[i][k] + a[k][j];
				//������̸� a[j][i] = a[i][j]; �� �߰��ϸ� �ȴ�
			}
		}
	}

	for (i = 1; i <= ARYN; i++)
	{
		for (j = 1; j <= ARYN; j++)
		{
			if (i != j) sol += a[i][j];
		}
	}
}

int main(void)
{
	input();
	find();
	sol /= (float)(ARYN * (ARYN-1));
	printf("%.3f\n", sol);
	return 0;
}
#endif

//[] [my] ���� ����
#if 0
#include <stdio.h>
#define MAX (100+10)
int N;
int map[MAX][MAX]; 
//int safe[MAX][MAX];
int sol; //������ ������ �ִ� ���� ->0���� �ʱ�ȭ�ؼ� �ִ밳���� ������ �����Ѵ�
int visit[MAX][MAX];  // copy

void input(void)
{
	int i, j;
	scanf("%d", &N);
	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			scanf("%d", &map[i][j]);
		}
	}
}

void copy(int rain)
{
	int i, j;
	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			visit[i][j] = (map[i][j] <= rain) ? (0) : (1);
		}
	}
}

struct st {
	int y, x;
};
struct st Queue[MAX*MAX];
int wp, rp;

void In_Queue(int y, int x)
{
	Queue[wp].y = y;
	Queue[wp].x = x;
	wp++;
}
struct st Out_Queue(void)
{
	return Queue[rp++];
}

//������: while(wp>rp)
//������: 
//�湮ǥ��: if(visit[][] > 0  && visit[][] <=rain ) visit[][] = 0;

//������ ���� �޾�. ħ���Ǹ� 0���� �ؼ� �湮ǥ�õ� �� ��
//for���� ���鼭 ���⼭ 

int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };

void BFS(int sy, int sx)
{
	int i, ny, nx;
	struct st out = { 0 };

	wp = rp = 0;
	In_Queue(sy, sx);
	visit[sy][sx] = 0;

	while (wp > rp)
	{
		out = Out_Queue();
		for (i = 0; i < 4; i++)
		{
			ny = out.y + dy[i];
			nx = out.x + dx[i];
			if (ny<1 || nx<1 || ny>N || nx>N) continue;

			if (visit[ny][nx] == 1)
			{
				visit[ny][nx] = 0;
				In_Queue(ny, nx);
			}
		}
	}
	sol++;
}

void Do_BFS(void)
{
	int i, j;
	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			if (visit[i][j] == 1) BFS(i, j);
		}
	}
}

int main(void)
{
	int i, max = 0;
	input();

	for (i = 1; i < 100; i++)
	{
		sol = 0;
		copy(i);
		Do_BFS();
		if (sol > max) max = sol;
	}
	printf("%d", max);
	return 0;
}

#endif

//[]��������(BASIC)
#if 0
#include <stdio.h>
#define MAX (12+10)
int a[MAX]; //���� ���Ը� ����
int N; //���� ���� 
int gCnt; //Ȯ���ؾߵǴ� ������ ���� 
int G; // Ȯ���ؾߵǴ� ������ ����

int sol;
int list[MAX]; // 0: �� �ø���. 1: ���ʿ� �ø���, 2: �����ʿ� �ø���
int cnt;

void printList(int L, int lS, int rS)
{
	int i;
	printf("%2d (%2d:%2d) : ", ++cnt, lS, rS);
	for (i = 1; i < L; i++)
	{
		printf("%2d ", list[i]);
	}
	printf("\n");
}

void input(void)
{
	int i;
	scanf("%d", &N);
	for (i = 1; i <= N; i++)
	{
		scanf("%d", &a[i]);
	}
}


int DFS(int L, int lS, int rS)
{
	printList(L, lS, rS);
	//��������
	if (lS == rS) return 1;

	//��������
	if (L > N) return 0;

	//���ʿ� �߸� �ø��� 
	list[L] = 1;
	if (DFS(L + 1, lS + a[L], rS) == 1)
	{
		return 1;
	}
	//�����ʿ� �߸� �ø���
	list[L] = 2;
	if (DFS(L + 1, lS, rS + a[L]) == 1)
	{
		return 1;
	}
	//�߸� �ø��� �ʴ´�
	list[L] = 0;
	if (DFS(L + 1, lS, rS) == 1)
	{
		return 1;
	}

	return 0;
}

int main(void)
{
	int i;
	char msg[] = { 'N', 'Y' };

	input();
	scanf("%d", &gCnt);
	//for (i = 1; i <= gCnt; i++)
	{
		scanf("%d", &G); //������ ���� Ȯ���ض�
		sol = DFS(1, G, 0); //������ ���ʿ� �൵ �ǰ� �����ʿ� �൵ �ȴ�
		printf("%c ", msg[sol]);
	}
	return 0;
}
#endif


//*******170513 ����, ��, N�� �� R���� �̴�, ���ٸ� ����


//[sol] 
/* [teacher]
void DFS(int L, int start)
{
int i, prev = 0;
if (L > M)
{
printList(L);
sol++;
return;
}

for (i = start, i <= N - M + L; i++)
{
if (prev != a[i])
{
prev = a[i];
list[L] = a[i];
DFS(L + 1, i + 1);
list[L] = 0;
}
}
}

int main(void)
{

}

*/

//minhee sunbae
#if 0 
#include <stdio.h>
#define MAX (20)
int N, M;
int a[MAX];
int sol;
int list[MAX];
int prev[MAX];
int cnt;
//int c[MAX];

void printList(int L) 
{
	int i;
	printf("%2d : ", ++cnt);
	for (i = 1; i < L; i++) {
		printf("%d ", list[i]);
	}
	printf("\n");
}

void sort(void) {
	int i, j, t;

	for (i = 1; i <= N - 1; i++){
		for (j = i + 1; j <= N; j++){
			if (a[j] < a[i]) {
			t = a[i]; a[i] = a[j]; a[j] = t;
			}
		}
	}
//for (i = 1; i <= N; i++) printf("%d ", a[i]);
//printf("\n");

}

void input(void) {
	int i;
	scanf("%d %d", &N, &M);
	for (i = 1; i <= N; i++) {
	scanf("%d ", &a[i]);
	}
}
int Check(void) {
	int i;
	for (i = 1; i <= M; i++) {
		if (prev[i] != list[i]) return 0;
		}
	return 1;
}
void DFS(int L, int s) {
	int i, prev = 0;
	//int prev[] = { 0, };
	if (L > M){
		sol++;
		//printList(L);
		return;
	}
	for (i = s; i <= (N - M + L); i++) {    //N ���� M ���� �̴� ��� ; N-M+L
		if (prev != a[i]) {
			prev = a[i];
			list[L] = a[i];
			DFS(L + 1, i + 1);
			list[L] = 0;
		}
	}
}
int main(void) {
	int T, tc;
	int i, j;

	scanf("%d", &T);
	for (tc = 1; tc <= T; tc++){
		input();
		sort();
		//check();
		sol = 0;
		//for (i = 1; i < N; i++) {
		DFS(1, 1);
		//}
		printf("#%d %d\n", tc, sol);
	}
	return 0;
}
#endif



//*******



//*******[] �ְ��� ������ ���϶�

//getValue()�� ���Ҷ�
#if 0
#include <stdio.h>
#define MAX (10+5)
int N;
int a[] = { 1, 2, 4, 8, 16, 32, 64, 128 };
int sol;
int W[MAX]; //4�� ���� ���� ��ġ
int V[MAX]; //5�� �̻� ���� ��ġ
int A; //�� �ϳ��� �߰���ġ

int list[MAX];
int cnt;
int best[MAX]; //�ְ��� ������ ��� �迭�̸�, �ְ��� ���°� ���ŵǱ� ���� 

void printList(int L)
{
	int i;
	printf("%2d : ", ++cnt);
	for (i = 0; i < L; i++)
	{
		printf("%2d ", list[i]);
	}
	printf("\n");
}

int getValue(int L)
{
	int i;
	int value = 0; //�������� �ʱ�ȭ
	for (i = 0; i < L; i++)//����� �������� ����
	{
		//���� 2�� ������ ���� ��ġ �հ�
		value += list[i] * ((list[i]<5) ? (W[i]) : (V[i])); //���� ������ ������ ��ü�� ��ȣ �ʿ�!
		//���� �� * ���� ��ġ

		//�� �ϳ��� �߰���ġ 
		value += (list[i] * A);
	}
	return value;
}
void DFS(int L, int R)
{
	int i;
	if (R == 0)
	{
		//printList(L);
		int value = getValue(L); //R==0�϶��� ��� �Ἥ �����°� ����. �ۿ��� �����ϴ°ź���
		if (sol < value)
		{
			sol = value;
			for (i = 0; i <= 6; i++)
			{
				best[i] = list[i];
			}
		}

		return;
	}
	if (a[L] > R || a[L] > N)
	{
		//0 0 0 �� ���� ���Ǵ� ��쿡�� ���ᰡ �Ǿ�� �ϹǷ� 
		//6 0 0 �� ���� ��쵵 ����
		//printList(L);
		return;
	}
	if (a[L] > N) //0 0 0 �� ���� ���Ǵ� ��쿡�� ���ᰡ �Ǿ�� �ϹǷ� 
	{
		//printList(L);
		return;
	}

	for (i = 0; i*a[L] <= R; i++)
	{
		list[L] = i;
		DFS(L + 1, R - (i*a[L]));
		list[L] = 0;
	}
}

void input(void)
{
	int i;
	scanf("%d", &N);
	for (i = 0; i <= 6; i++)
	{
		scanf("%d", &W[i]);
	}
	for (i = 0; i <= 6; i++)
	{
		scanf("%d", &V[i]);
	}
	scanf("%d", &A);
}

void output(void)
{
	int i;
	printf("%d\n", sol);
	for (i = 0; i <= 6; i++)
	{
		printf("%d ", best[i]);
	}
	printf("\n");
}

int main(void)
{
	//int T, tc;
	//scanf("%d", &T);
	//for (tc = 1; tc <= T; tc++)
	{
		input();
		sol = 0; //min������ �ʱ�ȭ
		DFS(0, N);
		output();
	}
	return 0;
}
#endif

//S�� �μ��� �ѱ涧
#if 0
#include <stdio.h>
#define MAX (10+5)
int N;
int a[] = { 1, 2, 4, 8, 16, 32, 64, 128 };
int sol;
int W[MAX]; //4�� ���� ���� ��ġ
int V[MAX]; //5�� �̻� ���� ��ġ
int A; //�� �ϳ��� �߰���ġ
int S;
int list[MAX];
int cnt;
int best[MAX]; //�ְ��� ������ ��� �迭�̸�, �ְ��� ���°� ���ŵǱ� ���� 

void printList(int L)
{
	int i;
	printf("%2d : ", ++cnt);
	for (i = 0; i < L; i++)
	{
		printf("%2d ", list[i]);
	}
	printf("\n");
}

void DFS(int L, int R, int S)
{
	int i;
	if (R == 0)
	{
		//printList(L);
		if (sol < S)
		{
			sol = S;
			for (i = 0; i <= 6; i++)
			{
				best[i] = list[i];
			}
		}

		return;
	}
	if (a[L] > R || a[L] > N)
	{
		//0 0 0 �� ���� ���Ǵ� ��쿡�� ���ᰡ �Ǿ�� �ϹǷ� 
		//6 0 0 �� ���� ��쵵 ����
		//printList(L);
		return;
	}
	if (a[L] > N) //0 0 0 �� ���� ���Ǵ� ��쿡�� ���ᰡ �Ǿ�� �ϹǷ� 
	{
		//printList(L);
		return;
	}

	for (i = 0; i*a[L] <= R; i++)
	{
		list[L] = i;
		DFS(L + 1, R - (i*a[L]), S + i*((i<5) ? (W[L]) : (V[L])) + (i*A));
		list[L] = 0;
	}
}

void input(void)
{
	int i;
	scanf("%d", &N);
	for (i = 0; i <= 6; i++)
	{
		scanf("%d", &W[i]);
	}
	for (i = 0; i <= 6; i++)
	{
		scanf("%d", &V[i]);
	}
	scanf("%d", &A);
}

void output(void)
{
	int i;
	printf("%d\n", sol);
	for (i = 0; i <= 6; i++)
	{
		printf("%d ", best[i]);
	}
	printf("\n");
}

int main(void)
{
	//int T, tc;
	//scanf("%d", &T);
	//for (tc = 1; tc <= T; tc++)
	{
		input();
		sol = 0; //min������ �ʱ�ȭ
		DFS(0, N, S);
		output();
	}
	return 0;
}
#endif

//*******




//[f] �׷���ĥ�ϱ�
#if 0
#include <stdio.h>

#define MAX (12+5)
int a[MAX][MAX];
int N, M;
int list[MAX];
int cnt;
int sol;

void printList(int L)
{
	int i;
	printf("%2d : ", ++cnt);
	for (i = 1; i <= N; i++)
	{
		printf("%2d ", list[i]);
	}
	printf("\n");
}
void input(void)
{
	int i, j;
	scanf("%d %d", &N, &M);
	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= i; j++)
		{
			scanf("%d", &a[i][j]);
			//a[j][i] = a[i][j];
		}
	}
}

int check(int L, int color)
{
	int i;
	for (i = 1; i < L; i++)
	{
		if (a[L][i] == 1 && color == list[i]) return 0;
		//���� ������ ���ε� ������ ���� ��
	}
	return 1;
}
int DFS(int L)
{
	int i;

	if (L > N)
	{
		//printList(L);
		return 1;
	}
	for (i = 1; i <= M; i++)
	{//���� ��ȣ����
		if (check(L, i) == 1)
		{
			list[L] = i;
			if (DFS(L + 1) == 1) return 1; //�� ��� ���� �Ϸ��� �ٽ� �� ���� �ϸ� �ȵǹǷ�, �׷��� ������ �ٽ� �� ����
			list[L] = 0;
		}
	}
	return 0;
}

int main(void)
{
	int i;
	sol = 0;
	input();
	sol = DFS(1);
	//output(sol);
	if (sol == 0)
	{
		printf("-1\n");
	}
	else
	{//�����ȣ ����Ʈ�� ����Ѵ�
		for (i = 1; i <= N; i++)
		{
			printf("%d ", list[i]);
		}
	}
	return 0;
}
#endif



//////////////////////////Day 7�� ���� //////////////////////

//�ֻ���������2
#if 0
#include <stdio.h>
#define MAX (7+5)
int N, M;
int list[MAX];
int cnt;
void input(void)
{
	scanf("%d %d", &N, &M);
}

void printList(int L, int S, int R)
{
	int i;
	//	printf("%2d (S: %2d - R: %2d) : ", ++cnt, S, R);
	for (i = 1; i < L; i++)
	{
		printf("%d ", list[i]);
	}
	printf("\n");
}

void DFS(int L, int S, int R)
{//L: depth, S: �� �� �ܰ迡���� �� ��
	int i;
	if (S>M) return;

	if (L>N)
	{
		if (S == M)
		{
			printList(L, S, R);
		}
		return;
	}

	for (i = 1; i <= 6; i++)
	{
		list[L] = i;
		DFS(L + 1, S + i, R - i);
		list[L] = 0;
	}
}
int main(void)
{
	input();
	DFS(1, 0, M);
	return 0;
}

#endif

// ��� ����
#if 0
#include <stdio.h>
#define MAXN (7+5)
#define MAXM (30+5)
int N, M;
int a[MAXN][MAXM];
int best[MAXN];
int sol;  // �������ͱ� �ִ�

int list[MAXN];
int cnt;
void printList(int L, int S)
{
	int i;
	printf("%2d : (%2d : %2d) : ", ++cnt, sol, S);
	for (i = 1; i < L; i++)
	{
		printf("%2d ", list[i]);
	}
	printf("\n");
}

void input(void)
{
	int i, j;
	scanf("%d %d", &M, &N);
	for (i = 1; i <= M; i++)
	{
		for (j = 0; j <= N; j++)
		{
			scanf("%d", &a[i][j]);
		}
	}
}
void output(void)
{
	int i;
	printf("%d\n", sol);
	for (i = 1; i <= N; i++)
	{
		printf("%d ", best[i]);
	}
	printf("\n");
}
// L : �����ȣ, S : ���� ���ͱ� ����, R : ���� ���ڱݾ�
void DFS(int L, int S, int R)
{
	int i;
	if (R == 0)
	{
		//	printList(L, S);
		if (sol < S)
		{
			sol = S;
			for (i = 1; i <= N; i++)
			{
				best[i] = list[i];
			}
		}
		return;
	}
	if (L > N)
	{
		//	printList(L, S);
		return;
	}
	for (i = 0; i <= R; i++)
	{
		list[L] = i;
		DFS(L + 1, S + a[i][L], R - i);
		list[L] = 0;
	}
}
int main(void)
{
	input();
	sol = 0; // �ּ� ������ �ʱ�ȭ �ʿ� (�ִ밪 ���ϴ� ��)
	DFS(1, 0, M);
	output();
	return 0;
}
#endif

//�ֻ��� ������ 1
#if 0
#include <stdio.h>
#define MAX (6)
#define NMAX (MAX+5) 
int N, M;
int list[NMAX]; //list�� MAXũ��� �ȵǰ� �� Ŀ�ߵ�!
int cnt;
int visit[NMAX];

void input(void)
{
	scanf("%d %d", &N, &M);
}

void printList(int L)
{
	int i;
	//printf("% 2d : ", ++cnt);
	for (i = 1; i<L; i++)
	{
		printf("%d ", list[i]);
	}
	printf("\n");
}

void DFS_1(int L)
{
	int i;
	if (L > N)
	{
		printList(L);
		return;
	}
	for (i = 1; i <= MAX; i++)
	{
		list[L] = i;
		DFS_1(L + 1);
	}
}

void DFS_2(int L, int start)
{
	int i, j;

	if (L > N)
	{
		printList(L);
		return;
	}

	for (i = start; i <= MAX; i++)
	{
		list[L] = i;
		DFS_2(L + 1, i);
	}

}

void DFS_3(int L)
{
	int i, j;

	if (L > N)
	{
		printList(L);
		return;
	}

	for (i = 1; i <= MAX; i++)
	{
		if (visit[i] == 0)
		{
			visit[i] = 1;
			list[L] = i;
			DFS_3(L + 1);
			//list[L] = 0;
			visit[i] = 0;
		}
	}
}

int main(void)
{
	input();
	if (M == 1) DFS_1(1);
	else if (M == 2) DFS_2(1, 1);
	else if (M == 3) DFS_3(1);
	return 0;
}
#endif

////////////////////////////////Day 7////////////////////////////////////////////

//[] ���ٸ� �ǳʱ�(BASIC)

//depth - �η縶��
#if 0
#include <stdio.h>
#define MAXR (10+5)
#define MAXB (30+5)

char B[2][MAXB]; //B[0]: �Ǹ�, B[1]: õ��
char R[MAXR];
int bLen, rLen;
int sol;

void input(void)
{
	scanf("%s", &R[0]);			//scanf("%s", R); scanf("%s", B[0]), scanf("%s", B[1]);
	scanf("%s", &B[0][0]); //�Ǹ�
	scanf("%s", &B[1][0]); //õ��

	for (bLen = 0; B[0][bLen] > 0; bLen++); //bridge�� ���ڿ� ���� ����
	for (rLen = 0; R[rLen] > 0; rLen++); //

}

void DFS(int L, int start, int da) //da: õ�� �Ǵ� �Ǹ��� ������
{
	int i;

	if (L >= rLen)
	{//�� ã�Ƽ� ���������� �� ���, 
		//DFS�� ��� �����ϴ� �� �� �� �ܰ迡�� �η縶�� ���ڸ� ã�ұ� ������
		sol++;
		return;
	}

	for (i = start; i <= bLen - rLen + L; i++)
	{
		if (B[da][i] == R[L])
		{
			DFS(L + 1, i+1, !da);
		}
	}

}

int main(void)
{
	input();
	//�Ǹ����� ����
	DFS(0, 0, 0);
	//õ�翡�� ����
	DFS(0, 0, 1);
	printf("%d", sol);
	return 0;
}
#endif


//*******[h] ������ ���� FF - BFS, DFS �Ѵ� ok

//DFS
#if 0

#include <stdio.h>
#define MAX (10+5)
int N;
int a[MAX][MAX]; // 0 ~ 11 (A: 10, B: 11)
int sy, sx; //������ǥ
int T[][4] = {
	{ 0, 0, 0, 0 },	//0, (0: �������±�, 1: �����ִ±�)
	{ 0, 0, 1, 1 },	//1
	{ 1, 1, 0, 0 },	//2
	{ 0, 1, 0, 1 },	//3
	{ 0, 1, 1, 0 },	//4
	{ 1, 0, 1, 0 },	//5
	{ 1, 0, 0, 1 },	//6
	{ 1, 1, 0, 1 },	//7
	{ 0, 1, 1, 1 },	//8
	{ 1, 1, 1, 0 },	//9
	{ 1, 0, 1, 1 },	//A
	{ 1, 1, 1, 1 },	//B
}; //��Ʈ�������� �ϸ� �ʿ����

int D[] = { 1, 0, 3, 2 };
int pipe;
int sol;

int visit[MAX][MAX];

int dy[] = { -1, 1, 0, 0 }; //lookup table�� �Ȱ��� �ؾߵ�, lookup �� �����¿� ������ ������� ������
int dx[] = { 0, 0, -1, 1 };


void DFS(int sy, int sx)
{
	int i, ny, nx;
	int cur, next;

	visit[sy][sx] = 1;
	pipe--;
	cur = a[sy][sx]; //���ɻ� ������ ��
	for (i = 0; i < 4; i++)
	{
		ny = sy + dy[i];
		nx = sx + dx[i];

		if (ny<0 || nx<0 || ny >= N || nx >= N || visit[ny][nx] == 1) continue;

		next = a[ny][nx]; //���� ��� ��

		if (T[cur][i] == 1 && T[next][D[i]] == 1)
		{//���� �� �� �ְ� ������ �༮�� �� �� �ִ� ���̸� -> ����Ǿ��ִ°�!
			//visit[ny][nx] = 1;
			//pipe--;
			//DFS ó�� ���� �� ������ ���ֱ� ������ ���⼭�� �ʿ����
			DFS(ny, nx);

		}
	}
}

void input(void)
{
	int i, j;
	char tmp[MAX] = { 0 };

	pipe = 0; //������ �ʱ�ȭ, tc �������϶�
	sol = 0;

	scanf("%d %d %d", &N, &sx, &sy);
	for (i = 0; i < N; i++)
	{
		scanf("%s", tmp);
		for (j = 0; j < N; j++)
		{
			if (tmp[j] == 'A') a[i][j] = 10;
			else if (tmp[j] == 'B') a[i][j] = 11;
			else a[i][j] = tmp[j] - '0';

			if (a[i][j] > 0) pipe++;
		}
	}

	//for (i = 0; i < N; i++)
	//{
	//	for (j = 0; j < N; j++)
	//	{
	//		printf("%3d", a[i][j]);
	//	}
	//	printf("\n");
	//}
}

void init(void)
{
	int i, j;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			a[i][j] = 0;
		}
	}
}
//������ ���� ������ �� ���: 
// �丶��ó�� ó���� ������ ���� �ôٰ� ã�������� ���� ���
// ���߿� for������ ������ ���� ���� ���

int main(void)
{
	input();
	DFS(sy, sx);
	printf("%d", pipe);
	init(); //visit �迭 �ʱ�ȭ, TC ���� ���
	return 0;
}

#endif

//BFS
#if 0

#include <stdio.h>
#define MAX (10+5)
int N;
int a[MAX][MAX]; // 0 ~ 11 (A: 10, B: 11)
int sy, sx; //������ǥ
int T[][4] = {
	{ 0, 0, 0, 0 },	//0, (0: �������±�, 1: �����ִ±�)
	{ 0, 0, 1, 1 },	//1
	{ 1, 1, 0, 0 },	//2
	{ 0, 1, 0, 1 },	//3
	{ 0, 1, 1, 0 },	//4
	{ 1, 0, 1, 0 },	//5
	{ 1, 0, 0, 1 },	//6
	{ 1, 1, 0, 1 },	//7
	{ 0, 1, 1, 1 },	//8
	{ 1, 1, 1, 0 },	//9
	{ 1, 0, 1, 1 },	//A
	{ 1, 1, 1, 1 },	//B
}; //��Ʈ�������� �ϸ� �ʿ����

int D[] = { 1, 0, 3, 2 };
int pipe;
int sol;

struct st{
	int x;
	int y;
};
struct st Queue[MAX*MAX];
int wp, rp;

void In_Queue(int y, int x)
{
	Queue[wp].y = y;
	Queue[wp].x = x;
	wp++;
}

struct st Out_Queue(void)
{
	return Queue[rp++];
}

//int printAry(void)
//{
//	int i, j;
//	for (i = 0; i < N; i++)
//	{
//		for (j = 0; j < N; j++)
//		{
//			printf("%3d ", a[i][j]);
//		}
//		printf("\n");
//	}
//	printf("\n");
//}

int dy[] = { -1, 1, 0, 0 }; //lookup table�� �Ȱ��� �ؾߵ�, lookup �� �����¿� ������ ������� ������
int dx[] = { 0, 0, -1, 1 };

int BFS(int sy, int sx)
{
	int i, ny, nx;
	struct st out = { 0 };
	int visit[MAX][MAX] = { 0 };
	int cur, next;

	wp = rp = 0;
	In_Queue(sy, sx);
	visit[sy][sx] = 1;
	pipe--;

	while (wp > rp)
	{
		out = Out_Queue();
		cur = a[out.y][out.x]; //���ɻ� ������ ��
		for (i = 0; i < 4; i++)
		{
			ny = out.y + dy[i];
			nx = out.x + dx[i];

			if (ny < 0 || nx < 0 || ny >= N || nx >= N || visit[ny][nx] == 1)
				continue;
			next = a[ny][nx]; //���� ��� ��

			if (T[cur][i] == 1 && T[next][D[i]] == 1)
			{//���� �� �� �ְ� ������ �༮�� �� �� �ִ� ���̸� -> ����Ǿ��ִ°�!
				visit[ny][nx] = 1;
				In_Queue(ny, nx);
				pipe--;
			}
		}
	}

	return pipe;
}

void input(void)
{
	int i, j;
	char tmp[MAX] = { 0 };

	pipe = 0; //������ �ʱ�ȭ, tc �������϶�
	sol = 0;

	scanf("%d %d %d", &N, &sx, &sy);
	for (i = 0; i < N; i++)
	{
		scanf("%s", tmp);
		for (j = 0; j < N; j++)
		{
			if (tmp[j] == 'A') a[i][j] = 10;
			else if (tmp[j] == 'B') a[i][j] = 11;
			else a[i][j] = tmp[j] - '0';

			if (a[i][j] > 0) pipe++;
		}
	}

	//for (i = 0; i < N; i++)
	//{
	//	for (j = 0; j < N; j++)
	//	{
	//		printf("%3d", a[i][j]);
	//	}
	//	printf("\n");
	//}
}

//������ ���� ������ �� ���: 
// �丶��ó�� ó���� ������ ���� �ôٰ� ã�������� ���� ���
// ���߿� for������ ������ ���� ���� ���

int main(void)
{
	//int sol;
	input();
	sol = BFS(sy, sx);
	printf("%d", sol);
	return 0;
}

#endif
//*******


//*******��������_170318

////[sol]
#if 0
#include <stdio.h>
#define MAX (12+5)

int a[MAX];
int cnt;
int list[MAX];
int check[MAX * 100];
int N, K; //K�� ���° �������� ã�ƶ�
int sol;
int sum;
int s[MAX * 100];

int printList(int L, int S)
{
	int i;
	printf("%2d (%2d) : ", ++cnt, S);
	for (i = 1; i < L; i++)
	{
		printf("%2d ", list[i]);
	}
	printf("\n");
}

void input(void)
{
	int i, j;
	scanf("%d %d", &N, &K);
	sum = 0;
	for (i = 1; i <= N; i++)
	{
		scanf("%d", &a[i]);
		sum += a[i]; //���� �ִ��, ���߿� K�� ���°���� ���� �� �ִ� ���� ��ġ�� �ȴ�, 1��°
	}

	//����ġ���
	for (i = 1; i <= N; i++)
	{
		s[i] = 0;
		for (j = 1; j <= N; j++)
		{
			s[i] += a[j];
		}
	}
}

int getPosition(void)
{//K�� ���°���� ���ϴ� �Լ�
	int i;
	int pcnt = 0;
	for (i = sum; i >= K; i--)
	{
		if (check[i] > 0) pcnt++;
	}
	return pcnt;
}


void DFS(int L, int S)
{
	//����ġ�� - S + ������ ���� ��� ���� �� < K �� return;
	//������ ��� ���� ���� �迭�� �̸� �Է¹޴´�
	if ((S + s[L])< K) return;

	if (L > N)
	{
		printList(L, S);
		check[S]++;
		return;
	}

	list[L] = 1; //������ ���� 
	DFS(L + 1, S + a[L]);
	list[L] = 0; //������ �� ���� 
	DFS(L + 1, S);
}


int main(void)
{
	input();
	DFS(1, 0);
	sol = getPosition();
	printf("%d", sol);
	return 0;
}

#endif

////[my] -> K�� �������� ���ϴ� �Լ��� ���� ���� �ٽ� �غ���, ����ġ�� �ٽ�
#if 0
#include <stdio.h>
#define MAX (12+5)

int a[MAX];
int cnt;
int list[MAX];
int sum[MAX * 100];
int N, K; //K�� ���° �������� ã�ƶ�
int sol;
int printList(int L, int S)
{
	int i;
	printf("%2d (%2d) : ", ++cnt, S);
	for (i = 1; i < L; i++)
	{
		printf("%2d ", list[i]);
	}
	printf("\n");
}

void input(void)
{
	int i;
	scanf("%d %d", &N, &K);
	for (i = 1; i <= N; i++)
	{
		scanf("%d", &a[i]);
	}
}

//void printSum(int num)
//{
//	int i;
//	printf("sum [] = ");
//	for (i = num; i >= 0;  i--)
//	{
//		if (sum[i] > 0) printf("%2d ", i);
//	}
//	printf("\n");
//
//}
//
//void output(void)
//{
//	int i, start, k_cnt=0;
//	for (i = MAX * 100; i >= 0; i--)
//	{
//		if (sum[i] > 0)
//		{
//			start = i;
//			break;
//		}
//	}
//
//	printf("start = %d ", start);
//
//	printSum(start);
//	for (i = start; i >= 0; i--)
//	{
//		if (sum[i] >0)
//		{
//			k_cnt++;
//			if (i == K)
//			{
//				sol = k_cnt;
//				break;
//			}
//		
//		}
//	}
//}


void output(void)
{
	int i, start, k_cnt = 0;
	for (i = MAX * 100; i >= 0; i--)
	{
		if (sum[i] > 0)
		{
			start = i;
			break;
		}
	}

	//printf("start = %d ", start);

	//printSum(start);
	for (i = start; i >= K; i--)
	{
		if (sum[i] >0)
		{
			k_cnt++;
		}
	}
	sol = k_cnt;
}

void DFS(int L, int S)
{
	//if (sum[S] == 1) return;

	if (L > N)
	{
		printList(L, S);
		sum[S]++;
		return;
	}

	list[L] = 1; //������ ���� 
	DFS(L + 1, S + a[L]);
	list[L] = 0; //������ �� ���� 
	DFS(L + 1, S);
}
int main(void)
{
	input();
	DFS(1, 0);
	output();
	printf("%d", sol);

	return 0;
}
#endif

//*******

//����Ż�� - DFS
#if 01
#include <stdio.h>
#define MAX (20+5)
int N;
int a[MAX];
int sol;
int list[MAX];
int cnt;

int printList(int L, int C)
{
	int i;
	printf("%2d (%2d:%2d) : ", ++cnt, sol, C);
	for (i = 1; i < L; i++)
	{
		printf("%2d ", list[i]);
	}
	printf("\n");
}

int check(int a, int b)
{
	while (a>0 && b > 0)
	{
		if (a % 10 + b % 10 > 9) return 0;
		a /= 10, b /= 10;
	}
	return 1;
}

void input(void)
{
	int i;
	scanf("%d", &N);
	for (i = 1; i <= N; i++)
	{
		scanf("%d", &a[i]);
	}
}

void DFS(int L, int C, int S)
{//L: �� ��ȣ, C: �迡 ź ���� ��, S: �迡 ź ���� ������ ��

	if (C + (N - L + 1) <= sol)
	{
		//printList(L, C);
		return;
	}

	if (L > N)
	{
		//printList(L, C);
		if (sol < C)
		{
			sol = C;
		}
		return;
	}

	if (check(S, a[L]) == 1) //������ ��
	{//�¿��
		list[L] = 1; //���Ը� �ᵵ ��, ���⼭�� ���پ�����
		DFS(L + 1, C + 1, S + a[L]);
	}
	//�¿��� �ʴ´�
	list[L] = 0;
	DFS(L + 1, C, S);
}
int main(void)
{
	input();
	sol = 0; //sol���� max���� ������ ���̹Ƿ� �ּҰ� 0���� �ʱ�ȭ
	DFS(1, 0, 0);
	printf("%d", sol);
	return 0;
}
#endif

//���� ã�� [���� ���� ����, BFS sol Ǯ�� ����ȭ]
#if  0

#include <stdio.h>

#define MAX (100+10)
int a[MAX][MAX];
int power[MAX][MAX];
int N;
int top_y, top_x; //����
int sol;

struct st{
	int x;
	int y;
};
struct st Queue[MAX*MAX*MAX];
int wp, rp;

void In_Queue(int y, int x)
{
	Queue[wp].y = y;
	Queue[wp].x = x;
	wp++;
}

struct st Out_Queue(void)
{
	return Queue[rp++];
}

int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };

void input(void)
{
	int i, j;
	scanf("%d", &N);
	scanf("%d %d", &top_y, &top_x);
	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			scanf("%d", &a[i][j]);
		}
	}
}

void init_power(void)
{
	int i, j;
	for (i = 2; i <= N - 1; i++)
	{
		for (j = 2; j <= N - 1; j++)
		{
			power[i][j] = 0x7fff0000;
		}
	}
}
//
//void print(void)
//{
//	int i, j;
//	printf("\n");
//	for (i = 1; i <= N; i++)
//	{
//		for (j = 1; j <= N; j++)
//		{
//			printf("%2d ", power[i][j]);
//		}
//		printf("\n");
//	}
//
//}
int BFS(void)
{
	struct st out = { 0 };
	int i, ny, nx;
	int value;

	wp = rp = 0;
	init_power();
	for (i = 1; i <= N; i++)
	{
		In_Queue(1, i);
		power[1][i] = a[1][i] * a[1][i];
		In_Queue(N, i);
		power[N][i] = a[N][i] * a[N][i];
	}
	for (i = 2; i <= N - 1; i++)
	{
		In_Queue(i, 1);
		power[i][1] = a[i][1] * a[i][1];
		In_Queue(i, N);
		power[i][N] = a[i][N] * a[i][N];
	}


	while (wp > rp)
	{
		out = Out_Queue();

		for (i = 0; i < 4; i++)
		{
			ny = out.y + dy[i];
			nx = out.x + dx[i];

			if (ny < 1 || nx < 1 || nx > N || ny > N) continue;

			//[my]
			//if (a[ny][nx] > a[out.y][out.x]) value = (a[ny][nx] - a[out.y][out.x]) * (a[ny][nx] - a[out.y][out.x]);
			//else if (a[ny][nx] < a[out.y][out.x]) value = a[out.y][out.x] - a[ny][nx];
			//else if (a[ny][nx] == a[out.y][out.x]) value = 0;

			//if (power[ny][nx] > power[out.y][out.x] + value)
			//{
			//	power[ny][nx] = power[out.y][out.x] + value;
			//	In_Queue(ny, nx);
			//}

			//[sol]
			value = a[out.y][out.x] - a[ny][nx];
			if (value < 0) value *= value;
			if (power[ny][nx] > power[out.y][out.x] + value)
			{
				power[ny][nx] = power[out.y][out.x] + value;
				In_Queue(ny, nx);
			}
		}
	}

	return power[top_y][top_x];

}

int main(void)
{
	int i, j, tmp;
	input();
	sol = BFS();

	//for (i = 1; i <= N; i++)
	//{
	//	tmp = BFS(1, i);
	//	if (sol > tmp) sol = tmp;
	//	tmp = BFS(N, i);
	//	if (sol > tmp) sol = tmp;

	//}

	//for (i = 2; i <= N - 1; i++)
	//{
	//	tmp = BFS(i, 1);
	//	if (sol > tmp) sol = tmp;
	//	tmp = BFS(i, N);
	//	if (sol > tmp) sol = tmp;
	//}

	printf("%d", sol);
	return 0;
}
#endif



////////////////////////////////Day 6////////////////////////////////////////////

//SumSets2
#if 0
#include <stdio.h>
#define MAX (10+5)
int N;
int a[] = { 1, 2, 4, 8, 16, 32, 64, 128 };
int sol;
int list[MAX];
int cnt;

void printList(int L)
{
	int i;
	printf("%2d : ", ++cnt);
	for (i = 0; i < L; i++)
	{
		printf("%2d ", list[i]);
	}
	printf("\n");
}

void DFS(int L, int R)
{
	int i;
	if (R == 0)
	{
		//printList(L);
		sol++;
		return;
	}
	//if (a[L] > R || a[L] > N) 
	//{
	////0 0 0 �� ���� ���Ǵ� ��쿡�� ���ᰡ �Ǿ�� �ϹǷ� 
	////6 0 0 �� ���� ��쵵 ����
	//	printList(L);
	//	return;
	//}
	if (a[L] > N) //0 0 0 �� ���� ���Ǵ� ��쿡�� ���ᰡ �Ǿ�� �ϹǷ� 
	{
		//printList(L);
		return;
	}
	for (i = 0; i*a[L] <= R; i++)
	{
		list[L] = i;
		DFS(L + 1, R - (i*a[L]));
		list[L] = 0;
	}

}

int main(void)
{
	int T, tc;
	scanf("%d", &T);
	for (tc = 1; tc <= T; tc++)
	{
		scanf("%d", &N);
		sol = 0;
		DFS(0, N);
		printf("%d\n", sol);
	}
	return 0;
}
#endif

//[����] N Queen, DFS ����
#if 0
#include <stdio.h>
#define MAX (13+5)
int N;
int col[MAX];
int d1[MAX * 3];//�˳��ϰ�
int d2[MAX * 3];
int sol;
int list[MAX];
int cnt;
void printList(int L)
{
	int i;
	printf("%2d : ", ++cnt);
	for (i = 1; i < L; i++)
	{
		printf("%2d ", list[i]);
	}
	printf("\n");
}
void DFS(int L)
{
	int i;
	printList(L);
	if (L > N)
	{
		printf("found==>\n");
		printList(L);
		sol++;
		return;
	}

	for (i = 1; i <= N; i++)
	{
		if (col[i] == 0 && d1[L + i] == 0 && d2[L - i + N] == 0)
		{
			list[L] = i;
			col[i] = 1; d1[L + i] = 1; d2[L - i + N] = 1;
			DFS(L + 1);
			list[L] = 0;
			col[i] = 0; d1[L + i] = 0; d2[L - i + N] = 0;
		}
	}
}

int main(void)
{
	scanf("%d", &N);
	sol = 0;
	DFS(1);
	printf("%d", sol);
	return 0;
}
#endif


//[����, �Һ�] ������� basic DFS. ���� �Һ�

//[����] ���ʽ� DFS, ����
#if 01
#include <stdio.h>
#define MAX (10+5)
int N;
int a[MAX][MAX]; //(��)�����-(��)�ϱ��� �迭
int b[MAX]; //���ʽ� �ݾ�
int visit[MAX];
int list[MAX];
int cnt;

void printList(int L)
{
	int i;

	printf("%2d : ", ++cnt);
	for (i = 1; i < L; i++)
	{
		printf("%2d ", list[i]);
	}
	printf("\n");
}

void sort(void)
{
	int i, j, t;
	for (i = 1; i <= 1; i++) //���� ū �͸� �� �� ã�� ��
	{
		for (j = i + 1; j <= N; j++)
		{
			if (b[i] < b[j])
			{
				t = b[i];
				b[i] = b[j];
				b[j] = t;
			}
		}
	}
}

void input(void)
{
	int M, y, x;
	int i;

	scanf("%d %d", &N, &M);
	for (i = 1; i <= M; i++)
	{
		scanf("%d %d", &y, &x); // y: �����, x: �ϱ���
		a[y][x] = 1; //������� (��: �����, ��: �ϱ���) 
	}
	for (i = 1; i <= N; i++)
	{
		scanf("%d", &b[i]);
	}
}

int check(int L, int bonus)
{//������ �� ������� ��������� �ϱ������� �Ǵ�
	int i;
	for (i = 2; i < L; i++)//i�� �̹� ���ʽ��� ���� ����
	{
		if (a[i][L] == 1 && list[i] <= bonus) return 0; // i�� ����� && ���� ����ں��� ���ʽ��� ���� �� ����Ǵ� ����
		if (a[L][i] == 1 && list[i] >= bonus) return 0; // i�� �ϱ��� && ���� �ϱ��ں��� ���ʽ��� ���� �� ����
	}
	return 1;
}

//�� �������� ������ ���ʽ��� �ο��Ѵ�. ���ʽ��� �� ������ �����Ѵ�
//�ߺ��Ǹ� �ȵǴϱ� visit[] 
//�ߺ� ���� ����
int DFS(int L)
{
	int i;

	if (L > N)
	{

		return 1; //��� �������� ���ʽ��� �� �����ſ���
	}


	for (i = 2; i <= N; i++) //������� ����
	{
		if (visit[i] == 0 && check(L, b[i]) == 1)
		{
			list[L] = b[i];
			visit[i] = 1;
			//	printList(L);
			if (DFS(L + 1) == 1) return 1;

			list[L] = 0;
			visit[i] = 0;
		}
	}
	return 0; //���ʽ� �Ҵ� ����
}


int main(void)
{
	int ret, i;
	input();
	sort();
	list[1] = b[1]; //����� ���ʽ� �Ҵ�
	ret = DFS(2); // ����� �����ϰ�

	//�� ������ �ʿ������, ���迡���� ����/������ ��쿡 ���ؼ� ��� ������� �� ���ɼ� ����
	//best[]�� �ʿ���� ������ �ѹ��� �ϰ� ������ �Ǵϱ�
	if (ret == 1)
	{
		for (i = 1; i <= N; i++)
		{
			printf("%d ", list[i]);
		}
	}
	else
	{
		printf("IMPOSSIBLE\n");
	}
	return 0;
}
#endif

//[Y] �ڵ������ִ�ȸ Basic DFS
#if 0
#include <stdio.h>
#define MAX (50+5)
int K, N;
int t[MAX];
int d[MAX];
int sol; //�ּ� ���� �ð�

int list[MAX];
int best[MAX];
int cnt;
void printList(int L, int tS)
{
	int i;
	printf("%2d (%2d:%2d) : ", L, sol, tS);
	for (i = 1; i < L; i++)
	{
		printf("%2d ", list[i]);
	}
	printf("\n");
}
void input(void)
{
	int i, j;
	scanf("%d %d", &K, &N);
	for (i = 0; i <= N; i++)
	{
		scanf("%d", &d[i]);
	}
	for (i = 1; i <= N; i++)
	{
		scanf("%d", &t[i]);
	}
}

//�鸰 ����� ���� (�μ� ��� ����, ���߿� ī����)
void output(void)
{
	int i, jcnt = 0;
	printf("%d\n", sol);
	if (sol == 0) return;
	for (i = 1; i <= N; i++)
	{
		if (best[i] > 0) jcnt++;
	}
	printf("%d\n", jcnt);
	for (i = 1; i <= N; i++)
	{
		if (best[i] > 0) printf("%d ", i);
	}
	printf("\n");
}

void DFS(int L, int tS, int dS)
{
	int i;

	if (tS >= sol)
	{
		//printList(L, tS);
		return;
	}

	if (L > N)
	{
		//printList(L, tS);
		if (sol > tS)
		{
			sol = tS;
			for (i = 1; i <= N; i++)
			{
				best[i] = list[i];
			}
		}
		return;
	}

	if (dS + d[L] <= K)
	{//���� �� �޾Ƶ� �Ǵϱ� 
		list[L] = 0;
		DFS(L + 1, tS, dS + d[L]);
	}
	list[L] = 1;
	DFS(L + 1, tS + t[L], d[L]);

}

int main(void)
{
	input();
	sol = 0x7fff0000;
	DFS(1, 0, d[0]);
	output();
	return 0;
}
#endif

//[Z] ������ BFS
#if 0

//�Է�: char a[MAX][MAX]; int b[MAX][MAX] => BFS�� ����� �迭
//������: a[i][j] == 'L'
//������: while(wp>rp){} ���� ��� loop
//������: b[ny][nx] == 0 ('L')
//�湮ǥ��: b[sy][sx] = 1; b[ny][nx] = b[out.y][out.x]+1;
//ť�� ũ��: struct st Queue[MAX*MAX] (�ѹ����� ���� �Ǵϱ�)

#include <stdio.h>
#define MAX (50+10)

char a[MAX][MAX];
int b[MAX][MAX];
int X, Y;
int sol;

struct st{
	int y;
	int x;
};
struct st Queue[MAX*MAX];
int wp, rp;

void In_Queue(int y, int x)
{
	Queue[wp].y = y;
	Queue[wp].x = x;
	wp++;
}

struct st Out_Queue(void)
{
	return Queue[rp++];
}


void input(void)
{
	int i, j;
	scanf("%d %d", &Y, &X);
	for (i = 0; i < Y; i++)
	{
		scanf("%s", &a[i][0]);
	}
}

void init(void)
{
	int i, j;
	for (i = 0; i < Y; i++)
	{
		for (j = 0; j < X; j++)
		{
			b[i][j] = ((a[i][j] == 'L') ? (0) : (1));
		}
	}
}
int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };

int BFS(int sy, int sx)
{
	int i, ny, nx;
	struct st out = { 0 };

	wp = rp = 0;
	b[sy][sx] = 1;
	In_Queue(sy, sx);

	while (wp > rp)
	{
		out = Out_Queue();
		for (i = 0; i < 4; i++)
		{
			ny = out.y + dy[i];
			nx = out.x + dx[i];

			if (ny < 0 || nx < 0 || ny >= Y || nx >= X) continue;
			if (b[ny][nx] == 0)
			{
				b[ny][nx] = b[out.y][out.x] + 1;
				In_Queue(ny, nx);
			}
		}
	}
	return b[out.y][out.x] - 1;
}

int main(void)
{
	int i, j, ret, sol;

	input();
	sol = 0;
	for (i = 0; i < Y; i++)
	{
		for (j = 0; j < X; j++)
		{
			if (a[i][j] == 'L')
			{
				init(); //copy a to b
				ret = BFS(i, j);
				if (sol < ret) sol = ret;
			}
		}
	}
	printf("%d", sol);
	return 0;
}
#endif


//FF Debugging
//1. ��ü ������ print
//2. InQueue �Ǵ� OutQueue ���� print

//[T] ġ�� FF BFS

//�Է�: int a[MAX][MAX]; %d, 1,1~Y,X (0,0~Y-1, X-1)
//������: 0,0 / 1,1 //��� ���� (�ѷ��� �����Ϳ� ���ԵǾ� �־)
//������: while(wp>rp) {}
//������: a[ny][nx] == 0
//		a[ny][nx] = 1; //ġ�� 
//�湮ǥ��: ������ = 2, ġ�� = 3
//1�ð� �� init() �Ѵ� (2,3�� 0���� ����)
//������ ������ ���� ��� depth�� ������� ������ DFS���ٴ� BFS�� ������

#if 0
#include <stdio.h>
#define MAX (100+10)
int X, Y;
int a[MAX][MAX];

struct st {
	int x;
	int y;
};
struct st Queue[MAX*MAX];
int wp, rp;
//ť�� ũ��: 
// 1) ������ ���� ( Queue[MAX];
// 2) ������ ��ǥ ( Queue[MAX*MAX];
// 3) �ϳ��� ������ ������ �湮�� �� ���� �� - ������ �ִ��*MAX
// - ������ ����: MAX*MAX , ������ ��ǥ: MAX*MAX*MAX

void In_Queue(int y, int x)
{
	Queue[wp].y = y;
	Queue[wp].x = x;
	wp++;
}

struct st Out_Queue(void)
{
	return Queue[rp++];
}

void input(void)
{
	int i, j;
	scanf("%d %d", &Y, &X);
	for (i = 1; i <= Y; i++)
	{
		for (j = 1; j <= X; j++)
		{
			scanf("%d", &a[i][j]);
		}
	}
}

void printAry(void)
{
	int i, j;

	for (i = 1; i <= Y; i++)
	{
		for (j = 1; j <= X; j++)
		{
			printf("%2d", a[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };

//�ð����� �ѹ��� ����
int FF_BFS(int sy, int sx)
{
	int i, ny, nx;
	struct st out;
	int c_cnt = 0; //ġ���� ����

	wp = rp = 0;
	a[sy][sx] = 2; // ������ �湮ǥ��
	In_Queue(sy, sx);



	while (wp > rp)
	{
		out = Out_Queue();
		for (i = 0; i < 4; i++)
		{
			ny = out.y + dy[i];
			nx = out.x + dx[i];

			if (ny<1 || nx<1 || ny > Y || nx>X) continue;

			if (a[ny][nx] == 0)
			{
				a[ny][nx] = 2;
				In_Queue(ny, nx);
			}
			else if (a[ny][nx] == 1)
			{
				c_cnt++;
				a[ny][nx] = 3;
			}
		}
	}

	return c_cnt;

}

void init(void)
{
	int i, j;
	for (i = 1; i <= Y; i++)
	{
		for (j = 1; j <= X; j++)
		{
			if (a[i][j] > 1) a[i][j] = 0;
		}
	}
}

int main(void)
{
	int ret = 0, sol;
	int time;
	printAry();
	input();

	for (time = 0;; time++)
	{
		ret = FF_BFS(1, 1);
		if (ret == 0) break;
		sol = ret;
		printAry(); printf("ret = %d ", ret);
		printf("time = %d\n", time);
		init();

	}

	printf("%d\n", time);
	printf("%d", sol);
	return 0;
}
#endif
