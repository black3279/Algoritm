#pragma warning (disable:4996)

#if 01

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>

typedef long long ll;

int N, Q;
int A[100001];
ll S[400000];
int nn;

using namespace std;

void input(){
	cin >> N >> Q;

	for (nn = 1; nn < N; nn *= 2);

	for (int i = 1; i <= N; i++){
		A[i] = i;
		S[nn + i - 1] = A[i];
	}

	for (int i = nn - 1; i >= 1; i--) S[i] = S[2 * i] * S[2 * i + 1];
}

void edit(int x, int y){

	int idx = x + nn - 1;
	S[idx] = y;
	idx /= 2;
	while (idx > 0){
		S[idx] = S[idx * 2] + S[idx * 2 + 1];
		idx /= 2;
	}
}

ll sum(int x, int y){
	ll ssum = 0;
	int l = nn + x - 1;
	int r = nn + y - 1;

	while (l <= r){
		if (l % 2 == 1){
			ssum += S[l++];
		}
		if (r % 2 == 0){
			ssum += S[r--];
		}
		r /= 2;
		l /= 2;
	}

	return ssum;
}

int main(void){

	int T, tc;

	cin >> T;

	for (tc = 1; tc <= T; tc++){
		ll sol = 0;
		input();
		for (int i = 0, op, a, b; i < Q; i++){
			scanf("%d %d %d", &op, &a, &b);
			if (op == 0){
				edit(a, b);
			}
			else {
				sol += sum(a, b);
				sol %= 1000000007;
			}

			printf("#%d %lld\n", tc, sol);
		}
	}

	return 0;

}




#endif