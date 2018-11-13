#if 01
#include <stdio.h>
#include <string.h>
int N;
int dx[] = { 0, 1, 0, -1 };
int dy[] = { -1, 0, 1, 0 };
int map[25][25];
int init_map[25][25];
int dir[6];
int max;
int cnt;

void P(void)
{
	int i, j;

	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void Move(int direc)
{
	int i, j, ny, nx, sx, sy;
	int num;
	int visit[25][25] = { 0, };

	if (direc == 0)
	{
		for (i = 2; i <= N; i++)
		{
			for (j = 1; j <= N; j++)
			{
				if (map[i][j])
				{

					num = map[i][j];
					ny = i;
					nx = j;
					for (;;)
					{
						sy = ny;
						sx = nx;
						nx = sx + dx[direc];
						ny = sy + dy[direc];

						if (ny == 1 && map[ny][nx] == 0)
						{
							map[i][j] = 0;
							map[ny][nx] = num;

							break;
						}

						if (map[ny][nx] == 0) continue;

						if (map[ny][nx] != num || (map[ny][nx] == num && visit[ny][nx] == 1))
						{
							map[i][j] = 0;
							map[sy][sx] = num;

							break;
						}

						if (map[ny][nx] == num && visit[ny][nx] == 0)
						{
							map[i][j] = 0;
							visit[ny][nx] = 1;
							map[ny][nx] = 2 * map[ny][nx];
							if (2 * num > max) max = 2 * num;
							break;
						}

					}
				}
			}
		}
	}

	if (direc == 1)
	{
		for (j = N - 1; j >= 1; j--)
		{
			for (i = 1; i <= N; i++)
			{
				if (map[i][j] != 0)
				{
					num = map[i][j];
					ny = i;
					nx = j;
					for (;;)
					{
						sy = ny;
						sx = nx;
						nx = nx + dx[direc];
						ny = ny + dy[direc];
						if (nx == N && map[ny][nx] == 0)
						{
							map[i][j] = 0;
							map[ny][nx] = num;
							break;
						}

						if (map[ny][nx] == 0) continue;

						if (map[ny][nx] != num || (map[ny][nx] == num && visit[ny][nx] == 1))
						{
							map[i][j] = 0;
							map[sy][sx] = num;
							break;
						}


						if (map[ny][nx] == num && visit[ny][nx] == 0)
						{
							map[i][j] = 0;
							visit[ny][nx] = 1;
							map[ny][nx] = 2 * map[ny][nx];
							if (2 * num > max) max = 2 * num;
							break;
						}

					}
				}
			}
		}
	}

	if (direc == 2)
	{
		for (i = N - 1; i >= 1; i--)
		{
			for (j = 1; j <= N; j++)
			{
				if (map[i][j])
				{
					num = map[i][j];
					ny = i;
					nx = j;
					for (;;)
					{
						sy = ny;
						sx = nx;
						nx = sx + dx[direc];
						ny = sy + dy[direc];

						if (ny == N && map[ny][nx] == 0)
						{
							map[i][j] = 0;
							map[ny][nx] = num;

							break;
						}

						if (map[ny][nx] == 0) continue;

						if (map[ny][nx] != num || (map[ny][nx] == num && visit[ny][nx] == 1))
						{
							map[i][j] = 0;
							map[sy][sx] = num;

							break;
						}


						if (map[ny][nx] == num && visit[ny][nx] == 0)
						{
							map[i][j] = 0;
							visit[ny][nx] = 1;
							map[ny][nx] = 2 * map[ny][nx];
							if (2 * num > max) max = 2 * num;
							break;
						}

					}
				}
			}
		}
	}

	if (direc == 3)
	{
		for (j = 2; j <= N; j++)
		{
			for (i = 1; i <= N; i++)
			{
				if (map[i][j])
				{
					num = map[i][j];
					ny = i;
					nx = j;
					for (;;)
					{

						sy = ny;
						sx = nx;
						nx = sx + dx[direc];
						ny = sy + dy[direc];

						if (nx == 1 && map[ny][nx] == 0)
						{
							map[i][j] = 0;
							map[ny][nx] = num;

							break;
						}


						if (map[ny][nx] == 0) continue;

						if (map[ny][nx] != num || (map[ny][nx] == num && visit[ny][nx] == 1))
						{
							map[i][j] = 0;
							map[sy][sx] = num;

							break;
						}

						if (map[ny][nx] == num && visit[ny][nx] == 0)
						{
							visit[ny][nx] = 1;
							map[i][j] = 0;
							map[ny][nx] = 2 * map[ny][nx];
							if (2 * num > max) max = 2 * num;

							break;
						}

					}
				}
			}
		}
	}
}


void DFS(int L)
{
	int i;
	if (L == 6)
	{
		memcpy(map, init_map, sizeof(map));
		for (i = 1; i <= 5; i++)
		{
			Move(dir[i]);
		}
		return;
	}

	for (i = 0; i < 4; i++)
	{
		dir[L] = i;
		DFS(L + 1);
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
			scanf("%d", &init_map[i][j]);
			if (init_map[i][j] > max) max = init_map[i][j];
		}
	}
}



int main(void)
{
	max = -1;
	input();

	DFS(1);
	/*memcpy(map, init_map, sizeof(map));
	P();
	Move(2);
	P();
	Move(2);
	P();
	Move(3);
	P();*/
	printf("%d", max);

	return 0;
}


#endif
