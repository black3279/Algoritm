#if 01
#include <stdio.h>
#include <string.h>
#define INF 0x7fff0000

int mx, M, my;
int radder[40][20];
int min;
int flag;

void input(void)
{
	int i, j;
	int a, b;
	scanf("%d %d %d", &mx, &M, &my);

	for (i = 1; i <= M; i++)
	{
		scanf("%d %d", &a, &b);
		radder[a][b] = 1;
	}
}

int check_sol(void)
{
	int i, j;
	int num;
	for (i = 1; i <= mx; i++)
	{
		num = i;
		for (j = 1; j <= my; j++)
		{
			if (radder[j][num])
			{
				num = num + 1;
				continue;
			}
			if (radder[j][num - 1])
			{
				num = num - 1;
				continue;
			}
		}
		if (num != i) return 0;
	}
	return 1;
}

void DFS(int L, int y, int x, int cnt)
{
	if (flag) return;

	if (y>my)
	{
		y = 1;
		x = x + 1;
	}

	if (L == cnt)
	{
		if (check_sol()) flag = 1;
		return;
	}

	if (x >= mx) return;

	if (radder[y][x - 1] == 0 && radder[y][x] == 0)
	{
		radder[y][x] = 1;
		DFS(L + 1, y + 1, x, cnt);
		radder[y][x] = 0;
	}

	DFS(L, y + 1, x, cnt);
}

int DFS_all(void)
{
	int cnt = 1;

	while (cnt <= 3)
	{
		DFS(0, 1, 1, cnt);
		if (flag) break;
		cnt++;
	}

	if (flag)
	{
		return cnt;
	}

	return -1;
}




int main(void)
{
	input();
	min = INF;


	if (check_sol())
	{
		printf("0\n");
		return 0;
	}

	printf("%d\n", DFS_all());


	return 0;
}


#endif