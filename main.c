#if 01
#include <stdio.h>
#include <string.h>

int visit[1010];
int one[1010][31];
int que[1010];
int wp, rp;
int start, end;
int N, K;


int abs(int num)
{
	return (num>0) ? num : -num;
}


void BFS(void)
{
	int out, i, j;
	int cnt = 0;
	wp = rp = 0;

	que[wp++] = start;
	visit[start] = -1;

	while (wp>rp)
	{
		out = que[rp++];

		for (i = 1; i <= N; i++)
		{
			if (visit[i] != 0 || out == i) continue;
			cnt = 0;

			for (j = 1; j <= K; j++)
			{
				if (one[out][j] != one[i][j]) cnt++;
				if (cnt == 2) break;
			}

			if (cnt == 1)
			{
				visit[i] = out;
				if (i == end) return;
				que[wp++] = i;
			}
		}
	}

}

void input(void)
{
	int i, j;
	int temp;
	scanf("%d %d", &N, &K);

	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= K; j++)
		{
			scanf("%1d", &one[i][j]);
		}
	}

	scanf("%d %d", &start, &end);
}

int main(void)
{
	int i = 0;
	int cnt = 1;
	int best[1010];

	input();

	BFS();

	if (visit[end] == 0)
	{
		printf("-1");
		return 0;
	}

	best[i] = end;

	for (;;)
	{
		if (visit[best[i]] == -1) break;
		best[cnt++] = visit[best[i++]];
	}
	for (i; i >= 0; i--) printf("%d ", best[i]);

	return 0;
}

#endif