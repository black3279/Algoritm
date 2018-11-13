#if 01
#include <stdio.h>
#include <string.h>

int FU[500000];
int FD[500000];
int sum[500000];
int N, H;
int half;
int min, sol;

void find_sol(void)
{
	int i;
	int num = H + 1;

	for (i = 2; i < H; i++)
	{
		sum[i] = sum[i - 1] - FD[i - 1] + FU[num - i];
		if (sum[i] == min)
		{
			sol++;
		}
		if (sum[i] < min)
		{
			min = sum[i];
			sol = 1;
		}
	}
}

void input(void)
{
	int i;
	int a, b;
	scanf("%d %d", &N, &H);
	half = N / 2;

	for (i = 1; i <= half; i++)
	{
		scanf("%d", &a);
		FD[a]++;

		scanf("%d", &b);
		FU[b]++;
	}

}

int main(void)
{
	input();

	min = half;
	sol = 2;
	sum[1] = sum[H] = half;

	find_sol();

	printf("%d %d", min, sol);


	return 0;
}

#endif