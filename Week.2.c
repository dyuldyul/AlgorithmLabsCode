#pragma warning (disable:4996)

#if 0
#include <stdio.h>
int main(void)
{
	return 0;
}
#endif

//DFS: 기본: 더하기(basic), 책꽂이, 농장 탈출
//순열: 기본: 건물세우기(basic), 주사위1, 보너스
//소비, 생산: 기업투자(basic)

/*
[문제유형]
FF:
둘레(
단지번호 붙이기 (좌표)
바이러스 (점수)

BFS
등산로
자외선 피해가기


DFS
조합
- 모든 경우
- R개 뽑기 (중복제거)
순열
- 모든 경우 (위치변환 표함)
- R개뽑기
생산/소비 (크리스마스트리)
- 꼭 포함
- 꼭 포함하지 않는다
그외
- 양팔저울
- 격자모양

*단방향/양방향 그래프의 인접행렬
*숫자 쪼개기 / 숫자 reverse
*상하관계 이해 (보너스, 해밀턴, 건물세우기)
인접행렬 - 참조표로 사용 - 보너스, 그래프, 건물세우기
인접행렬 - 연결된거 따라가기 용도 - 해밀턴, FF
*debugging: printList 활용하기

DFS에서의 주의할점:
- 중복 제거 방법
- int로 종료하기 방법 if(DFS() == 1) return 1;
- 가지치기 (최소값, 최대값, 똑같은 값)

배열 이용할 때:
- 가지치기
- 중복제거
- Lookup Table
- 정열
*/


//////////////////////////////마지막날시험////////////////////////////////////////////

//토마토
#if 0

#include <stdio.h>
#define MAX (100+10)
int a[MAX][MAX][MAX];
int tcnt; //토마토가 들어갈 수 있는 칸의 수
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

//꿀꿀이
#if 0
#include <stdio.h>
#define MAX (100+10)
char a[MAX][MAX]; //원본
int C[MAX][MAX]; //int로 받은 원본 - 일반꿀꿀이
int N;
int W[MAX][MAX]; //적색꿀꿀이

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
{//영역 찾은 걸 리턴 0: 찾기 실패, 1: 영역 찾기 성공
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
					C[ny][nx] = 0;//방문표시
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
					W[ny][nx] = 0;//방문표시
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
	int i, j, cb = 0, nor = 0; //cb: 적록색맹 꿀꿀, cn: 일반 꿀꿀
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

//[] 분수정렬
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

//[] 너비우선탐색
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
			//out한거와 같으면서 edge를 한번도 방문하지 않았으면 
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

//[j] [sol] 페이지전환
#if 0
#include <stdio.h>
#define MAX (500+10)
int N; //간선의 개수 
int V; //페이지 마지막 번호 vertex
int a[MAX][MAX];

int visit[MAX]; //연결된 간선을 저장 (정점 말고)
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
		{//인접행렬만큼 돈다
			//연결된 정점인데 아직 방문하지 않음 
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
//연속된 페이지가 아닐때 가정
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
			{//간선이면서 한번도 방문하지 않은거 
				visit[i] = visit[out] + 1;
				In_Queue(i);
			}
		}
	}

	for (i = 1; i <= V; i++)
	{
		sum += visit[i];
	}

	return (sum - V); //간선의 개수만큼 중복 더했으니까 뺀다

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

//[j] [my] 페이지전환
#if 0
#include <stdio.h>
#define MAX (500+5)
#define IMSIMAX (499)
int a[MAX][MAX];
int N, ARYN; //n: 정점 찾기용 for loop용
int list[MAX]; //각 depth별로 이동하는 횟수 list[1]부터 사용, 
float sol; // 전체 페이지 이동 평균 횟수 (소수 3자리)
int lnum;
void input(void)
{
	int i, j, start, end, t;
	scanf("%d", &N);
	for (i = 1; i <= N; i++)
	{
		scanf("%d %d", &start, &end);
		a[start][end] = 1; //정점으로 이어준다.
		t = (start < end) ? (end) : (start);
		ARYN = (t > ARYN) ? t : ARYN;
	}

	//정점으로 안 이어진 것은 최대값을 초기화한다
	for (i = 1; i <= ARYN; i++)
	{
		for (j = 1; j <= ARYN; j++)
		{
			if (!a[i][j])a[i][j] = IMSIMAX;
		}
	}
}

void find(void)
{//플로이드 알고리즘
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

//[] [sol]현진이의 농장
#if 0
#include <stdio.h>
#define MAX (5+1)

int a[MAX][MAX];
int K; //바위의 개수
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
		a[y][x] = 99; // 나무 위치 표시
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
	//{//나무를 다 안 심었는데 도착점에 온 경우
	//	return;
	//}

	for (i = 0; i < 4; i++)
	{
		ny = sy + dy[i];
		nx = sx + dx[i];

		if (ny < 1 || nx < 1 || ny > 5 || nx > 5) continue;

		if (a[ny][nx] == 0)
		{
			a[ny][nx] = L+1; //방문했다는 표시가 아니라, depth 표시
			DFS(L + 1, ny, nx);
			a[ny][nx] = 0;
		}
	}
}

int main(void)
{
	input();
	//나무를 심고 시작한다. 
	a[1][1] = 1; //시작점에 나무를 심는다. 
	DFS(2, 1, 1);//DFS(1, 1, 1); 
	printf("%d", sol);
	return 0;
}
#endif

//[] [my] 계단 오르기(BASIC)
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

//그래프칠하기, 최고의수식을 찾아라
//안전영역, 너비우선탐색
//양팔저울, 벽장문, 현진이의 농장, 계단오르기 - DFS

//계단오르기
//참고: http://blog.naver.com/PostView.nhn?blogId=occidere&logNo=220788947949

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

//[j] [my] 페이지전환
#if 0
#include <stdio.h>
#define MAX (500+5)
#define IMSIMAX (499)
int a[MAX][MAX];
int N, ARYN; //n: 정점 찾기용 for loop용
int list[MAX]; //각 depth별로 이동하는 횟수 list[1]부터 사용, 
float sol; // 전체 페이지 이동 평균 횟수 (소수 3자리)
int lnum;
void input(void)
{
	int i, j, start, end, t;
	scanf("%d", &N);
	for (i = 1; i <= N; i++)
	{
		scanf("%d %d", &start, &end);
		a[start][end] = 1; //정점으로 이어준다.
		t = (start < end) ? (end) : (start);
		ARYN = (t > ARYN) ? t : ARYN;
	}

	//정점으로 안 이어진 것은 최대값을 초기화한다
	for (i = 1; i <= ARYN; i++)
	{
		for (j = 1; j <= ARYN; j++)
		{
			if (!a[i][j])a[i][j] = IMSIMAX;
		}
	}
}

void find(void)
{//플로이드 알고리즘
	int i, j, k;
	for (k = 1; k <= ARYN; k++)
	{
		for (i = 1; i <= ARYN; i++)
		{
			for (j = 1; j <= ARYN; j++)
			{
				if (a[i][j] > a[i][k] + a[k][j]) a[i][j] = a[i][k] + a[k][j];
				//양방향이면 a[j][i] = a[i][j]; 를 추가하면 된다
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

//[] [my] 안전 영역
#if 0
#include <stdio.h>
#define MAX (100+10)
int N;
int map[MAX][MAX]; 
//int safe[MAX][MAX];
int sol; //안전한 영역의 최대 개수 ->0으로 초기화해서 최대개수를 만날때 변경한다
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

//도착점: while(wp>rp)
//연결점: 
//방문표시: if(visit[][] > 0  && visit[][] <=rain ) visit[][] = 0;

//원본을 복사 받아. 침수되면 0으로 해서 방문표시도 할 겸
//for문을 돌면서 여기서 

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

//[]양팔저울(BASIC)
#if 0
#include <stdio.h>
#define MAX (12+10)
int a[MAX]; //추의 무게를 저장
int N; //추의 개수 
int gCnt; //확인해야되는 구슬의 개수 
int G; // 확인해야되는 구슬의 무게

int sol;
int list[MAX]; // 0: 안 올린다. 1: 왼쪽에 올린다, 2: 오른쪽에 올린다
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
	//성공조건
	if (lS == rS) return 1;

	//종료조건
	if (L > N) return 0;

	//왼쪽에 추를 올린다 
	list[L] = 1;
	if (DFS(L + 1, lS + a[L], rS) == 1)
	{
		return 1;
	}
	//오른쪽에 추를 올린다
	list[L] = 2;
	if (DFS(L + 1, lS, rS + a[L]) == 1)
	{
		return 1;
	}
	//추를 올리지 않는다
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
		scanf("%d", &G); //구슬의 무게 확인해라
		sol = DFS(1, G, 0); //구슬을 왼쪽에 줘도 되고 오른쪽에 줘도 된다
		printf("%c ", msg[sol]);
	}
	return 0;
}
#endif


//*******170513 기출, 합, N개 중 R개를 뽑는, 돌다리 참조


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
	for (i = s; i <= (N - M + L); i++) {    //N 개중 M 개를 뽑는 경우 ; N-M+L
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



//*******[] 최고의 수식을 구하라

//getValue()로 구할때
#if 0
#include <stdio.h>
#define MAX (10+5)
int N;
int a[] = { 1, 2, 4, 8, 16, 32, 64, 128 };
int sol;
int W[MAX]; //4개 이하 사용시 가치
int V[MAX]; //5개 이상 사용시 가치
int A; //항 하나당 추가가치

int list[MAX];
int cnt;
int best[MAX]; //최고의 수식을 담는 배열이며, 최고의 상태가 갱신되기 때문 

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
	int value = 0; //누적변수 초기화
	for (i = 0; i < L; i++)//사용한 제곱수의 범위
	{
		//사용된 2의 제곱수 항의 가치 합계
		value += list[i] * ((list[i]<5) ? (W[i]) : (V[i])); //삼항 연산자 쓸떄는 전체적 괄호 필요!
		//항의 수 * 항의 가치

		//항 하나당 추가가치 
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
		int value = getValue(L); //R==0일때만 잠깐 써서 버리는게 나음. 밖에서 선언하는거보다
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
		//0 0 0 과 같이 사용되는 경우에도 종료가 되어야 하므로 
		//6 0 0 과 같은 경우도 종료
		//printList(L);
		return;
	}
	if (a[L] > N) //0 0 0 과 같이 사용되는 경우에도 종료가 되어야 하므로 
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
		sol = 0; //min값으로 초기화
		DFS(0, N);
		output();
	}
	return 0;
}
#endif

//S을 인수로 넘길때
#if 0
#include <stdio.h>
#define MAX (10+5)
int N;
int a[] = { 1, 2, 4, 8, 16, 32, 64, 128 };
int sol;
int W[MAX]; //4개 이하 사용시 가치
int V[MAX]; //5개 이상 사용시 가치
int A; //항 하나당 추가가치
int S;
int list[MAX];
int cnt;
int best[MAX]; //최고의 수식을 담는 배열이며, 최고의 상태가 갱신되기 때문 

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
		//0 0 0 과 같이 사용되는 경우에도 종료가 되어야 하므로 
		//6 0 0 과 같은 경우도 종료
		//printList(L);
		return;
	}
	if (a[L] > N) //0 0 0 과 같이 사용되는 경우에도 종료가 되어야 하므로 
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
		sol = 0; //min값으로 초기화
		DFS(0, N, S);
		output();
	}
	return 0;
}
#endif

//*******




//[f] 그래프칠하기
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
		//나와 인접한 애인데 색상이 같을 때
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
	{//색상 번호까지
		if (check(L, i) == 1)
		{
			list[L] = i;
			if (DFS(L + 1) == 1) return 1; //색 모두 배정 완료후 다시 색 배정 하면 안되므로, 그렇지 않으면 다시 색 배정
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
	{//색상번호 리스트를 출력한다
		for (i = 1; i <= N; i++)
		{
			printf("%d ", list[i]);
		}
	}
	return 0;
}
#endif



//////////////////////////Day 7후 과제 //////////////////////

//주사위던지기2
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
{//L: depth, S: 그 전 단계에서의 총 합
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

// 기업 투자
#if 0
#include <stdio.h>
#define MAXN (7+5)
#define MAXM (30+5)
int N, M;
int a[MAXN][MAXM];
int best[MAXN];
int sol;  // 투자이익금 최대

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
// L : 기업번호, S : 투자 이익금 누적, R : 남은 투자금액
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
	sol = 0; // 최소 값으로 초기화 필요 (최대값 구하는 것)
	DFS(1, 0, M);
	output();
	return 0;
}
#endif

//주사위 던지기 1
#if 0
#include <stdio.h>
#define MAX (6)
#define NMAX (MAX+5) 
int N, M;
int list[NMAX]; //list가 MAX크기면 안되고 더 커야됨!
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

//[] 돌다리 건너기(BASIC)

//depth - 두루마리
#if 0
#include <stdio.h>
#define MAXR (10+5)
#define MAXB (30+5)

char B[2][MAXB]; //B[0]: 악마, B[1]: 천사
char R[MAXR];
int bLen, rLen;
int sol;

void input(void)
{
	scanf("%s", &R[0]);			//scanf("%s", R); scanf("%s", B[0]), scanf("%s", B[1]);
	scanf("%s", &B[0][0]); //악마
	scanf("%s", &B[1][0]); //천사

	for (bLen = 0; B[0][bLen] > 0; bLen++); //bridge의 문자열 개수 세기
	for (rLen = 0; R[rLen] > 0; rLen++); //

}

void DFS(int L, int start, int da) //da: 천사 또는 악마의 길인지
{
	int i;

	if (L >= rLen)
	{//다 찾아서 도착점까지 온 경우, 
		//DFS를 계속 수행하는 건 그 전 단계에서 두루마리 글자를 찾았기 때문에
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
	//악마에서 시작
	DFS(0, 0, 0);
	//천사에서 시작
	DFS(0, 0, 1);
	printf("%d", sol);
	return 0;
}
#endif


//*******[h] 파이프 제거 FF - BFS, DFS 둘다 ok

//DFS
#if 0

#include <stdio.h>
#define MAX (10+5)
int N;
int a[MAX][MAX]; // 0 ~ 11 (A: 10, B: 11)
int sy, sx; //시작좌표
int T[][4] = {
	{ 0, 0, 0, 0 },	//0, (0: 갈수없는길, 1: 갈수있는길)
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
}; //비트연산으로 하면 필요없음

int D[] = { 1, 0, 3, 2 };
int pipe;
int sol;

int visit[MAX][MAX];

int dy[] = { -1, 1, 0, 0 }; //lookup table과 똑같이 해야됨, lookup 이 상하좌우 순으로 만들었기 때문에
int dx[] = { 0, 0, -1, 1 };


void DFS(int sy, int sx)
{
	int i, ny, nx;
	int cur, next;

	visit[sy][sx] = 1;
	pipe--;
	cur = a[sy][sx]; //성능상 도움이 됨
	for (i = 0; i < 4; i++)
	{
		ny = sy + dy[i];
		nx = sx + dx[i];

		if (ny<0 || nx<0 || ny >= N || nx >= N || visit[ny][nx] == 1) continue;

		next = a[ny][nx]; //굳이 없어도 됨

		if (T[cur][i] == 1 && T[next][D[i]] == 1)
		{//나도 갈 수 있고 인접한 녀석도 갈 수 있는 길이면 -> 연결되어있는거!
			//visit[ny][nx] = 1;
			//pipe--;
			//DFS 처음 들어올 때 위에서 해주기 때문에 여기서는 필요없어
			DFS(ny, nx);

		}
	}
}

void input(void)
{
	int i, j;
	char tmp[MAX] = { 0 };

	pipe = 0; //파이프 초기화, tc 여러개일때
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
//사용되지 않은 파이프 수 출력: 
// 토마토처럼 처음에 파이프 개수 셌다가 찾을때마다 빼는 방법
// 나중에 for문으로 파이프 개수 세는 방법

int main(void)
{
	input();
	DFS(sy, sx);
	printf("%d", pipe);
	init(); //visit 배열 초기화, TC 많은 경우
	return 0;
}

#endif

//BFS
#if 0

#include <stdio.h>
#define MAX (10+5)
int N;
int a[MAX][MAX]; // 0 ~ 11 (A: 10, B: 11)
int sy, sx; //시작좌표
int T[][4] = {
	{ 0, 0, 0, 0 },	//0, (0: 갈수없는길, 1: 갈수있는길)
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
}; //비트연산으로 하면 필요없음

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

int dy[] = { -1, 1, 0, 0 }; //lookup table과 똑같이 해야됨, lookup 이 상하좌우 순으로 만들었기 때문에
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
		cur = a[out.y][out.x]; //성능상 도움이 됨
		for (i = 0; i < 4; i++)
		{
			ny = out.y + dy[i];
			nx = out.x + dx[i];

			if (ny < 0 || nx < 0 || ny >= N || nx >= N || visit[ny][nx] == 1)
				continue;
			next = a[ny][nx]; //굳이 없어도 됨

			if (T[cur][i] == 1 && T[next][D[i]] == 1)
			{//나도 갈 수 있고 인접한 녀석도 갈 수 있는 길이면 -> 연결되어있는거!
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

	pipe = 0; //파이프 초기화, tc 여러개일때
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

//사용되지 않은 파이프 수 출력: 
// 토마토처럼 처음에 파이프 개수 셌다가 찾을때마다 빼는 방법
// 나중에 for문으로 파이프 개수 세는 방법

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


//*******기출유형_170318

////[sol]
#if 0
#include <stdio.h>
#define MAX (12+5)

int a[MAX];
int cnt;
int list[MAX];
int check[MAX * 100];
int N, K; //K가 몇번째 숫자인지 찾아라
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
		sum += a[i]; //합의 최대수, 나중에 K가 몇번째인지 구할 수 있는 시작 위치가 된다, 1번째
	}

	//가지치기용
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
{//K가 몇번째인지 구하는 함수
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
	//가지치기 - S + 앞으로 나올 모든 수의 합 < K 면 return;
	//앞으로 모든 수의 합은 배열로 미리 입력받는다
	if ((S + s[L])< K) return;

	if (L > N)
	{
		printList(L, S);
		check[S]++;
		return;
	}

	list[L] = 1; //덧셈에 쓴다 
	DFS(L + 1, S + a[L]);
	list[L] = 0; //덧셈에 안 쓴다 
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

////[my] -> K의 포지션을 구하는 함수를 따로 만들어서 다시 해보기, 가지치기 다시
#if 0
#include <stdio.h>
#define MAX (12+5)

int a[MAX];
int cnt;
int list[MAX];
int sum[MAX * 100];
int N, K; //K가 몇번째 숫자인지 찾아라
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

	list[L] = 1; //덧셈에 쓴다 
	DFS(L + 1, S + a[L]);
	list[L] = 0; //덧셈에 안 쓴다 
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

//농장탈출 - DFS
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
{//L: 소 번호, C: 배에 탄 소의 수, S: 배에 탄 소의 무게의 합

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

	if (check(S, a[L]) == 1) //가벼운 소
	{//태운다
		list[L] = 1; //무게를 써도 됨, 여기서는 탔다안탔다
		DFS(L + 1, C + 1, S + a[L]);
	}
	//태우지 않는다
	list[L] = 0;
	DFS(L + 1, C, S);
}
int main(void)
{
	input();
	sol = 0; //sol에는 max값을 저장할 것이므로 최소값 0으로 초기화
	DFS(1, 0, 0);
	printf("%d", sol);
	return 0;
}
#endif

//등산로 찾기 [과제 제출 성공, BFS sol 풀이 최적화]
#if  0

#include <stdio.h>

#define MAX (100+10)
int a[MAX][MAX];
int power[MAX][MAX];
int N;
int top_y, top_x; //정상
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
	////0 0 0 과 같이 사용되는 경우에도 종료가 되어야 하므로 
	////6 0 0 과 같은 경우도 종료
	//	printList(L);
	//	return;
	//}
	if (a[L] > N) //0 0 0 과 같이 사용되는 경우에도 종료가 되어야 하므로 
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

//[순열] N Queen, DFS 원리
#if 0
#include <stdio.h>
#define MAX (13+5)
int N;
int col[MAX];
int d1[MAX * 3];//넉넉하게
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


//[생산, 소비] 기업투자 basic DFS. 생산 소비

//[순열] 보너스 DFS, 순열
#if 01
#include <stdio.h>
#define MAX (10+5)
int N;
int a[MAX][MAX]; //(행)상급자-(열)하급자 배열
int b[MAX]; //보너스 금액
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
	for (i = 1; i <= 1; i++) //가장 큰 것만 한 번 찾을 때
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
		scanf("%d %d", &y, &x); // y: 상급자, x: 하급자
		a[y][x] = 1; //인접행렬 (행: 상급자, 열: 하급자) 
	}
	for (i = 1; i <= N; i++)
	{
		scanf("%d", &b[i]);
	}
}

int check(int L, int bonus)
{//나보다 전 사람들이 상급자인지 하급자인지 판단
	int i;
	for (i = 2; i < L; i++)//i는 이미 보너스를 받은 직원
	{
		if (a[i][L] == 1 && list[i] <= bonus) return 0; // i는 상급자 && 내가 상급자보다 보너스가 많을 때 위배되는 조건
		if (a[L][i] == 1 && list[i] >= bonus) return 0; // i는 하급자 && 내가 하급자보다 보너스가 적을 때 위배
	}
	return 1;
}

//각 직원에게 적합한 보너스를 부여한다. 보너스를 다 받으면 종료한다
//중복되면 안되니까 visit[] 
//중복 없는 순열
int DFS(int L)
{
	int i;

	if (L > N)
	{

		return 1; //모든 직원들이 보너스를 잘 받은거여서
	}


	for (i = 2; i <= N; i++) //사장님은 제외
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
	return 0; //보너스 할당 실패
}


int main(void)
{
	int ret, i;
	input();
	sort();
	list[1] = b[1]; //사장님 보너스 할당
	ret = DFS(2); // 사장님 제외하고

	//이 문제는 필요없지만, 시험에서는 실패/성공할 경우에 대해서 결과 찍으라고 할 가능성 있음
	//best[]이 필요없는 이유는 한번만 하고 끝내면 되니깐
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

//[Y] 자동차경주대회 Basic DFS
#if 0
#include <stdio.h>
#define MAX (50+5)
int K, N;
int t[MAX];
int d[MAX];
int sol; //최소 정비 시간

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

//들린 정비소 개수 (인수 사용 가능, 나중에 카운팅)
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
	{//정비 안 받아도 되니까 
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

//[Z] 보물섬 BFS
#if 0

//입력: char a[MAX][MAX]; int b[MAX][MAX] => BFS로 사용할 배열
//시작점: a[i][j] == 'L'
//도착점: while(wp>rp){} 까지 계속 loop
//연결점: b[ny][nx] == 0 ('L')
//방문표시: b[sy][sx] = 1; b[ny][nx] = b[out.y][out.x]+1;
//큐의 크기: struct st Queue[MAX*MAX] (한번씩만 들어가며 되니까)

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
//1. 전체 데이터 print
//2. InQueue 또는 OutQueue 지점 print

//[T] 치즈 FF BFS

//입력: int a[MAX][MAX]; %d, 1,1~Y,X (0,0~Y-1, X-1)
//시작점: 0,0 / 1,1 //모두 가능 (둘레가 데이터에 포함되어 있어서)
//도착점: while(wp>rp) {}
//연결점: a[ny][nx] == 0
//		a[ny][nx] = 1; //치즈 
//방문표시: 연결점 = 2, 치즈 = 3
//1시간 뒤 init() 한다 (2,3을 0으로 변경)
//공기의 면적이 넓을 경우 depth가 깊어지기 때문에 DFS보다는 BFS가 안전함

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
//큐의 크기: 
// 1) 정점이 숫자 ( Queue[MAX];
// 2) 정점이 좌표 ( Queue[MAX*MAX];
// 3) 하나의 정점을 여러번 방문할 수 있을 때 - 정점의 최대수*MAX
// - 정점이 숫자: MAX*MAX , 정점이 좌표: MAX*MAX*MAX

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

//시간마다 한번씩 수행
int FF_BFS(int sy, int sx)
{
	int i, ny, nx;
	struct st out;
	int c_cnt = 0; //치즈의 개수

	wp = rp = 0;
	a[sy][sx] = 2; // 공기의 방문표시
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
