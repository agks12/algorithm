#include<iostream>
#include<string>
using namespace std;

string a;
char a_test[22];
string arr[2];
char now;
int st,cnt;
void dfs(int nowbrigh,int level,int jst) {
	int flag = 0;
	if (level == a.size()) {
		for (int i = 0; i < a.size(); i++) {
			if (a_test[i] == a[i])continue;
			flag = 1;
		}
		if (flag == 0)cnt++;
		return;
	}
	if (0 == nowbrigh) {
	st = 0;
	nowbrigh = 1;
	}
	else {
	st = 1;
	nowbrigh = 0;
	}
	for (int i = 0; i < 2; i++) {
		if (i == nowbrigh)continue;
		for (int j = jst+1; j < arr[0].size(); j++) {
			a_test[level] = arr[i][j];
			if (a_test[level] != a[level])continue;
			dfs(nowbrigh, level + 1,j);
		}
	}
}
int main() {
	cin >> a >> arr[0] >> arr[1];
	dfs(0,0,-1);
	dfs(1,0,-1);
	cout << cnt;
	return 0;
}
