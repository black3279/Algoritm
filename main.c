#if 01
#include <stdio.h>
#define INF 0x7fff0000
int N, cost[13][13];
int min;
int visit[13];

void DFS(int L, int start, int sum)
{
	int i;
	if (sum >= min) return;
	if (L == N)
	{
		if (cost[start][1] == 0) return;
		if (sum + cost[start][1] < min) min = sum + cost[start][1];
		return;
	}

	for (i = 2; i <= N; i++)
	{
		if (visit[i] == 0 && cost[start][i]>0)
		{
			visit[i] = 1;
			DFS(L + 1, i, sum + cost[start][i]);
			visit[i] = 0;
		}
	}

}


void input(void)
{
	int i, j;
	scanf("%d", &N);

	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			scanf("%d", &cost[i][j]);
		}
	}
}


int main(void)
{
	input();
	min = INF;
	visit[1] = 1;
	DFS(1, 1, 0);

	if (min != INF)printf("%d\n", min);
	else printf("0\n");
	return 0;
}
#endif


