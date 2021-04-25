#pragma warning (disable:4996)

#if 01

#include <stdio.h>
#include <queue>
#include <functional>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

using namespace std;

struct person{
	char name[21];
	int length;
	long long score;
};


vector<string> solution(vector<vector<string>> arr) {


	vector<person> distinct[26];

	int idx = 0;
	char alph[26];


	struct cmp{
		bool operator()(person a, person b){
			return a.score > b.score;
		}
	};

	priority_queue<person, vector<person>, cmp> pq;

	for (int i = 0; i<26; i++){
		alph[i] = 'A' + i;
	}



	for (int idx = 0; idx < arr.size(); idx++){

		vector<string> data = arr[idx];

		string borrow = data[0];
		string lent = data[1];
		string point = data[2];

		char st_idx = borrow[0];
		char lent_idx = lent[0];
		for (int i = 0; i<26; i++){

			// borrow
			if (alph[i] == st_idx){
				if (distinct[i].empty()){
					person borrower;

					for (int j = 0; j<borrow.size(); j++){
						borrower.name[j] = borrow[j];
					}
					borrower.length = borrow.size();
					borrower.score = -(stoll(point));
					distinct[i].push_back(borrower);
				}
				else{
					for (int j = 0; j<distinct[i].size(); j++){ // 알파벳 명대로 vector 구조 탐색
						bool totalCmp = false;
						if (borrow.size() == distinct[i][j].length){ // 이름 길이가 일치할 경우
							bool cmp = false;
							for (int k = 0; k<borrow.size(); k++){
								if (borrow[k] != distinct[i][j].name[k]){
									break;
								}
								else if (borrow[k] == distinct[i][j].name[k] && k == borrow.size() - 1){
									cmp = true; // 비교 일치 확인
									break;
								}
							}

							if (cmp == true){
								totalCmp = true;
								distinct[i][j].score -= stoll(point);
								break;
							}
						}

						if (totalCmp == false && j == distinct[i].size() - 1){
							person borrower;
							for (int k = 0; k<borrow.size(); k++){
								borrower.name[k] = borrow[k];
							}
							borrower.length = borrow.size();
							borrower.score = -(stoll(point));
							distinct[i].push_back(borrower);
						}
					}
				}
			}

			// borrow

			// lent
			if (alph[i] == lent_idx){
				if (distinct[i].empty()){
					person lenter;
					for (int j = 0; j<lent.size(); j++){
						lenter.name[j] = lent[j];
					}
					lenter.length = lent.size();
					lenter.score = (stoll(point));
					distinct[i].push_back(lenter);
				}
				else{
					for (int j = 0; j<distinct[i].size(); j++){ // 알파벳 명대로 vector 구조 탐색
						bool totalCmp = false;
						if (lent.size() == distinct[i][j].length){ // 이름 길이가 일치할 경우
							bool cmp = false;
							for (int k = 0; k<lent.size(); k++){
								if (lent[k] != distinct[i][j].name[k]){
									break;
								}
								else if (lent[k] == distinct[i][j].name[k] && k == lent.size() - 1){
									cmp = true; // 비교 일치 확인
									break;
								}
							}

							if (cmp == true){
								totalCmp = true;
								distinct[i][j].score += stoll(point);
								break;
							}
						}

						if (totalCmp == false && j == distinct[i].size() - 1){
							person lenter;
							for (int k = 0; k<lent.size(); k++){
								lenter.name[j] = lent[j];
							}
							lenter.length = lent.size();
							lenter.score = (stoll(point));
							distinct[i].push_back(lenter);
						}
					}
				}
			}

		}

	}

	for (int i = 0; i<26; i++){
		for (int j = 0; j<distinct[i].size(); j++){
			if (distinct[i][j].score <0){
				pq.push(distinct[i][j]);
			}
		}
	}
	vector<string> rtn;
	long long before = 0;
	if (pq.empty()){
		rtn.push_back("None");
		return rtn;
	}
	else{
		while (!pq.empty()){
			if (before == 0){
				before = pq.top().score;
				string name = pq.top().name;
				pq.pop();
				rtn.push_back(name);
			}
			else{
				if (before != pq.top().score) return rtn;

				string name = pq.top().name;
				pq.pop();
				rtn.push_back(name);
			}
		}

		return rtn;
	}
}

int main()
{
	
	return 0;
}


#endif