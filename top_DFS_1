#include<iostream>
using namespace std;

int arr[101][101];
int sun;
int visited[101];

void dfs(int n,int start) {
	for (int i = 0; i <= n; i++) {
		if (arr[start][i] == 0)continue;
		if (visited[i] == 1)continue;
		visited[i] = 1;
		sun++;
		dfs(n, i);
	}
}

int main() {
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int index, to;
		cin >> index >> to;
		arr[index][to] = 1;
		arr[to][index] = 1;
	}
	visited[1] = 1;
	dfs(n, 1);
	cout << sun;

	return 0;
}
