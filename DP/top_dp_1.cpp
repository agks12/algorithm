#include<iostream>
using namespace std;

int arr[40];
int DP[40];
int TopDown(int n) {
	if (n == 0)return 0;
	if (n == 1)return 1;
	if (arr[n] > 0)return arr[n];
	arr[n] = TopDown(n - 1) + TopDown(n - 2);
	return arr[n];
}
void BottonTop(int n) {
	int arr[40] = { 0 };
	arr[0] = 0; arr[1] = 1;
	for (int i = 2; i < n; i++) {
		arr[i] = arr[i - 1] + arr[i - 2];
	}
	cout << arr[n-1];
}
int dfs(int n, int level) {
	int sum = 0;
	//입력n(40) 까지 되거 멈추면 그떄값 나와
	//level 0 부터 시작
	if (n == level) return DP[n - 1];
	//1번 돌떄마다 (지금 값 + 전값)
	if (n > 0) {
		sum += DP[n - 1];
		sum += DP[n];
		DP[n + 1] = sum;
		dfs(n + 1, level);
	}
	else dfs(n + 1, level);
}
int main() {
	int n; cin >> n;
	int ans = TopDown(n-1);
	cout << ans;
	//BottonTop(n);
	return 0;
}
