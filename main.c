#if 01

#include <stdio.h> 



int n;

int x[100 + 10], y[100 + 10];

int area;

int arr[101][101] = { 0, };


void paper(int C, int R)
{
	int i, j;

	for (i = R; i<R + 10; i++)
	{
		for (j = C; j<C + 10; j++)
		{
			arr[i][j]++;
		}
	}

}


int main(void)

{

	int i, j;

	// 입력받는 부분

	scanf("%d", &n);

	for (i = 0; i<n; i++)

	{

		scanf("%d %d", &x[i], &y[i]);

	}



	// 여기서부터 작성
	for (i = 0; i<n; i++)
	{
		paper(x[i], y[i]);
	}

	for (i = 1; i <= 100; i++)
	{
		for (j = 1; j <= 100; j++)
		{
			if (arr[i][j] >= 1) area++;
		}
	}

	// 출력하는 부분

	printf("%d", area);



	return 0;

}


#endif