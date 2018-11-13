#if 01
#include <stdio.h>
#include <string.h>

typedef struct {
	int y;
	int x;
	int dir;
}info;
int my, mx;
int visit[5][110][110];
int map[110][110];
int dy[] = { 0, 0, 0, 1, -1 };
int dx[] = { 0, 1, -1, 0, 0 };
int right[] = { 0, 3, 4, 2, 1 };
int left[] = { 0, 4, 3, 1, 2 };
info start;
info end;
info que[101000];
int wp, rp;

void P(void)
{
	int i, j;

	printf("sy= %d, sx= %d, sdir= %d, / ey= %d, ex= %d, edir= %d\n", start.y, start.x, start.dir, end.y, end.x, end.dir);

	printf("visit[1]\n");
	for (i = 1; i <= my; i++)
	{
		for (j = 1; j <= mx; j++)
		{
			printf("%d ", visit[1][i][j]);
		}
		printf("\n");
	}
	printf("\n");

	printf("visit[2]\n");
	for (i = 1; i <= my; i++)
	{
		for (j = 1; j <= mx; j++)
		{
			printf("%d ", visit[2][i][j]);
		}
		printf("\n");
	}
	printf("\n");

	printf("visit[3]\n");
	for (i = 1; i <= my; i++)
	{
		for (j = 1; j <= mx; j++)
		{
			printf("%d ", visit[3][i][j]);
		}
		printf("\n");
	}
	printf("\n");

	printf("visit[4]\n");
	for (i = 1; i <= my; i++)
	{
		for (j = 1; j <= mx; j++)
		{
			printf("%d ", visit[4][i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int BFS(void)
{
	int i, nx, nnx, nnnx, ny, nny, nnny;
	int dir, sx, sy;
	info out;

	wp = rp = 0;

	que[wp].y = start.y;
	que[wp].x = start.x;
	que[wp++].dir = start.dir;
	visit[start.dir][start.y][start.x] = 1;

	if (end.y == start.y && end.x == start.x && end.dir == start.dir) return 0;

	while (wp>rp)
	{
		out = que[rp++];
		sy = out.y, sx = out.x, dir = out.dir;

		if (left[dir] == end.dir && sy == end.y && sx == end.x) return visit[dir][sy][sx];
		if (right[dir] == end.dir && sy == end.y && sx == end.x) return visit[dir][sy][sx];

		if (visit[left[dir]][sy][sx] == 0)
		{
			que[wp].y = sy;
			que[wp].x = sx;
			que[wp++].dir = left[dir];
			visit[left[dir]][sy][sx] = visit[dir][sy][sx] + 1;
		}
		if (visit[right[dir]][sy][sx] == 0)
		{
			que[wp].y = sy;
			que[wp].x = sx;
			que[wp++].dir = right[dir];
			visit[right[dir]][sy][sx] = visit[dir][sy][sx] + 1;
		}


		nx = sx + dx[dir];
		ny = sy + dy[dir];
		if (nx<1 || ny<1 || nx>mx || ny>my) continue;
		if (map[ny][nx] == 1) continue;

		if (ny == end.y && nx == end.x && dir == end.dir) return visit[dir][sy][sx];
		if (map[ny][nx] == 0 && visit[dir][ny][nx] == 0)
		{
			que[wp].y = ny;
			que[wp].x = nx;
			que[wp++].dir = dir;
			visit[dir][ny][nx] = visit[dir][sy][sx] + 1;
		}

		nnx = nx + dx[dir];
		nny = ny + dy[dir];
		if (nnx<1 || nny<1 || nnx>mx || nny>my) continue;
		if (map[nny][nnx] == 1) continue;

		if (nny == end.y && nnx == end.x && dir == end.dir) return visit[dir][sy][sx];
		if (map[nny][nnx] == 0 && visit[dir][nny][nnx] == 0)
		{
			que[wp].y = nny;
			que[wp].x = nnx;
			que[wp++].dir = dir;
			visit[dir][nny][nnx] = visit[dir][sy][sx] + 1;
		}

		nnnx = nnx + dx[dir];
		nnny = nny + dy[dir];
		if (nnnx<1 || nnny<1 || nnnx>mx || nnny>my) continue;
		if (map[nnny][nnnx] == 1) continue;

		if (nnny == end.y && nnnx == end.x && dir == end.dir) return visit[dir][sy][sx];
		if (map[nnny][nnnx] == 0 && visit[dir][nnny][nnnx] == 0)
		{
			que[wp].y = nnny;
			que[wp].x = nnnx;
			que[wp++].dir = dir;
			visit[dir][nnny][nnnx] = visit[dir][sy][sx] + 1;
		}
	}


	return -1;

}


void input(void)
{
	int i, j;

	scanf("%d %d", &my, &mx);

	for (i = 1; i <= my; i++)
	{
		for (j = 1; j <= mx; j++)
		{
			scanf("%d", &map[i][j]);
		}
	}

	scanf("%d %d %d", &start.y, &start.x, &start.dir);

	scanf("%d %d %d", &end.y, &end.x, &end.dir);
}


int main(void)
{
	int sol;

	input();

	sol = BFS();

	//P();

	printf("%d", sol);


	return 0;
}



#endif