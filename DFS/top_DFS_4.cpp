#include<iostream>
using namespace std;

int arr[10][10];
int visited[10];
int sum;
int Min = 1000;
int Max = 0;
void dfs(int n, int to, int end) {
	if (to == end) {
		if (sum > Max)Max = sum;
		if (sum < Min)Min = sum;
		return;
	}
	for (int i = 0; i < n; i++) {
		if (arr[to][i] == 0)continue;
		if (visited[i] == 1)continue;
		visited[i] = 1;
		sum += arr[to][i];
		dfs(n, i, end);
		sum -= arr[to][i];
		visited[i] = 0;
	}
}
int main() {
	int n; cin >> n;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> arr[i][j];
	int st, end; cin >> st >> end;
	// i = from, j = to , arr[i][j] = cost
	visited[st] = 1;
	dfs(n, st, end);
	cout << Min << "\n" << Max;
	return 0;
}
