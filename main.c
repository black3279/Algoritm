#if 01
#include <stdio.h>
#include <string.h>

typedef struct {
	int y;
	int x;
	int jump;
}info;

int visit[31][210][210];
int my, mx, K;
int map[210][210];

int hy[] = { -2, -1, 1, 2, 2, 1, -1, -2 };
int hx[] = { 1, 2, 2, 1, -1, -2, -2, -1 };

int dx[] = { 0, 1, 0, -1 };
int dy[] = { -1, 0, 1, 0 };

info que[1300000];
int wp, rp;

int BFS(void)
{
	info out;
	int nx, ny, i;

	que[wp].y = 1;
	que[wp].x = 1;
	que[wp++].jump = 0;
	visit[0][1][1] = 1;

	while (wp>rp)
	{
		out = que[rp++];

		for (i = 0; i<4; i++)
		{
			nx = out.x + dx[i];
			ny = out.y + dy[i];
			if (nx<1 || ny<1 || nx>mx || ny>my) continue;

			if (ny == my && nx == mx) return visit[out.jump][out.y][out.x];
			if (map[ny][nx] == 0 && visit[out.jump][ny][nx] == 0)
			{
				visit[out.jump][ny][nx] = visit[out.jump][out.y][out.x] + 1;
				que[wp].y = ny;
				que[wp].x = nx;
				que[wp++].jump = out.jump;
			}
		}

		if (out.jump<K)
		{
			for (i = 0; i<8; i++)
			{
				nx = out.x + hx[i];
				ny = out.y + hy[i];
				if (nx<1 || ny<1 || nx>mx || ny>my) continue;

				if (ny == my && nx == mx) return visit[out.jump][out.y][out.x];
				if (map[ny][nx] == 0 && visit[out.jump + 1][ny][nx] == 0)
				{
					visit[out.jump + 1][ny][nx] = visit[out.jump][out.y][out.x] + 1;
					que[wp].y = ny;
					que[wp].x = nx;
					que[wp++].jump = out.jump + 1;
				}

			}
		}
	}

	return -1;
}


void input(void)
{
	int i, j;
	scanf("%d", &K);
	scanf("%d %d", &mx, &my);

	for (i = 1; i <= my; i++)
	{
		for (j = 1; j <= mx; j++)
		{
			scanf("%d", &map[i][j]);
		}
	}
}


int main(void)
{
	int sol;

	input();


	sol = BFS();

	printf("%d", sol);


	return 0;
}


#endif
