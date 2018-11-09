#if 01
#include <stdio.h>
#include <string.h>
#define INF 0x7fff0000

typedef struct{
	int y;
	int x;
	int flag;
}location;

int my, mx;
int map[6][10];
int init[6][10];
int pin_num;

int min_cnt;
int min_move;

location pin[9];
int dx[] = { 0, 1, 0, -1 };
int dy[] = { -1, 0, 1, 0 };


void input(void)
{
	int i, j;
	char temp;

	for (i = 1; i <= my; i++)
	{
		for (j = 1; j <= mx; j++)
		{
			scanf(" %c", &temp);
			if (temp == '#') map[i][j] = 9;
			if (temp == '.') map[i][j] = 0;
			if (temp == 'o')
			{
				pin[pin_num].y = i;
				pin[pin_num].x = j;
				map[i][j] = pin_num;
				pin_num++;
			}
		}
	}

	pin_num--;
}

int check_final(void)
{
	int i, j;
	int nx, ny;
	int nnx, nny;
	int sx, sy;
	int cnt = 0;

	for (i = 1; i <= pin_num; i++)
	{
		sx = pin[i].x;
		sy = pin[i].y;

		if (pin[i].flag == 0)
		{
			for (j = 0; j<4; j++)
			{
				nx = sx + dx[j];
				ny = sy + dy[j];

				nnx = nx + dx[j];
				nny = ny + dy[j];

				if (map[ny][nx]>0 && map[ny][nx]<9)
				{
					if (nnx<1 || nnx>mx || nny<1 || nny>my) continue;
					return 0;
				}
			}
		}
	}

	return 1;
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

void DFS(int L, int cnt)
{
	int i, j;
	int nx, ny, sx, sy;
	int nnx, nny;
	int delete_idx;
	int backup[6][10];
	if (cnt<min_cnt)
	{
		//P();
		min_cnt = cnt;
		min_move = pin_num - min_cnt;
	}

	for (i = 1; i <= pin_num; i++)
	{
		if (pin[i].flag == 0)
		{
			sx = pin[i].x;
			sy = pin[i].y;
			for (j = 0; j<4; j++)
			{
				nx = sx + dx[j];
				ny = sy + dy[j];

				nnx = nx + dx[j];
				nny = ny + dy[j];
				if (nnx<1 || nny<1 || nnx>mx || nny>my) continue;
				if (map[ny][nx] != 0 && map[ny][nx] != 9 && map[nny][nnx] == 0)
				{
					delete_idx = map[ny][nx];
					map[ny][nx] = 0;
					map[nny][nnx] = i;
					map[sy][sx] = 0;
					pin[i].y = nny;
					pin[i].x = nnx;
					pin[delete_idx].flag = 1;
					DFS(L + 1, cnt - 1);
					pin[i].y = sy;
					pin[i].x = sx;
					map[nny][nnx] = 0;
					map[sy][sx] = i;
					map[ny][nx] = delete_idx;
					pin[delete_idx].flag = 0;
				}
			}
		}
	}
}


int main(void)
{
	int T, tc;
	scanf("%d", &T);
	my = 5;
	mx = 9;
	for (tc = 1; tc <= T; tc++)
	{
		pin_num = 1;
		memset(pin, 0, sizeof(pin));
		input();
		//P();
		min_cnt = pin_num;
		min_move = 0;
		DFS(0, pin_num);

		printf("%d %d\n", min_cnt, min_move);

	}
	return 0;
}


#endif

