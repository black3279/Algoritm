#if 01

#include <stdio.h>

int main(void)

{
	int mo, ja;
	int i;
	int n;

	int clear[30000][2] = { 0, };


	scanf("%d", &n);

	printf("0/1\n");

	for (mo = 2; mo <= n; mo++)
	{
		for (ja = 1; ja <= mo - 1; ja++)
		{
			if ((clear[(30000 * ja) / mo][0] == 0))
			{
				clear[(30000 * ja) / mo][0] = ja;
				clear[(30000 * ja) / mo][1] = mo;
			}
		}
	}

	for (i = 0; i<30000; i++)
	{
		if (clear[i][0] != 0)
		{
			printf("%d/%d\n", clear[i][0], clear[i][1]);
		}
	}


	printf("1/1");

	// 여기서부터 작성

	return 0;

}

#endif
