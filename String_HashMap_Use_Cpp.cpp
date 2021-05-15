#pragma warning (disable:4996)

#if 01

#include <string.h>
#include <iostream>
#include <string>
#include <map>


using namespace std;

string country[4];
map< string, int > ctryMap;


void input(){

	string temp;
	getline(cin, temp);
	int idx = 0;
	bool seperate=false;
	while(idx<4){

		country[idx] = temp.substr(0, temp.find(' '));
		ctryMap.insert(make_pair(country[idx], idx));
		if(idx<3) temp = temp.substr(temp.find(' '), temp.size());
		else break;
		idx++;

		for (int i = 0; i < temp.size(); i++){
			if (temp.at(i) != ' '){
				temp = temp.substr(i, temp.size());
				break;
			}
		}
	}



}

int main(){

	input();

}

#endif

