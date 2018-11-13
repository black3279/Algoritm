#if 01
#include <stdio.h>
#include <string.h>

typedef struct {
	int y;
	int x;
	int dir; // dir 은 0이 가로 1이 세로
}info;

info que[1000000];

info start;
info end; // 큐도 만들기
int N;
char map[60][60];
int visit[2][60][60];
int wp, rp;

int dx[] = { 0, 1, 0, -1 };
int dy[] = { -1, 0, 1, 0 };

void map_P(void)
{
	int i, j;
	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			printf("%c ", map[i][j]);
		}
		printf("\n");
	}
	printf("\n");

}

void P(void)
{
	int i, j;

	printf("visit[0]\n");
	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			printf("%2d ", visit[0][i][j]);
		}
		printf("\n");
	}
	printf("\n");

	printf("visit[1]\n");
	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			printf("%2d ", visit[1][i][j]);
		}
		printf("\n");
	}
	printf("\n");

}

int BFS(void)
{
	info out;
	int nx, ny, i, direc;
	wp = rp = 0;

	que[wp].y = start.y;
	que[wp].x = start.x;
	que[wp++].dir = start.dir;
	visit[start.dir][start.y][start.x] = 1;


	while (wp > rp)
	{
		out = que[rp++];
		direc = out.dir;
		if (out.x == end.x && out.y == end.y && direc == end.dir) return visit[out.dir][out.y][out.x] - 1;

		for (i = 0; i < 4; i++)
		{
			nx = out.x + dx[i];
			ny = out.y + dy[i];

			if (nx<1 || nx>N || ny<1 || ny>N) continue;

			if (nx == end.x && ny == end.y && direc == end.dir) return visit[out.dir][out.y][out.x];

			if (direc == 0 && check_0(ny, nx, i) == 1)
			{
				if (visit[0][ny][nx] == 0)
				{
					visit[0][ny][nx] = visit[0][out.y][out.x] + 1;
					que[wp].y = ny;
					que[wp].x = nx;
					que[wp++].dir = direc;
				}
			}
			if (direc == 1 && check_1(ny, nx, i) == 1)
			{
				if (visit[1][ny][nx] == 0)
				{
					visit[1][ny][nx] = visit[1][out.y][out.x] + 1;
					que[wp].y = ny;
					que[wp].x = nx;
					que[wp++].dir = direc;
				}
			}
		}
		if (rotate(out.y, out.x) == 1 && visit[!out.dir][out.y][out.x] == 0)
		{
			visit[!out.dir][out.y][out.x] = visit[out.dir][out.y][out.x] + 1;
			que[wp].y = out.y;
			que[wp].x = out.x;
			que[wp++].dir = !out.dir;
		}
	}


	return -1;

}


int rotate(int y, int x)
{
	int i, j;
	int sx, sy, ex, ey;

	sy = y - 1;
	sx = x - 1;
	ey = y + 1;
	ex = x + 1;
	if (sy<1 || sx<1 || ey>N || ex>N) return 0;

	for (i = sy; i <= ey; i++)
	{
		for (j = sx; j <= ex; j++)
		{
			if (map[i][j] == '1') return 0;
		}
	}

	return 1;
}

int check_1(int y, int x, int dir)// _0은 현재 방향이 0일때
{
	int i, j, nx, ny;
	nx = x + dx[dir];
	ny = y + dy[dir];

	if (dir == 1 || dir == 3)
	{
		if (map[y][x] == '0' && map[y - 1][x] == '0' && map[y + 1][x] == '0') return 1;
		else return 0;
	}

	if (nx<1 || nx>N || ny<1 || ny>N) return;

	if (dir == 0 || dir == 2)
	{
		if (map[ny][nx] == '0') return 1;
		else return 0;
	}
}

//dir은 내가 가려는 방향.
int check_0(int y, int x, int dir)// _0은 현재 방향이 0일때
{
	int i, j, nx, ny;
	nx = x + dx[dir];
	ny = y + dy[dir];

	if (dir == 0 || dir == 2)
	{
		if (map[y][x] == '0' && map[y][x - 1] == '0' && map[y][x + 1] == '0') return 1;
		else return 0;
	}

	if (nx<1 || nx>N || ny<1 || ny>N) return;

	if (dir == 1 || dir == 3)
	{
		if (map[ny][nx] == '0') return 1;
		else return 0;
	}
}

void input(void)
{
	int i, j;
	int sflag = 0, eflag = 0;
	scanf("%d", &N);

	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			scanf(" %c", &map[i][j]);

			if (map[i][j] == 'B' && sflag == 2) map[i][j] = '0';
			if (map[i][j] == 'B' && sflag == 1)
			{
				start.y = i;
				start.x = j;
				sflag++;
				if (map[i][j - 1] == 'B')
				{
					start.dir = 0;
					map[i][j - 1] = '0';
				}
				if (map[i - 1][j] == 'B')
				{
					start.dir = 1;
					map[i - 1][j] = '0';
				}
				map[i][j] = '0';
			}
			if (map[i][j] == 'B' && sflag == 0) sflag++;

			if (map[i][j] == 'E' && eflag == 2) map[i][j] = '0';
			if (map[i][j] == 'E' && eflag == 1)
			{
				end.y = i;
				end.x = j;
				eflag++;
				if (map[i][j - 1] == 'E')
				{
					end.dir = 0;
					map[i][j - 1] = '0';
				}
				if (map[i - 1][j] == 'E')
				{
					end.dir = 1;
					map[i - 1][j] = '0';
				}
				map[i][j] = '0';
			}
			if (map[i][j] == 'E' && eflag == 0) eflag++;
		}
	}
}


int main(void)
{
	int sol;

	input();

	sol = BFS();

	//printf("ey = %d, ex = %d, edir = %d\n", end.y, end.x, end.dir);

	//P();

	//map_P();

	if (sol > 0) printf("%d", sol);
	else printf("0");

	return 0;
}


#endif