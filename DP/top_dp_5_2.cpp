#include<iostream>
using namespace std;

int n, m, arr[1001][1001], DP[1001][1001];

int dr[3] = { 1,1,1 };
int dc[3] = { -1,0,1 };

int dp(int row,int col) {

	if (col < 0 || col >= m)return -21e8; // 이건 0하면 안됨 0보다 작은실제값(음수)있으면 그거 적용안됨
	//if (arr[row][col] == 0)return -21e8; 이거 반환하면 이 길이 생기는 거라서 하면 안될줄 알았는데 상관 없는듯
	if (row >= n)return 0; // row가 끝낫을때는 0반환해야됨 -21반환하면 다 -21e라서 이값 적용됨
	if (DP[row][col] != -21e8)return DP[row][col];

	int Max = -21e8;
	for (int i = 0; i < 3; i++) {
		int nextrow = row + dr[i];
		int nextcol = col + dc[i];
		if (arr[row][col] == 0)continue;
		int ans = dp(nextrow, nextcol);
		if (ans > Max)Max = ans;
	}

	DP[row][col] = Max + arr[row][col];
	return DP[row][col];
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> arr[i][j];
			DP[i][j] = -21e8;
		}
	}
	int ans = dp(0, 0);

	cout << ans;
	return 0;
}
