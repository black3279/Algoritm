#if 01
#include <stdio.h>
#include <string.h>
#define INF 0x7fff0000
typedef struct {
	int idx;
	int rank;
}info;

info num[1000];
int cnt;

int N, M;

void input(void)
{
	int i;
	scanf("%d %d", &N, &M);
	for (i = 0; i < N; i++)
	{
		scanf("%d", &num[i].rank);
		num[i].idx = i;
	}
}

void move_forward(void)
{
	int i;
	info nul = { 0, };
	for (i = 1; num[i].rank; i++)
	{
		num[i - 1] = num[i];
		num[i] = nul;
	}
	return;
}

int find_end(void)
{
	int i, j;

	for (i = 0; num[i].rank; i++);

	return i;
}

int go_print(void)
{
	int i, j;
	int max;
	int max_idx;
	info temp;
	info nul = { 0, };
	int now;
	for (;;)
	{
		max = -1;
		for (j = 0; num[j].rank; j++)
		{
			if (num[j].rank > max)
			{
				max = num[j].rank;
				max_idx = j;
			}
		}

		if (max_idx != 0)
		{
			temp = num[0];
			move_forward();
			num[find_end()] = temp;
			continue;
		}
		if (max_idx == 0)
		{
			if (num[0].idx == M) return cnt;
			else
			{
				num[0] = nul;
				cnt++;
				move_forward();
			}
		}
	}
}


int main(void)
{
	int T, tc;
	int sol;
	scanf("%d", &T);

	for (tc = 1; tc <= T; tc++)
	{
		cnt = 1;
		memset(num, 0, sizeof(num));
		input();
		sol = go_print();

		printf("%d\n", sol);
	}

	return 0;
}

#endif