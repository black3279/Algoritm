#if 01
#include <stdio.h>
#include <string.h>

struct {
	int y;
	int x;
	int direc;
	int len;
}snake;

typedef struct {
	int map;
	int direc;
}info;

struct {
	int time;
	char LD;
}cmd[110];

info map[110][110];
int N;
int K;
int L;
int d_cnt;
int dx[] = { 0, 1, 0, -1 };
int dy[] = { -1, 0, 1, 0 };
int left[] = { 3, 0, 1, 2 };
int right[] = { 1, 2, 3, 0 };
int you[] = { 2, 3, 0, 1 };

void map_P(void)
{
	int i, j;
	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			printf("%d ", map[i][j].map);
		}
		printf("\n");
	}
	printf("\n");
}

void direc_P(void)
{
	int i, j;
	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			printf("%d ", map[i][j].direc);
		}
		printf("\n");
	}
	printf("\n");
}

void move_apple(int y, int x)
{
	map[y][x].map = 1;
	map[y][x].direc = snake.direc;
	snake.y = y;
	snake.x = x;
	snake.len++;
	return;
}

void move_none(int y, int x, int tk)
{
	int i, j, nx, ny, sx, sy;
	info nul = { 0, };
	int len;

	map[y][x].map = 1;
	map[y][x].direc = snake.direc;
	snake.y = y;
	snake.x = x;
	len = snake.len;
	nx = x;
	ny = y;
	//printf("move none = %d  len = %d\n", tk, len);
	for (i = len; i >= 1; i--)
	{
		sx = nx, sy = ny;
		//printf("sy = %d, sx = %d\n", sy, sx);
		nx = nx + dx[you[map[sy][sx].direc]];
		ny = ny + dy[you[map[sy][sx].direc]];
		//printf("ny = %d, nx = %d\n", ny, nx);
	}
	//printf("final ny = %d, nx = %d\n", ny, nx);
	map[ny][nx] = nul;

}

int time_start(void)
{
	int tk = 1;
	int nx, ny;
	//printf("0\n");
	//map_P();
	//direc_P();
	for (;;)
	{
		nx = snake.x + dx[snake.direc];
		ny = snake.y + dy[snake.direc];

		if (map[ny][nx].map == 1 || nx > N || ny > N || nx < 1 || ny < 1) return tk;
		if (map[ny][nx].map == 7) move_apple(ny, nx);
		else if (map[ny][nx].map == 0) move_none(ny, nx, tk);

		if (d_cnt <= L && tk == cmd[d_cnt].time)
		{
			if (cmd[d_cnt].LD == 'D') snake.direc = right[snake.direc];
			if (cmd[d_cnt].LD == 'L') snake.direc = left[snake.direc];
			d_cnt++;
		}
		//printf("%d\n", tk);
		//map_P();
		//direc_P();
		tk++;
	}
}

void input(void)
{
	int i, j;
	int x, y;
	snake.y = 1, snake.x = 1, snake.direc = 1, snake.len = 1;
	d_cnt = 1;
	scanf("%d", &N);
	scanf("%d", &K);
	for (i = 1; i <= K; i++)
	{
		scanf("%d %d", &y, &x);
		map[y][x].map = 7;
	}
	scanf("%d", &L);

	for (i = 1; i <= L; i++)
	{
		scanf("%d %c", &cmd[i].time, &cmd[i].LD);
	}

	map[1][1].map = 1;
	map[1][1].direc = 1;
}

int main(void)
{
	int sol;
	input();

	sol = time_start();

	printf("%d", sol);

	return 0;
}

#endif