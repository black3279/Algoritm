#if 01
#include <stdio.h>
#include <string.h>

typedef struct {
	int y;
	int x;
}location;
location start;
location end;
location que[1000 * 1000];

int wp, rp;
int soly, solx, type;
int dx[] = { 0, 1, 0, -1 };
int dy[] = { -1, 0, 1, 0 };
int you[] = { 2, 3, 0, 1 };
int pipe[8][4] = { { 0, }, { 1, 0, 1, 0 }, { 0, 1, 0, 1 }, { 1, 1, 1, 1 }, { 0, 1, 1, 0 }, { 1, 1, 0, 0 }, { 1, 0, 0, 1 }, { 0, 0, 1, 1 } };
int flag;
int my, mx;
int b_cnt;
int map[30][30];

void input(void)
{
	int i, j;
	char temp;
	scanf("%d %d", &my, &mx);

	for (i = 1; i <= my; i++)
	{
		for (j = 1; j <= mx; j++)
		{
			scanf(" %c", &temp);
			if (temp == '|') map[i][j] = 1;
			if (temp == '-') map[i][j] = 2;
			if (temp == '+') map[i][j] = 3;
			if (temp == '1') map[i][j] = 4;
			if (temp == '2') map[i][j] = 5;
			if (temp == '3') map[i][j] = 6;
			if (temp == '4') map[i][j] = 7;
			if (map[i][j] >= 1 && map[i][j] <= 7) b_cnt++;

			if (temp == 'M')
			{
				map[i][j] = 8;
				start.y = i;
				start.x = j;
			}
			if (temp == 'Z')
			{
				map[i][j] = 9;
				end.y = i;
				end.x = j;
			}
		}
	}

	b_cnt++;
}

int BFS(void)
{
	int i, j, nx, ny;
	int cnt = 0;
	int visit[30][30] = { 0, };
	location out;
	int flag = 0;

	visit[start.y][start.x] = 1;

	for (i = 0; i < 4; i++)
	{
		nx = start.x + dx[i];
		ny = start.y + dy[i];
		if (nx<1 || ny<1 || nx>mx || ny>my) continue;
		if (map[ny][nx] >= 1 && map[ny][nx] <= 7)
		{
			if (pipe[map[ny][nx]][you[i]] == 1)
			{
				que[wp].y = ny;
				que[wp++].x = nx;
				visit[ny][nx] = 1;
				cnt++;
			}
		}
	}

	while (wp > rp)
	{
		out = que[rp++];

		for (i = 0; i < 4; i++)
		{
			nx = out.x + dx[i];
			ny = out.y + dy[i];
			if (nx<0 || ny<0 || nx>mx + 1 || ny>my + 1) continue;
			if (pipe[map[out.y][out.x]][i] == 1)
			{
				if (map[ny][nx] == 0 || ((map[ny][nx] >= 1 && map[ny][nx] <= 7) && pipe[map[ny][nx]][you[i]] == 0))
				{
					rp = wp;
					return 0;
				}
				if (map[ny][nx] == 9)
				{
					if (flag != -1) flag = 1;
					continue;
				}
				if (visit[ny][nx] == 0 && map[ny][nx] >= 1 && map[ny][nx] <= 7)
				{
					if (pipe[map[ny][nx]][you[i]] == 1)
					{
						que[wp].y = ny;
						que[wp++].x = nx;
						visit[ny][nx] = 1;
						cnt++;
					}
				}
			}
		}
	}

	if (flag == 1 && cnt == b_cnt) return 1;
	return 0;
}

void BFS_all(void)
{
	int i, j, k;

	for (i = 1; i <= my; i++)
	{
		for (j = 1; j <= mx; j++)
		{
			for (k = 1; k <= 7; k++)
			{
				if (map[i][j] == 0)
				{
					//memset(visit, 0, sizeof(visit));
					map[i][j] = k;
					if (BFS())
					{
						soly = i;
						solx = j;
						type = k;
						return;
					}
					map[i][j] = 0;
				}
			}
		}
	}
}

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

int main(void)
{
	char sol_type;

	input();

	BFS_all();
	//P();
	if (type == 1) sol_type = '|';
	if (type == 2) sol_type = '-';
	if (type == 3) sol_type = '+';
	if (type == 4) sol_type = '1';
	if (type == 5) sol_type = '2';
	if (type == 6) sol_type = '3';
	if (type == 7) sol_type = '4';

	printf("%d %d %c", soly, solx, sol_type);

	return 0;
}

#endif