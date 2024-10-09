#include<iostream>
using namespace std;

int n;
int arr[12];
int arrPlus[26];
int arrMinus[26];


int cnt = 0;

void dfs1(int level) {

	if (level == n) {
		cnt++;
		return;
	}

	for (int i = 0; i < n; i++) {
		if (arr[i] == 1)continue;
		if (arrPlus[level + i] == 1)continue; // 대각선1
		if (arrMinus[13+level - i] == 1)continue;// 대각선2
		arr[i] = 1;
		arrPlus[level + i] = 1;
		arrMinus[13+level - i] = 1;


		dfs1(level + 1);
		arr[i] = 0;
		arrPlus[level + i] = 0;
		arrMinus[13+level - i] = 0;
	}
}

int main() {
	cin >> n;
	dfs1(0);
	cout << cnt;
	return 0;
}
