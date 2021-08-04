#pragma warning (disable : 4996)

#if 01
#include <stdio.h>
#include <string.h>

#define MAX 25
int N;
int direcx[]={1, -1, -1, 1};
int direcy[]={1, 1, -1, -1};
int mapx, mapy;
int max = -1;
int map[MAX][MAX];
int list[MAX*MAX];

int list_examine(int num, int L)
{
	int i;

	for(i=1;i<L;i++)
	{
		if(num==list[i]) return 1;
	}

	return 0;
}

void input(void)
{
	int i, j;
	scanf("%d", &N);

	for(i=1;i<=N;i++)
	{
		for(j=1;j<=N;j++)
		{
			scanf("%d", &map[i][j]);
		}
	}
}

void DFS(int L, int direc, int sx, int sy, int dx, int dy)
{
	int num;
	if(direc==3 && dx==mapx && dy==mapy)
	{
		if(L>max) max=L;
		return;
	}
	num=map[dy][dx];

	if(dx>N||dx<1||dy<1||dy>N || list_examine(num,L)) return;
	{
		direc++;
		dx=sx+direcx[direc];
		dy=sy+direcy[direc];
		num=map[dy][dx];
		if(dx>N||dx<1||dy<1||dy>N || list_examine(num,L)) return;
	}
	list[L]=num;
	DFS(L+1, direc, dx, dy, dx+direcx[direc], dy+direcy[direc]);
	list[L]=0;
}

void DFS_all(void)
{
	int i, j;
	int ny=N-1;
	for(i=1;i<N;i++)
	{
		for(j=2;j<=ny;j++)
		{
			list[1]=map[i][j];
			DFS(2, 0, i, j, i+direcx[0], j+direcy[0]);
		}
	}
}

int main(void)
{
	int T, tc;

	scanf("%d", &T);


	for(tc=1;tc<=T;tc++)
	{
		N=0, max=-1;
		memset(map, 0, sizeof (map));
		memset(list,0, sizeof(list));
		input();
		DFS_all();
		printf("#%d %d\n", tc, max);
	}

	return;
}

#endif



// 차량정비소, 함수를 복사할때는 확실히 변수를 다 바꿨는지 확인해라
// 시간을 기반으로 실시간으로 흘러갈 때와 같이 동시에 변수가 여러개 움직이는 경우,
// 간단하게 풀려고 하면 더 복잡해진다. 기준이 되는 변수를  확실히 정하고 그것을 기준으로 함수를 만들것
#if 0
#include <stdio.h>
#include <string.h>
#define MAX 1010
#define INF 0x7fff0000
typedef struct {
   int id;
   int Atime;
   int Spare;
}info;

int N, M, K, A, B; // N은 접수창고번호개수 M은 정비창구번호 개수 K명방문, A는 지갑 접수창구번호  B는 정비창구
int a[10]; // 접수창구 처리시간
int b[10]; // 정비창구 처리시간
info Custom[MAX];
info Waitfix[MAX];
info Subdesk[10];
info Fixdesk[10];
int visit[MAX];
int Sum;
int max_time;
int fix_line_cnt;
int Sub_line_cnt; // 고객 중 몇번까지 데스크로 보냈는지
int find_Subdesk(void);// 접수창고 빈 곳 번호 찾는다.
void In_to_Subdesk(int Sparetime);// sparetime을 받아서 고객 중 같은 애들 subdesk로 넣어준다.
void Full_Subdesk(void); // 접수창고 다 찼을 경우, min값을 찾아 감해주고 0인 것들 fix_line으로 보내준다.
void Goto_fix_line(void); // 접수처리 끝난 애들 Fix_line으로 보낸다


void Time_start(void)
{
   int tk;
   int cnt = 0;
   int flag = 0;
   int i, j;
   int num;
   for (tk = 0; tk <= 20010; tk++)
   {
	  for (i = 1; i <= N; i++)
      {
         if (Subdesk[i].id) Subdesk[i].Spare--;
      }
      Goto_fix_line();
      for (i = 1; i <= K; i++)
      {
         if (!Custom[i].id) continue;
         if (Custom[i].Atime > tk) break;
         if (Custom[i].Atime <= tk){
            num = find_Subdesk();
            if (num == 0) break;
            Subdesk[num].id = i;
            Subdesk[num].Atime = tk + a[num];
            Subdesk[num].Spare = a[num];
            Custom[i].id = 0;
         }
      }

      if (i == K + 1 && Custom[K].id == 0)
      {
         flag = 0;
         for (i = 1; i <= N; i++)
         {
            if (Subdesk[i].id)
            {
               flag = 1;
               break;
            }
         }
         if(flag==0) break;
      }

   }
}

int find_Subdesk(void) 
{
   int i;

   for (i = 1; i <= N; i++)
   {
      if (Subdesk[i].id == 0) return i;
   }
   return 0;
}

//void Full_Subdesk(void)
//{
//   int i, j;
//   int min = INF;
//
//   for (i = 1; i <= N; i++)
//   {
//      if (Subdesk[i].Spare < min) min = Subdesk[i].Spare;
//   }
//
//   for (i = 1; i <= N; i++)
//   {
//      Subdesk[i].Spare -= min;
//   }
//
//   Goto_fix_line();
//   return;
//}

void Goto_fix_line(void)
{
   int i, j;
   info Null = { 0, };
   for (i = 1; i <= N; i++)
   {
      if (Subdesk[i].id && Subdesk[i].Spare == 0){
         if (i == A)
         {
            visit[Subdesk[i].id]=1;
         }
         Waitfix[++fix_line_cnt] = Subdesk[i];
         Subdesk[i] = Null;
      }
   }
}

void Goto_final_line(void)
{
   int i, j;
   info Null = { 0, };
   for (i = 1; i <= M; i++)
   {
      if (Fixdesk[i].id && Fixdesk[i].Spare == 0){
         if (i == B && visit[Fixdesk[i].id])
         {
            Sum += Fixdesk[i].id;
         }
         Fixdesk[i] = Null;
      }
   }
}

int find_Fixdesk(void)
{
   int i;

   for (i = 1; i <= M; i++)
   {
      if (Fixdesk[i].id == 0) return i;
   }
   return 0;
}

void Fix_Time_start(void)
{
   int tk=Waitfix[1].Atime;
   int cnt = 0;
   int flag = 0;
   int i, j;
   int num;

   for (;;)
   {
	  for (i = 1; i <= M; i++)
      {
         if (Fixdesk[i].id) Fixdesk[i].Spare--;
      }
      Goto_final_line();
      for (i = 1; i <= K; i++)
      {
         if (!Waitfix[i].id) continue;
         if (Waitfix[i].Atime > tk) break;
         if (Waitfix[i].Atime <= tk){
            num = find_Fixdesk();
            if (num == 0) break;
            Fixdesk[num].id = Waitfix[i].id;
            Fixdesk[num].Spare = b[num];
            Waitfix[i].id = 0;
         }
      }

      if (i == K + 1 && Waitfix[K].id == 0 && Fixdesk[B].id==0) break;

      tk++;
   }
}

void print(void)
{
   int i, j;

   for (i = 1; i <= K; i++) printf("%d ", Custom[i].Atime);
}


void input(void)
{
   int i, j;
   scanf("%d %d %d %d %d", &N, &M, &K, &A, &B);
   for (i = 1; i <= N; i++) scanf("%d", &a[i]);
   for (i = 1; i <= M; i++) scanf("%d", &b[i]);

   for (i = 1; i <= K; i++)
   {
      scanf("%d", &Custom[i].Atime);
      Custom[i].id = i;
   }
}

void simple_sort(void)
{
   int i, j;
   info temp;
   for (i = 1; i <= K - 1; i++)
   {
      for (j = i + 1; j <= K; j++)
      {
         if (Custom[i].Atime > Custom[j].Atime)
         {
            temp = Custom[i];
            Custom[i] = Custom[j];
            Custom[j] = temp;
         }
      }
   }
}


int main(void)
{
   int T, tc;
   int i, j;
   scanf("%d", &T);

   for (tc = 1; tc <= T; tc++)
   {
      // 초기화 추가해주기

      Sub_line_cnt = 1;
      fix_line_cnt = 0;
      Sum = 0;
      memset(Subdesk, 0, sizeof(Subdesk));
      memset(Fixdesk, 0, sizeof(Fixdesk));
      memset(Waitfix, 0, sizeof(Waitfix));
      memset(Custom, 0, sizeof(Custom));
      memset(visit, 0, sizeof(visit));

      input();

      simple_sort();

      /*print();*/

      Time_start();

	  //   for (i = 1; i < fix_line_cnt; i++)
   //{
	  // printf("id : %d Arrive : %d Spare : %d\n", Waitfix[i].id, Waitfix[i].Atime, Waitfix[i].Spare);
   //}

	//for (i = 1; i <= K; i++)
 //  {
	//   printf("visit id (%d) : %d ", i, visit[i]);
 //  }
	//printf("\n");

      Fix_Time_start();

      if(Sum) printf("#%d %d\n", tc, Sum);
      else printf("#%d -1\n", tc);
   }

   return 0;
}

#endif



// 구슬넣기 2
#if 0
#include <stdio.h>

#define MAX 15
#define INF 0x7fff0000
typedef struct {
	int y;
	int x;
}location;
location red;
location blue;
location hole;
int map[MAX][MAX];
int dx[] = { 0, 1, 0, -1 };
int dy[] = { -1, 0, 1, 0 };
int my, mx;
int sol;
int min = INF;

//void check_sol(int redy, int redx, int bluey, int bluex)
//{
//	if (bluey == hole.y && bluex == hole.x)
//	{
//		sol = -1;
//		return;
//	}
//	if (redy == hole.y && redx == hole.x) sol = 1;
//
//	return;
//}

location move_ball(int color, int redy, int redx, int bluey, int bluex, int direc, int L)
{
	int i, j;
	location now = { 0, 0 };

	if(color==0)
	{
		for (;;)
		{
			redy += dy[direc];
			redx += dx[direc];

			if (map[redy][redx] == 4)
			{
				if (L + 1 < min){
					min = L + 1;
					sol = 1;

					if(map[redy][redx]!=4) map[redy][redx]=5;
					map[bluey][bluex]=2;
					for(i=1;i<=my;i++)
					{
						for(j=1;j<=mx;j++)
						{
							printf("%d", map[i][j]);
						}
						printf("\n");
					}
					printf("\n\n");
				}

				now.y = 0;
				now.x = 0;
				return now;
			}

			if ( (redy==bluey && redx==bluex)  || map[redy][redx] == 1)
			{
				now.y = redy - dy[direc];
				now.x = redx - dx[direc];

				return now;
			}
		}
	}

	else
	{
		for (;;)
		{
			bluey += dy[direc];
			bluex += dx[direc];

			if ( (bluex == redx && bluey == redy) || map[bluey][bluex] == 1)
			{
				now.y = bluey - dy[direc];
				now.x = bluex - dx[direc];

				return now;
			}
		}
	}


}

int check_blue(int direc, int bluey, int bluex)
{
	for (;;)
	{
		bluey += dy[direc];
		bluex += dx[direc];

		if (map[bluey][bluex] == 4) return 0;

		if (map[bluey][bluex] == 1) return 1;
	}

}

int find_mover(int direc, int redy, int redx, int bluey, int bluex)
{
	if (direc == 0)
	{
		if (redy > bluey) return 0;
		else return 1;
	}
	if (direc == 1)
	{
		if (redx > bluex) return 0;
		else return 1;
	}
	if (direc == 2)
	{
		if (redy < bluey) return 0;
		else return 1;
	}
	if (direc == 3)
	{
		if (redx < bluex) return 0;
		else return 1;
	}
}

void DFS(int L, int redy, int redx, int bluey, int bluex)
{
	int ball;
	int i, j;
	location Nred, Nblue;
	if (min<=L+1) return;
	if (L >= 10) return;

	for (i = 0; i < 4; i++)
	{
		if (check_blue(i, bluey, bluex) == 0) continue;

		ball = find_mover(i, redy, redx, bluey, bluex);

		if (ball == 0){
			Nred = move_ball(0, redy, redx, bluey, bluex, i, L);
			Nblue = move_ball(1, Nred.y, Nred.x, bluey, bluex, i, L);
			DFS(L + 1, Nred.y, Nred.x, Nblue.y, Nblue.x);
		}
		else
		{
			Nblue = move_ball(1, redy, redx, bluey, bluex, i, L);
			Nred = move_ball(0, redy, redx, Nblue.y, Nblue.x, i, L);
			DFS(L + 1, Nred.y, Nred.x, Nblue.y, Nblue.x);
		}
	}
}



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
			if (temp == '#') map[i][j] = 1;
			if (temp == 'R')
			{
				red.y = i;
				red.x = j;
			}
			if (temp == 'B')
			{
				blue.y = i;
				blue.x = j;
			}
			if (temp == 'O')
			{
				map[i][j] = 4;
				hole.y = i;
				hole.x = j;
			}
		}
	}
}

int main(void)
{
	int i;
	input();

	DFS(0, red.y, red.x, blue.y, blue.x);

	if (sol == 0)
	{
		printf("-1");
		return 0;
	}

	printf("%d", min);

	return 0;
}

#endif

// 치킨배달
#if 0
#include <stdio.h>
#include <string.h>
#define MAX 60
#define INF 0x7fff0000

int N, M;
int map[MAX][MAX];
typedef struct {
	int y;
	int x;
}location;

location chicken[15];
int num_chicken;
int min=INF;
int list[15];
location house[100];
int house_cnt;


int abs(int num)
{
	return (num > 0) ? num : -num;
}

int dis(int sy, int sx, int dy, int dx)
{
	return (abs(sy - dy) + abs(sx - dx));
}

int count_all(void)
{
	int i, j;
	int visit[100];
	int sum = 0;
	int n;
	memset(visit, 0xf, sizeof(visit));

	for (i = 1;i <= house_cnt;i++)
	{
		for (j = 1;j <= M;j++)
		{
			n = dis(house[i].y, house[i].x, chicken[list[j]].y, chicken[list[j]].x);
			if (visit[i] > n) visit[i] = n;
		}
	}

	for (i = 1;i <= house_cnt;i++) sum += visit[i];

	return sum;
}

void DFS(int L, int choice)
{
	int i, n;
	if (L > num_chicken) {
		if (choice == M+1)
		{
			n = count_all();
			if (min > n) min = n;
		}
		return;
	}

	list[choice] = L;
	DFS(L + 1, choice + 1);
	list[choice] = 0;
	DFS(L + 1, choice);
}

void input(void)
{
	int i, j;
	scanf("%d %d", &N, &M);

	for (i = 1;i <= N;i++)
		{
			for (j = 1;j <= N;j++)
			{
				scanf("%d", &map[i][j]);

				if (map[i][j] == 2)
				{
					num_chicken++;
					chicken[num_chicken].y = i;
					chicken[num_chicken].x = j;
				}

				if (map[i][j] == 1)
				{
					house_cnt++;
					house[house_cnt].y = i;
					house[house_cnt].x = j;
				}
			}
		}

}



int main(void)
{
	input();
	DFS(1, 1);

	printf("%d", min);

	return 0;
}

#endif


#if 0
int n,cnt;
//int a[] = {1, 2, 4, 8, 16, 32, 64, 128};

void DFS(int dept,int rem)
{
	int i;
	if (rem == 0)
	{
		cnt++;
		return;
	}
	if (dept>64 || rem<0)
	{
		return;
	}
	for (i = 0; i <= rem; i++)
	{
		if ((rem - i) % 2==0) DFS(dept*2, (rem - i)/2);
	}
}
// DFS(1, n);
int main(void)
{
	int ti, T;
	scanf("%d", &T);
	for (ti = 1; ti <= T; ti++)
	{
		scanf("%d", &n);
		cnt = 0;
		DFS(0, n);
		printf("%d\n", cnt);
	}
	return 0;
}
#endif

#if 0

#include <stdio.h>
#include <stdlib.h>

#define MAX (17)

int arr[MAX][MAX];
int list[MAX];
int best[MAX];
int visit[MAX];
int N;
int lcnt;
int N;
int limit;
int lcnt;
int min;

void input(void)
{
	int i, j;
	scanf("%d", &N);
	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			scanf("%d", &arr[i][j]);
		}
	}
}

void print_list(int L, int time_sum)
{
	int i;
	printf("%2d (%2d) : ", ++lcnt, time_sum);
	for (i = 1; i < L; i++)
	{
		printf("%2d ", list[i]);
	}
	printf("\n");
}

void building_dfs(int L, int sum)
{
	int i;
	if (min <= sum) return;  // 가지치기
	if (L > N)
	{
		print_list(L, sum);
		if (min > sum)
		{
			min = sum;
			for (i = 1; i <= N; i++) best[i] = list[i];
		}
		return;
	}

//  어떻게 동작 될 것인지에 대해서 분석해 보세요!
	//list[L] = 0;
	//building_dfs(L + 1, sum);
	for (i = 1; i <= N; i++)
	{
		if (visit[i]) continue;
		list[L] = i;
		visit[i] = 1;
		building_dfs(L + 1, sum + arr[L][i]);
		visit[i] = 0;
	}
}

int main(void)
{
	int i;
	input();
	min = 0x7fffffff;
	building_dfs(1, 0);
	printf("%d\n", min);
	for (i = 1; i <= N; i++)
	{
		printf("%d ", best[i]);
	}
	printf("\n");
	return 0;
}

#endif


#if 0
#define MAX 60

int mx, my;
int visit[MAX][MAX];
char map[MAX][MAX];
int p_clap;
int m_clap;
int N;
int dx[]={0, 1, 1, 1, 0 ,-1, -1, -1};
int dy[]={-1,-1,0,1,1,1,0,-1};



int FF_BFS(int sy, int sx)
{
	int i;
	int cnt=0;
	int nx, ny;

	for(i=0;i<8;i++)
	{
		nx=sx+dx[i];
		ny=sy+dy[i];
		if(ny<1|| nx<1||ny>my || nx>mx) continue;
		if(map[ny][nx]=='o')
		{
			cnt++;
		}
	}

	return cnt;
}

void input(void)
{
	int i, j;

	scanf("%d %d", &my, &mx);
	for(i=1;i<=my;i++)
	{
		for(j=1;j<=mx;j++)
		{
			scanf(" %c", &map[i][j]);
		}
	}
}

void FF_DFS_all(void)
{
	int i, j;
	int max=0;
	for(i=1;i<=my;i++)
	{
		for(j=1;j<=mx;j++)
		{
			if(map[i][j] == 'o') p_clap+= FF_BFS(i, j);

			if(map[i][j] == '.')
			{
				max = FF_BFS(i,j);
				if(m_clap<max) m_clap=max;
			}
		}
	}

	p_clap/=2;
}

int main (void)
{
	input();

	FF_DFS_all();

	printf("%d", m_clap+ p_clap);
	
	return 0;

}
#endif


#if 0
#define MAX 60
int tree[MAX];
int list[MAX];
int sol;
int N;
void printList(int L, int start, int sol)
{
	int i;
	printf("%2d (%2d) : %2d ", L, start, sol);
	printf("\n");
}
int check(int start, int num)
{
	int i;

	if (num == 1)
	{
		if (start == N) return 1;
		if (tree[start] != 2) return 0;
	}
	if (num == 2)
	{
		if(tree[start]==tree[start+1] && tree[start]!=2) return -1;
		if (tree[start] == tree[start + 1]) return 0;
	}
	if (num == 3)
	{
		if (tree[start] == tree[start + 1]|| tree[start+1]==tree[start+2]) return 0;
		if (tree[start] == tree[start+2]) return 0;
	}

	return 1;
}
void DFS(int L, int start)
{
	int i;
	if (start > N) {
		if(L > sol) sol = L;
		printList(L, start, sol);
		return;
	}
	for (i = 1; i <= 3; i++)
	{
		if(check(start, i) == -1) sol=-1;

		if (check(start, i) != 0)
		{
			DFS(L + 1, start+i);
		}
	}
}
void input(void)
{
	int i;
	scanf("%d", &N);
	for (i = 1; i <= N; i++) scanf("%d", &tree[i]);
}
int main(void)
{
	int T, tc;
	scanf("%d", &T);
	for (tc = 1; tc <= T; tc++)
	{
		sol=0;
		input();
		DFS(0, 1);
		printf("%d\n", sol);
	}
}
#endif

//sumsets
#if 0
#define MAX 10
int N;
int two[7];
int list[MAX];
int sol;
void square(void)
{
	int i;
	int n = 1;
	two[0] = 1;
	for (i = 1; i <= 6; i++)
	{
		n *= 2;
		two[i] = n;
	}
	return n;
}
void printList(int L, int S)
{
	int i;
	printf("\n%2d (%2d) : ", L, S);
	for (i = 1; i < L; i++) printf("%d ", list[i]);
	printf("\n");
}
void DFS_square(int L, int S, int start)
{
	int i;
	if (S >= N){
		if (S == N)
		{
			//printList(L, S);
			sol++;
		}
		return;
	}
	for (i = start; i <= 6; i++)
	{
		list[L] = two[i];
		DFS_square(L + 1, S + two[i], i);
	}

}
void input(void)
{
	scanf("%d", &N);
}
int main(void)
{
	int T, tc;
	int i;
	scanf("%d", &T);
	square();
	for (tc = 1; tc <= T; tc++)
	{
		sol = 0;
		input();
		DFS_square(1, 0, 0);
		printf("%d\n", sol);
	}
	return 0;
}

#endif

#if 0
#define MAX 110
typedef struct {
	int y;
	int x;
}location;
int N;
int netLen;
int fishNum;
location fish[MAX];
void input(void)
{
	int i;
	scanf("%d %d %d", &N, &netLen, &fishNum);
	for (i = 1; i <= fishNum; i++)
	{
		scanf("%d %d", &fish[i].y, &fish[i].x);
	}
	printf("%d %d", fish[1]);
}
int main(void)
{
	input();

}
#endif

// 기업 투자
#if 0
#define MAX 40
int invest_m;
int cor_cnt;
int max=0;
int lcnt;
int list[MAX];
int profit[MAX][MAX];
int best[MAX];
void printList(int L, int S)
{
	int i;
	printf("%2d L : %2d (%2d) : ", lcnt++, L, S);
	for (i = 1; i < L; i++)
	{
		printf("%d ", list[i]);
	}
	printf("\n");
}
void DFS_maxprofit(int L, int S, int vault)
{
	int i;
	if (L > cor_cnt)
	{
		if (S > max && vault >= 0)
		{
			max = S;
			for (i = 1; i < L; i++) best[i] = list[i];
		}
		return;
	}
	for (i = 0; i <= vault; i++)
	{ 
		list[L] = i;
		DFS_maxprofit(L + 1, S + profit[L][i], vault - i);
	}
}
void input(void)
{
	int i, j;
	int temp;
	scanf("%d %d", &invest_m, &cor_cnt);
	for (i = 1; i <= invest_m; i++)
	{
		scanf("%d", &temp);
		for (j = 1; j <= cor_cnt; j++)
		{
			scanf("%d", &profit[j][i]);
		}
	}
}
int main(void)
{
	int i;
	input();
	DFS_maxprofit(1, 0, invest_m);
	printf("%d\n", max);
	for (i = 1; i < cor_cnt; i++) printf("%d ", best[i]);
	printf("%d", best[i]);
}
#endif

//비행기 비용 계산 ,, 탈출 조건 한번 더 생각해보기
#if 0
#define MAX 20
int N;
int min = 1000000000;
int a[MAX][MAX];
int visit[MAX];
void input(void)
{
	int i, j;
	scanf("%d", &N);
	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			scanf("%d", &a[i][j]);
		}
	}
}
void DFS(int L, int sC, int start)
{
	int sum;
	int i;
	if (sC >= min) return;
	if (L >= N) {
		if (a[start][1])
		{
			sum = (sC + a[start][1]);
			if (sum < min) min = sum;
		}
		return;
	}
	for (i = 2; i <= N; i++)
	{
		if (a[start][i])
		{
			if (!visit[i])
			{
				visit[start] = 1;
				DFS(L + 1, sC + a[start][i], i);
				visit[start] = 0;
			}
		}
	}

}

int main(void)
{
	input();
	DFS(1, 0, 1);
	printf("%d", min);
}
#endif
// 돌다리 건너기
#if 0
#define MAX 40
int N;
int cnt;
int sol;
int len2;
char word[MAX];
char angel[2][MAX];
int lcnt;
char list[MAX];
int len;
void printList(int L, int AD, int start)
{
	int i;
	printf("%2d (%2d) (start : %2d) : ", ++lcnt, AD, start);
	printf("\n");
}
void DFS(int L, int AD, int start)
{
	int i;
	if (L >= len){
		sol++;
		//printList(L, AD, start);
		return;
	}
	for (i = start; i<len2; i++)
	{
		if (angel[AD][i] == word[L])
		{
			DFS(L + 1, !AD, i + 1);
		}
	}
}
void input(void)
{
	int i;
	scanf("%s", word);
	scanf("%s", angel[0]);
	scanf("%s", angel[1]);
	for (i = 0; word[i]; i++) len++;
	for (i = 0; angel[0][i]; i++) len2++;
}
int main(void)
{
	input();
	DFS(0, 0, 0);
	DFS(0, 1, 0);
	printf("%d", sol);
	return 0;
}
#endif

// 농장탈출 .. 시간 ?
#if 0
#define MAX 30
int Cow_w[MAX];
int cnt;
int max;
int N;
int list[MAX];
void printList(int L, int S)
{
	int i;
	printf("%2d (%2d) : ", L, S);
	for (i = 1; i < L; i++) printf("%d ", list[i]);
	printf("\n");
}
int carry_examine(int a, int b)
{
	int i;
	int cnt1=0, cnt2=0;
	for (; a || b;){
		if ((a % 10 + b % 10) >= 10) return 0;
		a /= 10;
		b /= 10;
	}
	return 1;
}
void DFS_find_max(int L, int S)
{
	int i;
	if (L > N){
		cnt = 0;
		for (i = 1; i <= N; i++)
		{
			if (list[i]) cnt++;
		}
		if (cnt > max) max = cnt;
		/*printList(L, S);*/
		return;
	}
	list[L] = 0;
	DFS_find_max(L + 1, S);
	if (carry_examine(S, Cow_w[L]) == 1)
	{
		list[L] = Cow_w[L];
		DFS_find_max(L + 1, S + Cow_w[L]);
	}
}
void input(void)
{
	int i;
	scanf("%d", &N);
	for (i = 1; i <= N; i++) scanf("%d", &Cow_w[i]);
}
int main(void)
{
	input();
	DFS_find_max(1, 0);
	printf("%d", max);
	return 0;
}
#endif

// 건물세우기 시간 오래걸림
#if 0
#define MAX 20
int N;
int visit[MAX];
int list[MAX];
int best[MAX];
int min = 1000000000;
int cost_build[MAX][MAX];

void input(void)
{
	int i, j;
	scanf("%d", &N);

	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			scanf("%d", &cost_build[i][j]);
		}
	}
}
void printList(int L, int S)
{
	int i;
	printf("%2d (%2d) : ", L, S);
	for (i = 1; i < L; i++)
	{
		printf("%d ", list[i]);
	}
	printf("\n");
}
void DFS_findmin(int L , int S)
{
	int i;
	if (min <= S) return;
	if (L > N)
	{
		/*printList(L, S);*/
		if (S < min)
		{
			min = S;
			for (i = 1; i <= N; i++)
			{
				best[i] = visit[i];
			}
		}
		return;
	}
	for (i = 1; i <= N; i++)
	{
		if (visit[i]) continue;
		visit[i] = L;
		list[L] = cost_build[L][i];
		DFS_findmin(L + 1, S+cost_build[L][i]);
		visit[i] = 0;
		list[L] = 0;
	}
}
void print_min(void)
{
	int i, j;
	int cnt = 0;
	int pr[MAX];
	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			if (best[j] == i) pr[cnt++]=j;
		}
	}
	for (i = 0; i < cnt - 1; i++)
	{
		printf("%d ", pr[i]);
	}
	printf("%d", pr[cnt - 1]);
}

int main(void)
{
	input();
	DFS_findmin(1, 0);
	printf("%d\n", min);
	print_min();
	return 0;
}
#endif
//자동차 경주 DFS, main 설계를 잘못한 케이스, 연습해보기
#if 0
#define MAX 60
int N;
int sol;
int t[MAX];
int list[MAX]; // 그때 그때 마다의 정비소 목록
int d[MAX];
int best[MAX]; // 최소 정비 시간일 때 정비소 목록
int K;
int lcnt;
void printList(int L, int tS)
{
	int i;
	printf("%2d (%2d) : ", ++lcnt, tS);
	for (i = 1; i < L; i++)
	{
		printf("%d ", list[i]);
	}
	printf("\n");
}
void DFS_car(int L, int tS, int dS)
{
	int i;
	if (sol <= tS) return;
	if (L > N)
	{
		if (tS < sol)
		{
			sol = tS;
			for (i = 1; i <= N; i++) best[i] = list[i];
		}
		return;
	}
	list[L] = 0;
	if (dS + d[L] <= K)
	{
		DFS_car(L + 1, tS, dS + d[L]);
	}
	list[L] = L;
	DFS_car(L + 1, tS + t[L], d[L]);
}
void input(void)
{
	int i;
	scanf("%d %d", &K, &N);
	for (i = 0; i <= N; i++)
	{
		scanf("%d", &d[i]);
	}
	for (i = 1; i <= N; i++)
	{
		scanf("%d", &t[i]);
	}
}
void output(void)
{
	int i;
	int cnt=0;
	printf("%d\n", sol);
	for (i = 1; i <= N; i++)
	{
		if (best[i]) cnt++;
	}
	if(cnt) printf("%d\n", cnt);
	for (i = 1; i <= N; i++)
	{
		if (best[i]) printf("%d ", best[i]);
	}
}
int main(void)
{
	input();
	sol = 1000000000;
	DFS_car(1, 0, d[0]);
	output();
	return 0;
}
#endif

#if 0
#define MAX 110
typedef struct {
	int y;
	int x;
}location;
int n;
int netlen;
int fish_n;
location fish[MAX];
int main(void)
{

}
#endif

#if 0
#define MAX 30
int N;
int Bh;
int Cowh[MAX];
int b[MAX];
int min= 100000000;
int list[MAX];
void printList(int L, int S)
{
	int i;
	printf("%2d (%2d) (min = %2d) : ", L, S, min);
	for (i = 1; i < L; i++)
	{
		printf("%2d ", list[i]);
	}
	printf("\n");
}
void DFS_Bh(int L, int S)
{
	if (S + b[L] < Bh || S >= Bh)
	{
		if (S < min && S >= Bh) min = S;
		return;
	}
	if (L > N){
		if (S<min && S>=Bh) min = S;
		//printList(L, S);
		return;
	}
	list[L] = Cowh[L];
	DFS_Bh(L + 1, S + list[L]);
	list[L] = 0;
	DFS_Bh(L + 1, S);

}
void input(void)
{
	int i;
	scanf("%d %d", &N, &Bh);
	for (i = 1; i <= N; i++)
	{
		scanf("%d", &Cowh[i]);
	}
}
void makeB(void)
{
	int i, j;
	for (i = 1; i <= N; i++)
	{
		b[i] = 0;
		for (j = i; j <= N; j++)
		{
			b[i] += Cowh[j];
		}
	}
}
int main(void)
{
	int T, tc;
	scanf("%d", &T);
	for (tc = 1; tc <= T; tc++)
	{
		min = 100000000;
		input();
		makeB();
		DFS_Bh(1, 0);
		printf("%d\n", min-Bh);
	}
	return 0;
}
#endif

// 감시구역
#if 0
#define MAX 20
typedef struct {
	int y;
	int x;
	int dir;
}location;
location queue[MAX*MAX];
int n;
int map[MAX][MAX];
int wp, rp;
int max;
int bspot;
int dx[] = { 0, 1, 0, -1 };
int dy[] = { -1, 0, 1, 0 };
void input(void)
{
	int i, j;
	scanf("%d", &n);
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
		{
			scanf("%d", &map[i][j]);
			if (map[i][j] == 0) bspot++;
		}
	}
}
int DFS_dirgo(int sx, int sy)
{
	int i, j;
	location out;
	int nx, ny;
	int cnt;
	wp = rp = 0;
	queue[wp].x = sx;
	queue[wp].y = sy;
	queue[wp++].dir = 4;
	cnt = 0;
	cnt++;
	while (wp > rp)
	{
		out = queue[rp++];
		if (out.dir == 4)
		{
			for (i = 0; i < 4; i++)
			{
				nx = out.x + dx[i];
				ny = out.y + dy[i];
				if (nx<1 || ny<1 || nx>n || ny>n) continue;
				if (map[ny][nx] == 0)
				{
					queue[wp].x = nx;
					queue[wp].y = ny;
					queue[wp++].dir = i;
					cnt++;
				}
			}
		}
		else
		{
			nx = out.x + dx[out.dir];
			ny = out.y + dy[out.dir];
			if (nx<1 || ny<1 || nx>n || ny>n) continue;
			if (map[ny][nx] == 0)
			{
				queue[wp].x = nx;
				queue[wp].y = ny;
				queue[wp].dir = out.dir;
				cnt++;
			}
		}
	}
	return cnt;
}
int find_max(void)
{
	int i, j;
	int tmp;
	for (i = 1; i <=n;i++)
	{
		for (j = 1; j <= n; j++)
		{
			tmp = DFS_dirgo(j, i);
			if (tmp > max) max = tmp;
		}
	}
	return max;
}
int main(void)
{
	int sol;
	input();
	sol = find_max();
	printf("%d", bspot-sol);
	return 0;
}
#endif

//100 만들기
#if 0
#define MAX 20
int N=9;
int list[MAX];
int arr[10];
void printList(int L)
{
	int i, j;
	int temp;
	for (i = 1; i < L - 1; i++)
	{
		for (j = i + 1; j < L; j++)
		{
			if (list[i]>list[j])
			{
				temp = list[i];
				list[i] = list[j];
				list[j] = temp;
			}
		}
	}
	for(i = 1; i < L; i++)
	{
		if (!list[i]) continue;
		printf("%d\n", list[i]);
	}
}
void DFS_usenum(int L, int S, int U)
{
	if (L > N){
		if (U==7 && S==100) printList(L);
		return;
	}
	list[L] = arr[L];
	DFS_usenum(L + 1, S + list[L], U+1);
	list[L] = 0;
	DFS_usenum(L + 1, S, U);
}
void input(void)
{
	int i;
	for (i = 1; i <= 9; i++)
	{
		scanf("%d", &arr[i]);
	}
}

int main(void)
{
	input();
	DFS_usenum(1, 0, 0);
	return 0;
}
#endif
#if 0
#define MAX 50
int n1, n2, n3;
int list[MAX][MAX][MAX];
int idx[MAX * 2];
int max;
void input(void)
{
	scanf("%d %d %d", &n1, &n2, &n3);
}
int find_max(void)
{
	int i, j, k;
	int cnt;
	for (i = 1; i <= n1; i++)
	{
		for (j = 1; j <= n2; j++)
		{
			for (k = 1; k <= n3; k++)
			{
				idx[i + j + k]++;
			}
		}
	}
	for (i = 3; i <= 80; i++)
	{
		if (!idx[i]) continue;
		if (idx[i] > max)
		{
			max = idx[i];
			cnt = i;
		}
	}
	return cnt;
}
int main(void)
{
	int sol;
	int cnt;
	input();
	sol = find_max();
	printf("%d", sol);
	return 0;
}
#endif
#if 0
#include <stdio.h>
#define MAX 20
typedef struct {
	int y;
	int x;
}location;
int pipe[][4] = { { 0 }, { 0, 1, 0, 1 }, { 1, 0, 1, 0 }, { 0, 1, 1, 0 }, \
{ 0, 0, 1, 1 }, { 1, 0, 0, 1 }, { 1, 1, 0, 0 }, { 1, 1, 1, 0 }, \
{ 0, 1, 1, 1 }, { 1, 0, 1, 1 }, { 1, 1, 0, 1 }, { 1, 1, 1, 1 } };
int dir[] = { 2, 3, 0, 1 };
int dx[] = { 0, 1, 0, -1 };
int dy[] = { -1, 0, 1, 0 };
int wp, rp;
int N;
int sx, sy;
int visit[MAX][MAX];
int map[MAX][MAX];
location queue[MAX*MAX];

void input(void)
{
	int i, j;
	scanf("%d %d %d", &N, &sx, &sy);
	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			scanf("%1d", &map[i][j]);
		}
	}
}
void BFS(int sy, int sx)
{
	int i, j;
	location out;
	int nx, ny;
	wp = rp = 0;
	queue[wp].x = sx;
	queue[wp++].y = sy;
	while (wp > rp)
	{
		out = queue[rp++];
		for (i = 0; i < 4; i++)
		{
			nx = out.x + dx[i];
			ny = out.y + dy[i];
			if (nx<1 || ny<1 || nx>N || ny>N) continue;
			for (j = 0; j < 4; j++)
			{
				if (pipe[a[out.y][out.x]][j] && pipe[a[ny][nx]][dir[j]])
				{
					map[out.y][out.x] = 0;
					queue[wp].x = nx;
					queue[wp++].y = ny;
				}
			}
		}
	}
}
int main(void)
{
	input();

}
#endif
// 더하기
#if 0
#include <stdio.h>
#define MAX 30
int N, K;
int b[MAX];
int list[MAX];
int a[MAX];
int sol;
void printList(int L, int S)
{
	int i;
	printf("%2d (%2d) : ", L, S);
	for (i = 1; i < L; i++)
	{
		printf("%2d ", list[i]);
	}
	printf("\n");
}
void makeB(void)
{
	int i, j;
	for (i = 1; i <= N; i++)
	{
		b[i] = 0;
		for (j = 1; j <= N; j++)
		{
			b[i] += a[j];
		}
	}
}
void DFS(int L, int S)
{
	if (S+b[L]<K || S > K || sol == 1) return;
	if (L > N){
		/*printList(L, S);*/
		if (S == K) sol = 1;
		return;
	}
	list[L] = a[L];
	DFS(L+1, S + a[L]);
	list[L] = 0;
	DFS(L+1, S);
}
void input(void)
{
	int i;
	scanf("%d %d", &N, &K);
	for (i = 1; i <= N; i++)
	{
		scanf("%d", &a[i]);
	}
}

int main(void)
{
	int T, tc;
	scanf("%d", &T);
	for (tc = 1; tc <= T; tc++)
	{
		sol = 0;
		input();
		makeB();
		DFS(1, 0);
		if (sol == 1) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
#endif
// 주사위 던지기 2
#if 0
#include <stdio.h>
#define MAX 20
int N, M;
int list[MAX];
void printList(int L)
{
	int i;
	for (i = 1; i < L; i++)
	{
		printf("%d ", list[i]);
	}
	printf("\n");
}
void DFS(int L, int S)
{
	int i;
	if (L > N){
		if (S == M) printList(L);
		return;
	}
	for (i = 1; i <= 6; i++)
	{
		list[L] = i;
		DFS(L + 1, S+i);
	}
}
int main(void)
{
	scanf("%d %d", &N, &M);
	DFS(1, 0);
	return 0;
}
#endif
// 주사위 던지기 1
#if 0
#include <stdio.h>
#define MAX (20)
int N;
int M;
int list[MAX];
int visit[MAX];
void printList(int L)
{
	int i;
	for (i = 1; i < L; i++)
	{
		printf("%d ", list[i]);
	}
	printf("\n");
}
void DFS_1(int L)
{
	int i;
	if (L > N)
	{
		printList(L);
		return;
	}
	for (i = 1; i <= 6; i++)
	{
		list[L] = i;
		DFS_1(L + 1);
	}
}
void DFS_2(int L, int start)
{
	int i;
	if (L > N){
		printList(L);
		return;
	}
	for (i = start; i <= 6; i++)
	{
		list[L] = i;
		DFS_2(L + 1, i);
	}
}
void DFS_3(int L)
{
	int i;
	if (L > N){
		printList(L);
		return;
	}
	for (i = 1; i <= 6; i++)
	{
		if (visit[i]) continue;
		list[L] = i;
		visit[i] = 1;
		DFS_3(L + 1);
		visit[i] = 0;
	}
}
int main(void)
{
	scanf("%d %d", &N, &M);
	switch(M){
  case 1: DFS_1(1);
	  break;
  case 2: DFS_2(1, 1);
	  break;
  case 3: DFS_3(1);
	}
	return 0;
}
#endif 