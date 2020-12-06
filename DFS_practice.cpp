#if 0
#include <stdio.h>
#define MAX (100+10)
int M, N, H;
int a[MAX][MAX][MAX];  // ���࿭
int sol;
// ��, �Ʒ�, ��, ��, ��, ����
int dz[] = { -1, 1, 0, 0, 0, 0 };
int dy[] = { 0, 0, -1, 1, 0, 0 };
int dx[] = { 0, 0, 0, 0, -1, 1 };

struct st {
	int x, y, z;
};

struct st Queue[MAX * MAX * MAX];
int wp, rp;

void In_Queue(int z, int y, int x)
{
	Queue[wp].x = x;
	Queue[wp].y = y;
	Queue[wp].z = z;
	wp++;
}

struct st Out_Queue(void)
{
	return Queue[rp++];
}

int Tomato_BFS(void)
{
	int i, j, k;
	struct st out;
	int nx, ny, nz;
	int cnt = 0;

	wp = rp = 0;
	for (k = 1; k <= H; k++)
	{
		for (i = 1; i <= N; i++)
		{
			for (j = 1; j <= M; j++)
			{
				if (a[k][i][j] == 1)
					In_Queue(k, i, j);
				else if (a[k][i][j] == 0)
					cnt++;
			}
		}
	}
	if (cnt == 0) return 0;
	//printf("cnt %d\n", cnt);
	while (wp > rp)
	{
		out = Out_Queue();
		//printf("%d %d %d\n", out.z, out.y, out.x);
		for (i = 0; i < 6; i++)
		{
			nx = out.x + dx[i];
			ny = out.y + dy[i];
			nz = out.z + dz[i];
			if (nx < 1 || ny < 1 || nz < 1 ||
				nx > M || ny > N || nz > H) continue;
			{
				if (a[nz][ny][nx] == 0)
				{
					a[nz][ny][nx] = a[out.z][out.y][out.x] + 1;
					In_Queue(nz, ny, nx);
					cnt--;
					if (cnt == 0) return a[out.z][out.y][out.x];
				}
			}
		}
	}
	//	printf("cnt : %d\n", cnt);	
	return -1;
}
int main(void)
{
	int i, j, k;

	scanf("%d %d %d", &M, &N, &H);

	for (k = 1; k <= H; k++)  // ����
	{
		for (i = 1; i <= N; i++)
		{
			for (j = 1; j <= M; j++)
			{
				scanf("%d", &a[k][i][j]);
			}
		}
	}
	sol = Tomato_BFS();

	printf("%d", sol);
	return 0;
}
#endif

// �̼�������ȸ
#if 0
#include <stdio.h>
#define MAX (100+10)
char a[MAX][MAX];
int N;
int sol1, sol2;

void input(void) {
	int i;
	scanf("%d", &N);
	for (i = 1; i <= N; i++) {
		scanf("%s", &a[i][1]);
	}

}
void output(void) {
	printf("%d %d\n", sol1, sol2);
}
int tColor, cColor;

void FF(int sy, int sx) {

	if (a[sy][sx] != tColor) return;

	a[sy][sx] = cColor;
	FF(sy - 1, sx);
	FF(sy + 1, sx);
	FF(sy, sx - 1);
	FF(sy, sx + 1);
}

int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };
void FF2(int sy, int sx) {
	int i, ny, nx;

	a[sy][sx] = cColor;
	for (i = 0; i < 4; i++)
	{
		ny = sy + dy[i];
		nx = sx + dx[i];
		if (ny<1 || nx<1 || ny>N || nx>N) continue;
		if (a[ny][nx] == tColor)
		{
			FF2(ny, nx);
		}
	}
}
int getCount(void) {
	int cnt = 0;
	int i, j;
	for (i = 1; i <= N; i++) {
		for (j = 1; j <= N; j++) {
			if (a[i][j] == 'R' || a[i][j] == 'G' || a[i][j] == 'B') {
				++cnt;
				tColor = a[i][j];
				if (tColor == 'R' || tColor == 'G') cColor = '.';
				else cColor = 'x';
				FF(i, j);
			}
		}
	}
	return cnt;
}
void changeColor(void) {
	int i, j;
	for (i = 1; i <= N; i++) {
		for (j = 1; j <= N; j++) {
			if (a[i][j] == '.') a[i][j] = 'R';
			else a[i][j] = 'B';
		}
	}
}
int main(void)
{
	input();
	sol1 = getCount();
	changeColor();
	sol2 = getCount();
	output();
	return 0;
}
#endif

// ��Ŷ
#if 0
#include <stdio.h>
#define MAX (10 + 5)
int N;
int s[MAX];
int b[MAX];
int S, B;  // �Ÿ�, ����
int sol;   // �Ÿ��� ������ ���� �ּ�

int list[MAX];
int cnt;
void printList(int L, int sG, int bS) {
	int i;
	printf("%2d (%d, %d, %d) : ", ++cnt, sol, sG, bS);
	for (i = 1; i < L; i++) {
		printf("%d ", list[i]);
	}
	printf("\n");
}

void input(void) {
	int i;
	scanf("%d", &N);
	for (i = 1; i <= N; i++) {
		scanf("%d %d", &s[i], &b[i]);
	}
}
#define ABS1(a, b) (((a)-(b)>0) ? ((a)-(b)) : ((b)-(a)))
#define ABS2(a)  ((a)>0 ? (a) : -(a))
void DFS(int L, int sG, int bS) {
	if (L > N) {
		if (sG == 1 && bS == 0) return;
		//printList(L, sG, bS);
		//int diff = (sG - bS)>0 ? sG - bS : bS - sG;
		int diff = ABS2(sG - bS);
		if (sol > diff) {
			sol = diff;
		}
		return;
	}
	// ��Ḧ �ȳִ´�
	list[L] = 0;
	DFS(L + 1, sG, bS);
	// ��Ḧ �ִ´�
	list[L] = 1;
	DFS(L + 1, sG * s[L], bS + b[L]);
}
int main(void) {
	input();
	sol = 0x7FFF0000;
	DFS(1, 1, 0);
	printf("%d\n", sol);
	return 0;
}
#endif

// ���� ����
#if 0
#include <stdio.h>
#define MAX (100+10)
int N;
int a[MAX][MAX];  // ����
int b[MAX][MAX];  // ���� ����� �迭
int sol;  // �ִ밪 (min���� �ʱ�ȭ �ʿ�)
int maxR;
int minR;
struct st {
	int y, x;
};
int wp, rp;
struct st Queue[MAX * MAX];
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

	maxR = 0;
	minR = 200;

	scanf("%d", &N);
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			scanf("%d", &a[i][j]);
			if (a[i][j] > maxR) maxR = a[i][j];
			if (a[i][j] < minR) minR = a[i][j];
		}
	}
}
void copytoB(int rain)
{
	int i, j;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			//if (a[i][j] <= rain) b[i][j] = 0;
			//else b[i][j] = 1;
			if (a[i][j] > rain) b[i][j] = 1;
		}
	}
}
void printAry(void)
{
	int i, j;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			printf("%d ", b[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };
void BFS(int sy, int sx)
{
	struct st out;
	int i, ny, nx;

	wp = rp = 0;
	In_Queue(sy, sx);
	b[sy][sx] = 0;
	while (wp > rp)
	{
		out = Out_Queue();
		for (i = 0; i < 4; i++)
		{
			ny = out.y + dy[i];
			nx = out.x + dx[i];
			if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
			if (b[ny][nx] == 1)  // ������
			{
				In_Queue(ny, nx);
				b[ny][nx] = 0;
			}
		}
	}
}

void DFS(int L, int sy, int sx)
{
	int i, ny, nx;
	//printf("%d : %d, %d\n", L, sy, sx);
	b[sy][sx] = 0;  // �湮ǥ��
	for (i = 0; i < 4; i++)
	{
		ny = sy + dy[i];
		nx = sx + dx[i];
		if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
		if (b[ny][nx] == 1)
		{
			DFS(L + 1, ny, nx);
		}
	}
}

void DFS2(int L, int sy, int sx)
{
	//printf("%d : %d, %d\n", L, sy, sx);
	if (sy < 0 || sx < 0 || sy >= N || sx >= N) return;
	if (b[sy][sx] != 1) return;
	b[sy][sx] = 0;  // �湮ǥ�� 

	DFS2(L + 1, sy - 1, sx);
	DFS2(L + 1, sy + 1, sx);
	DFS2(L + 1, sy, sx - 1);
	DFS2(L + 1, sy, sx + 1);
}

int getSafeAreaCnt(int rain)
{
	int saCnt = 0;
	int i, j;

	copytoB(rain);
	//printAry();
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			if (b[i][j] == 1)
			{
				saCnt++;
				//BFS(i, j);
				DFS(1, i, j);
			}
		}
	}
	//printAry();
	return saCnt;
}

int main(void)
{
	int tmp, i;

	input();
	sol = 0;

	if (minR == maxR)
	{
		sol = 1;
	}
	else {
		for (i = minR; i < maxR; i++)
		{
			tmp = getSafeAreaCnt(i);
			//printf("%d : %d\n", i, tmp);
			if (tmp > sol) {
				sol = tmp;
			}
		}
	}
	printf("%d\n", sol);

	return 0;
}
#endif

// ���幮�� �̵�
#if 0
#include <stdio.h>
#define ABS1(x, y) ( ((x)>(y)) ? ((x)-(y)) : ((y)-(x)) )
#define ABS2(x) ( ((x)<0) ? (-(x)) : (x) )
#define MAX (20+5)
int N, M; // N : ��ü ���� ����, M : ����� ���� ����
int D1, D2;
int a[MAX];
int sol; // �ּҰ� ����

int list[MAX];
int cnt;
void printList(int L, int C)
{
	printf("%3d (%2d: %2d) : ", ++cnt, sol, C);
	for (int i = 1; i < L; i++)
	{
		printf("%3d ", list[i]);
	}
	printf("\n");
}
void input(void)
{
	scanf("%d", &N);  // N : ��ü ���� ����
	scanf("%d %d", &D1, &D2);
	scanf("%d", &M);  // M : ����� ���� ����
	for (int i = 1; i <= M; i++)
	{
		scanf("%d", &a[i]);
	}
}

// D1, D2 : ���� �� ���� ��, C : �� �̵� Ƚ���� ����
void DFS(int L, int D1, int D2, int C)
{
	if (C >= sol) {  // ����ġ��
		//printList(L, C);
		return;
	}
	if (L > M)
	{
		//printList(L, C);
		if (sol > C) sol = C;
		return;
	}
	//list[L] = ABS1(a[L], D1);
	DFS(L + 1, a[L], D2, C + ABS1(a[L], D1));
	//list[L] = 100 + ABS1(a[L], D2);
	DFS(L + 1, D1, a[L], C + ABS1(a[L], D2));
}
int main(void)
{
	freopen("input_2649.txt", "r", stdin);
	input();
	sol = 0x7FFF0000;
	DFS(1, D1, D2, 0);
	printf("%d\n", sol);
	return 0;
}
#endif

// ���̿켱Ž�� I
#if 0
#include <stdio.h>

int X, Y;  // Y : ��������, X : ��������
int s[200 + 10];
int e[200 + 10];
int ap;
int sol[100 + 10];
int visit[100 + 10];

void DFS(int v)
{
	int i;
	if (visit[v] == 1 || ap > X) return;

	visit[v] = 1;
	sol[ap++] = v;

	for (i = 0; i < Y; i++)
	{
		// ����� ���
		if ((s[i] == v) && (visit[e[i]] == 0))
		{
			DFS(e[i]);
		}
		if ((e[i] == v) && (visit[s[i]] == 0))  // ����� ��� 
		{
			DFS(s[i]);
		}
	}
}

int main(void)
{
	int i;

	// �Է¹޴� �κ�
	scanf("%d %d", &X, &Y);
	for (i = 0; i < Y; i++)
	{
		scanf("%d %d", &s[i], &e[i]);
	}

	// ���⼭���� �ۼ�
	DFS(1);     // ������� 1�� �ϰ� ������ ������ �˷� ��

	// ����ϴ� �κ�
	for (i = 0; i < ap; i++)
	{
		printf("%d ", sol[i]);
	}
	return 0;
}
#endif

// ġ�� (cheese)  - BFS�� Nȸ �����ؼ� S ~ N���� �湮
#if 0
#include <stdio.h>
#define MAX (1000+10)
char a[MAX][MAX];
int b[MAX][MAX];
int X, Y, N;
int sol;
int sx, sy; // ������

struct st {
	int y, x;
};
int wp, rp;
struct st Queue[MAX * MAX];

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
// �Է� + ������ ã��
void input(void)
{
	scanf("%d %d %d", &Y, &X, &N);
	sy = 0; sx = 0;
	for (int i = 1; i <= Y; i++)
	{
		scanf("%s", &a[i][1]);
		if (sy != 0) continue;
		for (int j = 1; j <= X; j++)
		{
			if (a[i][j] == 'S')
			{
				sy = i; sx = j;
			}
		}
	}
}

void initB(void)
{
	int y, x;
	for (int i = 1; i <= Y; i++)
	{
		for (int j = 1; j <= X; j++)
		{
			b[i][j] = 0;
		}
	}
#if 0
	for (int i = 0; i < wp; i++)
	{
		y = Queue[i].y;
		x = Queue[i].x;
		b[y][x] = 0;
	}
#endif
}
int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };

int BFS(char cheese)
{
	struct st out;
	int i, ny, nx;
	char lastCheese = N + '0';   // '0' (48)  '1' (49)   '2' (50)  ...   //  2 + 48 = 50 => '2' 

	wp = rp = 0;
	In_Queue(sy, sx);
	b[sy][sx] = 1;

	while (wp > rp)
	{
		out = Out_Queue();
		for (i = 0; i < 4; i++)
		{
			ny = out.y + dy[i];
			nx = out.x + dx[i];
			if (ny<1 || nx<1 || ny>Y || nx>X) continue;
			if (a[ny][nx] == 'X' || b[ny][nx] > 0) continue;
			if (a[ny][nx] == cheese)
			{
				// �������� ��� �ؾ� �� ��
				sy = ny; sx = nx;
				return b[out.y][out.x];
			}
			// �������� �� �ؾ� �� ��
			In_Queue(ny, nx);
			b[ny][nx] = b[out.y][out.x] + 1;
			//if ( ((a[ny][nx] >='1' && a[ny][nx] <= lastCheese) || a[ny][nx] =='.') && b[ny][nx] == 0)
		}
	}
	return 0;  // �̷� ��Ȳ�� �߻��ϸ� �ȵ�
}
int main(void)
{
	freopen("input_2628.txt", "r", stdin);
	input();
	sol = 0;
	for (char i = '1'; i <= N + '0'; i++)
	{
		initB();  // b�迭 �ʱ�ȭ
		sol += BFS(i);
	}
	printf("%d\n", sol);
	return 0;
}
#endif

// ġ�� (cheese)  - BFS�� 1ȸ �����ؼ� S ~ N���� �湮
#if 0
#include <stdio.h>
#define MAX (1000+10)
char a[MAX][MAX];
int b[MAX][MAX];
int X, Y, N;
int sol;
int sx, sy; // ������

struct st {
	int y, x;
};
int wp, rp;
struct st Queue[MAX * MAX];

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
// �Է� + ������ ã��
void input(void)
{
	scanf("%d %d %d", &Y, &X, &N);
	sy = 0; sx = 0;
	for (int i = 1; i <= Y; i++)
	{
		scanf("%s", &a[i][1]);
		if (sy != 0) continue;
		for (int j = 1; j <= X; j++)
		{
			if (a[i][j] == 'S')
			{
				sy = i; sx = j;
			}
		}
	}
}

void initB(void)
{
	int y, x;
	for (int i = 1; i <= Y; i++)
	{
		for (int j = 1; j <= X; j++)
		{
			b[i][j] = 0;
		}
	}
#if 0
	for (int i = 0; i < wp; i++)
	{
		y = Queue[i].y;
		x = Queue[i].x;
		b[y][x] = 0;
	}
#endif
}
int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };

int BFS(int sy, int sx)
{
	struct st out;
	int i, ny, nx;
	int time = 0;
	char cheese = '1';
	char lastCheese = N + '0';   // '0' (48)  '1' (49)   '2' (50)  ...   //  2 + 48 = 50 => '2' 

	wp = rp = 0;
	In_Queue(sy, sx);
	b[sy][sx] = 1;

	while (wp > rp)
	{
		out = Out_Queue();
		for (i = 0; i < 4; i++)
		{
			ny = out.y + dy[i];
			nx = out.x + dx[i];
			if (ny<1 || nx<1 || ny>Y || nx>X) continue;
			if (a[ny][nx] == 'X' || b[ny][nx] > 0) continue;
			if (a[ny][nx] == cheese)
			{
				// �������� ��� �ؾ� �� ��
				time += b[out.y][out.x];
				initB();  // b�迭 �ʱ�ȭ
				wp = rp = 0;
				In_Queue(ny, nx);
				b[ny][nx] = 1;
				cheese++;
				break;
			}
			// �������� �� �ؾ� �� ��
			In_Queue(ny, nx);
			b[ny][nx] = b[out.y][out.x] + 1;
			//if ( ((a[ny][nx] >='1' && a[ny][nx] <= lastCheese) || a[ny][nx] =='.') && b[ny][nx] == 0)
		}
	}
	return time;
}
int main(void)
{
	freopen("input_2628.txt", "r", stdin);
	input();
	sol = BFS(sy, sx);
	printf("%d\n", sol);
	return 0;
}
#endif

// ���� ���� ����
#if 0

#include <stdio.h>
#define MAX (100+10)
int N;
int a[MAX][MAX];
int sol;
int wp, rp;
struct mt {
	int y, x;
};
struct mt Queue[MAX * MAX * MAX];
struct mt OutQueue(void) {
	return Queue[rp++];
}
void InQueue(int y, int x) {
	Queue[wp].y = y;
	Queue[wp].x = x;
	wp++;
}
int dy[] = { -1,1,0, 0 };
int dx[] = { 0,0,-1,1 };

void input(void) {
	int i, j;
	scanf("%d", &N);
	for (i = 1; i <= N; i++) {
		for (j = 1; j <= N; j++) {
			scanf("%1d", &a[i][j]);
		}

	}
}

void printAry(void) {
	int i, j;
	for (i = 1; i <= N; i++) {
		for (j = 1; j <= N; j++) {
			printf("%d ", a[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int BFS(void) {
	int i, j, ny, nx;
	int min, cnt;
	struct mt out = { 0 };
	wp = rp = 0;
	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			if (a[i][j] == 1) {
				InQueue(i, j);
			}
		}
	}
	while (wp > rp) {
		out = OutQueue();
		min = 0x7fff0000;
		cnt = 0;
		for (i = 0; i < 4; i++) {
			ny = out.y + dy[i];
			nx = out.x + dx[i];
			if (ny <1 || nx<1 || ny>N || nx>N) continue;
			// ������ �ƴ� ��� min�� ã�� ���� ����
			// ������ �ƴ� ���� ã�� �� out �������� ���ų� ���� �͸� ��ȿ
			if (a[ny][nx] >= a[out.y][out.x]) {
				if (min > a[ny][nx]) min = a[ny][nx];
				cnt++;
			}
			else break; // �ֺ��� ���� �� ���
		}
		if (cnt == 4)  // ������ ��� ����� ���
		{
			a[out.y][out.x] = min + 1;
			InQueue(out.y, out.x);
			//printf("%d %d = %d\n", out.y, out.x, min+1);
		}
	}
	printAry();
	return a[out.y][out.x];  // ������ ��ġ
}

int main(void) {
	input();
	sol = BFS();
	printf("%d", sol);
	return 0;
}

#endif

// �м�����
#if 0
#include <stdio.h>
#define MAX (50000)
int N, u[MAX + 10], d[MAX + 10];
int main(void) {
	int i, j, t;
	scanf("%d", &N);
	for (i = 1; i < N; i++) {
		for (j = i + 1; j <= N; j++) {
			t = MAX * i / j;
			if (d[t] == 0) { u[t] = i; d[t] = j; }
		}
	}
	printf("0/1\n");
	for (i = 1; i < MAX; i++) {
		if (d[i] != 0) printf("%d/%d\n", u[i], d[i]);
	}
	printf("1/1\n");
	return 0;
}
#endif