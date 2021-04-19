#pragma warning (disable:4996)

#if 00

#include<stdio.h>

int n, m;

void input(void);
void Union(int a, int b);
int Find(int x);
void solve(void);

typedef struct calSet{
	int calType, num1, num2;
};

calSet calSetVal[100000];
int parent[1000001];
int rank[1000001];

int main(void){

	input();

	solve();

}

int Find(int x){

	if (x == parent[x]) return x;
	else{
		parent[x] = Find(parent[x]);
		return parent[x];
	}
}

void Union(int a, int b){

	int resultA, resultB;

	resultA = Find(a);
	resultB = Find(b);

	if (resultA == resultB) return;
	else{
		if (rank[a] > rank[b]){
			parent[resultB] = resultA;
			rank[a]+=rank[b];
		}
		else{
			parent[resultA] = resultB;
			rank[b]+=rank[a];
		}
	}

}

void solve(void){

	for (int i = 0; i < m; i++){

		if (calSetVal[i].calType == 0){
			Union(calSetVal[i].num1, calSetVal[i].num2);
		}
		else if (calSetVal[i].calType == 1){
			if (Find(calSetVal[i].num1) == Find(calSetVal[i].num2)){
				printf("YES\n");
			}
			else {
				printf("NO\n");
			}
		}
		else{
		}

	}

}



void input(void){

	n = m = 0;

	scanf("%d %d", &n, &m);

	for (int i = 0; i < m; i++){

		scanf("%d %d %d", &calSetVal[i].calType, &calSetVal[i].num1, &calSetVal[i].num2);

	}

	for (int i = 1; i <= n; i++){

		parent[i] = i;
		rank[i] = 1;

	}

}




#endif