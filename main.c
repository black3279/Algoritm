#if 01
#include <stdio.h>
#include <string.h>
#define INF 0x7fff0000
typedef struct {
	int y;
	int x;
}location;

int my, mx;

char temp[60][60];
int map[60][60];
int temp_visit[60][60];
int dx[] = { 0, 1, 0, -1 };
int dy[] = { -1, 0, 1, 0 };
int min;


void P(void)
{
	int i, j;

	for (i = 1; i <= my; i++)
	{
		for (j = 1; j <= mx; j++)
		{
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void dot(int y, int x, int num)
{
	int i, j;
	int nx, ny;
	int wp, rp;
	location out;
	location que[3000] = { 0, };
	wp = rp = 0;

	que[wp].y = y;
	que[wp++].x = x;
	temp_visit[y][x] = 1;
	map[y][x] = num;
	while (wp > rp)
	{
		out = que[rp++];

		for (i = 0; i < 4; i++)
		{
			nx = out.x + dx[i];
			ny = out.y + dy[i];
			if (nx<1 || ny<1 || nx>mx || ny>my) continue;

			if (temp_visit[ny][nx] == 0 && temp[ny][nx] == 'X')
			{
				que[wp].y = ny;
				que[wp++].x = nx;
				temp_visit[ny][nx] = 1;
				map[ny][nx] = num;
			}
		}
	}
}

void init(void)
{
	int i, j;
	int num = 1;
	for (i = 1; i <= my; i++)
	{
		for (j = 1; j <= mx; j++)
		{
			if (temp_visit[i][j] == 0 && temp[i][j] == 'X')
			{
				dot(i, j, num);
				num++;
			}
		}
	}
}


void input(void)
{
	int i, j;
	scanf("%d %d", &my, &mx);

	for (i = 1; i <= my; i++)
	{
		for (j = 1; j <= mx; j++)
		{
			scanf(" %c", &temp[i][j]);
		}
	}
}



int BFS(int sy, int sx)
{
	int i, j;
	int di, dj;
	int nx, ny;
	int wp, rp;
	int visit[60][60] = { 0, };
	location out;
	location que[3000] = { 0, };

	wp = rp = 0;

	que[wp].y = sy;
	que[wp++].x = sx;
	visit[sy][sx] = 0;

	while (wp > rp)
	{
		out = que[rp++];

		for (i = 0; i < 4; i++)
		{
			nx = out.x + dx[i];
			ny = out.y + dy[i];

			if (nx<1 || ny<1 || nx>mx || ny>my) continue;

			if (map[ny][nx] == 2)
			{
				/*if (visit[out.y][out.x] == 2)
				{
				printf("visit = %d\n", visit[out.y][out.x]);
				for (di = 1; di <= my; di++)
				{
				for (dj = 1; dj <= mx; dj++)
				{
				visit[que[0].y][que[0].x] = 9;
				printf("%d ", visit[di][dj]);
				}
				printf("\n");
				}
				printf("\n");
				}*/
				return visit[out.y][out.x];
			}

			if (map[ny][nx] == 0 && visit[ny][nx] == 0)
			{
				que[wp].y = ny;
				que[wp++].x = nx;
				visit[ny][nx] = visit[out.y][out.x] + 1;
			}
		}
	}

	return INF;
}


void BFS_all(void)
{
	int i, j, k, nx, ny;
	int num;
	for (i = 1; i <= my; i++)
	{
		for (j = 1; j <= mx; j++)
		{
			if (map[i][j] == 1)
			{
				for (k = 0; k < 4; k++)
				{
					ny = i + dy[k];
					nx = j + dx[k];
					if (ny<1 || nx<1 || ny>my || nx>mx) continue;
					if (map[ny][nx] == 0)
					{
						num = BFS(i, j);

						if (num < min) min = num;
						break;
					}
				}
			}
		}
	}
}


int main(void)
{
	input();

	init();

	//P();

	min = INF;

	BFS_all();

	printf("%d", min);

	return 0;
}

#endif

