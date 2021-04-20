#pragma warning (disable:4996)

#if 00

#include <stdio.h>
#include <queue>
#include <functional>
#include <vector>

using namespace std;

int main(void){

	vector<int> v;

	priority_queue<int, vector<int>> q ;
	q.push(4);
	q.push(9);
	q.push(1);
	q.push(7);
	q.push(10);
	q.push(2);
	q.push(3);
	while (!q.empty()) {
		printf("%d\n", q.top());
		q.pop();
	}

	priority_queue<int, vector<int>, greater<int>> p;

	p.push(4);
	p.push(9);
	p.push(1);
	p.push(7);
	p.push(10);
	p.push(2);
	p.push(3);
	while (!p.empty()) {
		printf("%d\n", p.top());
		p.pop();
	}

	vector<int> vc[100];

	for (int i = 0; i < 10; i++){
		for (int j = 0; j < i; j++){
			vc[i].push_back(j);
		}
	}

	printf("\n");

	for (int i = 0; i < 10; i++){
		for (int j = 0; j < i; j++){
			printf("%d ", vc[i][j]);
		}
		printf("\n");
	}

	printf("\n");

	for (int i = 0; i < 10; i++){
		while (!vc[i].empty()){
			printf("%d ", vc[i].back());
			vc[i].pop_back();
		}
		printf("\n");
	}

	return 0;

}




#endif