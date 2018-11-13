#if 01
#include <stdio.h>
#include <string.h>

typedef struct {
	int y;
	int x;
}location;


location que[110 * 110 * 200];
int wp, rp;
int H_max, H_min;
int N;
int map[110][110];
int max;
int dx[] = { 0, 1, 0, -1 };
int dy[] = { -1, 0, 1, 0 };

void input(void)
{
	int i, j;
	int num;
	scanf("%d", &N);

	H_max = -1;
	H_min = 1000000000;

	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			scanf("%d", &map[i][j]);
			num = map[i][j];
			if (num > H_max) H_max = num;
			if (num < H_min) H_min = num;
		}
	}

	H_max++;
	H_min--;
}

int BFS(int sy, int sx, int height)
{
	int i, j, nx, ny;
	location out;
	que[wp].y = sy;
	que[wp++].x = sx;
	map[sy][sx]--;
	while (wp > rp)
	{
		out = que[rp++];

		for (i = 0; i < 4; i++)
		{
			nx = out.x + dx[i];
			ny = out.y + dy[i];
			if (map[ny][nx] == height)
			{
				que[wp].y = ny;
				que[wp++].x = nx;
				map[ny][nx]--;

			}
		}
	}

	return 1;
}

void BFS_all(void)
{
	int i, j, k;
	int sum = 0;

	for (k = H_max; k > H_min; k--)
	{
		sum = 0;
		for (i = 1; i <= N; i++)
		{
			for (j = 1; j <= N; j++)
			{
				if (map[i][j] == k) sum += BFS(i, j, k);
			}
		}
		if (sum > max) max = sum;
	}
}



int main(void)
{
	input();
	max = -1;

	BFS_all();

	printf("%d", max);


	return 0;
}

#endif
