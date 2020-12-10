#pragma warning (disable:4996)

#if 0

#include <stdio.h>
int main(void)
{
	return 0;
}

#endif
/////////////////////////////////////////////////////

//숨바꼭질
#if 0
#include <stdio.h>
#define SIZE (10000+1)
int data[SIZE];
int N, K;
struct st {
	int pos;
	int time;
};
struct st Queue[SIZE*SIZE];
int visit[SIZE];
int dir[] = { -1, 1, 2 };

int wp, rp;

void In_Queue(int pos, int time)
{
	Queue[wp].pos = pos;
	Queue[wp].time = time;
	wp++;
}

struct st Out_Queue(void)
{
	return Queue[rp++];
}

void BFS(int start, int stime)
{
	int i;
	struct st out = { 0 };

	wp = rp = 0;
	In_Queue(start, stime);
	visit[start] = 1;

	while (wp > rp)
	{
		out = Out_Queue();
		if (out.pos == K)
		{
			printf("%d\n", out.time);
			break;
		}

		if (out.pos < N) continue;
		for (i = 2; i >=0 ; i--)
		{
			if (dir[i] == 2)
			{
				if (visit[out.pos * 2] == 0)
				{
					visit[out.pos * 2] = 1;
					In_Queue(out.pos * 2, out.time + 1);
				}
			}
			else
			{
				if (visit[out.pos + dir[i]] == 0)
				{
					visit[out.pos + dir[i]] = 1;
					In_Queue(out.pos + dir[i], out.time + 1);
				}
			}
		}
	}
}

int main(void)
{
	scanf("%d %d", &N, &K);

	BFS(N, 0);

	return 0;
}

#endif

//BFS, DFS
#if 0
#include <stdio.h>
#define SIZE (1000+1)
int visit[SIZE];
int data[SIZE][SIZE];
int N, M, start;
int Queue[SIZE*SIZE];
int wp, rp;

void In_Queue(int data)
{
	Queue[wp++] = data;
}

int Out_Queue(void)
{
	return Queue[rp++];
}

void BFS(int start)
{
	int i, out = 0;

	wp = rp = 0;
	visit[start] = 1;
	printf("%d ", start);
	In_Queue(start);

	while (wp > rp)
	{
		out = Out_Queue();

		for (i = 1; i <= N; i++)
		{
			if (data[out][i] == 1 && visit[i] == 0)
			{
				visit[i] = 1;
				printf("%d ", i);
				In_Queue(i);
			}
		}
	}
}

void DFS(int start)
{
	int i;

	visit[start] = 1;
	printf("%d ", start);

	for (i = 1; i <= N; i++)
	{
		if (data[start][i] == 1 && visit[i] == 0)
		{
			visit[i] = 1;
			DFS(i);
		}
	}

}

void init(void)
{
	int i;
	for (i = 0; i < SIZE; i++)
	{
		visit[i] = 0;
	}
}

int main(void)
{
	int i;
	scanf("%d %d %d", &N, &M, &start);
	for (i = 0; i < M; i++)
	{
		int x, y;
		scanf("%d %d", &y, &x);
		data[y][x] = data[x][y] = 1;
	}

	DFS(start);
	printf("\n");
	init();
	BFS(start);
	printf("\n");
	return 0;
}

#endif

//정수 소수로 변환하기 
#if 0
#include <stdio.h>
#define SIZE (10000)
int check[SIZE + 2];
int p, q;

void init(void)
{
	int i;
	for (i = 0; i < SIZE + 2; i++)
	{
		check[i] = 0;
	}
}
int main(void)
{
	int tc, T;
	scanf("%d", &T);
	for (tc = 1; tc <= T; tc++)
	{
		init();
		scanf("%d %d", &p, &q);

		if ((p == 0 && q != 0) || (p >= q && p%q == 0))
		{
			printf("%d\n", p / q);
			continue;
		}

		printf("%d.", p / q);

		//소수부 찾기 
		int f, idx = 0;
		char str[100] = { 0 };
		p = p%q;
		while (p != 0)
		{
			p *= 10;
			f = p / q;
			check[f]++;
			if (check[f] > 1)
			{
				break;
			}
			str[idx++] = f + '0';
			p = p%q;
		}

		if (check[f] > 1)
		{
			int tidx = idx;
			while (str[tidx] - '0' != f && tidx >= 0 )
			{
				str[tidx] = str[tidx - 1];
				str[tidx - 1] = '0';
				tidx--;
			}
			str[tidx+1] = '(';
			str[idx + 1] = ')';
		}
		
		printf("%s\n", str);
	}
	return 0;
}
#endif

#if 0

#include <stdio.h>
int N;
void hanoi(int n, int s, int t, int e)
{
	if (n == 1)
	{
		printf("%d : %d -> %d\n", n, s, e);
		return;
	}
	hanoi(n - 1, s, e, t);
	printf("%d : %d -> %d\n", n, s, e);
	hanoi(n - 1, t, s, e);
}
int main(void)
{
	scanf("%d", &N);
	hanoi(N, 1, 2, 3);
	return 0;
}

#endif

//양팔저울
#if 0
#include <stdio.h>
#define CSIZE (12+2)
int chu[CSIZE];
int N;
int G, Gi;

int DFS(int n, int left, int right)
{
	if (n == N)
	{
		if (left == right) return 1;
		else return 0;
	}

	if (DFS(n + 1, left + chu[n], right) == 1) return 1;
	if (DFS(n + 1, left, right + chu[n] )== 1) return 1;
	if (DFS(n + 1, left, right) == 1) return 1;

	return 0;
}

int main(void)
{
	int i;
	scanf("%d", &N);
	for (i = 0; i < N; i++)
	{
		scanf("%d", &chu[i]);
	}
	scanf("%d", &G);
	for (i = 0; i < G; i++)
	{
		scanf("%d", &Gi);
		if (DFS(0, Gi, 0) == 1) printf("Y ");
		else printf("N ");
	}
	return 0;
}

#endif

//벽장문의이동
#if 0
#include <stdio.h>
#define SIZE (20+2)
int door[SIZE]; //사용할 벽장들의 순서의 길이 
int N; //벽장의 개수 
int open[2]; //초기에 열려있는 두개의 벽장
int len;  //사용할 벽장들의 순서의 길이
int sol;
#define abs(x) ( ( (x)<0) ? ( -(x) ) : (x)  )
void DFS(int n, int left, int right, int sum)
{
	if (n == len)
	{
		if (sol > sum) sol = sum;
		return;
	}

	if (sum >= sol) return; 
	DFS(n + 1, door[n], right, sum+abs(left-door[n]));
	DFS(n + 1, left, door[n], sum+abs(right-door[n]));
	//DFS(n + 1, left, right, sum);
}
int main(void)
{
	int i;
	scanf("%d %d %d %d", &N, &open[0], &open[1], &len);
	for (i = 0; i < len; i++)
	{
		scanf("%d", &door[i]);
	}

	sol = 0x7fff0000;
	DFS(0, open[0], open[1], 0);
	printf("%d\n", sol);
	return 0;
}

#endif

//보너스 
#if 0

#include <stdio.h>
#define SIZE (10+5)
int data[SIZE][SIZE];
int M, N;
int b[SIZE]; //
int s[SIZE]; //할당된 정답 보너스 금액 
int visit[SIZE]; //중복체크용

int temp[SIZE];

void mergeSort(int * Array, int size, int * Temp)
{
	if (size == 1) return;

	int ASize = size / 2;
	int BSize = size - ASize;

	mergeSort(Array, ASize, Temp);
	mergeSort(Array + ASize, BSize, Temp);

	int * A = Array;
	int * B = Array + ASize;
	int AIdx = 0, BIdx = 0, TIdx = 0;

	while (AIdx < ASize && BIdx < BSize)
	{
		if (A[AIdx] > B[BIdx])
		{
			Temp[TIdx] = A[AIdx];
			TIdx++, AIdx++;
		}
		else
		{
			Temp[TIdx] = B[BIdx];
			TIdx++, BIdx++;
		}
	}

	if (AIdx < ASize) Temp[TIdx++] = A[AIdx++];
	if (BIdx < BSize) Temp[TIdx++] = B[BIdx++];

	for (int i = 0; i < size; i++)
	{
		Array[i] = Temp[i];
	}
}

int check(int L, int bonus)
{
	for (int i = 2; i < L; i++)
	{
		if (data[i][L] == 1 && s[i] <= bonus) return 0;
		if (data[L][i] == 1 && s[i] >= bonus) return 0;
	}
	return 1;
}
int DFS(int depth)
{
	if (depth > N) return 1;

	for (int i = 2; i <= N; i++)
	{
		if (visit[i]==0  && check(depth, b[i])==1)
		{
			visit[i] = 1;
			s[depth] = b[i];
			if (DFS(depth + 1) == 1) return 1;
			visit[i] = 0;
			s[depth] = 0;
		}
	}

	return 0;
}

void print(void)
{
	for (int i = 1; i <= N; i++)
	{
		printf("%d ", s[i]);
	}
}

void sort(void)
{
	int i, j, t;
	for (i = 1; i < N; i++)
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
int main(void)
{
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= M; i++)
	{
		int x, y;
		scanf("%d %d", &y, &x);
		data[y][x] = 1;
	}
	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &b[i]);
	}
	
	visit[1] = 1;
//	mergeSort(b, N, temp);
	sort();
	s[1] = b[1];
	if (DFS(2) == 1) print();


	return 0;
}
#endif

//자동차경주대회
#if 01

#include <stdio.h>
#define SIZE (50+2)
int maxDist;
int N;
struct st {
	int time;
	int dist;
};
struct st PLACE[SIZE];
int minTime; //sol

void input(void)
{
	int i;
	scanf("%d", &maxDist);
	scanf("%d", &N);
	for (i = 0; i <= N; i++)
	{
		scanf("%d", &PLACE[i].dist);
	}
	for (i = 1; i <= N; i++)
	{
		scanf("%d", &PLACE[i].time);
	}
}

void DFS(int L, int sT, int sD)
{
	if (sT >= minTime) return;

	if (L == N + 1)
	{
		if (minTime > sT) minTime = sT;
		return;
	}

	if (sD + PLACE[L].dist <= maxDist)
	{//정비 안한다
		DFS(L + 1, sT, sD + PLACE[L].dist);
	}
	DFS(L + 1, sT + PLACE[L].time, PLACE[L].dist);

}

void output(void)
{
	printf("%d", minTime);
}
int main(void)
{
	input();
	minTime = 0x7fff0000;
	DFS(1, 0, PLACE[0].dist);
	output();
	return 0;
}
#endif